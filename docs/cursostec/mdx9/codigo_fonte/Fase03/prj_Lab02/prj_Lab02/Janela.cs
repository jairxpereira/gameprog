// Prj_Lab01 - Arquivo: Janela.cs
// Esse projeto permite acompanhar visualmente a manipulação dos
// argumentos das matrizes de projeção, visualização e espaço mundial
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_Lab01
{
  public partial class Janela : Form
  {
    private Device device = null;     // Para criação do dispositivo gráfico

    // Branco cor de fundo para nossa janela       
    private int cor_fundo = System.Drawing.Color.CornflowerBlue.ToArgb(); 
    
    // Recipiente para os vértices do triângulo
    // SetPosition() desse formato de vértice aceita uma
    // estrutura Vector3 com uma posição (x, y, z)
    private CustomVertex.PositionColored[] triangulo=null;

    // Vetores para guardar a posição (x,y,z) dos vértices        
    Vector3 p0, p1, p2, p3, p4, p5;

    // Edição desligada: -1   Ligada: 1    
    private int triangulo_edit   = 1; // afeta Triângulo
    private int triangulo02_edit  = -1; // afeta device.Transform.World
    private int projet_edit = -1; // afeta device.Transform.Projection

    // Vetores que alimentam as matrizes
    private int vector_left_edit = 1;
    private int vector_center_edit = -1;
    private int vector_right_edit = -1;

    // Dados para a configuração da matriz de projeção
    float campo_visao = (float)Math.PI / 4; // Campo de visão
    float corte_perto = 1.0f;
    float corte_longe = 100.0f;

    // Dados para a configuração da matriz de visualização
    Vector3 cam_pos = new Vector3(0, 0, 5.0f); // Posição da camera
    Vector3 cam_alvo = new Vector3(0.0f, 0.0f, 0.0f); // Alvo da câmera
    Vector3 cam_orientacao = new Vector3(0, 1.0f, 0); // Orientação da câmera   

    // Dados para a configuração da matriz de espaço de mundo
    Vector3 mundo_pos        = new Vector3(0.0f, 0.0f, 0.0f); // Posição do mundo
    Vector3 mundo_escala       = new Vector3(1.0f, 1.0f, 1.0f); // Alvo do mundo
    Vector3 mundo_rotacao = new Vector3(0.0f, 0.0f, 0.0f); // Orientação do mundo   


    public Janela()
    {
      // Qualquer configuração em algum componente, faça depois dessa função!
      // Pois a geração automática de código pode suprimir algo que você
      // fizer antes dela
      InitializeComponent();

      // Toda renderização deverá ocorrer dentro do evento onPaint()
      // Isso evita interferência estrangeira de processamento default
      // do sistema Windows
      
      this.SetStyle(ControlStyles.AllPaintingInWmPaint, true);

      btnTriangulo.BackColor = Color.LightGreen;
      btnVectorLeft.BackColor = Color.LightGreen;

      // Posições para os 3 vértices do triangulo
      p0 = new Vector3(1.0f, 1.0f, 1.0f);
      p1 = new Vector3(-1.0f, -1.0f, 1.0f);
      p2 = new Vector3(1.0f, -1.0f, 1.0f);

      p3 = new Vector3(1.0f, 1.0f, 1.0f);
      p4 = new Vector3(-1.0f, 1.0f, 1.0f);
      p5 = new Vector3(-1.0f, -1.0f, 1.0f);

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
      device = new Device(adaptador, DeviceType.Hardware, Tela,
        CreateFlags.SoftwareVertexProcessing, pps);

    } // initGfx()

    private void AtualizarCamera()
    {
      // Dados para a configuração da matriz de projeção
      int largura = Tela.Width; // largura da janela
      int altura = Tela.Height;  // altura da janela      
      float aspecto = largura / altura; // aspecto dos gráficos   
       
      // Mostra a parte interna do polígono
      // Experimente desativar essa linha com a instrução de comentário      
      device.RenderState.CullMode = Cull.None;

      // Utiliza iluminação default
      // Experimente desativar essa linha com a instrução de comentário  
      device.RenderState.Lighting = false;

      // Configura a matriz de projeção
      device.Transform.Projection = Matrix.PerspectiveFovLH(campo_visao,
          aspecto, corte_perto, corte_longe);

      // Produz matrizes parciais para configurar a matriz de espaço mundial
      Matrix mtx_movimento = Matrix.Translation(mundo_pos);
      Matrix mtx_escala = Matrix.Scaling(mundo_escala);
      Matrix mtx_rotacao = Matrix.RotationYawPitchRoll(mundo_rotacao.X,
                                         mundo_rotacao.Y, mundo_rotacao.Z);
      
      // Combina com a multiplicação o efeito de todas as matrizes
      // e joga na matriz final de espaço mundial
      device.Transform.World = mtx_movimento * mtx_rotacao * mtx_escala;  
      

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
      device.DrawUserPrimitives(PrimitiveType.TriangleList, 2, triangulo);

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
      triangulo = new CustomVertex.PositionColored[6];



      // Os vértices estão alinhados na mesma posição de profundidade
      float zpos = 1.0f;

      // Define a cor dos vértices
      triangulo[0].Color = vermelho;
      triangulo[1].Color = verde;
      triangulo[2].Color = azul;


      triangulo[3].Color = vermelho;
      triangulo[4].Color = azul;
      triangulo[5].Color = verde;


      // Posição do primeiro vértice
      triangulo[0].SetPosition(p0);

      // Posição do primeiro vértice      
      triangulo[1].SetPosition(p1);

      // Posição do primeiro vértice      
      triangulo[2].SetPosition(p2);

      // Posição do primeiro vértice - segundo triângulo
      triangulo[3].SetPosition(p3);
      // Posição do primeiro vértice - segundo triângulo
      triangulo[4].SetPosition(p4);
      // Posição do primeiro vértice - segundo triângulo
      triangulo[5].SetPosition(p5);


    } // montar_triangulo().fim

   

    private void btnView_Click(object sender, EventArgs e)
    {
      triangulo_edit = triangulo_edit * -1;
      if (triangulo_edit == -1) btnTriangulo.BackColor = Color.LightGray;      
      if (triangulo_edit == 1) btnTriangulo.BackColor = Color.LightGreen;
      if (triangulo_edit == 1)      {
        loadTriangulo01Data();
      } // endif
    }

    private void loadTriangulo01Data()
    {
         
      txt_m11.Text = p0.X.ToString();
      txt_m12.Text = p0.Y.ToString();
      txt_m13.Text = p0.Z.ToString();

      txt_m21.Text = p1.X.ToString();
      txt_m22.Text = p1.Y.ToString();
      txt_m23.Text = p1.Z.ToString();

      txt_m31.Text = p2.X.ToString();
      txt_m32.Text = p2.Y.ToString();
      txt_m33.Text = p2.Z.ToString();
    } // loadTrianguloData().fim

    private void loadTriangulo02Data()
    {

      txtWorld_m11.Text = p3.X.ToString();
      txtWorld_m12.Text = p3.Y.ToString();
      txtWorld_m13.Text = p3.Z.ToString();

      txtWorld_m21.Text = p4.X.ToString();
      txtWorld_m22.Text = p4.Y.ToString();
      txtWorld_m23.Text = p4.Z.ToString();

      txtWorld_m31.Text = p5.X.ToString();
      txtWorld_m32.Text = p5.Y.ToString();
      txtWorld_m33.Text = p5.Z.ToString();
    } // loadTriangulo02Data().fim   


    private void btnVectorLeft_Click(object sender, EventArgs e)
    {
      vector_left_edit  = vector_left_edit * -1;
      if (vector_left_edit == -1) btnVectorLeft.BackColor = Color.LightGray;
      if (vector_left_edit == 1) btnVectorLeft.BackColor = Color.LightGreen;
    }

    private void btnUp_Click(object sender, EventArgs e)
    {
      
      // Controle de edição da matriz de visualização
      // device.Transform.View
      if (triangulo_edit == 1)
      {
        
        // edição de cam_pos
        if (vector_left_edit == 1)
        {
          if (chkx.Checked) p0.X += 0.5f;
          if (chky.Checked) p0.Y += 0.5f;
          if (chkz.Checked) p0.Z += 0.5f;
      
        } // endif vector_left_edit == 1

        // edição de cam_alvo
        if (vector_center_edit == 1)
        {
          if (chkx.Checked) p1.X += 0.5f;
          if (chky.Checked) p1.Y += 0.5f;
          if (chkz.Checked) p1.Z += 0.5f;
       
        } // endif vector_center_edit == 1

        // edição de cam_orientacao
        if (vector_right_edit == 1)
        {
          if (chkx.Checked) p2.X += 0.5f;
          if (chky.Checked) p2.Y += 0.5f;
          if (chkz.Checked) p2.Z += 0.5f;

        } // endif vector_right_edit == 1
        loadTriangulo01Data();
      } // endif view_edit == 1

      // Controle de edição da matriz de visualização
      // device.Transform.View
      if (triangulo02_edit == 1)
      {

        // edição de cam_pos
        if (vector_left_edit == 1)
        {
          if (chkx.Checked) p3.X += 0.5f;
          if (chky.Checked) p3.Y += 0.5f;
          if (chkz.Checked) p3.Z += 0.5f;

        } // endif vector_left_edit == 1

        // edição de cam_alvo
        if (vector_center_edit == 1)
        {
          if (chkx.Checked) p4.X += 0.5f;
          if (chky.Checked) p4.Y += 0.5f;
          if (chkz.Checked) p4.Z += 0.5f;

        } // endif vector_center_edit == 1

        // edição de cam_orientacao
        if (vector_right_edit == 1)
        {
          if (chkx.Checked) p5.X += 0.5f;
          if (chky.Checked) p5.Y += 0.5f;
          if (chkz.Checked) p5.Z += 0.5f;

        } // endif vector_right_edit == 1
        loadTriangulo02Data();
      } // endif view_edit == 1
    }

    private void btnReset_Click(object sender, EventArgs e)
    {
          

      // Reset na edição da matriz de visualização
      if (triangulo_edit == 1)
      {
        if (vector_left_edit == 1)
        {
          p0 = new Vector3(1.0f, 1.0f, 1.0f);
          } // endif

        if (vector_center_edit == 1)
        {
          p1 = new Vector3(-1.0f, -1.0f, 1.0f);          
        } // endif

        if (vector_right_edit == 1)
        {
          p2 = new Vector3(1.0f, -1.0f, 1.0f);
        } // endif 

        loadTriangulo01Data();
      } // endif

      
      // Reset na edição da matriz de visualização
      if (triangulo02_edit == 1)
      {
        if (vector_left_edit == 1)
        {
          p3 = new Vector3(1.0f, 1.0f, 1.0f);
          } // endif

        if (vector_center_edit == 1)
        {
          p4 = new Vector3(-1.0f, 1.0f, 1.0f);          
        } // endif

        if (vector_right_edit == 1)
        {
          p5 = new Vector3(-1.0f, -1.0f, 1.0f);
        } // endif 

        loadTriangulo02Data();
      } // endif

      
    }

    private void btnDown_Click(object sender, EventArgs e)
    {      
     

      // Controle de edição da matriz de visualização
      // device.Transform.View
      if (triangulo_edit == 1)
      {

        // edição de cam_pos
        if (vector_left_edit == 1)
        {
          if (chkx.Checked) p0.X -= 0.5f;
          if (chky.Checked) p0.Y -= 0.5f;
          if (chkz.Checked) p0.Z -= 0.5f;

        } // endif vector_left_edit == 1

        // edição de cam_alvo
        if (vector_center_edit == 1)
        {
          if (chkx.Checked) p1.X -= 0.5f;
          if (chky.Checked) p1.Y -= 0.5f;
          if (chkz.Checked) p1.Z -= 0.5f;

        } // endif vector_center_edit == 1

        // edição de cam_orientacao
        if (vector_right_edit == 1)
        {
          if (chkx.Checked) p2.X -= 0.5f;
          if (chky.Checked) p2.Y -= 0.5f;
          if (chkz.Checked) p2.Z -= 0.5f;

        } // endif vector_right_edit == 1
        loadTriangulo01Data();
      } // endif view_edit == 1

      // Controle de edição da matriz de visualização
      // device.Transform.View
      if (triangulo02_edit == 1)
      {

        // edição de cam_pos
        if (vector_left_edit == 1)
        {
          if (chkx.Checked) p3.X -= 0.5f;
          if (chky.Checked) p3.Y -= 0.5f;
          if (chkz.Checked) p3.Z -= 0.5f;

        } // endif vector_left_edit == 1

        // edição de cam_alvo
        if (vector_center_edit == 1)
        {
          if (chkx.Checked) p4.X -= 0.5f;
          if (chky.Checked) p4.Y -= 0.5f;
          if (chkz.Checked) p4.Z -= 0.5f;

        } // endif vector_center_edit == 1

        // edição de cam_orientacao
        if (vector_right_edit == 1)
        {
          if (chkx.Checked) p5.X -= 0.5f;
          if (chky.Checked) p5.Y -= 0.5f;
          if (chkz.Checked) p5.Z -= 0.5f;

        } // endif vector_right_edit == 1
        loadTriangulo02Data();
      } // endif view_edit == 1
    }

    private void btnVectorCenter_Click(object sender, EventArgs e)
    {
      vector_center_edit = vector_center_edit * -1;
      if (vector_center_edit == -1) btnVectorCenter.BackColor = Color.LightGray;
      if (vector_center_edit == 1) btnVectorCenter.BackColor = Color.LightGreen;
    }

    private void btnVectorRight_Click(object sender, EventArgs e)
    {
      vector_right_edit = vector_right_edit * -1;
      if (vector_right_edit == -1) btnVectorRight.BackColor = Color.LightGray;
      if (vector_right_edit == 1) btnVectorRight.BackColor = Color.LightGreen;
    }

    private void btnWorld_Click(object sender, EventArgs e)
    {
      triangulo02_edit = triangulo02_edit * -1;
      if (triangulo02_edit == -1) btnWorld.BackColor = Color.LightGray;
      if (triangulo02_edit == 1) btnWorld.BackColor = Color.LightGreen;
      if (triangulo02_edit == 1)
      {
        loadWorldData();
      } // endif
    }

    

    private void btnSair_Click(object sender, EventArgs e)
    {
      Application.Exit();
    }

    private void Janela_Load(object sender, EventArgs e)
    {
      loadTriangulo01Data();
      loadTriangulo02Data();
      
    } 


    private void loadWorldData()
    {      
      // Primeiro vector
      txtWorld_m11.Text = mundo_pos.X.ToString();
      txtWorld_m12.Text = mundo_pos.Y.ToString();
      txtWorld_m13.Text = mundo_pos.Z.ToString();

      // segundo vector
      txtWorld_m21.Text = mundo_rotacao.X.ToString();
      txtWorld_m22.Text = mundo_rotacao.Y.ToString();
      txtWorld_m23.Text = mundo_rotacao.Z.ToString();

      // segundo vector
      txtWorld_m31.Text = mundo_escala.X.ToString() ;
      txtWorld_m32.Text = mundo_escala.Y.ToString();
      txtWorld_m33.Text = mundo_escala.Z.ToString();
    } // getWorldMatrixData().fim        

  } // fim da classe
} // fim do namespace
