using System;
using System.Drawing;
using System.Collections;
using System.ComponentModel;
using System.Windows.Forms;
using System.Data;
using Microsoft.DirectX;
using Microsoft.DirectX.Direct3D;

namespace Chapter10Code
{
  /// <summary>
  /// Summary description for Form1.
  /// </summary>
  public class Form1 : System.Windows.Forms.Form
  {
    private Device device = null;

    private Mesh skybox = null;
    private Material[] skyboxMaterials;
    private Texture[] skyboxTextures;

    private CubeTexture environment = null;
    private RenderToEnvironmentMap rte = null;

    private const int CubeMapSize = 128;
    private readonly Matrix ViewMatrix = Matrix.Translation(0.0f, 0.0f, 13.0f);

    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.Container components = null;
    private float angle = 0.0f;

    public Form1()
    {
      //
      // Required for Windows Form Designer support
      //
      InitializeComponent();
      this.Size = new Size(640, 480);

      this.SetStyle(ControlStyles.AllPaintingInWmPaint | ControlStyles.Opaque, true);
    }

    /// <summary>
    /// We will initialize our graphics device here
    /// </summary>
    public bool InitializeGraphics()
    {
      // Set our presentation parameters
      PresentParameters presentParams = new PresentParameters();

      presentParams.Windowed = true;
      presentParams.SwapEffect = SwapEffect.Discard;
      presentParams.AutoDepthStencilFormat = DepthFormat.D16;
      presentParams.EnableAutoDepthStencil = true;

      // Create our device
      device = new Device(0, DeviceType.Hardware, this, CreateFlags.SoftwareVertexProcessing, presentParams);
      device.DeviceReset += new EventHandler(OnDeviceReset);
      OnDeviceReset(device, null);

      // Do we support cube maps?
      if (!device.DeviceCaps.TextureCaps.SupportsCubeMap)
        return false;

      // Load our meshes
      skybox = LoadMesh(@"c:\gameprog\gdkmedia\sky\skybox2.x", ref skyboxMaterials, ref skyboxTextures);


      return true;
    }

    /// <summary>
    /// Handle the device reset event, recreate our
    /// environment maps
    /// </summary>
    private void OnDeviceReset(object sender, EventArgs e)
    {
      Device dev = (Device)sender;

      rte = new RenderToEnvironmentMap(dev, CubeMapSize, 1,
          Format.X8R8G8B8, true, DepthFormat.D16);

      environment = new CubeTexture(dev, CubeMapSize, 1,
          Usage.RenderTarget, Format.X8R8G8B8, Pool.Default);
    }

