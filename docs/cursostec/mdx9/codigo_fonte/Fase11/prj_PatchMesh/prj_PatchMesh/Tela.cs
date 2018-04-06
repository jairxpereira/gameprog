// prj_PatchMesh - Arquivo: Tela.cs
// Esse projeto mostra como aumentar o detalhamento
// do modelo 3d utilizando a classe PatchMesh.
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Direct3D = Microsoft.DirectX.Direct3D;


namespace prj_PatchMesh
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

    // Vetores para a posição e rotação do objeto 3d
    Vector3 posicao, rotacao;

    // Variável global para as propriedades dos objetos
    Propriedades3D g_props;

    // Essa variável controla o nível de retalhamento do objeto 3d
    private float nTesselacao = 4.0f;

    // Objeto Font do DirectX para mostrar texto
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
      pps.EnableAutoDepthStencil = true;
      pps.AutoDepthStencilFormat = DepthFormat.D16;
      
      // Adaptador default, processamento no hardware, processamento de vértice 
      // no software, janela (this), parâmetros de apresentação (pps)
      device = new Device(0, DeviceType.Hardware, this,
        CreateFlags.SoftwareVertexProcessing, pps);

      // Configuração das fontes para mostrar mensagens
      g_font = new System.Drawing.Font("Arial", 16.0f, FontStyle.Bold);
      dxfMensagem = new Direct3D.Font(device, g_font);

    } // initGfx().fim
    // ---]

    private void AtualizarCamera()
    {
      // Dados para a configuração da matriz de projeção
      int largura = this.Width; // largura da janela
      int altura = this.Height;  // altura da janela      
      float aspecto = largura / altura; // aspecto dos gráficos      
      float campo_visao = (float)Math.PI / 4; // Campo de visão
      float corte_perto = 1.0f;
      float corte_longe = 100.0f;

      // Atualiza angulo para dar movivento
      angulo += 0.05f;

      // Mostra a parte interna do polígono  
      device.RenderState.CullMode = Cull.None;

      // Configura a matriz de projeção
      device.Transform.Projection = Matrix.PerspectiveFovLH(campo_visao,
          aspecto, corte_perto, corte_longe);

      // Dados para a configuração da matriz de visualização
      Vector3 cam_pos = new Vector3(0, 0, 5.0f);
      Vector3 cam_alvo = new Vector3(0.0f, 0.0f, 0.0f);
      Vector3 cam_orientacao = new Vector3(0, 1.0f, 0);

      // Configura a matriz de visualização
      device.Transform.View = Matrix.LookAtLH(cam_pos, cam_alvo, cam_orientacao);
    }  // AtualizarCamera()

    // [---
    public void Renderizar()
    {

      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.White, 1.0f, 0);

      device.BeginScene();
      // (...) Todo o código de desenhar vai aqui         

      // Atualiza a luz e camera
      AtualizarCamera();
      AtualizarLuz();

      // Deleta o objeto3d se ele existir neste ponto porque
      // ele será criado mais adiante no código.
      if (objeto3D != null) objeto3D.Dispose();

      // Cria uma esfera lowpoly que será renderizada em wireframe
      device.RenderState.FillMode = FillMode.WireFrame;
      objeto3D = Mesh.Sphere(device, 2.0f, 4, 4);      
      // Desenha essa esfera no canto superior-esquerdo
      posicao = new Vector3(2.5f, 2.5f, -7.0f);
      rotacao = new Vector3(-10, 10, 0);
      g_props = new Propriedades3D(posicao, rotacao);
      g_props.color = Color.SaddleBrown;
      desenharObjeto(objeto3D, g_props);

      // Deleta esfera anterior e cria uma outra para ser
      // retalhada
      objeto3D.Dispose();
      objeto3D = Mesh.Sphere(device, 2.0f, 4, 4);      
      // Gera a esfera retalhada
      gerarModeloRetalhado(ref objeto3D, nTesselacao);   
      // Posiciona-a no canto inferior-esquerdo
      g_props.position = new Vector3(2.5f, -2.0f, -7.0f);
      desenharObjeto(objeto3D, g_props);

      // Vamos gerar agora as versões sólidas das esferas.
      // Deleta a esfera anterior e estabelece o modo sólido 
      // de renderização      
      objeto3D.Dispose();
      device.RenderState.FillMode = FillMode.Solid;
      // Gera a esfera retalhada e coloca-a no canto inferior-direito
      objeto3D = Mesh.Sphere(device, 2.0f, 4, 4);
      gerarModeloRetalhado(ref objeto3D, nTesselacao);
      g_props.position = new Vector3(-2.5f, -2.0f, -7.0f);
      desenharObjeto(objeto3D, g_props);
      String info = String.Format("nVértices: {0}", objeto3D.NumberVertices);
      MostrarMensagem(420, 10, info);

      // Deleta a esfera anterior e renderiza a versão lowpoly
      // no canto superior-direito
      objeto3D.Dispose();
      objeto3D = Mesh.Sphere(device, 2.0f, 4, 4);
      g_props.position = new Vector3(-2.5f, 2.5f, -7.0f);
      desenharObjeto(objeto3D, g_props);

      // Mostra o nível de tesselação e dica de teclado
      info = String.Format("nTesselação: {0}", nTesselacao.ToString());
      MostrarMensagem(20, 10, info);     
      info = " +  Aumentar nível de detalhe       - Reduzir nível de detalhe";
      MostrarMensagem(20, this.Height - 60, info);  

      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar()
    // ---]

    private void desenharObjeto(Mesh obj, Propriedades3D props)
    {

      // Ajusta rotação da caixa
      Matrix obj_rot = Matrix.RotationX(props.rotation.X) *
        Matrix.RotationY(props.rotation.Y + angulo) *
        Matrix.RotationZ(props.rotation.Z);

      // Ajusta posição da caixa
      Matrix obj_pos = Matrix.Translation(props.position);

      // Tranfere posição e rotação para o mundo
      device.Transform.World = obj_rot * obj_pos;

      // Prepara e aplica material na caixa
      Material obj_mtl = new Material();
      obj_mtl.Diffuse = props.color;
      obj_mtl.Ambient = props.color;

      // Informa ao dispositivo o material a ser utilizado
      // na renderização
      device.Material = obj_mtl;

      // Renderiza o mesh
      obj.DrawSubset(0);
    } // desenharObjeto()


    // Configuração de luz
    private void AtualizarLuz()
    {
      device.RenderState.Ambient = Color.DarkGray;
      device.RenderState.Lighting = true;
      device.Lights[0].Type = LightType.Directional;
      device.Lights[0].Diffuse = Color.Yellow;
      device.Lights[0].Direction = new Vector3(0, -1, -1);
      device.Lights[0].Commit();
      device.Lights[0].Enabled = true;
    } // AtualizarLuz().fim

    protected override void OnPaint(PaintEventArgs e)
    {
      // Trate outros processos padrões
      base.OnPaint(e);

      // Renderize a cena
      this.Renderizar();

      // Invalide para chamar novamente onPaint()
      this.Invalidate();
    } // onPaint().fim 

    // [---
    private void gerarModeloRetalhado(ref Mesh obj3d, float nivelTesselacao)
    {
      
      // Produz o mesh do tipo PatchMesh que vai retalhar o objeto
      // 3d original.
      PatchMesh retalhador = PatchMesh.CreateNPatchMesh(obj3d); 

      // Calcula a nova quantidade de vértices e faces para o novo mesh
      int nFaces = (int)(obj3d.NumberFaces    * Math.Pow(nivelTesselacao, 3));
      int nVerts = (int)(obj3d.NumberVertices * Math.Pow(nivelTesselacao, 3));

      // Obtém o formato de vértice do objeto 3d original
      VertexFormats obj_vfm = obj3d.VertexFormat;

      // O objeto 3d original não é mais necessário e precisa
      // ser dispensado neste ponto
      obj3d.Dispose();

      // Recria o objeto com espaço necessário para as novas faces
      // e vértices
      obj3d = new Mesh(nFaces, nVerts, MeshFlags.Managed
          | MeshFlags.Use32Bit, obj_vfm, device);

      // Retalha o objeto (obj3d) de acordo com o nível de retalhamento
      // dado por nivelTesselacao
      retalhador.Tessellate(nivelTesselacao, obj3d);     

      // O objeto retalhador não é mais necessário
      retalhador.Dispose();

    } // gerarModeloRetalhado().fim
    // ---]
    // [---
    private void Tela_KeyDown(object sender, KeyEventArgs e)
    {

      // A tecla '+' aumenta o nível de retalhamento
      if (e.KeyCode == Keys.Add) nTesselacao += 0.1f;

      // A tecla '-' reduz o nível de retalhamento
      if (e.KeyCode == Keys.Subtract) nTesselacao -= 0.1f;

      // O máximo nível de retalhamento é 30.0f
      // O nível mínimo depende da geometria de cada objeto 
      // e deve ser percebido com a experiência.
      if (nTesselacao <= 2.4f) nTesselacao = 2.4f;
      if (nTesselacao > 10.0f) nTesselacao = 10.0f;

    } // Tela_KeyDown().fim
    // ---]

    // Mostra texto na posição (x, y) da tela
    private void MostrarMensagem(int xpos, int ylin, string txt)
    {
      // Configura posição
      Rectangle position = new Rectangle(xpos, ylin, 0, 0);

      // Mostra texto
      dxfMensagem.DrawText(null, txt, position,
        DrawTextFormat.NoClip, Color.Blue);
    } // MostrarMensagem().fim

  } // fim da classe
} // fim do namespace

