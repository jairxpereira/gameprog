using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;

namespace apostilaMaker
{
  // [--- -
  class HtmlMaker
  {
    public string htmlfile;
    public string header;
    public string body;
    public string title;
    public string savefolder;
    public string sourcefile;
    public int recortar;

    StringBuilder sb_css = null;
    StringBuilder sb_recorte = null;

    public System.Windows.Forms.Label aviso = null;
    // ---] -

    public HtmlMaker()
    {
      htmlfile = "track-0x-x.html";
      title = "Gameprog";
      
      sb_recorte = new StringBuilder();

      // sb_recorte.AppendLine(openHeader());
      LoadCss();
      
      // sb_recorte.AppendLine(sb_css.ToString());
      // sb_recorte.AppendLine(closeHeader());
      
      sb_recorte.AppendLine(openBody());      

    } // fim do construtor

    // [--- -
    public void bonitificarCodigo()
    {

      // 0 - indefinido - 1- aberto 2-fechado
      int recorte_status = 0;
      
      
      // Abre o arquivo para gravação
      string fullpath_saida = this.savefolder + "\\" + this.htmlfile;
      string fullpath_entrada = this.sourcefile;
      string linha = null;
      string linha_bonita = null;

      StreamWriter html_fluxo = new StreamWriter(fullpath_saida, false);
      StreamReader cs_influxo = new StreamReader(fullpath_entrada);
      StringBuilder sb_trecho = new StringBuilder();

      // Gravando os dados...
      // html_fluxo.WriteLine(openHeader());
      // if (sb_css != null) html_fluxo.WriteLine(sb_css.ToString());

      // html_fluxo.WriteLine(closeHeader());
      // html_fluxo.WriteLine(openBody());

      do
      {
        linha = cs_influxo.ReadLine();

        if (linha != null)
        {

          if (linha.Contains("// <b>")) sb_trecho.AppendLine("<b>");
          if (linha.Contains("// </b>")) sb_trecho.AppendLine("</b>");
          if (linha.Contains("// <b>")) linha = String.Empty;
          if (linha.Contains("// </b>")) linha = String.Empty;
          
          if (linha.Contains("// [--" + "-" )) sb_recorte.AppendLine(openRecorte());
          if (linha.Contains("// [--" + "-" )) recorte_status = 1;

          if (linha.Contains("// ---" + "]")) recorte_status = 2;

          linha_bonita = bonitificar_linha(linha);
          
          if (recorte_status == 1) sb_trecho.AppendLine(linha_bonita);

          if (recorte_status == 2)
          {
          sb_recorte.AppendLine ( sb_trecho.ToString());
          sb_recorte.AppendLine("</div>");
          sb_trecho.Replace("\n", "\n\n");
          sb_recorte.AppendLine(sb_trecho.ToString());
          sb_trecho.Remove(0, sb_trecho.Length);
          recorte_status = 0;
          } // endif - recorte = 2

          if (linha.Contains("// [--" + "-")) linha = String.Empty;
          if (linha.Contains("// [--" + "-")) linha = String.Empty;

          if (linha.Contains("// ---" + "]")) linha = String.Empty;

        } // endif - recheando recorte

        if (linha_bonita != null)
          html_fluxo.WriteLine(linha_bonita);
        if (aviso != null) aviso.Text = linha;

      } while (linha != null);

      // html_fluxo.WriteLine(closeBody());
     
      html_fluxo.Close();
      cs_influxo.Close();

      // Grava o recorte
      string recorte_saida = this.savefolder + "\\" + "recorte.html";
      html_fluxo = new StreamWriter(recorte_saida, false);
      html_fluxo.WriteLine(sb_recorte.ToString());

      html_fluxo.Close();



      string temp_files = "";
      temp_files += "bonitificarCodigo()" + "\n";
      temp_files += "-------------------------------------------------" + "\n";

      temp_files += fullpath_saida + "\n";
      temp_files += recorte_saida + "\n";

      MessageBox.Show(temp_files, "Arquivos criados:");


    } // bonitificarCodigo().fim
    // ---] -

    private string openHeader()
    {
      string temp = "<html>\n";
      temp += "<head>\n";
      temp += String.Format("<title>{0}</title>", this.title);
      this.header = temp;

      return this.header;
    } // openHeader().fim

    private string closeHeader()
    {
      string temp = "</head>\n";
      this.header = temp;
      return this.header;
    } // closeHeader().fim