    private Mesh LoadMesh(string file, ref Material[] meshMaterials, ref Texture[] meshTextures)
    {
      ExtendedMaterial[] mtrl;

      // Load our mesh
      Mesh mesh = Mesh.FromFile(file, MeshFlags.Managed, device, out mtrl);

      // If we have any materials, store them
      if ((mtrl != null) && (mtrl.Length > 0))
      {
        meshMaterials = new Material[mtrl.Length];
        meshTextures = new Texture[mtrl.Length];

        // Store each material and texture
        for (int i = 0; i < mtrl.Length; i++)
        {
          meshMaterials[i] = mtrl[i].Material3D;
          if ((mtrl[i].TextureFilename != null) && (mtrl[i].TextureFilename != string.Empty))
          {
            // We have a texture, try to load it
            meshTextures[i] = TextureLoader.FromFile(device, @"c:\gameprog\gdkmedia\sky\" + mtrl[i].TextureFilename);
          }
        }
      }
      if ((mesh.VertexFormat & VertexFormats.Normal) != VertexFormats.Normal)
      {
        // We must have normals for our patch meshes
        Mesh tempMesh = mesh.Clone(mesh.Options.Value,
            mesh.VertexFormat | VertexFormats.Normal, device);

        tempMesh.ComputeNormals();

        mesh.Dispose();
        mesh = tempMesh;
      }
      return mesh;
    }


    /// <summary>
    /// Render the scene with the necessary view and projection matrices
    /// </summary>
    /// <param name="View">View Matrix of the scene</param>
    /// <param name="Project">Projection Matrix of the scene</param>
    /// <param name="shouldRenderCar">Should the car be rendered?</param>
    private void RenderScene(Matrix View, Matrix Project, bool shouldRenderCar)
    {
      // Render the skybox first
      device.Transform.World = Matrix.Scaling(10.0f, 10.0f, 10.0f);
      Matrix matView = View;
      matView.M41 = matView.M42 = matView.M43 = 0.0f;

      device.Transform.View = matView;
      device.Transform.Projection = Project;

      device.TextureState[0].ColorArgument1 = TextureArgument.TextureColor;
      device.TextureState[0].ColorOperation = TextureOperation.SelectArg1;
      device.SamplerState[0].MinFilter = TextureFilter.Linear;
      device.SamplerState[0].MagFilter = TextureFilter.Linear;
      device.SamplerState[0].AddressU = TextureAddress.Mirror;
      device.SamplerState[0].AddressV = TextureAddress.Mirror;

      // Always pass Z-test, so we can avoid clearing color and depth buffers
      device.RenderState.ZBufferFunction = Compare.Always;
      DrawSkyBox();
      device.RenderState.ZBufferFunction = Compare.LessEqual;
     

    } // RenderScene

    protected override void OnPaint(System.Windows.Forms.PaintEventArgs e)
    {
      RenderSceneIntoEnvMap();

      device.BeginScene();

      RenderScene(ViewMatrix, Matrix.PerspectiveFovLH((float)Math.PI / 4, this.Width / this.Height, 1.0f, 10000.0f), true);

      device.EndScene();

      device.Present();

      this.Invalidate();
    }


    /// <summary>
    /// Renders the scene to each of the 6 faces of the cube map
    /// </summary>
    private void RenderSceneIntoEnvMap()
    {

      // Set the projection matrix for a field of view of 90 degrees
      Matrix matProj;
      matProj = Matrix.PerspectiveFovLH((float)Math.PI * 0.5f, 1.0f, 0.5f, 1000.0f);


      // Get the current view matrix, to concat it with the cubemap view vectors
      Matrix matViewDir = ViewMatrix;
      matViewDir.M41 = 0.0f; matViewDir.M42 = 0.0f; matViewDir.M43 = 0.0f;



      // Render the six cube faces into the environment map
      if (environment != null)
        rte.BeginCube(environment);

      for (int i = 0; i < 6; i++)
      {
        rte.Face((CubeMapFace)i, 1);

        // Set the view transform for this cubemap surface
        Matrix matView = Matrix.Multiply(matViewDir, GetCubeMapViewMatrix((CubeMapFace)i));

        // Render the scene (except for the teapot)
        RenderScene(matView, matProj, false);
      }

      rte.End(1);
    }


    private void DrawSkyBox()
    {
      for (int i = 0; i < skyboxMaterials.Length; i++)
      {
        device.Material = skyboxMaterials[i];
        device.SetTexture(0, skyboxTextures[i]);
        skybox.DrawSubset(i);
      }
    }

    /// <summary>
    /// Returns a view matrix for rendering to a face of a cubemap.
    /// </summary>
    private Matrix GetCubeMapViewMatrix(CubeMapFace face)
    {
      Vector3 vEyePt = new Vector3(0.0f, 0.0f, 0.0f);
      Vector3 vLookDir = new Vector3();
      Vector3 vUpDir = new Vector3();

      switch (face)
      {
        case CubeMapFace.PositiveX:
          vLookDir = new Vector3(1.0f, 0.0f, 0.0f);
          vUpDir = new Vector3(0.0f, 1.0f, 0.0f);
          break;
        case CubeMapFace.NegativeX:
          vLookDir = new Vector3(-1.0f, 0.0f, 0.0f);
          vUpDir = new Vector3(0.0f, 1.0f, 0.0f);
          break;
        case CubeMapFace.PositiveY:
          vLookDir = new Vector3(0.0f, 1.0f, 0.0f);
          vUpDir = new Vector3(0.0f, 0.0f, -1.0f);
          break;
        case CubeMapFace.NegativeY:
          vLookDir = new Vector3(0.0f, -1.0f, 0.0f);
          vUpDir = new Vector3(0.0f, 0.0f, 1.0f);
          break;
        case CubeMapFace.PositiveZ:
          vLookDir = new Vector3(0.0f, 0.0f, 1.0f);
          vUpDir = new Vector3(0.0f, 1.0f, 0.0f);
          break;
        case CubeMapFace.NegativeZ:
          vLookDir = new Vector3(0.0f, 0.0f, -1.0f);
          vUpDir = new Vector3(0.0f, 1.0f, 0.0f);
          break;
      }

      // Set the view transform for this cubemap surface
      Matrix matView = Matrix.LookAtLH(vEyePt, vLookDir, vUpDir);
      return matView;
    }


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

    #region Windows Form Designer generated code
    /// <summary>
    /// Required method for Designer support - do not modify
    /// the contents of this method with the code editor.
    /// </summary>
    private void InitializeComponent()
    {
      this.SuspendLayout();
      // 
      // Form1
      // 
      this.ClientSize = new System.Drawing.Size(276, 194);
      this.Name = "Form1";
      this.Text = "Form1";
      this.ResumeLayout(false);

    }
    #endregion

    /// <summary>
    /// The main entry point for the application.
    /// </summary>
    static void Main()
    {
      using (Form1 frm = new Form1())
      {
        // Show our form and initialize our graphics engine
        frm.Show();
        if (!frm.InitializeGraphics())
        {
          MessageBox.Show("Your card does not support cube maps.");
          frm.Close();
        }
        else
        {
          Application.Run(frm);
        }
      }
    }
  }
}
