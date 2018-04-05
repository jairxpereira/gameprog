// prj_Sprite02 - Arquivo: Tela.cs
// Esse projeto mostra como desenhar sprites via DirectDraw
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.DirectDraw;
using DirectInput = Microsoft.DirectX.DirectInput;

namespace prj_Sprite02
{
  // [---
  public partial class Tela : Form
  {

    // Variável para criação do dispositivo de gerenciamento teclado
    private DirectInput.Device teclado = null;

    // Para criação do dispositivo gráfico DirectDraw.Device
    private Device device = null;

    // A tecla Escape terminará a aplicação
    private bool terminar = false;
    // <b>
    // Vamos guardar aqui a resolução do modo de vídeo corrente
    int xtela = 0;
    int ytela = 0;

    // Coordenadas (xcol, ylin) para movimentação da sprite
    int xcol = 0;
    int ylin = 0;

    // Todos esses objetos giram em torno de se desenhar uma sprite
    // na tela
    // O objeto sprite em si
    private Surface g_sprite = null;
    private Surface tela = null;
    private Surface backBuffer = null;

    // Esse retângulo indica a área a ser desenhada da sprite
    // Isso permite produzir animações recortando partes diferentes da
    // sprite
    private Rectangle g_recorte;
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

    // [---
    public void initGfx()
    {
      // <b>
      // Cria o dispositivo DirectDraw.Device
      device = new Device();

      // Configurando o nível de configuração: tela cheia exclusiva
      device.SetCooperativeLevel(this, CooperativeLevelFlags.FullscreenExclusive);

      // Verifica configuração atual do vídeo e reaplica-o em tela cheia
      SurfaceDescription video_atual_descricao = device.DisplayMode;
      xtela = video_atual_descricao.Width;
      ytela = video_atual_descricao.Height;
      device.SetDisplayMode(xtela, ytela, 32, 0, false);

      // Configura a superfície primária ( a tela )
      SurfaceDescription tela_descricao = new SurfaceDescription();

      // Define a superfície como primária, isto é, representa a memória
      // de vídeo imediata
      tela_descricao.SurfaceCaps.PrimarySurface = true;

      // A 'tela ' vai receber o backbuffer virado sobre ela
      tela_descricao.SurfaceCaps.Flip = true;

      // Complex quer dizer que a superfície vai conter outras
      // outras superfícies (backbuffers)
      tela_descricao.SurfaceCaps.Complex = true;
      tela_descricao.BackBufferCount = 1;

      // Cria a superfície primária ( a tela )
      tela = new Surface(tela_descricao, device);


      // Obtém o backbuffer a partir da superfície primária
      SurfaceCaps caps = new SurfaceCaps();
      caps.BackBuffer = true;
      backBuffer = tela.GetAttachedSurface(caps);

      // Ignore as exceções geradas
      DirectXException.IgnoreExceptions();

      inicializarSprite();

      // Define posição inicial da sprite
      xcol = 320;
      ylin = 240;

      inicializarTeclado();
      // </b>

    } // initGfx()
    // ---]

    // [---
    private void inicializarSprite()
    {
      // Diretório base de imagens
      string diretorioBase = @"c:\gameprog\gdkmedia\bitmap\";

      // Cria um objeto 'descrição de superfície'
      SurfaceDescription desc = new SurfaceDescription();

      // Cria a superfície bitmap a partir de uma imagem
      g_sprite = new Surface(diretorioBase + "logo.bmp", desc, device);

      // Faz um recorte da área a ser desenhada; nesse caso a textura toda
      g_recorte = new Rectangle(0, 0, desc.Width, desc.Height);      

      // Indica a cor transparente (color key) da sprite       
      ColorKey ck = new ColorKey();
      g_sprite.SetColorKey(ColorKeyFlags.SourceDraw, ck);

    } // inicializarSprite().fim
    // ---]   


    // [---
    public void Renderizar()
    {
      // <b>
      verificarTeclado();
      if (terminar == true) return;
      // </b>

      // Preenche de branco o backbuffer
      backBuffer.ColorFill(0xFFFFFF);

      // Mostra a coordenada da sprite na tela
      string info = String.Format("({0},{1})", xcol, ylin);
      backBuffer.DrawText(10, 10, info, false);

      // Desenha a sprite
      backBuffer.DrawFast(xcol, ylin, g_sprite, g_recorte,
        DrawFastFlags.DoNotWait | DrawFastFlags.SourceColorKey);

      // Vira o backbuffer para a tela
      tela.Flip(backBuffer, FlipFlags.DoNotWait);

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

      // Processa a tecla Escape
      if (terminar)
      {
        device.Dispose();
        teclado.Dispose();
        this.Close();
        Application.Exit();
      } // endif

    } // AtualizarTeclado()  

  } // fim da classe
} // fim do namespace