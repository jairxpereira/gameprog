// prj_Joystick - Arquivo: Tela.cs
// Esse projeto mostra como usar o joystick via DirectInput
// Exemplo 01 - Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Direct3D = Microsoft.DirectX.Direct3D;
using DirectInput = Microsoft.DirectX.DirectInput;

namespace prj_Joystick
{

  // [---
  public partial class Tela : Form
  {

    // <b>
    // Variável para criação do dispositivo de gerenciamento do joystick
    private DirectInput.Device joystick = null;
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
      inicializarJoystick();
      // </b>

    } // initGfx()
    // ---]


    // [---
    public void Renderizar()
    {

      // <b>
      if (joystick != null)
      {
        verificarJoystick();
        if (terminar == true) return;       
      } // endif
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
      mostrarJoystickInfo();
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
    void verificarJoystick()
    {

      if (joystick == null) return;
         
      // Variáveis para guardar o estado das teclas
      int seta_esquerda = 0;
      int seta_direita = 0;
      int seta_cima = 0;
      int seta_abaixo = 0;

      // <b>
      DirectInput.JoystickState state = joystick.CurrentJoystickState;
      byte[] btn = state.GetButtons();

      if (state.X < -40) seta_esquerda = 1;
      if (state.X > 1) seta_direita = 1;
      if (state.Y < -40) seta_cima = 1;
      if (state.Y > 0) seta_abaixo = 1;
      if (state.Z < -40) seta_cima = 1;
      if (state.Z > 1) seta_abaixo = 1;        
      // </b>

      // Atualiza posicionamento do 'jogador'
      if (seta_abaixo == 1) ylin += 5;
      if (seta_cima == 1) ylin -= 5;
      if (seta_esquerda == 1) xcol -= 5;
      if (seta_direita == 1) xcol += 5;

      // Muda 'jogador' conforme seta pressionada
      if (seta_esquerda == 1) jogador = "<(-:";
      if (seta_direita == 1) jogador = ":-)>";
      
      // Aplique um reset se botão 1 for pressionando
      if (btn[1] > 0)
      {
        xcol = 320;
        ylin = 240;
      } // endif

      // Pressione os dois botões [0] e [1] do joystick para sair
      if ((btn[1] > 0) && (btn[0] > 1)) terminar = true; 

      // Processa a tecla Escape
      if (terminar)
      {
        device.Dispose();
        joystick.Dispose();
        this.Close();
        Application.Exit();
      } // endif

    } // Atualizarjoystick()
    // ---]


    // Mostra texto com tamanho de fonte grande para títulos
    private void MostrarTitulo(int xpos, int ylin, string txt, Color font_cor)
    {
      // Configura posição
      Rectangle position = new Rectangle(xpos, ylin, 0, 0);

      // Mostra texto
      dxfTitulo.DrawText(null, txt, position, DrawTextFormat.NoClip, font_cor);
    } // MostrarTitulo().fim


    private void inicializarJoystick()
    {

      // Verifica os controles de videogames conectados
      DirectInput.DeviceList Dispositivos =
        DirectInput.Manager.GetDevices(DirectInput.DeviceClass.GameControl,
           DirectInput.EnumDevicesFlags.AttachedOnly);

      // Repassa a lista de controles e pega o primeiro item
      foreach (DirectInput.DeviceInstance dispositivo in Dispositivos)
      {
        joystick = new DirectInput.Device(dispositivo.InstanceGuid);
        
        // Quebre o foreach depois de pegar o primeiro item conectado 
        break;
      }

      // Se não tiver Joystick vá embora da função...
      if (joystick == null) return;

      // Os dados do dispositivo serão tratados como dados de Joystick
      joystick.SetDataFormat(DirectInput.DeviceDataFormat.Joystick);

      // Configura nível de cooperação
      joystick.SetCooperativeLevel(this,
        DirectInput.CooperativeLevelFlags.Background |
         DirectInput.CooperativeLevelFlags.NonExclusive);

      // Configura eixo
       joystick.Properties.AxisModeAbsolute = true;
      
      // Configura faixa de valor retornado pelos eixos
      DirectInput.InputRange eixo_faixaValor;
      eixo_faixaValor = new DirectInput.InputRange(-5000, 5000);
      foreach (DirectInput.DeviceObjectInstance item in joystick.Objects)
      {

        int eixo_ok = item.ObjectId & (int)DirectInput.DeviceObjectTypeFlags.Axis;
        if (eixo_ok != 0)
        {
          // Configura a faixa de valores do eixo encontrado
          joystick.Properties.SetRange(DirectInput.ParameterHow.ById,
              item.ObjectId, eixo_faixaValor);
        } // endif
      } // endfor each

      joystick.Acquire();

    } // inicializarJoystick().fim

    private void mostrarJoystickInfo()
    {
      // Variáveis para coletar e mostrar dados do joystick
      DirectInput.JoystickState joy_state;
      byte[] btn = null;
      string info = null;
      
      // Coleta informações do estado de eixos e botões
      joy_state = joystick.CurrentJoystickState;
      btn = joy_state.GetButtons();

      // Mostre os botões na tela
      int ntam = btn.Length;
      for (int ncx = 0; ncx < 12; ncx++)
      {
        info = String.Format("btn[{0}]:{1}", ncx, btn[ncx].ToString() );
        mostrarMensagem(550, (ncx + 1) * 22, info);

      } // endfor

      // Mostre o estado dos eixos
      info = String.Format("eixo_x:{0}", joy_state.X.ToString() );
      mostrarMensagem(450, 22, info);

      info = String.Format("eixo_y:{0}", joy_state.Y.ToString());
      mostrarMensagem(450, 44, info);

      info = String.Format("eixo_z:{0}", joy_state.Z.ToString());
      mostrarMensagem(450, 66 , info);

      info = String.Format("Rz:{0}", joy_state.Rz.ToString ());
      mostrarMensagem(450, 88, info);
      
    } // mostrarJoystickInfo()

    private void mostrarMensagem(int coluna, int linha, string txt)
    {
      Rectangle pos = new Rectangle(coluna, linha, 0, 0);
      dxfMensagem.DrawText(null, txt, pos, 
        DrawTextFormat.NoClip, Color.Blue);
    } // Mensagem().fim


  } // fim da classe
} // fim do namespace

