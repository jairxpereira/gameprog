// prj_EntradaPontoNet - Arquivo: Tela.cs
// Esse projeto mostra como usar o teclado e mouse via 
// Framework .net - Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Direct3D = Microsoft.DirectX.Direct3D;

namespace prj_EntradaPontoNet
{

  // [---
  // Estrutura para processar teclado\mouse
  struct EntradaInfo
  {
    public bool seta_esquerda;
    public bool seta_direita;
    public bool seta_cima;
    public bool seta_baixo;
    public bool mouse_btn01;
    public bool mouse_btn02;
    public bool escape;
    public bool shift;
    public int xmouse;
    public int ymouse;

    public void limparEntrada()
    {
      seta_esquerda = false;
      seta_direita = false;
      seta_cima = false;
      seta_baixo = false;
      mouse_btn01 = false;
      mouse_btn02 = false;
      escape = false;
      shift = false;
      xmouse = 0;
      ymouse = 0;
    } // limparEntrada().fim
  }; // struct.fim
  // ---]


  // [---
  public partial class Tela : Form
  {
    // <b>
    // Variável para gerenciamento de mouse e teclado
    private EntradaInfo g_mouse;
    private EntradaInfo g_teclado;
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
      // Inicialização das estruturas de controle de entrada
      g_mouse = new EntradaInfo();
      g_teclado = new EntradaInfo();
      g_mouse.limparEntrada();
      g_teclado.limparEntrada();
      // </b>

    } // initGfx()
    // ---]

    // [---
    void verificarEntrada()
    {

      // Variáveis para guardar o estado das teclas
      int seta_esquerda = 0;
      int seta_direita = 0;
      int seta_cima = 0;
      int seta_abaixo = 0;

      // <b>
      // Verifica teclado e mouse atualizando teclas de estado e
      // coordenadas de tela
      if (g_teclado.seta_baixo) seta_abaixo = 1;
      if (g_teclado.seta_cima) seta_cima = 1;
      if (g_teclado.seta_esquerda) seta_esquerda = 1;
      if (g_teclado.seta_direita) seta_direita = 1;
      if (g_teclado.shift) xcol = 320;
      if (g_teclado.shift) ylin = 240;
      if (g_teclado.escape) terminar = true;

      // Botão esquerdo coloca 'jogador' na coordenada do mouse  
      if (g_mouse.mouse_btn01)
      {
        xcol = g_mouse.xmouse;
        ylin = g_mouse.ymouse;
      } // endif

      // Botão direito coloca 'jogador' na coordenada (320,240)
      if (g_mouse.mouse_btn02)
      {
        xcol = 320;
        ylin = 240;
      } // endif

      // Botão esquerdo + direito = fim da aplicação  
      if (g_mouse.mouse_btn01 && g_mouse.mouse_btn02) terminar = true;
      // </b>

      // Atualiza posicionamento do 'jogador'
      if (seta_abaixo == 1) ylin += 5;
      if (seta_cima == 1) ylin -= 5;
      if (seta_esquerda == 1) xcol -= 5;
      if (seta_direita == 1) xcol += 5;

      // Muda 'jogador' conforme seta pressionada
      if (seta_esquerda == 1) jogador = "<(-:";
      if (seta_direita == 1) jogador = ":-)>";

      // Processa a tecla Escape
      if (terminar)
      {
        device.Dispose();
        this.Close();
        Application.Exit();
      } // endif

    } // verificarEntrada()
    // ---]

  
    public void Renderizar()
    {    
      if (terminar == true) return;
     
      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target, Color.White, 1.0f, 0);

      device.BeginScene();
      // (...) Todo o código de desenhar vai aqui   

      // Mostra 'jogador' e sua posição na tela
      String info = String.Format("({0},{1})", xcol, ylin);
      MostrarTitulo(10, 10, info, Color.Black);
      MostrarTitulo(xcol, ylin, jogador, Color.Red);
     
      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar()    


    // [---
    protected override void OnPaint(PaintEventArgs e)
    {
      // Trate outros processos padrões
      base.OnPaint(e);

      // Renderize a cena     
      verificarEntrada();
      Renderizar();

      // Invalide para chamar novamente onPaint()
      this.Invalidate();
    } // onPaint().fim 
    // ---]


    // Mostra texto com tamanho de fonte grande para títulos
    private void MostrarTitulo(int xpos, int ylin, string txt, Color font_cor)
    {
      // Configura posição
      Rectangle position = new Rectangle(xpos, ylin, 0, 0);

      // Mostra texto
      dxfTitulo.DrawText(null, txt, position, DrawTextFormat.NoClip, font_cor);
    } // MostrarTitulo().fim

    // [---
    private void Tela_KeyDown(object sender, KeyEventArgs e)
    {
      // Atualiza estrutura de teclado conforme tecla pressionada
      if (e.KeyCode == Keys.Escape) g_teclado.escape = true;
      if (e.KeyCode == Keys.Shift) g_teclado.shift = true;
      if (e.KeyCode == Keys.ShiftKey) g_teclado.shift = true;

      if (e.KeyCode == Keys.Up) g_teclado.seta_cima = true;
      if (e.KeyCode == Keys.Down) g_teclado.seta_baixo = true;
      if (e.KeyCode == Keys.Left) g_teclado.seta_esquerda = true;
      if (e.KeyCode == Keys.Right) g_teclado.seta_direita = true;
    } // Tela_KeyDown().fim
    // ---]

    // [---
    private void Tela_KeyUp(object sender, KeyEventArgs e)
    {
      g_teclado.limparEntrada();
    } // Tela_KeyUp().fim
    // ---]

    // [---
    private void Tela_MouseDown(object sender, MouseEventArgs e)
    {
      // Atualiza botões da estrutura
      if (e.Button == MouseButtons.Left) g_mouse.mouse_btn01 = true;
      if (e.Button == MouseButtons.Right) g_mouse.mouse_btn02 = true;

      // Atualiza (xmouse, ymouse)
      g_mouse.xmouse = e.X;
      g_mouse.ymouse = e.Y;

    } // Tela_MouseDown().fim
    // ---]

    // [---
    private void Tela_MouseUp(object sender, MouseEventArgs e)
    {
      g_mouse.limparEntrada();
    } // Tela_MouseUp().fim
    // ---]

  } // fim da classe
} // fim do namespace

