// prj_HLSL01 - Arquivo: Tela.cs
// Esse projeto mostra como renderizar um quadrado com HLSL
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_HLSL01
{
  // [---
  public partial class Tela : Form
  {
    // Para criação do dispositivo gráfico
    private Device device = null;
    // <b>
    // Esse objeto aplica o efeito produzido com HLSL
    private Effect efeito = null;
    
    // O VertexShader precisa saber como cada vértice está estruturado
    private VertexDeclaration decl = null;
    
    // Nossas matrizes para compor a Camera no Vertexshader
    private Matrix mundo;
    private Matrix visao;
    private Matrix projecao;

    // Variável para provocar mudanças de cor no VertexShader
    private float nMovimento = 0.0f;
    private float nPasso = 0.01f;
    // </b>

    // Recipiente para os vértices dos triângulos
    // SetPosition() desse formato de vértice aceita uma
    // estrutura Vector3 com uma posição (x, y, z)
    private CustomVertex.PositionOnly[] triangulo;

    // Memória ou buffer de vértices para o quadrado
    private VertexBuffer vbQuadrado = null;

    // Essa variável atualizada a cada ciclo ocasionará 
    // a animação do quadrado
    private float angulo = 0.0f;
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

      // Adaptador default, processamento no hardware, processamento de vértice 
      // no software, janela (this), parâmetros de apresentação (pps)
         device = new Device(0, DeviceType.Hardware, this,
        CreateFlags.HardwareVertexProcessing | CreateFlags.PureDevice,
        pps);

      // Montamos inicialmente nossos triângulos 
      montar_triangulos();

      // Inicializamos o buffer de vértices
      inicializarVertexBuffer();

      // Inicializa o efeito
      inicializarEfeito();

      // Declara o uso dos vértices
      DeclararVertices();

      // Inicializa a Camera para o VertexShader
      inicializarCamera();

    } // initGfx().fim
    // ---]
    // [---
    private void DeclararVertices()
    {
      // Cria os elementos que informam a estruturação dos vértices
      VertexElement[] Elementos;
      VertexElement elemento;

      // Configura a informação de um elemento
      elemento = new VertexElement(0, 0, DeclarationType.Float3 ,
        DeclarationMethod.Default , DeclarationUsage.Position  , 0);

      // Configura a informação de todos os elementos
      Elementos = new VertexElement[] { elemento, VertexElement.VertexDeclarationEnd };

      // Configura finalmente a declação de dados
      decl = new VertexDeclaration(device, Elementos);
    } // DeclararVertices().fim
    // ---]
    // [---
    private void inicializarEfeito()
    {
      // Carrega o efeito do disco
      efeito = Effect.FromFile(device, @"c:\gameprog\gdkmedia\shader\simples.fx",
    null, ShaderFlags.None , null);

      // Seleciona a técnica de renderização
      efeito.Technique = "MovimentoCor";

    } // InicializarEfeito().fim
    // ---]   
    // [---
    private void inicializarCamera()
    {
      // Dados para a configuração da matriz de projeção
      int largura = this.Width; // largura da janela
      int altura = this.Height;  // altura da janela      
      float aspecto = largura / altura; // aspecto dos gráficos      
      float campo_visao = (float)Math.PI / 4; // Campo de visão
      float corte_perto = 1.0f;
      float corte_longe = 100.0f;

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
    // ---]
    // [---
    private void AtualizarCamera()
    {
      // Atualiza cor
      nMovimento += nPasso;
      if (nMovimento >= 1.0f) nPasso *= -1;
      if (nMovimento <= 0.0f) nPasso *= -1;

      // Atualiza ângulo
      angulo += 0.05f;
      mundo = Matrix.RotationZ(angulo);

      // Atualiza variáveis do efeito
      Matrix camera = mundo * visao * projecao;
      efeito.SetValue("nMovimento", nMovimento);
      efeito.SetValue("Camera", camera);

    } // AtualizarCamera().fim
    // ---]
    // [---
    public void Renderizar()
    {

      // Atualiza a Camera no VertexShader
      AtualizarCamera();

      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target, Color.DarkGreen, 1.0f, 0);

      device.BeginScene();

      // O renderizador é informado da origem dos dados
      device.SetStreamSource(0, vbQuadrado, 0);

      // O VertexShader é informado da estruturação dos vértices
      device.VertexDeclaration = decl;

      // Renderiza o quadrado usando o efeito
      int numPasses = efeito.Begin(0);
      for (int ncx = 0; ncx < numPasses; ncx++)
      {
        // Renderiza uma etapa no VertexShader
        efeito.Pass(ncx);       

        // Renderiza a primitiva
        device.DrawPrimitives(PrimitiveType.TriangleList, 0, 2);

      } // endfor

      // Finaliza o efeito
      efeito.End();

      // Finaliza a cena
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


    public void montar_triangulos()
    {
      // É necessário 3 vértices para compor cada triângulo
      triangulo = new CustomVertex.PositionOnly[6];

      // Vetores para guardar a posição (x,y,z) dos vértices        
      Vector3 p0, p1, p2, p3, p4, p5;

      // Os vértices estão alinhados na mesma posição de profundidade
      float zpos = 1.0f;

      // Posições para os 3 vértices do triangulo
      p0 = new Vector3(-1.0f, 1.0f, zpos);
      p1 = new Vector3(-1.0f, -1.0f, zpos);
      p2 = new Vector3(1.0f, -1.0f, zpos);

      // Posições para os 3 vértices do segundo triangulo
      p3 = new Vector3(-1.0f, 1.0f, zpos);
      p4 = new Vector3(1.0f, -1.0f, zpos);
      p5 = new Vector3(1.0f, 1.0f, zpos);

      // Posição do primeiro vértice
      triangulo[0].SetPosition(p0);
      triangulo[1].SetPosition(p1);
      triangulo[2].SetPosition(p2);

      triangulo[3].SetPosition(p3);
      triangulo[4].SetPosition(p4);
      triangulo[5].SetPosition(p5);

    } // montar_triangulos().fim 

    // Remonta o buffer de vértice no evento onCreate
    private void quandoVertexBufferCriado(object sender, EventArgs e)
    {
      int nInicioDeslocamentoTrancado = 0;
      VertexBuffer buffer = (VertexBuffer)sender;
      buffer.SetData(triangulo, nInicioDeslocamentoTrancado, LockFlags.None);

    } // quandoVertexBufferCriado().fim    
    
    private void inicializarVertexBuffer()
    {
      // O buffer de vértices vbQuadrado é criado.
      vbQuadrado = new VertexBuffer(typeof(CustomVertex.PositionOnly),
         6, device, Usage.Dynamic | Usage.WriteOnly,
         CustomVertex.PositionOnly.Format,
         Pool.Default);

      // O buffer de vértices recebe os vértices da forma geométrica
      vbQuadrado.SetData(triangulo, 0, LockFlags.None);

      // O buffer de vértices recebe a função quandoVertexBufferCriado()
      // para responder ao evento onCreate() gerado pelo dispositivo
      vbQuadrado.Created += new EventHandler(this.quandoVertexBufferCriado);
    } // inicializarVertexBuffer().fim    
   
  } // fim da classe
} // fim do namespace
