// prj_Primitivas - Arquivo: Tela.cs
// Esse projeto mostra como renderizar outras primitivas
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_Primitivas
{
  public partial class Tela : Form
  {

    // Pega o tempo marcado no relógio do sistema
    private static int InitialTickCount = Environment.TickCount;

    // Quantidade vértices. Utilize múltiplos de 12
    private static int nVerticesQtd = 60;

    // Para criação do dispositivo gráfico
    private Device device = null;

    // Recipiente para os vértices dos triângulos
    // SetPosition() desse formato de vértice aceita uma
    // estrutura Vector3 com uma posição (x, y, z)
    private CustomVertex.PositionColored[] triangulo;

    // Memória ou buffer de vértices para o quadrado
    private VertexBuffer vbQuadrado = null;

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
      device = new Device(0, DeviceType.Hardware, this,
       CreateFlags.SoftwareVertexProcessing, pps);

      // Montamos inicialmente nossos triângulos 
      montar_triangulos();

      // O buffer de vértices vbQuadrado é criado.
      vbQuadrado = new VertexBuffer(typeof(CustomVertex.PositionColored),
         nVerticesQtd, device, Usage.Dynamic | Usage.WriteOnly,
         CustomVertex.PositionColored.Format, Pool.Default);

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

      // Mostra a parte interna do polígono
      // Experimente desativar essa linha com a instrução de comentário      
      device.RenderState.CullMode = Cull.None;

      // Utiliza iluminação default
      // Experimente desativar essa linha com a instrução de comentário  
      device.RenderState.Lighting = false;

      // Configura a matriz de projeção
      device.Transform.Projection = Matrix.PerspectiveFovLH(campo_visao,
          aspecto, corte_perto, corte_longe);

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
      device.Clear(ClearFlags.Target, 0xFFFFFF, 1.0f, 0);

      device.BeginScene();
      // (...) Todo o código de desenhar vai aqui   

      // Configura formato do vértice
      device.VertexFormat = CustomVertex.PositionColored.Format;

      // Atualiza a câmera
      AtualizarCamera();

      // O renderizador é informado da origem dos dados
      device.SetStreamSource(0, vbQuadrado, 0);

      // Configuração do tamanho do ponto desenhado
      device.RenderState.PointSize = 12.0f;

      // Aguarda um momento e gera um número de 0 a 5.
      int index = ((Environment.TickCount - InitialTickCount) / 2000) % 6;

      switch (index)
      {

        case 0: // PointList
          device.DrawPrimitives(PrimitiveType.PointList, 0, nVerticesQtd);
          this.Text = "prj_Primitivas: PointList";
          break;

        case 1: // LineList
          this.Text = "prj_Primitivas: LineList";
          device.DrawPrimitives(PrimitiveType.LineList, 0, nVerticesQtd / 2);
          break;

        case 2: // LineStrip
          this.Text = "prj_Primitivas: LineStrip";
          device.DrawPrimitives(PrimitiveType.LineStrip, 0, nVerticesQtd - 1);
          break;

        case 3: // TriangleList
          this.Text = "prj_Primitivas: TriangleList";
          device.DrawPrimitives(PrimitiveType.TriangleList, 0, nVerticesQtd / 3);
          break;

        case 4: // TriangleStrip
          this.Text = "prj_Primitivas: TriangleStrip";
          device.DrawPrimitives(PrimitiveType.TriangleStrip, 0, nVerticesQtd - 2);
          break;

        case 5: // TriangleFan
          this.Text = "prj_Primitivas: TriangleFan";
          device.DrawPrimitives(PrimitiveType.TriangleFan, 0, nVerticesQtd - 2);
          break;
      } // end switch

      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar().fim

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

      // Inicializa a array de vértices
      triangulo = new CustomVertex.PositionColored[nVerticesQtd];

      // Gera um gerador de número aleatórios
      Random sorteio = new Random();

      // Variáveis para o posicionamento dos vértices
      float xcol = 0.0f;
      float ylin = 0.0f;
      float zpos = 1.0f;

      // Para acessar o vértice mais adiante...
      int ndx = 0;

      // Distribuição circular dos vértices no espaço
      int passo = 360 / nVerticesQtd;

      // Vamos criar nVerticesQtd vértices em círculo
      for (float ncx = 0.0f; ncx < 360.0f; ncx += passo)
      {

        // Converte graus para radianos
        double radianos = ncx * (Math.PI / 180.0f);

        // (x,y) distribuidos de maneira circular
        xcol = (float)Math.Cos(radianos);
        ylin = (float)Math.Sin(radianos);

        // Configura a posição do vetor
        triangulo[ndx].SetPosition(new Vector3(xcol, ylin, zpos));

        // Configura cor com valor aleatório
        triangulo[ndx].Color = sorteio.Next(0xFFFFFF);

        // Coloca no centro o terceiro vértice de cada triângulo
        if (ndx % 3 == 0) triangulo[ndx].SetPosition(new Vector3(0, 0, 0));

        // Atualiza índice de controle do vértice
        ndx++;

      } // endfor
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
