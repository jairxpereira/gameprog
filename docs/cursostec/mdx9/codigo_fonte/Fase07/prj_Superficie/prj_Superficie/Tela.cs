// prj_Superficie - Arquivo: Tela.cs
// Esse projeto mostra como renderizar na textura, salvar uma
// imagem da tela e configurar a função callback de reconfiguração
// do dispositivo.
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_Superficie
{

  // Estrutura para propriedades 3d do objeto
  // posição, rotação e cor
  struct Propriedades3D
  {
    public Vector3 position;
    public Vector3 rotation;
    public Color color;

    public Propriedades3D(Vector3 pos, Vector3 rot)
    {
      position = pos;
      rotation = rot;
      color = Color.White;
    }
  };


  // [---
  public partial class Tela : Form
  {
    // Para criação do dispositivo gráfico
    private Device device = null;

    // Essa variável atualizada a cada ciclo ocasionará 
    // a animação do objeto
    private float angulo = 0.0f;

    // Variável para guardar uma malha 3d
    private Mesh objeto3D = null;

    // Recipiente de materiais do mesh
    private Material[] g_meshMtl = null;

    // Recipiente de texturas do mesh
    private Texture[] g_meshTex = null;

    // Pasta de localização do arquivo mesg e sua textura
    private string diretorioBase = null;

    // Vetores para a posição e rotação do objeto 3d
    Vector3 posicao, rotacao;

    // Variável global para propriedade dos objetos
    Propriedades3D g_props;
    // <b>
    // Preparando a infraestrutura para renderizar na textura
    private Texture texturaAlvo = null;
    
    // Camada de dados da textura
    private Surface superficieAlvo = null;
    const int superficie_ntam = 192;

    // Renderizador
    private RenderToSurface Renderizador = null;

    // Este objeto vai exibir a textura na tela
    private Sprite radar = null;       
    // </b>
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

      // Configuração dos parâmetros de apresentação
      PresentParameters pps = new PresentParameters();
      pps.Windowed = true;
      pps.SwapEffect = SwapEffect.Discard;

      // Ativando o buffer de profundidade
      pps.EnableAutoDepthStencil = true;
      pps.AutoDepthStencilFormat = DepthFormat.D16;

      // Adaptador default, processamento no hardware, processamento de vértice 
      // no software, janela (this), parâmetros de apresentação (pps)
      int adaptador = 0;
      device = new Device(adaptador, DeviceType.Hardware, this,
        CreateFlags.SoftwareVertexProcessing, pps);

      // Carrega modelo
      diretorioBase = @"c:\Gameprog\Gdkmedia\Modelos\Tiny\";
      CarregarModelo(diretorioBase, "tiny.x");
      // <b>
      // Configura função de reconfiguração do dispositivo
      device.DeviceReset += new EventHandler(reconfigurarDispositivo);

      // Inicializa os objetos para o processo de renderizar na textura
      reconfigurarDispositivo(device, null);
      // </b>

    } // initGfx()
    // ---]

    // [---
    private void inicializarRenderizacaoNaTextura()
    {
      // Inicializa o Renderizador
      Renderizador = new RenderToSurface(device, superficie_ntam, superficie_ntam,
               Format.X8R8G8B8, true, DepthFormat.D16);

      // Cria uma textura alvo da renderização
      texturaAlvo = new Texture(device, superficie_ntam, superficie_ntam, 1,
          Usage.RenderTarget, Format.X8R8G8B8, Pool.Default);

      // Acessa a superficie de dados da textura
      superficieAlvo = texturaAlvo.GetSurfaceLevel(0);

      // Cria uma sprite para a textura
      radar = new Sprite(device);
    }
    // ---]

    // [---
    private void renderizarNaTextura()
    {
      // Prepara a configuração da janela de visualização
      Viewport visao = new Viewport();
      visao.Width = superficie_ntam;
      visao.Height = superficie_ntam;
      visao.MaxZ = 1.0f;

      // Inicia a renderização da cena
      Renderizador.BeginScene(superficieAlvo, visao);
      
      // Limpa o dispositivo
      device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.White, 1.0f, 0);      
    
      // Modo de preenchimento da renderização: pontos
      device.RenderState.FillMode = FillMode.Point;

      // Desenha o objeto na textura
      posicao = new Vector3(0.0f, 0.2f, -50.0f);
      rotacao = new Vector3(0, 0, 0);
      g_props = new Propriedades3D(posicao, rotacao);
      desenharObjeto(objeto3D, g_props);

      // Recupera modo de preenchimento da renderização: sólido
      device.RenderState.FillMode = FillMode.Solid;
     
      // Finaliza a cena no Renderizador
      Renderizador.EndScene(Filter.None);     

    } // renderizarNaTextura()
    // ---]


    // [---
    private void reconfigurarDispositivo(object sender, EventArgs e)
    {
      device = (Device)sender;
      AtualizarCamera();
      AtualizarLuz();
      inicializarRenderizacaoNaTextura();

    } // reconfigurarDispositivo().fim
    // ---]

    private void AtualizarCamera()
    {
      // Dados para a configuração da matriz de projeção
      int largura = this.Width; // largura da janela
      int altura = this.Height;  // altura da janela      
      float aspecto = largura / altura; // aspecto dos gráficos      
      float campo_visao = (float)Math.PI / 4; // Campo de visão
      float corte_perto = 1.0f;

      // Essa variável foi modificar para acomodar o tamanho
      // do modelo
      float corte_longe = 10000.0f;

      // Atualiza angulo para dar movimento ao objeto 3d
      angulo += 0.05f;

      // Mostra a parte interna do polígono
      // Experimente desativar essa linha com a instrução de comentário      
      device.RenderState.CullMode = Cull.None;

      // Configura a matriz de projeção
      device.Transform.Projection = Matrix.PerspectiveFovLH(campo_visao,
          aspecto, corte_perto, corte_longe);

      // Dados para a configuração da matriz de visualização
      // O eixo z foi modificar para comportar o tamanho do modelo
      Vector3 cam_pos = new Vector3(0, 0, 600.0f);
      Vector3 cam_alvo = new Vector3(0.0f, 0.0f, 0.0f);
      Vector3 cam_orientacao = new Vector3(0, 1.0f, 0);

      // Configura a matriz de visualização
      device.Transform.View = Matrix.LookAtLH(cam_pos, cam_alvo, cam_orientacao);
    }  // AtualizarCamera()

    // [---
    public void Renderizar()
    {
      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target | ClearFlags.ZBuffer,
        Color.CornflowerBlue, 1.0f, 0);

      device.BeginScene();
      // (...) Todo o código de desenhar vai aqui   

      // Atualiza a câmera
      AtualizarCamera();
      AtualizarLuz();

      radar.Begin(SpriteFlags.None);
      radar.Draw(texturaAlvo, new Rectangle(0, 0, superficie_ntam, superficie_ntam),
      new Vector3(0, 0, 0), new Vector3(10, 10, 1.0f), Color.White);
      radar.End();

      posicao = new Vector3(-50.0f, 0.2f, -200.0f);
      rotacao = new Vector3(0, 0, 0);
      g_props = new Propriedades3D(posicao, rotacao);
      desenharObjeto(objeto3D, g_props);

      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar()
    // ---]

    // [---
    private void desenharObjeto(Mesh obj, Propriedades3D props)
    {

      // Ajusta rotação do objeto 3d
      Matrix obj_rot = Matrix.RotationX(props.rotation.X + angulo) *
        Matrix.RotationY(props.rotation.Y) *
        Matrix.RotationZ(props.rotation.Z);

      // Ajusta posição do objeto 3d
      Matrix obj_pos = Matrix.Translation(props.position);

      // Tranfere posição e rotação para o mundo
      device.Transform.World = obj_rot * obj_pos;

      // Prepara e aplica uma material\textura no objeto
      for (int ncx = 0; ncx < g_meshMtl.Length; ncx++)
      {
        // Informa ao dispositivo o material a ser utilizado
        // na renderização    
        device.Material = g_meshMtl[ncx];
        device.SetTexture(0, g_meshTex[ncx]);

        // Renderiza o mesh
        obj.DrawSubset(ncx);
      } // endfor

    } // desenharObjeto()
    // ---]


    // Configuração de luz
    private void AtualizarLuz()
    {

      device.RenderState.Lighting = true;
      device.Lights[0].Type = LightType.Directional;
      device.Lights[0].Diffuse = Color.White;
      device.Lights[0].Direction = new Vector3(0, -1, -1);
      device.Lights[0].Commit();
      device.Lights[0].Enabled = true;
    } // AtualizarLuz().fim

    // [---
    protected override void OnPaint(PaintEventArgs e)
    {
      // Trate outros processos padrões
      base.OnPaint(e);

      // Renderize a cena

      renderizarNaTextura();

      this.Renderizar();

      // Invalide para chamar novamente onPaint()
      this.Invalidate();
    } // onPaint().fim 
    // ---]

    private void CarregarModelo(string diretorioBase, string arquivo)
    {
      // Composição do nome final do arquivo
      string caminhoFinal = diretorioBase + arquivo;

      // Recebe nome do arquivo de textura sendo carregado
      string arquivo_textura = null;

      // Quantidade de materiais\texturas encontrados no modelo3d
      int nTam = 0;

      // Pacote de materiais e texturas do modelo 3d
      ExtendedMaterial[] xMtl;

      // Carrega modelo 3d com suas texturas e materiais
      objeto3D = Mesh.FromFile(caminhoFinal, MeshFlags.Managed,
        device, out xMtl);

      // Verifica quantidade de texturas\materiais do modelo
      nTam = xMtl.Length;

      // Carrega as texturas caso nTam > 0
      if ((xMtl != null) && (nTam > 0))
      {

        // Inicializa as variáveis arrays de materiais e texturas
        g_meshMtl = new Material[nTam];
        g_meshTex = new Texture[nTam];

        for (int ncx = 0; ncx < nTam; ncx++)
        {
          // Carrega materiais
          g_meshMtl[ncx] = xMtl[ncx].Material3D;

          // Carrega texturas
          arquivo_textura = xMtl[ncx].TextureFilename;
          if ((arquivo_textura != null) && arquivo_textura != String.Empty)
          {
            g_meshTex[ncx] = TextureLoader.FromFile(device,
              diretorioBase + arquivo_textura);
          } // endif (texturas)
        } // endfor (materiais\texturas)
      } // endif (verificação de texturas\materiais presentes)
    } // CarregarModelo().fim


    
    private void Tela_KeyDown(object sender, KeyEventArgs e)
    {

      if (e.KeyCode == Keys.S)
      {
        salvarImagem();
      }
    } // _KeyDown().fim


    // [---
    private void salvarImagem()
    {

      Surface backbuffer = device.GetBackBuffer(0, 0, BackBufferType.Mono);
      SurfaceLoader.Save("foto_tela.jpg", ImageFileFormat.Jpg, backbuffer);
      backbuffer.Dispose();
      this.Text = "Ok. Imagem salva no disco";
    }
    // ---]

  } // fim da classe
} // fim do namespace

