// Prj_Triangulo3d - Arquivo: Tela.cs
// Esse projeto ilustra como renderizar um triângulo 3d
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_Triangulo3d
{
  public partial class Tela : Form
  {
    private Device device = null;     // Para criação do dispositivo gráfico
    private int cor_fundo = 0xFFFFFF; // Branco cor de fundo para nossa janela       
    
    // Recipiente para os vértices do triângulo
    // SetPosition() desse formato de vértice aceita uma
    // estrutura Vector3 com uma posição (x, y, z)
    private CustomVertex.PositionColored[] triangulo;
    
    // Essa variável atualizada a cada ciclo ocasionará a animação
    // do triângulo
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
      angulo += 0.1f;

      // Mostra a parte interna do polígono
      // Experimente desativar essa linha com a instrução de comentário      
      device.RenderState.CullMode = Cull.None;
      
      // Utiliza iluminação default
      // Experimente desativar essa linha com a instrução de comentário  
      device.RenderState.Lighting = false;

      // Configura a matriz de projeção
      device.Transform.Projection = Matrix.PerspectiveFovLH(campo_visao,
          aspecto, corte_perto, corte_longe);    

      // Cálculo de rotação dos eixos
      float xcam_rot, ycam_rot, zcam_rot, angulo_final;      
      xcam_rot = angulo / ((float)Math.PI * 2.0f);
      ycam_rot = angulo / ((float)Math.PI * 4.0f);
      zcam_rot = angulo / ((float)Math.PI * 6.0f);
      angulo_final = angulo / ((float)Math.PI);

      // Estabelece um vetor de rotação nos eixos x, y, z)
      Vector3 cam_rot = new Vector3( xcam_rot, ycam_rot, zcam_rot);

      // Rotaciona o triangulo indiretamente através da rotação dos
      // eixos da matriz mundial.
      device.Transform.World = Matrix.RotationAxis(cam_rot, angulo_final);      

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
      
      // Monta o triângulo
      montar_triangulo();

      // Atualiza a câmera
      AtualizarCamera();

      // Renderiza o triângulo
      device.DrawUserPrimitives(PrimitiveType.TriangleList, 1, triangulo);

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


    public void montar_triangulo()
    {     
      // Cores para os vértices
      const int vermelho = 0xFF0000;
      const int verde = 0x00FF00;
      const int azul = 0x0000FF;

      // É necessário 3 vértices para compor o triângulo
      triangulo = new CustomVertex.PositionColored[3];

      // Vetores para guardar a posição (x,y,z) dos vértices        
      Vector3 p0, p1, p2;      

      // Os vértices estão alinhados na mesma posição de profundidade
      float zpos = 1.0f;     

      // Define a cor dos vértices
      triangulo[0].Color = vermelho;
      triangulo[1].Color = verde;
      triangulo[2].Color = azul;

      // Posições para os 3 vértices do triangulo
      p0 = new Vector3(0.0f,  1.0f,   zpos);
      p1 = new Vector3(-1.0f, -1.0f,  zpos);
      p2 = new Vector3(1.0f,  -1.0f,  zpos);
      
      // Posição do primeiro vértice
      triangulo[0].SetPosition(p0);

      // Posição do primeiro vértice      
      triangulo[1].SetPosition(p1);

      // Posição do primeiro vértice      
      triangulo[2].SetPosition(p2);

    } // montar_triangulo().fim 

  } // fim da classe
} // fim do namespace
