// Prj_Triangulo - Arquivo: Tela.cs
// Esse projeto ilustra como renderizar um triângulo
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_Triangulo
{
  public partial class Tela : Form
  {
    private Device device = null;     // Para criação do dispositivo gráfico
    private int cor_fundo = 0xFFFFFF; // Branco cor de fundo para nossa janela   

    // Vértices com configuração de posição e cor
    private CustomVertex.TransformedColored[] triangulo;

    // Construtor
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
    } // fim do construtor

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

      // Configura a camera
      SetupCamera();

    } // initGfx()

    private void SetupCamera()
    {

      // Dados para a configuração da matriz de projeção
      int largura = this.Width; // largura da janela
      int altura = this.Height;  // altura da janela      
      float aspecto = largura / altura; // aspecto dos gráficos      
      float campo_visao = (float)Math.PI / 4; // Campo de visão
      float corte_perto = 1.0f;
      float corte_longe = 100.0f;

      // Configura a matriz de projeção
      device.Transform.Projection = Matrix.PerspectiveFovLH(campo_visao,
          aspecto, corte_perto, corte_longe);

      // Dados para a configuração da matriz de visualização
      Vector3 cam_pos = new Vector3(0, 0, 18.0f); // Posição da camera
      Vector3 cam_alvo = new Vector3(0, 1.0f, 0); // Alvo da câmera
      Vector3 cam_orientacao = new Vector3(0, 1.0f, 0); // Orientação da câmera

      // Configura a matriz de visualização
      device.Transform.View = Matrix.LookAtLH(cam_pos, cam_alvo, cam_orientacao);
    }  // setupCamera()

    public void Renderizar()
    {
      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target, cor_fundo, 1.0f, 0);

      // Monta o contexto de renderização
      device.BeginScene();
      
      // (...) Todo o código de desenhar vai aqui 
      device.VertexFormat = CustomVertex.TransformedColored.Format;
      montar_triangulo();
      device.DrawUserPrimitives(PrimitiveType.TriangleList, 1, triangulo);     

      // Desmonta o contexto de renderização
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

    public void montar_triangulo()
    {
      // Pega as dimensões da tela
      int altura = this.Height;
      int largura = this.Width;

      // Cores para os vértices
      const int vermelho = 0xFF0000;
      const int verde = 0x00FF00;
      const int azul = 0x0000FF;

      // É necessário 3 vértices para compor o triângulo
      triangulo = new CustomVertex.TransformedColored[3];
      
      // Vetores para guardar a posição (x, y, z ) dos vértices e mais
      // uma informação de cor
      Vector4 p0, p1, p2;

      // O tamanho do triangulo vai adaptar-se interativamente
      // ao tamanho da janela
      float meia_largura = largura / 2.0f;
      float larg_80p = largura * 0.8f;
      float larg_20p = largura * 0.2f;
      float alt_80p = altura * 0.8f;

      // Posicionamento de profundidade
      float zpos = -0.5f;
      
      // Intensidade de propagação de cor do vértice
      float p0_cor_intensidade = 1.0f;
      float p1_cor_intensidade = 1.0f;
      float p2_cor_intensidade = 1.0f;

      // Define a cor dos vértices
      triangulo[0].Color = vermelho;
      triangulo[1].Color = verde;
      triangulo[2].Color = azul;

      // Posições para os 3 vértices do triangulo
      p0 = new Vector4(meia_largura, 50.0f, zpos, p0_cor_intensidade);
      p1 = new Vector4(larg_80p, alt_80p, zpos, p1_cor_intensidade);
      p2 = new Vector4(larg_20p, alt_80p, zpos, p2_cor_intensidade);

      // Posição do primeiro vértice
      triangulo[0].SetPosition(p0);

      // Posição do primeiro vértice      
      triangulo[1].SetPosition(p1);

      // Posição do primeiro vértice      
      triangulo[2].SetPosition(p2);      
      
    } // montar_triangulo().fim 

  } // fim da classe
} // fim do namespace
