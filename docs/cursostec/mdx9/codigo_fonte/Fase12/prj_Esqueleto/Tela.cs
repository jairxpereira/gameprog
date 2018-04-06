using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace Chapter13Code
{

  public class dlgTela : System.Windows.Forms.Form
  {
    private Device device = null;

    // prj_Esqueleto code
    private AnimationRootFrame quadroRaiz;
    private Vector3 objetoCentro;
    private float objetoRaio;
    private float tempoDecorrido;


    private System.ComponentModel.Container components = null;

    // Construtor
    public dlgTela()
    {
      InitializeComponent();
      this.Size = new Size(640, 480);

      this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.Opaque, true);
    }


    public bool initGfx()
    {
      // Set our presentation parameters
      PresentParameters pps = new PresentParameters();

      pps.Windowed = true;
      pps.SwapEffect = SwapEffect.Discard;
      pps.AutoDepthStencilFormat = DepthFormat.D16;
      pps.EnableAutoDepthStencil = true;

      bool canDoHardwareSkinning = true;
      // Does a hardware device support shaders?
      Caps hardware = Manager.GetDeviceCaps(0, DeviceType.Hardware);
      // We will need at least four blend matrices

      CreateFlags flags;


      flags = CreateFlags.HardwareVertexProcessing;


      flags |= CreateFlags.PureDevice;

      // Yes, Create our device
      device = new Device(0, DeviceType.Hardware, this, flags, pps);


      // Create the animation
      carregarModeloAnimado(@"..\..\tiny.x", pps);

      // Hook the device reset event
      device.DeviceReset += new EventHandler(atualizarCamera);
      atualizarCamera(device, null);

      return canDoHardwareSkinning;
    }

    /// <summary>
    /// Occurs after the device has been reset
    /// </summary>
    private void atualizarCamera(object sender, EventArgs e)
    {
      Device dev = (Device)sender;

      // Set the view matrix
      Vector3 vEye = new Vector3(0, 0, -1.8f * objetoRaio);
      Vector3 vUp = new Vector3(0, 1, 0);

      dev.Transform.View = Matrix.LookAtLH(vEye, objetoCentro, vUp);

      // Setup the projection matrix
      float aspectRatio = (float)dev.PresentationParameters.BackBufferWidth
          / (float)dev.PresentationParameters.BackBufferHeight;

      dev.Transform.Projection = Matrix.PerspectiveFovLH((float)Math.PI / 4, aspectRatio,
          objetoRaio / 64.0f, objetoRaio * 200.0f);

      // Initialize our light
      dev.Lights[0].Type = LightType.Directional;
      dev.Lights[0].Direction = new Vector3(0.0f, 0.0f, 1.0f);
      dev.Lights[0].Diffuse = Color.White;
      dev.Lights[0].Commit();
      dev.Lights[0].Enabled = true;
    }

    /// <summary>
    /// Create the animation hierarchy for this file
    /// </summary>
    private void carregarModeloAnimado(string file, PresentParameters presentParams)
    {
      // Create our allocate hierarchy derived class
      HierarquiaAlojamento alloc = new HierarquiaAlojamento(this);

      // Load our file
      quadroRaiz = Mesh.LoadHierarchyFromFile(file, MeshFlags.Managed,
          device, alloc, null);

      // Calculate the center and radius of a bounding sphere
      objetoRaio = Frame.CalculateBoundingSphere(quadroRaiz.FrameHierarchy,
          out objetoCentro);

      // Setup the matrices for animation
      ossos_ConfigurarMatrizes((QuadroDerivado)quadroRaiz.FrameHierarchy);

      // Start the timer
      DXUtil.Timer(DirectXTimer.Start);
    } // carregarModeloAnimado().fim

    protected override void OnPaint(System.Windows.Forms.PaintEventArgs e)
    {
      Renderizar();

      this.Invalidate();
    } // OnPaint().fim

    private void Renderizar()
    {
      processaProximoQuadro();

      device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, 
        Color.CornflowerBlue, 1.0f, 0);

      device.BeginScene();

      // Draw our root quadro
      desenharQuadro((QuadroDerivado)quadroRaiz.FrameHierarchy);

      device.EndScene();

      device.Present();
    } // Renderizar().fim

    /// <summary>
    /// Draw a quadro and all child and sibling frames
    /// </summary>
    /// <param name="quadro">Frame to draw</param>
    private void desenharQuadro(QuadroDerivado frame)
    {
      Packmesh mesh = (Packmesh)frame.MeshContainer;
    
      while (mesh != null)
      {
        desenharPackmesh(mesh, frame);

        mesh = (Packmesh)mesh.NextContainer;
      } // endwhile

      if (frame.FrameSibling != null)
      {
        desenharQuadro((QuadroDerivado)frame.FrameSibling);
      } // endif

      if (frame.FrameFirstChild != null)
      {
        desenharQuadro((QuadroDerivado)frame.FrameFirstChild);
      } // endif
    } // desenharQuadro().fim

    /// <summary>
    /// Draw a meshcontainer
    /// </summary>
    /// <param name="packmesh">Mesh container to draw</param>
    /// <param name="quadro">Parent quadro of this container</param>
    private void desenharPackmesh(Packmesh mesh, QuadroDerivado frame)
    {
      // Is there skin information?
      if (mesh.SkinInformation != null)
      {

        int attribIdPrev = -1;

        // Draw 
        for (int iattrib = 0; iattrib < mesh.nAtributos; iattrib++)
        {
          int numBlend = 0;
          BoneCombination[] bones = mesh.GetBones();
          for (int i = 0; i < mesh.nInfluencias; i++)
          {
            if (bones[iattrib].BoneId[i] != -1)
            {
              numBlend = i;
            } // endif
          } // endfor

          if (device.DeviceCaps.MaxVertexBlendMatrices >= numBlend + 1)
          {
            // first calculate the world matrices for the current set of 
            // blend weights and get the accurate count of the number of 
            // blends
            Matrix[] offsetMatrices = mesh.GetOffsetMatrices();
            QuadroDerivado[] frameMatrices = mesh.GetFrames();
            for (int i = 0; i < mesh.nInfluencias; i++)
            {
              int matrixIndex = bones[iattrib].BoneId[i];
              if (matrixIndex != -1)
              {
                Matrix tempMatrix = offsetMatrices[matrixIndex] *
                    frameMatrices[matrixIndex].CombinedTransformationMatrix;

                device.Transform.SetWorldMatrixByIndex(i, tempMatrix);

              } // endif
            } // endfor

            device.RenderState.VertexBlend = (VertexBlend)numBlend;
            // lookup the material used for this subset of faces
            if ((attribIdPrev != bones[iattrib].AttribId) ||
                (attribIdPrev == -1))
            {
              device.Material = mesh.GetMaterials()[
                  bones[iattrib].AttribId].Material3D;

              device.SetTexture(0, mesh.GetTextures()[
                  bones[iattrib].AttribId]);

              attribIdPrev = bones[iattrib].AttribId;
            }// endif

            mesh.MeshData.Mesh.DrawSubset(iattrib);
          }
        }
      } // endif
      else // standard packmesh, just draw it after setting material properties
      {
        device.Transform.World = frame.CombinedTransformationMatrix;

        ExtendedMaterial[] mtrl = mesh.GetMaterials();
        for (int iMaterial = 0; iMaterial < mtrl.Length; iMaterial++)
        {
          device.Material = mtrl[iMaterial].Material3D;
          device.SetTexture(0, mesh.GetTextures()[iMaterial]);
          mesh.MeshData.Mesh.DrawSubset(iMaterial);
        } // endfor
      } // endelse
    } // desenharPackmesh().fim

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    protected override void Dispose(bool disposing)
    {
      if (disposing)
      {
        if (components != null)
        {
          components.Dispose();
        }
      }
      base.Dispose(disposing);
    }

    /// <summary>
    /// Generate the skinned packmesh information
    /// </summary>
    /// <param name="packmesh">Container of packmesh to generate</param>
    public void gerarModeloElastico(Packmesh packmesh)
    {
      if (packmesh.SkinInformation == null)
        throw new ArgumentException();

      int numInfl = 0;
      BoneCombination[] ossos;

      // Use ConvertToBlendedMesh to generate a drawable packmesh
      MeshData mesh_info = packmesh.MeshData;
      mesh_info.Mesh = packmesh.SkinInformation.ConvertToBlendedMesh(mesh_info.Mesh, 
        MeshFlags.Managed | MeshFlags.OptimizeVertexCache, 
        packmesh.GetAdjacencyStream(), out numInfl, out ossos);

      // Store this info
      packmesh.nInfluencias = numInfl;
      packmesh.SetBones(ossos);

      // Get the number of attributes
      packmesh.nAtributos = ossos.Length;

      packmesh.MeshData = mesh_info;
    }

    /// <summary>
    /// Do all the processing for this quadro before we render it
    /// </summary>
    private void processaProximoQuadro()
    {
      // Get the current elapsed time
      tempoDecorrido = DXUtil.Timer(DirectXTimer.GetElapsedTime);

      // Set the world matrix
      Matrix worldMatrix = Matrix.Translation(objetoCentro);
      device.Transform.World = worldMatrix;

      if (quadroRaiz.AnimationController != null)
        quadroRaiz.AnimationController.AdvanceTime(tempoDecorrido, null);

      quadro_AtualizarMatrizes((QuadroDerivado)quadroRaiz.FrameHierarchy, worldMatrix);
    } // processaProximoQuadro().fim

    /// <summary>
    /// This method will set the bone matrices for a quadro
    /// </summary>
    private void ossos_ConfigurarMatrizes(QuadroDerivado frame)
    {
      if (frame.MeshContainer != null)
      {
        ossos_ConfigurarMatrizes((Packmesh)frame.MeshContainer);
      } // endif

      if (frame.FrameSibling != null)
      {
        ossos_ConfigurarMatrizes((QuadroDerivado)frame.FrameSibling);
      } // endif

      if (frame.FrameFirstChild != null)
      {
        ossos_ConfigurarMatrizes((QuadroDerivado)frame.FrameFirstChild);
      } // endif
    } // ossos_ConfigurarMatrizes().fim

    /// <summary>
    /// Sets the bone matrices for a packmesh container
    /// </summary>
    private void ossos_ConfigurarMatrizes(Packmesh mesh)
    {
      // Is there skin information?  If so, setup the matrices
      if (mesh.SkinInformation != null)
      {
        int nOssos = mesh.SkinInformation.NumberBones;

        QuadroDerivado[] frameMatrices = new QuadroDerivado[nOssos];
        for (int i = 0; i < nOssos; i++)
        {
          QuadroDerivado frame = (QuadroDerivado)Frame.Find(
              quadroRaiz.FrameHierarchy,
              mesh.SkinInformation.GetBoneName(i));

          if (frame == null) throw new ArgumentException();

          frameMatrices[i] = frame;
        } // endfor
        mesh.SetFrames(frameMatrices);
      } // endif
    } // ossos_ConfigurarMatrizes().fim

    /// <summary>
    /// Update the frames matrices and combine it with it's parents
    /// </summary>
    private void quadro_AtualizarMatrizes(QuadroDerivado frame, Matrix matrizPai)
    {
      frame.CombinedTransformationMatrix = frame.TransformationMatrix *
          matrizPai;

      if (frame.FrameSibling != null)
      {
        quadro_AtualizarMatrizes((QuadroDerivado)frame.FrameSibling, matrizPai);
      }

      if (frame.FrameFirstChild != null)
      {
        quadro_AtualizarMatrizes((QuadroDerivado)frame.FrameFirstChild,
            frame.CombinedTransformationMatrix);
      }
    }

    #region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.SuspendLayout();
      // 
      // dlgTela
      // 
      this.ClientSize = new System.Drawing.Size(269, 233);
      this.Name = "dlgTela";
      this.Text = "prj_Esqueleto";
      this.ResumeLayout(false);

    }
    #endregion


    static void Main()
    {
      using (dlgTela frm = new dlgTela())
      {
        // Show our form and initialize our graphics engine
        frm.Show();
        if (!frm.initGfx())
        {
          MessageBox.Show("Your card can not perform skeletal animation on " +
              "this file in hardware. This application will run in " +
              "ref mode instead.");
        }
        Application.Run(frm);
      }
    }
  }
  /// <summary>
  /// The derived quadro class
  /// </summary>
  public class QuadroDerivado : Frame
  {
    // Store the combined transformation matrix
    private Matrix combined = Matrix.Identity;
    public Matrix CombinedTransformationMatrix
    {
      get { return combined; }
      set { combined = value; }
    }
  }

  /// <summary>
  /// The derived packmesh container class
  /// </summary>
  public class Packmesh : MeshContainer
  {
    private Texture[] meshTextures = null;

    private int numAttr = 0;

    private int numInfl = 0;

    private BoneCombination[] ossos;

    private QuadroDerivado[] quadroMatriz;

    private Matrix[] deslocamentoMatriz;

    // Public properties
    public Texture[] GetTextures() { return meshTextures; }
    public void SetTextures(Texture[] textures) { meshTextures = textures; }

    public BoneCombination[] GetBones() { return ossos; }
    public void SetBones(BoneCombination[] b) { ossos = b; }

    public QuadroDerivado[] GetFrames() { return quadroMatriz; }
    public void SetFrames(QuadroDerivado[] frames) { quadroMatriz = frames; }

    public Matrix[] GetOffsetMatrices() { return deslocamentoMatriz; }
    public void SetOffsetMatrices(Matrix[] matrices) { deslocamentoMatriz = matrices; }

    public int nAtributos { get { return numAttr; } set { numAttr = value; } }
    public int nInfluencias { get { return numInfl; } set { numInfl = value; } }
  }

  /// <summary>
  /// AllocateHierarchy derived class
  /// </summary>
  public class HierarquiaAlojamento : AllocateHierarchy
  {
    dlgTela app = null;
    /// <summary>
    /// Create new instance of this class
    /// </summary>
    /// <param name="parent">Parent of this class</param>
    public HierarquiaAlojamento(dlgTela parent)
    {
      app = parent;
    }

    /// <summary>
    /// Create a new quadro
    /// </summary>
    /// <returns>The newly created quadro</returns>
    public override Frame CreateFrame(string name)
    {
      QuadroDerivado quadro = new QuadroDerivado();
      quadro.Name = name;
      quadro.TransformationMatrix = Matrix.Identity;
      quadro.CombinedTransformationMatrix = Matrix.Identity;

      return quadro;
    }

    /// <summary>
    /// Create a new packmesh container
    /// </summary>
    /// <returns>The newly created container</returns>
    /// 
    public override MeshContainer CreateMeshContainer(string name,
        MeshData meshData, ExtendedMaterial[] materials,
        EffectInstance effectInstances, GraphicsStream adjacency,
        SkinInformation skinInfo)
    {
      // We only handle meshes here
      if (meshData.Mesh == null)
        throw new ArgumentException();

      // We must have a vertex format packmesh
      if (meshData.Mesh.VertexFormat == VertexFormats.None)
        throw new ArgumentException();

      Packmesh packmesh = new Packmesh();

      packmesh.Name = name;
      int numFaces = meshData.Mesh.NumberFaces;
      Device dev = meshData.Mesh.Device;

      // Make sure there are normals
      if ((meshData.Mesh.VertexFormat & VertexFormats.Normal) == 0)
      {
        // Clone the packmesh
        Mesh tempMesh = meshData.Mesh.Clone(meshData.Mesh.Options.Value,
            meshData.Mesh.VertexFormat | VertexFormats.Normal, dev);

        meshData.Mesh = tempMesh;
        meshData.Mesh.ComputeNormals();
      }

      // Store the materials
      packmesh.SetMaterials(materials);
      packmesh.SetAdjacency(adjacency);
      Texture[] texturas = new Texture[materials.Length];

      // Create any textures
      for (int i = 0; i < materials.Length; i++)
      {
        if (materials[i].TextureFilename != null)
        {
          texturas[i] = TextureLoader.FromFile(dev, @"..\..\" +
              materials[i].TextureFilename);
        }
      }
      packmesh.SetTextures(texturas);
      packmesh.MeshData = meshData;

      // If there is skinning info, save any required data
      if (skinInfo != null)
      {
        packmesh.SkinInformation = skinInfo;
        int nOssos = skinInfo.NumberBones;
        Matrix[] offsetMatrices = new Matrix[nOssos];

        for (int i = 0; i < nOssos; i++)
          offsetMatrices[i] = skinInfo.GetBoneOffsetMatrix(i);

        packmesh.SetOffsetMatrices(offsetMatrices);

        app.gerarModeloElastico(packmesh);
      }

      return packmesh;
    }

  }
}
