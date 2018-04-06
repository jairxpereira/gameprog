// prj_Sprite01 - Arquivo: Tela.cs
// Esse projeto mostra como desenhar sprites via Direct3d
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Direct3D = Microsoft.DirectX.Direct3D;
using DirectInput = Microsoft.DirectX.DirectInput;

namespace prj_Sprite01
{

  // [---
  // Estrutura para propriedades da sprite
  // posição, posição do centro e cor
  struct SpriteInfo
  {
    public Vector3 position;
    public Vector3 center;
    public Color color;

    public SpriteInfo(Vector3 pos, Vector3 centro)
    {
      position = pos;
      center = centro;
      color = Color.White;
    }
  };
  // ---]



  // [---
  public partial class Tela : Form
  {
    
    // Variável para criação do dispositivo de gerenciamento teclado
    private DirectInput.Device teclado = null;
    

    // Para criação do dispositivo gráfico
    private Device device = null;

    // A tecla Escape terminará a aplicação
    private bool terminar = false;

    // Objeto Font do DirectX para mostrar texto (titulos)
    private Direct3D.Font dxfTitulo = null;
    // Objeto Font tradicional do namespace System.Drawing
    private System.Drawing.Font g_font = null;

    // Vamos guardar aqui a resolução do modo de vídeo corrente
    int xtela = 0;
    int ytela = 0;
    
    // Todos esses objetos giram em torno de se desenhar uma sprite
    // na tela
    // O objeto sprite em si
    private Sprite g_sprite = null;
    
    // A imagem da sprite é composta por uma textura
    private Texture g_textura = null;    

    // Esse retângulo indica a área a ser desenhada da sprite
    // Isso permite produzir animações recortando partes diferentes da
    // sprite
    private Rectangle g_recorte;

   // Esse objeto vai guardar cor, posição, posição do centro da sprite
    private SpriteInfo g_sInfo;

    
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
      pps.SwapEffect = SwapEffect.Discard;
      // <b>
      // Obtém a configuração do modo de vídeo atual
      xtela = Manager.Adapters[0].CurrentDisplayMode.Width;
      ytela = Manager.Adapters[0].CurrentDisplayMode.Height;
      Format video_fmt = Manager.Adapters[0].CurrentDisplayMode.Format;

      bool tela_cheia_ok = false;

      // O modo de video atual permite tela cheia?
      tela_cheia_ok = Manager.CheckDeviceType(0, DeviceType.Hardware,
        video_fmt, video_fmt, false);

      // Configura tela cheia se houver esse suporte no modo de video atual
      if (tela_cheia_ok)
      {
        pps.Windowed = false;
        pps.BackBufferCount = 1;
        pps.BackBufferFormat = video_fmt;
        pps.BackBufferWidth = xtela;
        pps.BackBufferHeight = ytela;

      } // endif
      // Se não tiver suporte para tela cheia, pode ser janela mesmo!
      else
      {
        pps.Windowed = true;
      } // end else
      // </b>

      // Adaptador default, processamento no hardware, processamento de vértice 
      // no software, janela (this), parâmetros de apresentação (pps)
      int adaptador = 0;
      device = new Device(adaptador, DeviceType.Hardware, this,
        CreateFlags.SoftwareVertexProcessing, pps);

      // Configuração das fontes para mostrar títulos
      g_font = new System.Drawing.Font("Arial", 36.0f, FontStyle.Bold);
      dxfTitulo = new Direct3D.Font(device, g_font);

      // <b>
      inicializarSprite();
      inicializarJogador();
      inicializarTeclado();
      // </b>

    } // initGfx()
    // ---]

    // [---
    private void inicializarSprite()
    {
      // Diretório base de imagens
      string diretorioBase = @"c:\gameprog\gdkmedia\bitmap\";

      // Carrega a textura do diretório base
      g_textura = TextureLoader.FromFile(device, diretorioBase + "logo.tga");

      // Acessa a superfície da textura
      // Esse objeto apresenta um objeto Graphics!
      Surface tex_superficie = g_textura.GetSurfaceLevel(0);

      // Obtém a descrição da superfície
      SurfaceDescription desc = tex_superficie.Description;

      // Faz um recorte da área a ser desenhada; nesse caso a textura toda
      g_recorte = new Rectangle(0, 0, desc.Width, desc.Height);

      // Dispensa a superfície
      tex_superficie.Dispose();

      // Cria uma sprite
      g_sprite = new Sprite(device);

    } // inicializarSprite().fim
    // ---]


    // [---
    private void inicializarJogador()
    {

      // Vetores para configura posição e centro da sprite
      Vector3 posicao, centro;
      posicao = new Vector3(0.0f, 0.0f, 1.0f);

      // Calcula o centro da tela para ser o centro da sprite
      centro = new Vector3(0.0f, 0.0f, 0.0f);
      centro.X = xtela / -2;
      centro.Y = ytela / -2;

      // Inicializa g_sInfo com posição e centro da sprite
      g_sInfo = new SpriteInfo(posicao, centro);

    } // inicializarJogador().fim
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
      String info = String.Format("({0},{1})", 
        g_sInfo.position.X, g_sInfo.position.Y);
      MostrarTitulo(10, 10, info, Color.Black);

      // SpriteFlags.AlphaBlend - permite efeito de transparência
      g_sprite.Begin(SpriteFlags.AlphaBlend);

      // Desenha a sprite utilizando a textura, imagem, centro, 
      // posição e cor apontados
      g_sprite.Draw(g_textura, g_recorte, 
        g_sInfo.center, g_sInfo.position, g_sInfo.color);

      // terminar de desenhar as sprites
      g_sprite.End();
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

    
    void verificarTeclado()
    {

      // Variáveis para guardar o estado das teclas
      int seta_esquerda = 0;
      int seta_direita = 0;
      int seta_cima = 0;
      int seta_abaixo = 0;

      // <b>
      DirectInput.Key[] teclasPressionadas = teclado.GetPressedKeys();

      // Verifica teclado e atualiza teclas de estado
      foreach (DirectInput.Key tecla in teclasPressionadas)
      {

        if (tecla == DirectInput.Key.DownArrow) seta_abaixo = 1;
        if (tecla == DirectInput.Key.UpArrow) seta_cima = 1;
        if (tecla == DirectInput.Key.LeftArrow) seta_esquerda = 1;
        if (tecla == DirectInput.Key.RightArrow) seta_direita = 1;
        if (tecla == DirectInput.Key.RightShift) g_sInfo.position.X = 0;
        if (tecla == DirectInput.Key.RightShift) g_sInfo.position.Y = 0;
        if (tecla == DirectInput.Key.Escape) terminar = true;
      } // endfor each
      // </b>

      // Atualiza posicionamento do 'jogador'
      if (seta_abaixo == 1) g_sInfo.position.Y += 5;
      if (seta_cima == 1) g_sInfo.position.Y -= 5;
      if (seta_esquerda == 1) g_sInfo.position.X -= 5;
      if (seta_direita == 1) g_sInfo.position.X += 5;

      // Processa a tecla Escape
      if (terminar)
      {
        device.Dispose();
        teclado.Dispose();
        this.Close();
        Application.Exit();
      } // endif

    } // AtualizarTeclado()  


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

