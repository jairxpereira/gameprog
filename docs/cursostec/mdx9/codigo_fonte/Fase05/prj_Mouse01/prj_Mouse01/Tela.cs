// prj_Mouse01 - Arquivo: Tela.cs
// Esse projeto mostra como usar o mouse via DirectInput
// Exemplo 01 - Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Direct3D = Microsoft.DirectX.Direct3D;
using DirectInput = Microsoft.DirectX.DirectInput;

namespace prj_Mouse01
{

  // [---
  public partial class Tela : Form
  {

    // <b>
    // Variável para criação do dispositivo de gerenciamento do mouse
    private DirectInput.Device mouse = null;
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
    private Direct3D.Font dxfMensagem = null;
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

      // Configuração das fontes para mostrar Mensagens e títulos
      g_font = new System.Drawing.Font("Arial", 36.0f, FontStyle.Bold);
      dxfTitulo = new Direct3D.Font(device, g_font);
      g_font = new System.Drawing.Font("Arial", 12.0f, FontStyle.Bold);
      dxfMensagem = new Direct3D.Font(device, g_font);

      // Inicializa jogador
      xcol = 320;
      ylin = 240;
      jogador = ":-)>";

      // <b>
      inicializarMouse();
      // </b>

    } // initGfx()
    // ---]


    // [---
    public void Renderizar()
    {

      // <b>
      verificarMouse();
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
      MostrarMouseInfo();
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
    private void inicializarMouse()
    {
      // Cria o dispositivo de gerenciamento do mouse
      mouse = new DirectInput.Device(DirectInput.SystemGuid.Mouse);

      // Configura nível de cooperação
      mouse.SetCooperativeLevel(this,
        DirectInput.CooperativeLevelFlags.Background |
           DirectInput.CooperativeLevelFlags.NonExclusive);

      // Configurado como false, os eixos terão valores relativos ao último frame
      mouse.Properties.AxisModeAbsolute = false;

      // Adquire o mouse
      mouse.Acquire();

    } // inicializarMouse().fim
    // ---]


    // [---
    void verificarMouse()
    {

      if (this.Focused == false) return;

      // Variáveis para guardar o estado das teclas
      int seta_esquerda = 0;
      int seta_direita = 0;
      int seta_cima = 0;
      int seta_abaixo = 0;

      // <b>
      DirectInput.MouseState state;
      state = mouse.CurrentMouseState;

      byte[] btn = state.GetMouseButtons();

      if (btn[0] > 0)
      {
        if (state.X < 0) seta_esquerda = 1;
        if (state.X > 0) seta_direita = 1;
        if (state.Y < 0) seta_cima = 1;
        if (state.Y > 0) seta_abaixo = 1;
      } // endif

      if (state.Z > 0) seta_cima = 1;
      if (state.Z < 0) seta_abaixo = 1;

      if (btn[1] > 0)
      {
        xcol = 320;
        ylin = 240;
      } // endif

      // Pressione os dois botões do mouse para sair
      if ((btn[1] > 0) && (btn[0] > 1)) terminar = true;
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
        mouse.Dispose();
        this.Close();
        Application.Exit();
      } // endif

    } // verificarMouse()
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
    private void MostrarMouseInfo()
    {

      // Variáveis string para coletar informações do mouse
      string btn_info = null;
      string eixo_info = null;

      // Verifica o estado do mouse
      DirectInput.MouseState estadoMouse = mouse.CurrentMouseState;

      // Obtém e mostra informação sobre os eixos do mouse
      eixo_info = string.Format("X:{0} Y:{1} Z:{2}\r\n",
        estadoMouse.X, estadoMouse.Y, estadoMouse.Z);

      dxfMensagem.DrawText(null, eixo_info, new Rectangle(20, 70, 0, 0),
        DrawTextFormat.NoClip, Color.Blue);

      // Obtém e mostra estado dos botões
      byte[] buttons = estadoMouse.GetMouseButtons();

      btn_info += string.Format(" Btn[0]:{0}  ", buttons[0].ToString());
      btn_info += string.Format(" Btn[1]:{0}  ", buttons[1].ToString());
      btn_info += string.Format(" Btn[2]:{0}  ", buttons[2].ToString());

      dxfMensagem.DrawText(null, btn_info, new Rectangle(120, 70, 0, 0),
        DrawTextFormat.NoClip, Color.Blue);

    } // MostrarMouseInfo().fim   
    // ---]

  } // fim da classe
} // fim do namespace

