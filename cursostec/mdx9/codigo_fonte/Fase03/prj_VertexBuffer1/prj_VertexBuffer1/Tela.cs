// prj_VertexBuffer1 - Arquivo: Tela.cs
// Esse projeto mostra como utilizar o recipiente de vértices
// produzido pela classe VertexBuffer.
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_VertexBuffer1
{
  public partial class Tela : Form
  {
    // Para criação do dispositivo gráfico
    private Device device = null;

    // Branco cor de fundo para nossa janela 
    private int cor_fundo = 0xFFFFFF;

    // Recipiente para os vértices dos triângulos
    // SetPosition() desse formato de vértice aceita uma
    // estrutura Vector3 com uma posição (x, y, z)
    private CustomVertex.PositionColored[] triangulo;

    // Memória ou buffer de vértices para o quadrado
    private VertexBuffer vbQuadrado = null;

    // Essa variável atualizada a cada ciclo ocasionará 
    // a animação do quadrado
    private float angulo = 0.0f;

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

      // Montamos inicialmente nossos triângulos 
      montar_triangulos();

      // O buffer de vértices vbQuadrado é criado.
      vbQuadrado = new VertexBuffer(typeof(CustomVertex.PositionColored),
         6, device, Usage.Dynamic | Usage.WriteOnly,
         CustomVertex.PositionColored.Format,
         Pool.Default);

      // O buffer de vértices recebe os vértices da forma geométrica
      vbQuadrado.SetData(triangulo, 0, LockFlags.None);

      // O buffer de vértices recebe a função quandoVertexBufferCriado()
      // para responder ao evento onCreate() gerado pelo dispositivo
      vbQuadrado.Created += new EventHandler(this.quandoVertexBufferCriado);

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
      device.VertexFormat = CustomVertex.PositionColored.Format;

      // Atualiza a câmera
      AtualizarCamera();

      // O renderizador é informado da origem dos dados
      int nStream = 0;
      int nDeslocamento = 0;
      device.SetStreamSource(nStream, vbQuadrado, nDeslocamento);

      // O quadrado é aqui renderizado
      device.DrawPrimitives(PrimitiveType.TriangleList, nDeslocamento, 2);

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
      // Cores para os vértices
      const int vermelho = 0xFF0000;
      const int verde = 0x00FF00;
      const int azul = 0x0000FF;

      // É necessário 3 vértices para compor cada triângulo
      triangulo = new CustomVertex.PositionColored[6];

      // Vetores para guardar a posição (x,y,z) dos vértices        
      Vector3 p0, p1, p2, p3, p4, p5;

      // Os vértices estão alinhados na mesma posição de profundidade
      float zpos = 1.0f;

      // Define a cor dos vértices
      triangulo[0].Color = vermelho;
      triangulo[1].Color = verde;
      triangulo[2].Color = azul;

      triangulo[3].Color = vermelho;
      triangulo[4].Color = azul;
      triangulo[5].Color = verde;

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


  } // fim da classe
} // fim do namespace
