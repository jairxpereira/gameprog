// prj_Som01 - Arquivo: Tela.cs
// Esse projeto mostra como tocar um efeito sonoro
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Direct3D = Microsoft.DirectX.Direct3D;
using DirectSound = Microsoft.DirectX.DirectSound;

namespace prj_Som01
{
  // [---
  public partial class Tela : Form
  {    
    // Para criação do dispositivo gráfico
    private Device device = null;
   
    // Objeto Font do DirectX para mostrar texto (mensagens)
    private Direct3D.Font dxfMensagem = null;    
    // Objeto Font tradicional do namespace System.Drawing
    private System.Drawing.Font g_font = null;

    // <b>
    // Para criação do dispositivo sonoro
    private DirectSound.Device radio = null;

    // Esse objeto carrega e toca efetivamente o som
    private DirectSound.SecondaryBuffer som;
    // </b>
    // (...)
    // ---]

    public Tela()
    {
      // Inicialização dos componentes.
      InitializeComponent();

      // Toda renderização deverá ocorrer dentro do evento onPaint()
      // Isso evita interferência estrangeira de processamento default
      // do sistema Windows
      this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.Opaque, true);

    } // construtor

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

      // Configuração das fontes para mostrar mensagens
      g_font = new System.Drawing.Font("Arial", 12.0f, FontStyle.Bold );
      dxfMensagem = new Direct3D.Font(device, g_font);     
      // <b>
      // Inicializa e toca um som inicial
      inicializarSom();
      // </b>

    } // initGfx().fim 

    // [---
    public void inicializarSom()
    {
      string som_arquivo = @"c:\gameprog\gdkmedia\som\shoot.wav";

      // Cria um dispositivo de som
      radio = new DirectSound.Device();

      // Estabelece o nível de cooperação
      radio.SetCooperativeLevel(this, DirectSound.CooperativeLevel.Normal);

      // Cria um objeto SecondaryBuffer que toca o som
      som = new DirectSound.SecondaryBuffer(som_arquivo, radio);

      // Toca o som efetivamente
      som.Play(0, DirectSound.BufferPlayFlags.Default);

    } // inicializarSom().fim
    // ---]


    public void Renderizar()
    {
      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target, Color.White, 1.0f, 0);

      device.BeginScene();
      MostrarTexto(20, 40, "Pressione qualquer tecla para tocar o som");      
      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar() // desenharObjeto()   

    protected override void OnPaint(PaintEventArgs e)
    {
      // Trate outros processos padrões
      base.OnPaint(e);

      // Renderize a cena
      this.Renderizar();

      // Invalide para chamar novamente onPaint()
      this.Invalidate();
    } // onPaint().fim  
   
    // Mostra texto centralizado
    private void MostrarTexto(int xpos, int ylin, string txt)
    {
      // Configura posição
      Rectangle position = new Rectangle(xpos, ylin, 0, 0);

      // Mostra texto
      dxfMensagem.DrawText(null, txt, position,
        DrawTextFormat.NoClip, Color.Blue);
    } // MostrarTexto().fim

    private void Tela_KeyDown(object sender, KeyEventArgs e)
    {
      // Toca o som efetivamente
      som.Play(0, DirectSound.BufferPlayFlags.Default);
    }

  } // fim da classe
} // fim do namespace

