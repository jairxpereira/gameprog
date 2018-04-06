// prj_HLSL02 - Arquivo: Tela.cs
// Esse projeto mostra como renderizar um mesh com hlsl
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_HLSL02
{
  // Estrutura para propriedades 3d do objeto
  // posição, rotação. A cor vai ser dada pelo Shader
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
    private Effect efeito = null;

    // Variável para guardar uma malha 3d 
    private Mesh objeto3D = null;

    // Vetores para a posição e rotação do objeto 3d
    Vector3 posicao, rotacao;

    // Variável global para propriedade dos objetos
    Propriedades3D g_props;

    // Matrizes para configuração de camera
    private Matrix mundo;
    private Matrix visao;
    private Matrix projecao;

    // Variáveis para compor animação simples
    private float nMovimento = 0.0f;
    private float nPasso = 0.01f;

    // Essa variável atualizada a cada ciclo ocasionará 
    // a animação do cilindro
    private float angulo = 0.0f;
    // (...)
    // ---]

    public Tela()
    {

      // Inicialização dos componentes.
      InitializeComponent();
      this.Size = new Size(320, 240);

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

      // Adaptador default, processamento de vértice no hardware,
      // janela (this), parâmetros de apresentação (pps)
      device = new Device(0, DeviceType.Hardware, this,
     CreateFlags.HardwareVertexProcessing | CreateFlags.PureDevice,
     pps);

      // Criando e configurando o cilindro    
      objeto3D = Mesh.Cylinder(device, 0.5f, 1.0f, 5.0f, 32, 32);
      posicao = new Vector3(0.0f, 0.0f, -5.0f);
      rotacao = new Vector3(-10, 10, 0);
      g_props = new Propriedades3D(posicao, rotacao);

      inicializarCamera();

      inicializarEfeito();

    } // initGfx().fim
    // ---]
    // [---
    private void inicializarEfeito()
    {
      // Cria o efeito
      efeito = Effect.FromFile(device, @"c:\gameprog\gdkmedia\shader\mesh_simples.fx",
    null, ShaderFlags.None, null);
      efeito.Technique = "MovimentoCor";

    } // InicializarEfeito().fim
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
      Vector3 cam_pos = new Vector3(0, 0, 5.0f); // Posição da camera
      Vector3 cam_alvo = new Vector3(0, 0.0f, 0); // Alvo da câmera
      Vector3 cam_orientacao = new Vector3(0, 1.0f, 0); // Orientação da câmera          

      // Configura a matriz de visualização
      visao = Matrix.LookAtLH(cam_pos, cam_alvo, cam_orientacao);

    }  // inicializarCamera().fim

    // [---
    public void Renderizar()
    {

      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.DarkGreen, 1.0f, 0);

      device.BeginScene();

      // Renderiza o objeto 3d utilizando o efeito
      int numPasses = efeito.Begin(0);
      for (int ncx = 0; ncx < numPasses; ncx++)
      {
        efeito.Pass(ncx);
        // <b>
        desenharObjeto(objeto3D, g_props);
        // </b>
      } // endfor

      efeito.End();
      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar().fim
    // ---]

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
    private void desenharObjeto(Mesh obj, Propriedades3D props)
    {

      // Ajusta rotação do objeto 3d 
      Matrix obj_rot = Matrix.RotationX(props.rotation.X) *
      Matrix.RotationY(props.rotation.Y + angulo) *
      Matrix.RotationZ(props.rotation.Z);

      // Ajusta posição do objeto
      Matrix obj_pos = Matrix.Translation(props.position);

      // Atualiza animação
      nMovimento += nPasso;
      if (nMovimento >= 1.0f) nPasso *= -1;
      if (nMovimento <= 0.0f) nPasso *= -1;
      angulo += 0.05f;

      // Tranfere posição e rotação para o mundo 
      mundo = obj_rot * obj_pos;

      // Atualiza variáveis do efeito
      Matrix Camera = mundo * visao * projecao;
      efeito.SetValue("nMovimento", nMovimento);
      efeito.SetValue("Camera", Camera);

      // Renderiza o mesh 
      obj.DrawSubset(0);
    } // desenharObjeto().fim
    // ---]

  } // fim da classe
} // fim do namespace
