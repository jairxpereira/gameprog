// prj_HLSL03 - Arquivo: Tela.cs
// Esse projeto mostra como renderizar um modelo 3D
// texturizado com hlsl - By www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_HLSL03
{

  // Estrutura para propriedades 3d do objeto
  // posição, rotação e cor
  struct Propriedades3D
  {
    public Vector3 position;
    public Vector3 rotation;

    public Propriedades3D(Vector3 pos, Vector3 rot)
    {
      position = pos;
      rotation = rot;
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

    // Matrizes de composição da camera
    private Matrix mundo;
    private Matrix visao;
    private Matrix projecao;
    Effect efeito = null;
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

      // Configuração dos parâmetros de apresentação
      PresentParameters pps = new PresentParameters();
      pps.Windowed = true;
      pps.SwapEffect = SwapEffect.Discard;

      // Ativando o buffer de profundidade
      pps.EnableAutoDepthStencil = true;
      pps.AutoDepthStencilFormat = DepthFormat.D16;

      // Adaptador default, processamento de vértice no
      // hardware, janela (this), parâmetros de apresentação (pps)
      int adaptador = 0;
      device = new Device(adaptador, DeviceType.Hardware, this,
        CreateFlags.SoftwareVertexProcessing, pps);

      // Carrega o modelo
      diretorioBase = @"c:\Gameprog\Gdkmedia\Modelos\Tiny\";
      CarregarModelo(diretorioBase, "tiny.x");

      // Inicializa a camera e o efeito
      inicializarCamera();
      inicializarEfeito();

    } // initGfx().fim
    // ---]

    private void inicializarCamera()
    {
      // Dados para a configuração da matriz de projeção
      int largura = this.Width; // largura da janela
      int altura = this.Height;  // altura da janela      
      float aspecto = largura / altura; // aspecto dos gráficos      
      float campo_visao = (float)Math.PI / 4; // Campo de visão
      float corte_perto = 1.0f;
      float corte_longe = 10000.0f;

      // Configura a matriz de projeção
      projecao = Matrix.PerspectiveFovLH(campo_visao,
          aspecto, corte_perto, corte_longe);

      // Rotaciona o triangulo indiretamente através da rotação dos
      // eixos da matriz mundial.
      mundo = Matrix.RotationZ(angulo);

      // Dados para a configuração da matriz de visualização
      Vector3 cam_pos = new Vector3(0, 0, 700.0f); // Posição da camera
      Vector3 cam_alvo = new Vector3(0, 0.0f, 0); // Alvo da câmera
      Vector3 cam_orientacao = new Vector3(0, 1.0f, 0); // Orientação da câmera          

      // Configura a matriz de visualização
      visao = Matrix.LookAtLH(cam_pos, cam_alvo, cam_orientacao);

    }  // inicializarCamera()

    // [---
    private void inicializarEfeito()
    {
      // Cria o efeito
      efeito = Effect.FromFile(device,
    @"c:\gameprog\gdkmedia\shader\mesh-texturizado.fx",
    null, ShaderFlags.None, null);

      efeito.Technique = "texturaOriginal";
    } // InicializarEfeito()
    // ---]
    // [---
    public void Renderizar()
    {
      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Azure, 1.0f, 0);
      device.BeginScene();
      // <b>
      // Renderiza o mesh usando textura negativa
      efeito.Technique = "texturaNegativa";
      int numPasses = efeito.Begin(0);
      for (int ncx = 0; ncx < numPasses; ncx++)
      {
        efeito.Pass(ncx);
        // Desenha o primeiro mesh
        posicao = new Vector3(-150.0f, 40.0f, -100.0f);
        rotacao = new Vector3(0, 0, 0);
        g_props = new Propriedades3D(posicao, rotacao);
        desenharObjeto(objeto3D, g_props);
      } // endfor
      efeito.End();
     
      // Renderiza o mesh usando textura original    
      efeito.Technique = "texturaOriginal";
      numPasses = efeito.Begin(0);
      for (int ncx = 0; ncx < numPasses; ncx++)
      {
        efeito.Pass(ncx);
        // Desenha o segundo mesh
        g_props.position.X = 100.0f; g_props.position.Y = 0.2f;
        desenharObjeto(objeto3D, g_props);
      } // endfor
      efeito.End();
      // </b>
      device.EndScene();
      device.Present();
      Application.DoEvents();
    } // Renderizar().fim
    // ---]
    // [---
    private void desenharObjeto(Mesh obj, Propriedades3D props)
    {
      // Ajusta rotação da objeto 3d
      Matrix obj_rot = Matrix.RotationX(props.rotation.X + angulo) *
      Matrix.RotationY(props.rotation.Y) *
      Matrix.RotationZ(props.rotation.Z);

      // Ajusta posição do objeto
      Matrix obj_pos = Matrix.Translation(props.position);

      // Atualiza ângulo
      angulo += 0.01f;

      // Tranfere posição e rotação para o mundo 
      // Atualiza variáveis do efeito
      mundo = obj_rot * obj_pos;
      Matrix camera = mundo * visao * projecao;
      efeito.SetValue("Camera", camera);

      // Renderiza o mesh texturizado
      for (int ncx = 0; ncx < g_meshTex.Length; ncx++)
      {
        device.SetTexture(0, g_meshTex[ncx]);
        obj.DrawSubset(ncx);
      } // endfor

    } // desenharObjeto().fim
    // ---]

    protected override void OnPaint(PaintEventArgs e)
    {
      // Trate outros processos padrões
      base.OnPaint(e);
      this.Renderizar();
      this.Invalidate();
    } // onPaint().fim 


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

  } // fim da classe
} // fim do namespace