    private string closeBody()
    {
      string temp = "</body>\n </html>";
      this.body = temp;
      return this.body;
    } // closeBody().fim

    private string openBody()
    {
      // string temp = "<body><pre> hackeado\n";
      string temp = "";
      this.body = temp;
      return this.body;
    } // openBody().fim

    // [--- -
    string getWordClass(string codeword)
    {
      string wordclass = "";
      wordclass = "no_fmt";

      // Formatação do código vertexshader WORLDVIEWPROJECTION
      if (codeword.Equals("WORLDVIEWPROJECTION")) wordclass = "sc16";
      if (codeword.Equals("WORLDVIEWPROJECTION;")) wordclass = "sc16";
      if (codeword.Equals("POSITION")) wordclass = "sc16";
      if (codeword.Equals("POSITION;")) wordclass = "sc16";
      if (codeword.Equals("TEXCOORD")) wordclass = "sc16";
      if (codeword.Equals("TEXCOORD0")) wordclass = "sc16";
      if (codeword.Equals("TEXCOORD;")) wordclass = "sc16";
      if (codeword.Equals("TEXCOORD0;")) wordclass = "sc16";
      if (codeword.Equals("TEXCOORD1")) wordclass = "sc16";
      if (codeword.Equals("NORMAL")) wordclass = "sc16";
      if (codeword.Equals("COLOR0")) wordclass = "sc16";
      if (codeword.Equals("COLOR0;")) wordclass = "sc16";

      if (codeword.Equals("float2")) wordclass = "prg";
      if (codeword.Equals("float3")) wordclass = "prg";
      if (codeword.Equals("float4")) wordclass = "prg";
      if (codeword.Equals("float4x4")) wordclass = "prg";
      if (codeword.Equals("compile")) wordclass = "prg";
      if (codeword.Equals("dot")) wordclass = "sc16";
      if (codeword.Equals("mul")) wordclass = "sc16";
      if (codeword.Equals("lerp")) wordclass = "sc16";
      if (codeword.Equals("tex2D")) wordclass = "sc16";
      if (codeword.Equals("in")) wordclass = "sc16";
      if (codeword.Equals("out")) wordclass = "sc16";



      if (codeword.Equals("technique")) wordclass = "sc5";
      if (codeword.Equals("pass")) wordclass = "sc5";
      if (codeword.Equals("VertexShader")) wordclass = "sc5";
      if (codeword.Equals("PixelShader")) wordclass = "sc5";
      if (codeword.Equals("sampler")) wordclass = "sc5";

      if (codeword.Equals("CullMode")) wordclass = "sc6";
      if (codeword.Equals("FillMode")) wordclass = "sc6";
      if (codeword.Equals("ps_1_1")) wordclass = "sc16";
      if (codeword.Equals("vs_1_1")) wordclass = "sc16";
      if (codeword.Equals("ps_2_0")) wordclass = "sc16";
      if (codeword.Equals("vs_2_0")) wordclass = "sc16";
      if (codeword.Equals("ps_3_0")) wordclass = "sc16";
      if (codeword.Equals("vs_3_0")) wordclass = "sc16";

      // Using e namespaces
      if (codeword.Contains(".")) wordclass = "prg";

      if (codeword.Contains("\"")) wordclass = "sc6";

      if (codeword.Contains("0 ")) wordclass = "sc4";
      if (codeword.Contains("1 ")) wordclass = "sc4";
      if (codeword.Contains("2 ")) wordclass = "sc4";
      if (codeword.Contains("3 ")) wordclass = "sc4";
      if (codeword.Contains("4 ")) wordclass = "sc4";
      if (codeword.Contains("5 ")) wordclass = "sc4";
      if (codeword.Contains("6 ")) wordclass = "sc4";
      if (codeword.Contains("7 ")) wordclass = "sc4";
      if (codeword.Contains("8 ")) wordclass = "sc4";
      if (codeword.Contains("9 ")) wordclass = "sc4";

      if (codeword.Equals("0")) wordclass = "sc4";
      if (codeword.Equals("1")) wordclass = "sc4";
      if (codeword.Equals("2")) wordclass = "sc4";
      if (codeword.Equals("3")) wordclass = "sc4";
      if (codeword.Equals("4")) wordclass = "sc4";
      if (codeword.Equals("5")) wordclass = "sc4";
      if (codeword.Equals("6")) wordclass = "sc4";
      if (codeword.Equals("7")) wordclass = "sc4";
      if (codeword.Equals("8")) wordclass = "sc4";
      if (codeword.Equals("9")) wordclass = "sc4";
      if (codeword.Contains("-0.")) wordclass = "sc4";
      if (codeword.Contains("-1")) wordclass = "sc4";
      if (codeword.Contains("-2")) wordclass = "sc4";
      if (codeword.Contains("-3")) wordclass = "sc4";
      if (codeword.Contains("-4")) wordclass = "sc4";
      if (codeword.Contains("-5")) wordclass = "sc4";
      if (codeword.Contains("-6")) wordclass = "sc4";
      if (codeword.Contains("-7")) wordclass = "sc4";
      if (codeword.Contains("-8")) wordclass = "sc4";
      if (codeword.Contains("-9")) wordclass = "sc4";

      if (codeword.Contains("0f")) wordclass = "sc4";
      if (codeword.Contains("1f")) wordclass = "sc4";
      if (codeword.Contains("2f")) wordclass = "sc4";
      if (codeword.Contains("3f")) wordclass = "sc4";
      if (codeword.Contains("4f")) wordclass = "sc4";
      if (codeword.Contains("5f")) wordclass = "sc4";
      if (codeword.Contains("6f")) wordclass = "sc4";
      if (codeword.Contains("7f")) wordclass = "sc4";
      if (codeword.Contains("8f")) wordclass = "sc4";
      if (codeword.Contains("9f")) wordclass = "sc4";

      if (codeword.Equals("using")) wordclass = "sc16";
      if (codeword.Equals("const")) wordclass = "sc16";
      if (codeword.Equals("typeof")) wordclass = "sc16";
      if (codeword.Equals("System")) wordclass = "sc16";
      if (codeword.Equals("System;")) wordclass = "sc16";
      if (codeword.Equals("System.Collections.Generic")) wordclass = "sc16";
      if (codeword.Equals("System.ComponentModel")) wordclass = "sc16";
      if (codeword.Equals("System.Drawing")) wordclass = "sc16";
      if (codeword.Equals("System.Windows.Forms")) wordclass = "sc16";
      if (codeword.Equals("Microsoft.DirectX")) wordclass = "sc16";
      if (codeword.Equals("Microsoft.DirectX.Direct3D")) wordclass = "sc16";
      if (codeword.Equals("Microsoft.DirectX.DirectInput")) wordclass = "sc16";
      if (codeword.Equals("Microsoft.DirectX.DirectSound")) wordclass = "sc16";

      // Instruções rotineiras
      if (codeword.Equals("public")) wordclass = "prg";
      if (codeword.Equals("partial")) wordclass = "prg";
      if (codeword.Equals("private")) wordclass = "prg";
      if (codeword.Equals("class")) wordclass = "prg";
      if (codeword.Equals("for")) wordclass = "prg";
      if (codeword.Equals("foreach")) wordclass = "prg";
      if (codeword.Equals("void")) wordclass = "prg";
      if (codeword.Equals("double")) wordclass = "prg";
      if (codeword.Equals("new")) wordclass = "prg";
      if (codeword.Equals("int")) wordclass = "prg";
      if (codeword.Equals("uint")) wordclass = "prg";
      if (codeword.Equals("float")) wordclass = "prg";
      if (codeword.Equals("string")) wordclass = "prg";
      if (codeword.Equals("true")) wordclass = "prg";
      if (codeword.Equals("false")) wordclass = "prg";
      if (codeword.Equals("true;")) wordclass = "prg";
      if (codeword.Equals("false;")) wordclass = "prg";
      if (codeword.Equals("null;")) wordclass = "prg";
      if (codeword.Equals("null")) wordclass = "prg";
      if (codeword.Equals("this")) wordclass = "prg";
      if (codeword.Equals("this,")) wordclass = "prg";
      if (codeword.Equals("this;")) wordclass = "prg";
      if (codeword.Equals("(this)")) wordclass = "prg";
      if (codeword.Equals("struct")) wordclass = "prg";
      if (codeword.Equals("interface")) wordclass = "prg";
      if (codeword.Equals("internal")) wordclass = "prg";
      if (codeword.Equals("protected")) wordclass = "prg";
      if (codeword.Equals("override")) wordclass = "prg";
      if (codeword.Equals("if")) wordclass = "sc9";
      if (codeword.Equals("else")) wordclass = "sc9";
      if (codeword.Equals("do")) wordclass = "sc9";
      if (codeword.Equals("while")) wordclass = "sc9";
      if (codeword.Equals("switch")) wordclass = "sc9";
      if (codeword.Equals("bool")) wordclass = "prg";
      if (codeword.Equals("byte")) wordclass = "prg";
      if (codeword.Equals("return")) wordclass = "sc6";
      if (codeword.Equals("break")) wordclass = "sc6";
      if (codeword.Equals("break;")) wordclass = "sc6";
      if (codeword.Equals("out")) wordclass = "prg";
      if (codeword.Equals("ref")) wordclass = "prg";
      if (codeword.Equals("in")) wordclass = "prg";

      // Classes
      if (codeword.Equals("Audio")) wordclass = "sc5";
      if (codeword.Equals("Effect")) wordclass = "sc5";
      
      if (codeword.Equals("EventHandler")) wordclass = "sc5";
      if (codeword.Equals("Format")) wordclass = "sc5";
      if (codeword.Equals("KeyEventArgs")) wordclass = "sc5"; 

      if (codeword.Equals("object")) wordclass = "sc5";
      if (codeword.Equals("Vector2")) wordclass = "sc5";
      if (codeword.Equals("Vector3")) wordclass = "sc5";
      if (codeword.Equals("Vector4")) wordclass = "sc5";
      if (codeword.Equals("VertexDeclaration")) wordclass = "sc5";
      if (codeword.Equals("VertexElement")) wordclass = "sc5";
      if (codeword.Equals("Viewport")) wordclass = "sc5";
      if (codeword.Equals("Device")) wordclass = "sc5";
      if (codeword.Equals("Line")) wordclass = "sc5";
      if (codeword.Equals("IndexBuffer")) wordclass = "sc5";
      if (codeword.Equals("VertexBuffer")) wordclass = "sc5";
      if (codeword.Equals("Form")) wordclass = "sc5";
      if (codeword.Equals("Matrix")) wordclass = "sc5";
      if (codeword.Equals("Color")) wordclass = "sc5";
      if (codeword.Equals("Mesh")) wordclass = "sc5";
      if (codeword.Equals("BaseMesh")) wordclass = "sc5";
      if (codeword.Equals("Material")) wordclass = "sc5";
      if (codeword.Equals("ExtendedMaterial")) wordclass = "sc5";

      if (codeword.Equals("Rectangle")) wordclass = "sc5";
      if (codeword.Equals("Random")) wordclass = "sc5";
      if (codeword.Equals("RenderToSurface")) wordclass = "sc5";
      if (codeword.Equals("RenderToEnvironmentMap")) wordclass = "sc5";
      if (codeword.Equals("PaintEventArgs")) wordclass = "sc5";
      if (codeword.Equals("ProgressiveMesh")) wordclass = "sc5";
      if (codeword.Equals("PatchMesh")) wordclass = "sc5";


      if (codeword.Equals("Surface")) wordclass = "sc5";
      if (codeword.Equals("SimplificationMesh")) wordclass = "sc5";
      if (codeword.Equals("SurfaceCaps")) wordclass = "sc5";
      if (codeword.Equals("SurfaceDescription")) wordclass = "sc5";
      if (codeword.Equals("Sprite")) wordclass = "sc5";

      if (codeword.Equals("GraphicsStream")) wordclass = "sc5";
       if (codeword.Equals("Stream")) wordclass = "sc5";
      if (codeword.Equals("StreamWriter")) wordclass = "sc5";
       if (codeword.Equals("StreamReader")) wordclass = "sc5";
       if (codeword.Equals("StringBuilder")) wordclass = "sc5";
       if (codeword.Equals("String")) wordclass = "sc5"; 
      if (codeword.Equals("Texture")) wordclass = "sc5";
      if (codeword.Equals("WeldEpsilons")) wordclass = "sc5";
      if (codeword.Equals("WeldEpsilonsFlags")) wordclass = "sc5";


      if (codeword.Equals("Matrix.PerspectiveFovLH")) wordclass = "prg";
      if (codeword.Equals("Matrix.ProjectView")) wordclass = "prg";
      if (codeword.Equals("Matrix.LookAtLH")) wordclass = "prg";
      if (codeword.Equals("Matrix.RotationX")) wordclass = "prg";
      if (codeword.Equals("Matrix.RotationY")) wordclass = "prg";
      if (codeword.Equals("Matrix.RotationZ")) wordclass = "prg";
      if (codeword.Equals("Matrix.Translation")) wordclass = "prg";
      if (codeword.Equals("Mesh.FromFile")) wordclass = "prg";
      if (codeword.Equals("PresentParameters")) wordclass = "sc5";
      if (codeword.Equals("TextureLoader.FromFile")) wordclass = "prg";
      if (codeword.Equals("Video")) wordclass = "sc5";


      // Array das classes
      if (codeword.Equals("Vector3[]")) wordclass = "sc5";
      if (codeword.Equals("Vector4[]")) wordclass = "sc5";
      if (codeword.Equals("Device[]")) wordclass = "sc5";
      if (codeword.Equals("IndexBuffer[]")) wordclass = "sc5";
      if (codeword.Equals("VertexBuffer[]")) wordclass = "sc5";
      if (codeword.Equals("Form[]")) wordclass = "sc5";
      if (codeword.Equals("Matrix[]")) wordclass = "sc5";
      if (codeword.Equals("Color[]")) wordclass = "sc5";
      if (codeword.Equals("Mesh[]")) wordclass = "sc5";
      if (codeword.Equals("Material[]")) wordclass = "sc5";
      if (codeword.Equals("ExtendedMaterial[]")) wordclass = "sc5";
      if (codeword.Equals("Texture[]")) wordclass = "sc5";

      // Instruções dispersas e pontuações
      if (codeword.Equals("namespace")) wordclass = "sc16";
      if (codeword.Equals("{")) wordclass = "sc16";
      if (codeword.Equals("}")) wordclass = "sc16";
      if (codeword.Equals("};")) wordclass = "sc16";
      if (codeword.Equals("//")) wordclass = "sc2";

      return wordclass;
    } // getWordClass().fim
    // ---] -

