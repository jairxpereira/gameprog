// prj_Explodir - Arquivo: Tela.cs
// Esse projeto mostra como explodir em vários pedaços
// um modelo 3d.
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace prj_Explodir
{
  // Estrutura para propriedades 3d do objeto
  // posição e rotação
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

    // Essa variável atualizada a cada ciclo ocasionará 
    // a animação do objeto
    private float angulo = 0.0f;

    // Variáveis para guardar a malha 3d original e seus pedaços
    private Mesh objeto3D = null;
    private Mesh[] pedacos = null;

    // Recipiente de materiais do mesh
    private Material[] g_meshMtl = null;

    // Recipiente de texturas do mesh
    private Texture[] g_meshTex = null;

    // Pasta de localização do arquivo mesh e sua textura
    private string diretorioBase = null;    

    // Variável global para o posicionamento dos objetos 3d
    Propriedades3D[] g_props;

    // Este objeto Random será utilizado para produzir valores
    // para o posicionamento (x,y,z) dos sub-objetos 3d criados
    Random sorteio;
    // (...)
    // ---]

    public Tela()
    {

      // Inicialização dos componentes.
      InitializeComponent();
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

      // Adaptador default, processamento no hardware, processamento de vértice 
      // no software, janela (this), parâmetros de apresentação (pps)      
      device = new Device( 0, DeviceType.Hardware, this,
        CreateFlags.SoftwareVertexProcessing, pps);

      // Carrega o modelo
      diretorioBase = @"c:\Gameprog\Gdkmedia\Modelos\Tiny\";
      CarregarModelo(diretorioBase, "tiny.x");

      // Inicializa o objeto Random
      sorteio = new Random();

      // O modelo é quebrado em muitos pedaços nesta função.
      explodirModelo();

    } // initGfx().fim
    // ---]
    // [---
    private void explodirModelo()
    {
      // Os valores destas variáveis serão sorteados
      float xruido, yruido, zruido;

      // Tamanho máximo em vértices do sub-mesh gerado
      int nVerticesMax = 40;

      // Quebra o objeto 3d em pedaços menores
      pedacos = Mesh.Split(objeto3D, null, nVerticesMax, objeto3D.Options.Value);

      // Inicializa a array de posicionamento conforme a quantidade
      // de pedaços gerada
      g_props = new Propriedades3D[pedacos.Length];

      // Sorteia para cada pedaço seu respectivo posicionamento (x,y,z)
      for (int ncx = 1; ncx < g_props.Length; ncx++)
      {
        // Sorteia (x, y, z) para cada pedaço
        xruido = 100.0f * (float)sorteio.NextDouble();
        yruido = 100.0f * (float)sorteio.NextDouble();
        zruido = 100.0f * (float)sorteio.NextDouble();

        // Configura posicionamento para cada pedaço
        g_props[ncx].position.X = xruido;
        g_props[ncx].position.Y = yruido;
        g_props[ncx].position.Z = zruido;

        // A rotação de cada um será zerada
        g_props[ncx].rotation = new Vector3(0.0f, 0.0f, 0.0f);

      } // endfor

      // Dispensa o objeto 3d original
      objeto3D.Dispose();

    } // explodirModelo().fim
    // ---]
    private void AtualizarCamera()
    {
      // Dados para a configuração da matriz de projeção
      int largura = this.Width; // largura da janela
      int altura = this.Height;  // altura da janela      
      float aspecto = largura / altura; // aspecto dos gráficos      
      float campo_visao = (float)Math.PI / 4; // Campo de visão
      float corte_perto = 1.0f;

      // Essa variável foi modificada para acomodar o tamanho
      // do modelo
      float corte_longe = 1000.0f;

      // Atualiza ângulo para dar movimento ao objeto 3d
      angulo += 0.04f;

      // Mostra a parte interna do polígono
      device.RenderState.CullMode = Cull.None;

      // Configura a matriz de projeção
      device.Transform.Projection = Matrix.PerspectiveFovLH(campo_visao,
          aspecto, corte_perto, corte_longe);

      // Dados para a configuração da matriz de visualização
      // O eixo z foi modificado para comportar o tamanho do modelo
      Vector3 cam_pos = new Vector3(0, 0, 600.0f);
      Vector3 cam_alvo = new Vector3(0.0f, 0.0f, 0.0f);
      Vector3 cam_orientacao = new Vector3(0, 1.0f, 0);

      // Configura a matriz de visualização
      device.Transform.View = Matrix.LookAtLH(cam_pos, cam_alvo, cam_orientacao);
    }  // AtualizarCamera().fim

    // [---
    public void Renderizar()
    {

      // Limpa os dispositivos e os buffers de apoio
      device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.White, 1.0f, 0);

      // Verifica quantos pedaços foram produzidos a partir do objeto original
      int nTam = pedacos.Length;
      
      device.BeginScene();
      // (...) Todo o código de desenhar vai aqui   

      // Atualiza luz e câmera
      AtualizarCamera();
      device.RenderState.Lighting = false;
 
      // Desenha cada pedaço do objeto
      for (int ncx = 0; ncx < nTam; ncx++)
      {
        desenharObjeto(pedacos[ncx], g_props[ncx]);
      } // endfor

      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();    


      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar()
    // ---]
    // [---
    private void desenharObjeto(Mesh obj, Propriedades3D props)
    {   
      // Ajusta rotação do objeto 3d
      Matrix obj_rot = Matrix.RotationX(props.rotation.X + angulo) *
        Matrix.RotationY(props.rotation.Y) *
        Matrix.RotationZ(props.rotation.Z);   

      Matrix obj_pos = Matrix.Translation(props.position);

      // Tranfere posição e rotação para o mundo
      device.Transform.World = obj_rot * obj_pos;
      
        device.Material = g_meshMtl[0];
        device.SetTexture(0, g_meshTex[0]);

        // Renderiza o mesh
        obj.DrawSubset(0);      

    } // desenharObjeto().fim
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

    private void CarregarModelo(string diretorioBase, string arquivo)
    {
      // Composição do nome final do arquivo
      string caminhoFinal = diretorioBase + arquivo;

      // Recebe nome do arquivo de textura sendo carregado
      string arquivo_textura = null;

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

          // Carrega texturas
          arquivo_textura = xMtl[ncx].TextureFilename;
          if ((arquivo_textura != null) && arquivo_textura != String.Empty)
          {
            g_meshTex[ncx] = TextureLoader.FromFile(device,
              diretorioBase + arquivo_textura);
          } // endif (texturas)
        } // endfor (materiais\texturas)
      } // endif (verificação de texturas\materiais presentes)     

    } // CarregarModelo().fim

  

  } // fim da classe
} // fim do namespace

