// prj_Teclado01 - Arquivo: Tela.cs
// Esse projeto mostra como usar o teclado via DirectInput
// Exemplo 01 - Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Direct3D = Microsoft.DirectX.Direct3D;
using DirectInput = Microsoft.DirectX.DirectInput;

namespace prj_Teclado01
{
  
  // [---
  public partial class Tela : Form
  {

    // <b>
    // Variável para criação do dispositivo de gerenciamento teclado
    private DirectInput.Device teclado = null;    
    // </b>
    
    // Para criação do dispositivo gráfico
    private Device device = null;    
    
    // A tecla Escape terminará a aplicação
    private bool terminar = false;

    // Dados para o 'jogador'
    private int xcol;
    private int ylin;
    string jogador = null;

    // Fontes para mostrar o 'jogador' na tela
    // Objeto Font do DirectX para mostrar texto (titulos)
    private Direct3D.Font dxfTitulo = null;
    // Objeto Font tradicional do namespace System.Drawing
    private System.Drawing.Font g_font = null;

    // (...)
    // ---]
    public Tela()
    {

      // Inicialização dos componentes.
      InitializeComponent();
      this.Size = new Size(640, 480);

      // Toda renderização deverá ocorrer dentro do evento onPaint()
      // Isso evita interferência estrangeira de processamento default
      // do sistema Windows
      this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.Opaque, true);

    } // construtor

    // [---
    public void initGfx()
    {

      // Configuração dos parâmetros de apresentação
      PresentParameters pps = new PresentParameters();
      pps.Windowed = true;
      pps.SwapEffect = SwapEffect.Discard;

      // Adaptador default, processamento no hardware, processamento de vértice 
      // no software, janela (this), parâmetros de apresentação (pps)
      int adaptador = 0;
      device = new Device(adaptador, DeviceType.Hardware, this,
        CreateFlags.SoftwareVertexProcessing, pps);

      // Configuração das fontes para mostrar títulos
      g_font = new System.Drawing.Font("Arial", 36.0f, FontStyle.Bold);
      dxfTitulo = new Direct3D.Font(device, g_font);

      // Inicializa jogador
      xcol = 320;
      ylin = 240;
      jogador = ":-)>";
      
      // <b>
      inicializarTeclado();
      // </b>

    } // initGfx()
    // ---]


    // [---
    public void Renderizar()
    {

      // <b>
      verificarTeclado();
      if (terminar == true) return;
      // </b>
      
      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target, Color.White, 1.0f, 0);

      device.BeginScene();
      // (...) Todo o código de desenhar vai aqui   

      // <b>
      // Mostra 'jogador' e sua posição na tela
      String info = String.Format("({0},{1})", xcol, ylin);
      MostrarTitulo(10, 10, info, Color.Black);
      MostrarTitulo(xcol, ylin, jogador, Color.Red);
      // </b>

      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar()
    // ---]


    protected override void OnPaint(PaintEventArgs e)
    {
      // Trate outros processos padrões
      base.OnPaint(e);

      // Renderize a cena     
      Renderizar();

      // Invalide para chamar novamente onPaint()
      this.Invalidate();
    } // onPaint().fim 

    
    // [---
    private void inicializarTeclado()
    {
      // Cria o dispositivo de gerenciamento do teclado
      teclado = new DirectInput.Device(DirectInput.SystemGuid.Keyboard);
      
      // Configura nível de cooperação
      teclado.SetCooperativeLevel(this,
        DirectInput.CooperativeLevelFlags.Background |
           DirectInput.CooperativeLevelFlags.NonExclusive);
      
      // Adquire o teclado
      teclado.Acquire();
     
    } // inicializarTeclado().fim
    // ---]

    
    // [---
    void verificarTeclado()
    {      
     
      string sInfo = "prj_Teclado01 - Teclas pressionadas: ";
      
      // Variáveis para guardar o estado das teclas
      int seta_esquerda = 0;
      int seta_direita = 0;
      int seta_cima = 0;
      int seta_abaixo = 0;

      // <b>
      DirectInput.Key[] teclasPressionadas = teclado.GetPressedKeys();
      
      // Verifica teclado e atualiza teclas de estado
      foreach (DirectInput.Key tecla in teclasPressionadas )
      {
        sInfo += tecla.ToString() + " ";

        if (tecla == DirectInput.Key.DownArrow) seta_abaixo = 1;
        if (tecla == DirectInput.Key.UpArrow) seta_cima = 1;
        if (tecla == DirectInput.Key.LeftArrow) seta_esquerda = 1;
        if (tecla == DirectInput.Key.RightArrow) seta_direita = 1;
        if (tecla == DirectInput.Key.RightShift) xcol = 320;
        if (tecla == DirectInput.Key.RightShift) ylin = 240;
        if (tecla == DirectInput.Key.Escape) terminar = true;
      } // endfor each
      // </b>

      // Atualiza posicionamento do 'jogador'
      if (seta_abaixo == 1) ylin += 5;
      if (seta_cima == 1) ylin -= 5;
      if (seta_esquerda == 1) xcol -= 5;
      if (seta_direita == 1) xcol += 5;

      // Muda 'jogador' conforme seta pressionada
      if (seta_esquerda == 1) jogador = "<(-:";
      if (seta_direita == 1) jogador = ":-)>";

      this.Text = sInfo;

      // Processa a tecla Escape
      if (terminar)
      {
        device.Dispose();
        teclado.Dispose();
        this.Close();
        Application.Exit();             
      } // endif

    } // AtualizarTeclado()
    // ---]
    
   
    // Mostra texto com tamanho de fonte grande para títulos
    private void MostrarTitulo(int xpos, int ylin, string txt, Color font_cor)
    {
      // Configura posição
      Rectangle position = new Rectangle(xpos, ylin, 0, 0);

      // Mostra texto
      dxfTitulo.DrawText(null, txt, position, DrawTextFormat.NoClip, font_cor);
    } // MostrarTitulo().fim

  } // fim da classe
} // fim do namespace

