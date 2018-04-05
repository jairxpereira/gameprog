// prj_ModificarTextura - Arquivo: Tela.cs
// Esse projeto mostra como modificar a textura
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_ModificarTextura
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

  // [---
  public partial class Tela : Form
  {
    // Para criação do dispositivo gráfico
    private Device device = null;

    // Essa variável atualizada a cada ciclo ocasionará 
    // a animação do objeto
    private float angulo = 0.0f;

    // Variável para guardar uma malha 3d
    private Mesh objeto3D = null;

    // Recipiente de materiais do mesh
    private Material[] g_meshMtl = null;

    // Recipiente de texturas do mesh
    private Texture[] g_meshTex = null;

    // Pasta de localização do arquivo mesg e sua textura
    private string diretorioBase = null;

    // Vetores para a posição e rotação do objeto 3d
    Vector3 posicao, rotacao;

    // Variável global para propriedade dos objetos
    Propriedades3D g_props;

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

    public void initGfx()
    {

      // Configuração dos parâmetros de apresentação
      PresentParameters pps = new PresentParameters();
      pps.Windowed = true;
      pps.SwapEffect = SwapEffect.Discard;

      // Ativando o buffer de profundidade
      pps.EnableAutoDepthStencil = true;
      pps.AutoDepthStencilFormat = DepthFormat.D16;

      // Adaptador default, processamento no hardware, processamento de vértice 
      // no software, janela (this), parâmetros de apresentação (pps)
      int adaptador = 0;
      device = new Device(adaptador, DeviceType.Hardware, this,
        CreateFlags.SoftwareVertexProcessing, pps);

      diretorioBase = @"c:\Gameprog\Gdkmedia\Modelos\Tiny\";
      CarregarModelo(diretorioBase, "tiny.x");

    } // initGfx()

    // [---
    private void CarregarModelo(string diretorioBase, string arquivo)
    {
      // Composição do nome final do arquivo
      string caminhoFinal = diretorioBase + arquivo;

      // Quantidade de materiais\texturas encontrados no modelo3d
      int nTam = 0;

      // Pacote de materiais e texturas do modelo 3d
      ExtendedMaterial[] xMtl;

      // Carrega modelo 3d com suas texturas e materiais
      objeto3D = Mesh.FromFile(caminhoFinal, MeshFlags.Managed,
        device, out xMtl);

      // Verifica quantidade de texturas\materiais do modelo
      nTam = xMtl.Length;

      // Carrega as texturas caso nTam > 0
      if ((xMtl != null) && (nTam > 0))
      {

        // Inicializa as variáveis arrays de materiais e texturas
        g_meshMtl = new Material[nTam];
        g_meshTex = new Texture[nTam];

        for (int ncx = 0; ncx < nTam; ncx++)
        {
          // Carrega materiais
          g_meshMtl[ncx] = xMtl[ncx].Material3D;

          // Cria uma nova textura e preenche com cores aleatórias
          g_meshTex[ncx] = new Texture(device, 256, 256, 1, 0,
            Format.X8R8G8B8, Pool.Managed);
          ModificarTextura(g_meshTex[ncx]);

        } // endfor (materiais\texturas)
      } // endif (verificação de texturas\materiais presentes)
    } // CarregarModelo().fim
    // ---]

    // [---
    private void ModificarTextura(Texture textura)
    {
      // Gerador de números aleatórios
      Random sorteio = new Random();
      
      // Componentes rgb para montar depois a cor final
      byte r, g, b;

      // Obtém a descrição da textura
      SurfaceDescription desc = textura.GetLevelDescription(0);
      
      // Obtém a área de dados da textura
      uint[,] cores;
      cores = (uint[,]) textura.LockRectangle(typeof(uint), 0,
          LockFlags.None, desc.Width, desc.Height);

      // Escreve uma cor aleatória em cada ponto da textura
      for (int linha = 0; linha < desc.Width; linha++)
      {
        for (int coluna = 0; coluna < desc.Height; coluna++)
        {
          // Produz uma cor aleatória
          r = (byte) sorteio.Next(255);
          g = (byte) sorteio.Next(255);
          b = (byte) sorteio.Next(255);
          Color cor = Color.FromArgb(r, g, b);

          // Escreve a cor na área de dados da textura
          cores[linha, coluna] = (uint) cor.ToArgb();

        } // endfor coluna
      } // endfor linha

      // Libera a textura para o sistema\placa de vídeo
      textura.UnlockRectangle(0);

    } // ModificarTextura().fim
    // ---]

    // [---
    private void desenharObjeto(Mesh obj, Propriedades3D props)
    {

      // Ajusta rotação do objeto 3d
      Matrix obj_rot = Matrix.RotationX(props.rotation.X + angulo) *
        Matrix.RotationY(props.rotation.Y) *
        Matrix.RotationZ(props.rotation.Z);

      // Ajusta posição do objeto 3d
      Matrix obj_pos = Matrix.Translation(props.position);

      // Tranfere posição e rotação para o mundo
      device.Transform.World = obj_rot * obj_pos;

      // Prepara e aplica uma material\textura no objeto
      for (int ncx = 0; ncx < g_meshMtl.Length; ncx++)
      {
        // Informa ao dispositivo o material a ser utilizado
        // na renderização    
        device.Material = g_meshMtl[ncx];
        // <b>
        // Modifica a textura 
        ModificarTextura(g_meshTex[ncx]);
        // </b>
        device.SetTexture(0, g_meshTex[ncx]);

        // Renderiza o mesh
        obj.DrawSubset(ncx);
      } // endfor

    } // desenharObjeto()
    // ---]

    private void AtualizarCamera()
    {
      // Dados para a configuração da matriz de projeção
      int largura = this.Width; // largura da janela
      int altura = this.Height;  // altura da janela      
      float aspecto = largura / altura; // aspecto dos gráficos      
      float campo_visao = (float)Math.PI / 4; // Campo de visão
      float corte_perto = 1.0f;

      // Essa variável foi modificar para acomodar o tamanho
      // do modelo
      float corte_longe = 10000.0f;

      // Atualiza angulo para dar movimento ao objeto 3d
      angulo += 0.01f;

      // Mostra a parte interna do polígono
      // Experimente desativar essa linha com a instrução de comentário      
      device.RenderState.CullMode = Cull.None;

      // Configura a matriz de projeção
      device.Transform.Projection = Matrix.PerspectiveFovLH(campo_visao,
          aspecto, corte_perto, corte_longe);

      // Dados para a configuração da matriz de visualização
      // O eixo z foi modificar para comportar o tamanho do modelo
      Vector3 cam_pos = new Vector3(0, 0, 600.0f);

      Vector3 cam_alvo = new Vector3(0.0f, 0.0f, 0.0f);
      Vector3 cam_orientacao = new Vector3(0, 1.0f, 0);

      // Configura a matriz de visualização
      device.Transform.View = Matrix.LookAtLH(cam_pos, cam_alvo, cam_orientacao);
    }  // AtualizarCamera()

    // [---
    public void Renderizar()
    {
      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target | ClearFlags.ZBuffer,
        Color.White.ToArgb(), 1.0f, 0);

      device.BeginScene();
      // (...) Todo o código de desenhar vai aqui   

      // Atualiza a câmera
      AtualizarCamera();
      AtualizarLuz();

      // Desenha o primeiro mesh
      posicao = new Vector3(-150.0f, 40.0f, -200.0f);
      rotacao = new Vector3(0, 0, 0);
      g_props = new Propriedades3D(posicao, rotacao);
      // <b>
      // Modifica propriedades da textura
      device.SamplerState[0].MagFilter = TextureFilter.Linear;
      // </b>
      desenharObjeto(objeto3D, g_props);
      
      // Desenha um segundo mesh
      g_props.position.X = 100.0f; g_props.position.Y = 0.2f;
      // <b>
      // Modifica propriedades da textura
      device.SamplerState[0].MagFilter = TextureFilter.None ;
      // </b>
      desenharObjeto(objeto3D, g_props);

      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar()
    // ---]

    
    // Configuração de luz
    private void AtualizarLuz()
    {
      device.RenderState.Ambient = Color.White;
      device.RenderState.Lighting = true;
      device.Lights[0].Type = LightType.Directional;
      device.Lights[0].Diffuse = Color.White;
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

