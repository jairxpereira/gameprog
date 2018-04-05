// Prj_Textura - Arquivo: Tela.cs
// Esse projeto ilustra como renderizar um quadrado com textura
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_Textura
{
  public partial class Tela : Form
  {
    // Para criação do dispositivo gráfico
    private Device device = null;
    
    // Branco cor de fundo para nossa janela       
    private int cor_fundo = 0xFFFFFF; 

    // Recipiente para os vértices dos triângulos 
    private CustomVertex.PositionTextured[] triangulo;

    // Referência da textura
    private Texture tex = null;
    
    // Buffer de vértices para o quadrado
    private VertexBuffer vbQuadrado = null;
    
    // Caminho de ligação dos vértices para o quadrado
    private short[] ndxQuadrado = null;

    // Buffer de índices para o quadrado
    private IndexBuffer ibQuadrado = null;

    // Essa variável atualizada a cada ciclo ocasionará a animação
    // do quadrado texturizado
    private float angulo = 0.0f;

    public Tela()
    {
      // Qualquer configuração em algum componente, faça depois dessa função!
      // Pois a geração automática de código pode suprimir algo que você
      // fizer antes dela
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

      // Adaptador default, processamento no hardware, processamento de vértice no
      // software, janela (this), parâmetros de apresentação (pps)
      int adaptador = 0;
      device = new Device(adaptador, DeviceType.Hardware, this,
        CreateFlags.SoftwareVertexProcessing, pps);

      // Carregando a textura
      tex = new Texture(device, 
        new Bitmap(this.GetType(), "textura2x2.png"), 
        0, Pool.Managed);     
      
      // Configuração dos vértices no espaço 3d com mapeamento da textura
      montar_triangulos();

      // ****** Montagem do buffer de vértices (vertexbuffer) *****
      // O buffer de vértices vbQuadrado é criado. 
      vbQuadrado = new VertexBuffer(typeof(CustomVertex.PositionTextured),
      4, device, Usage.Dynamic | Usage.WriteOnly,
      CustomVertex.PositionTextured.Format,
      Pool.Default);

      // Joga os vértices no buffer de vértices
      vbQuadrado.SetData(triangulo, 0, LockFlags.None);

      // configura o método calback da recriação do buffer de vértices 
      vbQuadrado.Created += new EventHandler(this.quandoVertexBufferCriado);

     
      // ****** Montagem do buffer de índices (indexbuffer) *****
      // Caminho de ligação dos vértices para montar o quadrado
      // 0,1,2 - Primeiro triângulo   2,3,0 - Segundo triângulo
      ndxQuadrado = new short[] { 0, 1, 2, 2, 3, 0 };

      // Inicialização do buffer de índices
      ibQuadrado = new IndexBuffer(typeof(short),
        ndxQuadrado.Length, device, Usage.Dynamic | Usage.WriteOnly, 
        Pool.Default);

      // Joga dentro do buffer de índices os elementos da array ndxQuadrado
      ibQuadrado.SetData(ndxQuadrado, 0, LockFlags.None);

      // configura o método calback da recriação do buffer de índices
      ibQuadrado.Created += new EventHandler(this.quandoIndexBufferCriado);

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

      // Utiliza iluminação default
      // Experimente desativar essa linha com a instrução de comentário  
      device.RenderState.Lighting = false;

      // Configura a matriz de projeção
      device.Transform.Projection = Matrix.PerspectiveFovLH(campo_visao,
          aspecto, corte_perto, corte_longe);

      // Rotaciona o triangulo indiretamente através da rotação dos
      // eixos da matriz mundial.
      device.Transform.World = Matrix.RotationZ(angulo);

      // Dados para a configuração da matriz de visualização
      Vector3 cam_pos = new Vector3(0, 0, 5.0f); // Posição da camera
      Vector3 cam_alvo = new Vector3(0, 0.0f, 0); // Alvo da câmera
      Vector3 cam_orientacao = new Vector3(0, 1.0f, 0); // Orientação da câmera          

      // Configura a matriz de visualização
      device.Transform.View = Matrix.LookAtLH(cam_pos, cam_alvo, cam_orientacao);
    }  // AtualizarCamera()

    public void Renderizar()
    {
      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target, cor_fundo, 1.0f, 0);

      device.BeginScene();
      // (...) Todo o código de desenhar vai aqui   

      // Configura formato do vértice
      device.VertexFormat = CustomVertex.PositionTextured.Format;

      // Atualiza a câmera
      AtualizarCamera();
      
      // Configura a fonte de vértices
      device.SetStreamSource(0, vbQuadrado, 0);
      
      // Configura a fonte de índices
      device.Indices = ibQuadrado;

      // Configura a textura
      int nEstagio = 0;
      device.SetTexture(nEstagio, tex);

      // Renderiza o quadrado
      int verticesQtd = triangulo.Length;
      int verticeInicial = 0;
      int verticeMenorIndice = 0;
      int primitivasQtd = ndxQuadrado.Length / 3;
      device.DrawIndexedPrimitives(PrimitiveType.TriangleList, verticeInicial, 
        verticeMenorIndice, verticesQtd, 0, primitivasQtd );

      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar()

    protected override void OnPaint(PaintEventArgs e)
    {
      // Trate outros processos padrões
      base.OnPaint(e);

      // Renderize a cena
      this.Renderizar();

      // Invalide para chamar novamente onPaint()
      this.Invalidate();
    } // onPaint().fim 


    public void montar_triangulos()
    {

      // É necessário apenas 4 vértices para compor o quadrado 
      // utilizando o buffer de índices
      triangulo = new CustomVertex.PositionTextured[4];

      // Os vértices estão alinhados na mesma posição de profundidade
      float zpos = 1.0f;

      // p0      
      triangulo[0] = new CustomVertex.PositionTextured(1.0f, 1.0f, zpos, 0.0f, 0.0f);

      // p1
      triangulo[1] = new CustomVertex.PositionTextured(-1.0f, 1.0f, zpos, 0.5f, 0.0f);

      // p2
      triangulo[2] = new CustomVertex.PositionTextured(-1.0f, -1.0f, zpos, 0.5f, 0.5f);

      // p3
      triangulo[3] = new CustomVertex.PositionTextured(1.0f, -1.0f, zpos, 0.0f, 0.5f);

    } // montar_triangulos().fim 

    
    // Recupera o buffer de vértices
    private void quandoVertexBufferCriado(object sender, EventArgs e)
    {
      VertexBuffer buffer = (VertexBuffer)sender;
      buffer.SetData(triangulo, 0, LockFlags.None);

    } // quandoVertexBufferCriado().fim

    
    // Recupera o buffer de índices
    private void quandoIndexBufferCriado(object sender, EventArgs e)
    {
      IndexBuffer buffer = (IndexBuffer)sender;
      buffer.SetData(ndxQuadrado, 0, LockFlags.None);

    } // quandoIndexBufferCriado()


  } // fim da classe
} // fim do namespace