    // [--- -
    private string spanification(string[] codewords, string[] wordclasses, string wspaces, string linha_feia)
    {
      string span = null;
      string logica = "";
      string next_class = null;
      string old_class = null;
      int ntam = codewords.Length;
      ntam = codewords.Length;

      // Se a linha for de comentários dispense-a rapidamente
      if (codewords[0] == "//")
      {
        span = String.Format("{0}<span class={1}>{2}</span>", wspaces, wordclasses[0], linha_feia);
        return span;
      } // endif


      // Se houver apenas uma codeword dispense-a rapidamente
      if (ntam == 1)
      {
        if (wordclasses[0] != "no_fmt")
        {
          span = String.Format("{0}<span class={1}>{2}</span>", wspaces, wordclasses[0], linha_feia);
        } // endif

        if (wordclasses[0] == "no_fmt")
        {
          span = String.Format("{0}{1}</span>", wspaces, linha_feia);
        } // endif


        return span;

      } // endif

      // Se houver apenas uma codeword dispense-a rapidamente
      if (linha_feia.Contains("//"))
      {
        linha_feia = linha_feia.Replace("//", "<span class=sc2>//");
        linha_feia = linha_feia.Replace("{", "<span class=sc16>{</span>");
        linha_feia += "</span>";
        span = String.Format("{0}<span class={1}>{2}</span>", wspaces, wordclasses[0], linha_feia);
        return span;
      } // endif


      for (int ncx = 0; ncx < (ntam - 1); ncx++)
      {
        if (ntam > 1) next_class = codewords[ncx + 1];
        if (ncx > 0) old_class = codewords[ncx - 1];
        if (ncx == 0) span += wspaces;

        if (wordclasses[ncx] == old_class) logica += "=";
        if (wordclasses[ncx] != old_class) logica += "#";
        if (wordclasses[ncx] == next_class) logica += "=";
        if (wordclasses[ncx] != next_class) logica += "#";

        // 01.classe atual diferente da classe anterior e diferente da próxima classe
        // Abro o span e fecho-o
        if (logica.Equals("##"))
        {
          if (wordclasses[ncx] != "no_fmt")
          {
            span += String.Format("<span class={0}>{1} </span>", wordclasses[ncx], codewords[ncx]);
          } // endif

          if (wordclasses[ncx] == "no_fmt")
          {
            span += String.Format("{0} ", codewords[ncx]);
          } // endif
        } // endif

        // 02.classe atual igual à classe anterior e diferente da próxima classe
        // Não Abro o span mas fecho-o
        if (logica.Equals("=#"))
        {
          if (wordclasses[ncx] != "no_fmt")
          {
            span += String.Format("{1} </span>", codewords[ncx]);
          } // endif

          if (wordclasses[ncx] == "no_fmt")
          {
            span += String.Format("{0} ", codewords[ncx]);
          } // endif
        } // endif


        // 03.classe atual igual à classe anterior e igual a próxima classe
        // Não Abro o span e não fecho-o
        if (logica.Equals("=="))
        {
          if (wordclasses[ncx] != "no_fmt ==")
          {
            span += codewords[ncx];
          } // endif

          if (wordclasses[ncx] == "no_fmt")
          {
            span += String.Format("{0} ", codewords[ncx]);
          } // endif
        } // endif


        // 04.classe atual diferente da classe anterior e igual a próxima classe
        // Abro o span e não fecho-o
        if (logica.Equals("#="))
        {
          if (wordclasses[ncx] != "no_fmt")
          {
            span += String.Format("<span class={0}>{1} ", wordclasses[ncx], codewords[ncx]);
          } // endif

          if (wordclasses[ncx] == "no_fmt")
          {
            span += String.Format("{0} ", codewords[ncx]);
          } // endif
        } // endif

        logica = "";

      } // endfor

      // Conserta última palavra   
      ntam = codewords.Length;
      ntam--;
      old_class = codewords[ntam - 1];
      logica = "";
      if (wordclasses[ntam] == old_class) logica += "=";
      if (wordclasses[ntam] != old_class) logica += "#";

      // 01.classe atual igual a classe anterior
      // Apenas fecho o span
      if (logica.Equals("="))
      {
        if (wordclasses[ntam] != "no_fmt")
        {
          span += String.Format("{0}</span>", codewords[0]);
        } // endif

        if (wordclasses[ntam] == "no_fmt")
        {
          span += String.Format("{0} ", codewords[ntam]);
        } // endif
      } // endif

      // 01.classe atual diferente da classe anterior
      // Abro e fecho o span
      if (logica.Equals("#"))
      {
        if (wordclasses[ntam] != "no_fmt")
        {
          span += String.Format("<span class={0}>{1}</span>", wordclasses[ntam], codewords[ntam]);
        } // endif

        if (wordclasses[ntam] == "no_fmt")
        {
          span += String.Format("{0} ", codewords[ntam]);
        } // endif
      } // endif
      return span;
    } // spanification().fim
    // ---] -

