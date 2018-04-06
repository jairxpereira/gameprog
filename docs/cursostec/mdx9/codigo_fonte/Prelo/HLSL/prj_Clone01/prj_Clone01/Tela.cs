// prj_Clone01 - Arquivo: Tela.cs
// Esse projeto mostra como renderizar primitivas 3D
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;


namespace prj_Clone01
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


  public partial class Tela : Form
  {

    // Pega o tempo marcado no relógio do sistema 
    private static int InitialTickCount = Environment.TickCount;

    // Para criação do dispositivo gráfico
    private Device device = null;

    // Essa variável atualizada a cada ciclo ocasionará 
    // a animação do objeto
    private float angulo = 0.0f;

    // Variável para guardar uma malha 3d
    private Mesh objeto3D = null;

    // Vetores para a posição e rotação do objeto 3d
    Vector3 posicao, rotacao;

    // Variável global para propriedade dos objetos
    Propriedades3D g_props;

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

    } // initGfx()

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

    public void Renderizar()
    {

      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target, Color.White.ToArgb(), 1.0f, 0);

      device.BeginScene();
      // (...) Todo o código de desenhar vai aqui   

      // Aguarda um momento e gera um número de 0 a 5. 
      int index = ((Environment.TickCount - InitialTickCount) / 2000) % 6;

      // Atualiza a câmera
      AtualizarCamera();
      AtualizarLuz();

      switch (index)
      {

        case 0:
          objeto3D = Mesh.Box(device, 1.0f, 1.0f, 1.0f);
          posicao = new Vector3(0.0f, 0.0f, 2.0f);
          rotacao = new Vector3(-10, 10, 0);
          g_props = new Propriedades3D(posicao, rotacao);
          g_props.color = Color.Brown;
          desenharObjeto(objeto3D, g_props);
          this.Text = " prj_Clone01:  box";
          break;

        case 1:
          objeto3D = Mesh.Polygon(device, 2.0f, 8);
          posicao = new Vector3(0.0f, 0.0f, -5.0f);
          rotacao = new Vector3(-10, 10, 0);
          g_props = new Propriedades3D(posicao, rotacao);
          g_props.color = Color.DarkGreen;
          desenharObjeto(objeto3D, g_props);
          this.Text = " prj_Clone01:  Polygon";
          break;

        case 2:
          objeto3D = Mesh.Teapot(device);
          posicao = new Vector3(0.0f, 0.0f, -2.0f);
          rotacao = new Vector3(5, 0, 0);
          g_props = new Propriedades3D(posicao, rotacao);
          g_props.color = Color.Red;
          desenharObjeto(objeto3D, g_props);
          this.Text = " prj_Clone01:  Teapot";
          break;

        case 3:
          objeto3D = Mesh.Sphere(device, 2.0f, 32, 32);
          posicao = new Vector3(0.0f, 0.0f, -5.0f);
          rotacao = new Vector3(-10, 10, 0);
          g_props = new Propriedades3D(posicao, rotacao);
          g_props.color = Color.DarkOrange;
          desenharObjeto(objeto3D, g_props);
          this.Text = " prj_Clone01:  Sphere";
          break;

        case 4:
          objeto3D = Mesh.Torus(device, 0.5f, 1.0f, 32, 32);
          posicao = new Vector3(0.0f, 0.0f, -5.0f);
          rotacao = new Vector3(-10, 10, 0);
          g_props = new Propriedades3D(posicao, rotacao);
          g_props.color = Color.DarkRed;
          desenharObjeto(objeto3D, g_props);
          this.Text = " prj_Clone01:  Torus";
          break;

        case 5:
          objeto3D = Mesh.Cylinder(device, 0.5f, 1.0f, 5.0f, 32, 32);
          posicao = new Vector3(0.0f, 0.0f, -5.0f);
          rotacao = new Vector3(-10, 10, 0);
          g_props = new Propriedades3D(posicao, rotacao);
          g_props.color = Color.DarkViolet;
          desenharObjeto(objeto3D, g_props);
          this.Text = " prj_Clone01:  Cylinder";
          break;
      } // end switch 

      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar()

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

      // Prepara e aplica uma material na caixa
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

  } // fim da classe
} // fim do namespace

