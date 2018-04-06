﻿// prj_Simplificar - Arquivo: Tela.cs
// Esse projeto mostra como simplificar um modelo 3D
// utilizando o método Mesh.Simplify()
// Produzido por www.gameprog.com.br
using System;
using System.Drawing;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;
using Direct3D = Microsoft.DirectX.Direct3D;

namespace prj_Simplificar
{

  // Estrutura para propriedades 3d do objeto
  // posição, rotação e cor
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

    // Variável para guardar uma malha 3d
    private Mesh objeto3D = null;
    private Mesh mesh_limpo = null;
    private Mesh mesh_simplificado = null;
    
    // Variável para gravar informação de adjacências. Essa
    // informação vai ser usada na função gerarModeloSimplificado()
    GraphicsStream adj;
    
    // Controla modo wireframe ligado ou não
    bool bWireframe = false;

    // Pacote de materiais e texturas do modelo 3d que
    // precisa ser global na classe para ser utilizada também
    // no método salvarModelo()
    ExtendedMaterial[] xMtl;

    // Recipiente de materiais do mesh
    private Material[] g_meshMtl = null;

    // Recipiente de texturas do mesh
    private Texture[] g_meshTex = null;

    // Pasta de localização do arquivo mesh e sua textura
    private string diretorioBase = null;

    // Vetores para a posição e rotação do objeto 3d
    Vector3 posicao, rotacao;

    // Variável global para propriedade dos objetos
    Propriedades3D g_props;

    // Objeto Font do DirectX para mostrar texto
    private Direct3D.Font dxfMensagem = null;

    // Objeto Font tradicional do namespace System.Drawing
    private System.Drawing.Font g_font = null;
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

      // Ativando o buffer de profundidade
      pps.EnableAutoDepthStencil = true;
      pps.AutoDepthStencilFormat = DepthFormat.D16;

      // Adaptador default, processamento no hardware, processamento de vértice 
      // no software, janela (this), parâmetros de apresentação (pps)
      int adaptador = 0;
      device = new Device(adaptador, DeviceType.Hardware, this,
        CreateFlags.SoftwareVertexProcessing, pps);

      // Configuração das fontes para mostrar mensagens
      g_font = new System.Drawing.Font("Arial", 12.0f, FontStyle.Bold);
      dxfMensagem = new Direct3D.Font(device, g_font);

      diretorioBase = @"c:\Gameprog\Gdkmedia\Modelos\Tiny\";
      CarregarModelo(diretorioBase, "tiny.x");
      gerarModeloSimplificado();

    } // initGfx().fim
    // ---]

    // [---
    private void CarregarModelo(string diretorioBase, string arquivo)
    {
      // Composição do nome final do arquivo
      string caminhoFinal = diretorioBase + arquivo;

      // Recebe nome do arquivo de textura sendo carregado
      string arquivo_textura = null;

      // Quantidade de materiais\texturas encontrados no modelo3d
      int nTam = 0;

      // Carrega modelo 3d com suas texturas e materiais e
      // informação de adjacências
      objeto3D = Mesh.FromFile(caminhoFinal, MeshFlags.Managed,
        device, out adj, out xMtl);

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
    // ---]

    // [---
    private void gerarModeloSimplificado()
    {
      // Limpa do objeto 3d
      mesh_limpo = Mesh.Clean(objeto3D, adj, adj);

      // Geração do objeto simplificado
      int nVerts_alvo = 1000;
      mesh_simplificado = Mesh.Simplify(mesh_limpo, adj, null, nVerts_alvo,
        MeshFlags.SimplifyVertex);

    } // gerarModeloSimplificado()
    // ---]

    // [---
    private void salvarModelo()
    {
      // Define uma variável array para informação de adjacência
      int[] modelo_adj = new int[mesh_simplificado.NumberFaces * 3];

      // Gera informação de adjacência
      mesh_simplificado.GenerateAdjacency(0.0f, modelo_adj);

      // Limpa o modelo
      Mesh meshLimpo = Mesh.Clean(mesh_simplificado, modelo_adj,
        out modelo_adj);

      // Salva o modelo simplificado em arquivo x modo texto
      meshLimpo.Save(diretorioBase + "tinySimplificado.x", modelo_adj,
        xMtl, XFileFormat.Text);

      meshLimpo.Dispose();

    } // salvarModelo().fim
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
      float corte_longe = 5000.0f;

      // Atualiza angulo para dar movimento ao objeto 3d
      angulo += 0.02f;

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

      // Configuração de luz
      device.RenderState.Lighting = false;

      // Posicionamento do primeiro modelo
      posicao = new Vector3(100.0f, 0.2f, -100.0f);
      rotacao = new Vector3(0, 0, 0);
      g_props = new Propriedades3D(posicao, rotacao);
      desenharObjeto(objeto3D, g_props);

      // Positionamento do modelo simplificado
      g_props.position  = new Vector3(-100.0f, 0.2f, -200.0f);      
      desenharObjeto(mesh_simplificado, g_props);

      // Mostra o número de vértices de cada modelo
      string info;
      info = String.Format("Modelo limpo: {0}", 
        mesh_limpo.NumberVertices);
      MostrarMensagem(20, 20, info);
      
      info = String.Format("simplificado: {0}", 
        mesh_simplificado.NumberVertices);
      MostrarMensagem(220, 20, info);

      info = String.Format("original: {0}", 
        objeto3D.NumberVertices);
      MostrarMensagem(420, 20, info);

      device.EndScene();

      // Apresenta a cena renderizada na tela
      device.Present();

      // Libera a janela para processar outros eventos
      Application.DoEvents();
    } // Renderizar().fim
    // ---]

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

      // Prepara e aplica material\textura no objeto
      for (int ncx = 0; ncx < g_meshMtl.Length; ncx++)
      {
        // Informa ao dispositivo o material a ser utilizado
        // na renderização    
        device.Material = g_meshMtl[ncx];
        device.SetTexture(0, g_meshTex[ncx]);

        // Renderiza o mesh
        obj.DrawSubset(ncx);
      } // endfor

    } // desenharObjeto()  

    protected override void OnPaint(PaintEventArgs e)
    {
      // Trate outros processos padrões
      base.OnPaint(e);

      // Renderize a cena
      this.Renderizar();

      // Invalide para chamar novamente onPaint()
      this.Invalidate();
    } // onPaint().fim     

    // [---
    private void Tela_KeyDown(object sender, KeyEventArgs e)
    {
      // A tecla W liga\desliga o modo wireframe
      if (e.KeyCode == Keys.W) bWireframe = !bWireframe;
      if (bWireframe) device.RenderState.FillMode = FillMode.WireFrame;
      else device.RenderState.FillMode = FillMode.Solid;

      // A tecla S salva o modelo
      if (e.KeyCode == Keys.S) salvarModelo();
      
    } // Tela_KeyDown().fim
    // ---]

    // Mostra texto na posição (x,y) da tela
    private void MostrarMensagem(int xpos, int ylin, string txt)
    {
      // Configura posição do texto
      Rectangle position = new Rectangle(xpos, ylin, 0, 0);

      // Mostra texto
      dxfMensagem.DrawText(null, txt, position, DrawTextFormat.NoClip, 
        Color.Blue);
    } // MostrarMensagem().fim
  } // fim da classe
} // fim do namespace