    private string bonitificar_linha(string linha_feia)
    {

           
      // Se a linha for null vá embora
      if (linha_feia == null) return linha_feia;

      // Vamos pegar os espaços iniciais
      linha_feia = linha_feia.TrimEnd();
      string wespaces = null;
      wespaces = getWhiteSpace(linha_feia);

      // Limpa a linha
      linha_feia = linha_feia.Trim();
      if (linha_feia == String.Empty) return linha_feia;

      if (linha_feia.Contains("// [---"))
      {
      
        return "";
      }

      if (linha_feia.Contains("// ---]"))
      {
        recortar = 2;
        return "";
      }



      string[] palavras = null;
      string[] wclasses = null;
      int npalavras = 0;
      string espanificado = null;

      // Camufla caracteres com significados especiais em html
      if (linha_feia.Contains("<")) linha_feia = linha_feia.Replace("<", "&lt;");
      if (linha_feia.Contains(">")) linha_feia = linha_feia.Replace(">", "&gt;");

      // Camufla os espaços em brancos das strings
      if (linha_feia.Contains("\""))
        linha_feia = camuflarString(linha_feia);

      // Realiza espaçamento de pontuação especiais
      if (linha_feia.Contains("(")) linha_feia = linha_feia.Replace("(", " ( ");
      if (linha_feia.Contains("+")) linha_feia = linha_feia.Replace("+", " + ");
      if (linha_feia.Contains(")")) linha_feia = linha_feia.Replace(")", " ) ");
      if (linha_feia.Contains("[")) linha_feia = linha_feia.Replace("[", " [ ");
      if (linha_feia.Contains("]")) linha_feia = linha_feia.Replace("]", " ] ");
      if (linha_feia.Contains(",")) linha_feia = linha_feia.Replace(",", " , ");
      if (linha_feia.Contains(" ;")) linha_feia = linha_feia.Replace(" ;", " ; ");

      // Fatia a linha em várias palavras
      palavras = linha_feia.Split();

      npalavras = palavras.Length;
      wclasses = new string[npalavras];

      // Carrega lista de classes
      for (int ncx = 0; ncx < npalavras; ncx++)
      {
        wclasses[ncx] = getWordClass(palavras[ncx]);
      } // endfor each


      espanificado = spanification(palavras, wclasses, wespaces, linha_feia);

      // Remove espaçamento extra de pontuação especiais
      if (espanificado.Contains(" ( ")) espanificado = espanificado.Replace(" ( ", "(");
      if (espanificado.Contains(" ) ")) espanificado = espanificado.Replace(" ) ", ")");
      if (espanificado.Contains(" [ ")) espanificado = espanificado.Replace(" [ ", "[");
      if (espanificado.Contains(" ] ")) espanificado = espanificado.Replace(" ] ", "]");
      if (espanificado.Contains(" , ")) espanificado = espanificado.Replace(" , ", ",");
      if (espanificado.Contains(" ; ")) espanificado = espanificado.Replace(" ; ", "; ");
      if (espanificado.Contains(" ,")) espanificado = espanificado.Replace(" ,", ",");
      if (espanificado.Contains(" ;")) espanificado = espanificado.Replace(" ;", "; ");
      if (espanificado.Contains(" </span>,")) espanificado = espanificado.Replace(" </span>,", "</span>,");
      if (espanificado.Contains("</span>,  ")) espanificado = espanificado.Replace("</span>,  ", "</span>, ");
      if (espanificado.Contains(" </span>;")) espanificado = espanificado.Replace(" </span>;", "</span>;");
      if (espanificado.Contains(" </span>)")) espanificado = espanificado.Replace(" </span>)", "</span>)");
      if (espanificado.Contains(" </span>( ")) espanificado = espanificado.Replace(" </span>( ", "</span>(");
      if (espanificado.Contains(" </span>) ")) espanificado = espanificado.Replace(" </span>) ", "</span>)");
      if (espanificado.Contains(" </span>[ ")) espanificado = espanificado.Replace(" </span>[ ", "</span>[");
      if (espanificado.Contains(" </span>] ")) espanificado = espanificado.Replace(" </span>] ", "</span>]");
      if (espanificado.Contains("¢")) espanificado = espanificado.Replace("¢", " ");
      if (espanificado.Contains(" + ")) espanificado = espanificado.Replace(" + ", "+");

      return espanificado;

    } // bonitificar_linha().fim

