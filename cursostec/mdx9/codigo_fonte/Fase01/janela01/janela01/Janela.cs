// Prj_Janela - Arquivo: Janela.cs
// Esse projeto ilustra como inicializar o motor gráfico do DirectX 9
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_Janela
{
  public partial class Tela : Form
  {
    private Device device = null;     // Para criação do dispositivo gráfico
    private int cor_fundo = 0xFFFFFF; // Branco cor de fundo para nossa janela   

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

      device.BeginScene();
      // (...) Todo o código de desenhar vai aqui   
      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // render()

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
