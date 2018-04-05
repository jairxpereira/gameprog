// prj_Clonagem - Arquivo: Tela.cs
// Esse projeto mostra como clonar meshes
// Produzido por www.gameprog.com.br
// Versão Dx gerenciado: 1.0.2902.0(X/3D) 1.0.2911.0 (3DX)
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Direct3D = Microsoft.DirectX.Direct3D;


namespace prj_Clonagem
{

  // Estrutura para propriedades 3d do objeto
  // posição e rotação
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

    // Controla iluminação
    bool estadoLuz = true;

    // Vetores para a posição e rotação do objeto 3d
    Vector3 posicao, rotacao;

    // Variável global para propriedade dos objetos
    Propriedades3D g_props;

    // Objeto Font do DirectX para mostrar texto 
    private Direct3D.Font dxfMensagem = null;

    // Objeto Font tradicional do namespace System.Drawing
    private System.Drawing.Font g_font = null;
    // <b>
    // Variáveis para guardar as malhas tridimensionais  
    private Mesh cubo = null;
    private Mesh cuboClonado = null;
    private Mesh segundoClone = null;
    // </b>
    // (...)
    // ---]
    public Tela()
    {
      // Inicialização dos componentes.
      InitializeComponent();
      this.Size = new Size(640, 480);
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
      int adaptador = 0;
      device = new Device(adaptador, DeviceType.Hardware, this,
        CreateFlags.SoftwareVertexProcessing, pps);

      // Configuração das fontes para mostrar mensagens
      g_font = new System.Drawing.Font("Arial", 16.0f, FontStyle.Bold);
      dxfMensagem = new Direct3D.Font(device, g_font);

      // Montamos o cubo e o clonamos duas vezes
      montarCubo();
      clonarCubo();
      segundaClonagem();

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
      angulo += 0.04f;

      // Mostra a parte interna do polígono
      // Experimente desativar essa linha com a instrução de comentário      
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

      // Atualiza a câmera
      AtualizarCamera();
      AtualizarLuz();

      // Mostra primeiro cubo clonado
      device.VertexFormat = CustomVertex.PositionNormalColored.Format;
      posicao = new Vector3(-2.0f, -2.0f, -7.0f);
      rotacao = new Vector3(-10, 10, 0);
      g_props = new Propriedades3D(posicao, rotacao);
      desenharObjeto(cuboClonado, g_props);

      // Mostra cubo original
      device.VertexFormat = CustomVertex.PositionColored.Format;
      posicao = new Vector3(0.0f, 2.0f, -7.0f);
      g_props = new Propriedades3D(posicao, rotacao);
      desenharObjeto(cubo, g_props);

      // Mostra segundo cubo clonado
      device.VertexFormat = CustomVertex.PositionNormalColored.Format;
      posicao = new Vector3(2.0f, -2.0f, -7.0f);
      g_props = new Propriedades3D(posicao, rotacao);
      desenharObjeto(segundoClone, g_props);

      // Verifica se cubo tem informação de normal
      if ((cubo.VertexFormat & VertexFormats.Normal) != VertexFormats.Normal)
        MostrarMensagem(20, 100, "Cubo não tem informação de normal");
      else
        MostrarMensagem(20, 100, "Cubo tem informação de normal");

      // Verifica se cubo clonado tem informação de normal
      if ((cuboClonado.VertexFormat & VertexFormats.Normal) != VertexFormats.Normal)
        MostrarMensagem(220, 240, "cuboClonado não tem informação de normal");
      else
        MostrarMensagem(200, 420, "cuboClonado tem informação de normal");

      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar().fim
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

      // Renderiza o mesh
      obj.DrawSubset(0);
    } // desenharObjeto().fim