    private void LoadCss()
    {
      StreamReader css_fluxo = new StreamReader(@"d:\Misc\Apostila\css_mdx9.css");
      string temp_line = null;

      sb_css = new StringBuilder();

      do
      {
        temp_line = css_fluxo.ReadLine();
        sb_css.AppendLine(temp_line);
      } while (temp_line != null);

      css_fluxo.Close();


    } // LoadCss().fim

    string getWhiteSpace(string linha_feia)
    {
      int ntam = 0;
      string temp = "";
      string letter = "";
      ntam = linha_feia.Length;

      for (int ncx = 0; ncx < ntam; ncx++)
      {
        letter = linha_feia.Substring(ncx, 1);
        if (letter.Equals(" ")) temp += " ";
        if (letter.Equals("\t")) temp += "  ";
        if ((letter != " ") && (letter != "\t")) break;
      } // endfor
      return temp;
    } // getWhiteSpace().fim


    public string camuflarString(string linha_feia)
    {
      string temp = "";
      string letter = "";
      string letterBefore = "";

      int ntam = linha_feia.Length;
      int camuflador = -1;

      for (int ncx = 0; ncx < ntam; ncx++)
      {
        letter = linha_feia.Substring(ncx, 1);

        if (ncx > 0) letterBefore = linha_feia.Substring(ncx - 1, 1);

        if (letterBefore != @"\")
        {
          if (letter == "\"") camuflador = camuflador * -1;
        } // endif   


        if ((camuflador == 1) && (letter == " ")) letter = "¢";
        if ((camuflador == 1) && (letter == "\t")) letter = "¢¢";

        temp += letter;
      } // endfor

      return temp;

    } // camuflarString().end

    private string openRecorte()
    {
      string stemp = "";
      stemp = "<b><u>2.x Fazendo alguma coisa</u></b>\n";
      stemp += "<div class=niceview>";
      return stemp;
    } // openRecorte().fim


  } // fim da classe
} // fim do namespace