    // Configuração de luz
    private void AtualizarLuz()
    {
      device.RenderState.Lighting = estadoLuz;
      device.Lights[0].Type = LightType.Directional;
      device.Lights[0].Diffuse = Color.White;
      device.Lights[0].Direction = new Vector3(0, -1, -1);
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
    private void montarCubo()
    {
      // Número de vértices do cubo
      int nVerts = 8;

      // Índices de ligação dos vértices
      short[] indices =
			{
				0,1,2, // face frontal
				1,3,2, // face frontal
				4,5,6, // face traseira
				6,5,7, // face traseira
				0,5,4, // face de cima
				0,2,5, // face de cima
				1,6,7, // face do fundo
				1,7,3, // face do fundo
				0,6,1, // face esquerda
				4,6,0, // face esquerda
				2,3,7, // face direita
				5,2,7  // face direita
			};

      // Vamos criar um mesh a partir do zero
      cubo = new Mesh(nVerts * 3, nVerts, MeshFlags.Managed,
        CustomVertex.PositionColored.Format, device);

      // Vamos preencher o buffer de vértices
      VertexBuffer vb = cubo.VertexBuffer;

      // Produz um objeto GraphicsStream com os dados do buffer de vértices
      GraphicsStream data = vb.Lock(0, 0, LockFlags.None);

      // Configura a posição e cor dos vértices
      const int vermelho = 0xFF0000;
      const int verde = 0x00FF00;
      const int azul = 0x0000FF;
      const int amarelo = 0xFFFF00;

      // Posicionamento dos vértices do cubo
      data.Write(new CustomVertex.PositionColored( -1.0f, 1.0f, 1.0f, vermelho ));
      data.Write(new CustomVertex.PositionColored( -1.0f, -1.0f, 1.0f, verde ));
      data.Write(new CustomVertex.PositionColored( 1.0f, 1.0f, 1.0f, vermelho ));
      data.Write(new CustomVertex.PositionColored( 1.0f, -1.0f, 1.0f, verde ));
      data.Write(new CustomVertex.PositionColored( -1.0f, 1.0f, -1.0f, azul ));
      data.Write(new CustomVertex.PositionColored( 1.0f, 1.0f, -1.0f, azul ));
      data.Write(new CustomVertex.PositionColored( -1.0f, -1.0f, -1.0f, amarelo ));
      data.Write(new CustomVertex.PositionColored( 1.0f, -1.0f, -1.0f, amarelo ));

      // Libera o buffer de vértices para a placa de video
      vb.Unlock();

      // Inicializa o buffer de índices
      IndexBuffer ib = cubo.IndexBuffer;
      ib.SetData(indices, 0, LockFlags.None);
      
      // Dispensa os objetos utilizados
      vb.Dispose();
      ib.Dispose();

    } // montarCubo().fim
    // ---]

    // [---
    private void clonarCubo()
    {
      // Clona o cubo adicionando dados de normal
      cuboClonado = cubo.Clone( MeshFlags.Managed,
        CustomVertex.PositionNormalColored.Format, device );

      // Calcula as normais
      cuboClonado.ComputeNormals();
    } // clonarCubo().fim
    // ---]
    // [---
    private void segundaClonagem()
    {
      // Verifica se o mesh possui informação de normal
      // Se não possui, inclui esse dado
      if (( cubo.VertexFormat & VertexFormats.Normal ) != VertexFormats.Normal )
      {
        // Acrescenta espaço para informação de normal
        segundoClone = cubo.Clone(cubo.Options.Value,
          cubo.VertexFormat | VertexFormats.Normal, device );

        // Cálcula as normais do cubo clonado
        segundoClone.ComputeNormals();

      } // endif
    } // segundaClonagem().fim
    // ---]
    // Mostra texto na posição (x,y) da tela
    private void MostrarMensagem(int xpos, int ylin, string txt)
    {
      // Configura posição
      Rectangle position = new Rectangle(xpos, ylin, 0, 0);

      // Mostra texto
      dxfMensagem.DrawText(null, txt, position, 
        DrawTextFormat.NoClip, Color.Blue);
    } // MostrarMensagem().fim

    private void Tela_KeyDown(object sender, KeyEventArgs e)
    {
      
      if (e.KeyCode == Keys.Space) estadoLuz = !estadoLuz;
    } // Tela_KeyDown().fim

  } // fim da classe
} // fim do namespace

