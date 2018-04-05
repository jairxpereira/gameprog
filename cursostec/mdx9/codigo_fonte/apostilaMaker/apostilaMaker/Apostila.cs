using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Windows.Forms;

namespace apostilaMaker
{
  
  class Apostila
  {

    // Arquivo html
    public string htmlfile;
    public string header;
    public string body;
    public string title;
    public string savefolder;
    public string sourcefile;
    public string cursotec;

    StringBuilder sb_css = null;

    public int nchapter;
    public int ntopic;
    public string nextlink;
    public string previouslink;
    private string fase;
    public string objetivo;

    public string prj_exemplo;
    public string prj_exemplo_snapshot;
    public string prj_exemplo_esquema;
    // ---]

    public Apostila()
    {
      htmlfile = "track-0x-x.html";
      title = "Gameprog";
      cursotec = "";
      LoadCss();
    }


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
      string temp = "";

      temp += "<hr>\n";
      temp += "<table align='bottom' border='0' cellspacing='0' cellpadding='0' width='20%'>\n";
      temp += "<tr><td><a href='mdx9.html#start' style='color:blue'> index </a></td>\n";
      temp += String.Format("<td><a href='{0}' style='color:blue'>&lt;&lt;</a></td>\n", this.previouslink);
      temp += String.Format("<td><a href='{0}' style='color:blue'>&gt;&gt;</a></td></tr></table><pre>\n", this.nextlink);
      temp += "<hr><div style='background-color:lightyellow;color:blue'>\n";
      temp += "<center>Produzido por Gameprog: Jair Pereira - Março/2014 ©\n";
      temp += "gameprog.br@gmail.com\n";
      temp += "<a href='http://www.gameprog.com.br'>http://www.gameprog.com.br</center><hr></div></div></body></html>\n";

      this.body = temp;
      return this.body;
    } // closeBody().fim

    private string openBody()
    {

      string temp = "";
      string info = "";

      temp += "<body class=mybody><font color='black'>\n";
      temp += "<div class=pagebody>\n";
      temp += "<hr>\n";

      info = string.Format("<center><b style='font-size:1.5em;' >{0}</b><br>\n", cursotec);
      temp += info;      
      
      temp += "Gameprog - Escola de programação de jogos digitais<br>\n";
      temp += "Contato: gameprog.br@gmail.com<br>\n";
      temp += String.Format("<b>{0}</b></center>\n", this.fase);
      temp += "<hr>\n";
      temp += "<table align='left' border='0' cellspacing='0' cellpadding='0' width='20%'>\n";
      temp += "<tr><td><a href='mdx9.html#start' style='color:blue'> index </a></td>\n";

      temp += String.Format("<td><a href='{0}' style='color:blue'>&lt;&lt;</a></td>\n", this.previouslink);

      temp += String.Format("<td><a href='{0}' style='color:blue'>&gt;&gt;</a></td></tr></table><br><pre>\n",
        this.nextlink);

      temp += "<hr><a name='topo'></a>\n";
      temp += String.Format("<h3 style='background-color:#80ff80'>{0}</h3><pre>\n",
        this.objetivo);

      // temp += "\n";
      temp += "<b><u>1.1 Visão geral</b></u>\n";

      temp +="<div class=prg-code>";
      temp += String.Format ("<img src=images\\{0}>", this.prj_exemplo_snapshot );
      temp +="</div>\n";

      temp +="<b><u>1.2 Estrutura principal da aplicação</b></u>\n";
      temp += "<div class=prg-code>\n";
      temp += String.Format ("<img src=images\\{0}></div>\n", this.prj_exemplo_esquema );

      this.body = temp;
      return this.body;
    } // openBody().fim

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

    public void gerarApostila()
    {
      // Abre o arquivo para gravação
      string fullpath_saida = this.savefolder + "\\" + this.htmlfile;
      
      string fullpath_entrada = this.sourcefile;
      fullpath_entrada = @"d:\misc\apostila\temp.html";


      string linha = null;
      string temp = null;

      StreamWriter html_fluxo = new StreamWriter(fullpath_saida, false);
      StreamReader cs_influxo = new StreamReader(fullpath_entrada);

      // Gravando os dados...
      html_fluxo.WriteLine(openHeader());
      if (sb_css != null) html_fluxo.WriteLine(sb_css.ToString());

      html_fluxo.WriteLine(closeHeader());
      html_fluxo.WriteLine(openBody());
      
      html_fluxo.WriteLine(loadRecorte(null));


      // Insere código do projeto de exemplo
      temp = String.Format("<b><u>3. Código fonte do projeto de exemplo:{0}</u></b>\n",
        this.prj_exemplo);      
      temp += "<div class=prg-code>\n";
      temp += String.Format("<img src=images\\{0}>\n", this.prj_exemplo_snapshot);
      html_fluxo.WriteLine(temp);
 
      do
      {
        linha = cs_influxo.ReadLine();
        html_fluxo.WriteLine(linha);
      } while (linha != null);
      html_fluxo.WriteLine("</div>\n");

      html_fluxo.WriteLine(closeBody());
      html_fluxo.Close();
      // cs_influxo.Close();

      Process.Start(new ProcessStartInfo("notepad.exe ", fullpath_saida));
      Process.Start(new
        ProcessStartInfo(@"C:\Users\admin\AppData\Local\Google\Chrome\Application\chrome.exe ",
        fullpath_saida));
    } // gerarApostila().fim
     


    public void makeTitle(string curso)
    {
      string temp = "";
      int nbefore;
      int nafter;

      nbefore = ntopic - 1;
      nafter = ntopic + 1;


      if (nchapter < 10)
      {
        temp = curso + "_fase0" + this.nchapter.ToString() + "-" + this.ntopic.ToString();
        this.htmlfile = "track0" + this.nchapter.ToString() + "-" + this.ntopic.ToString();
        this.htmlfile += ".html";
        this.fase = "Fase 0" + this.nchapter.ToString() + "-" + this.ntopic.ToString();
        this.previouslink = "track0" + this.nchapter.ToString()
          + "-" + nbefore.ToString() + ".html";
        this.nextlink = "track0" + this.nchapter.ToString()
          + "-" + nafter.ToString() + ".html";

        this.objetivo = "0" + this.nchapter.ToString() + "." + this.ntopic.ToString() + " " + this.objetivo;
      } // endif

      if (nchapter > 9)
      {
        temp = curso + "_fase" + this.nchapter.ToString() + "-" + this.ntopic.ToString();
        this.htmlfile = "track" + this.nchapter.ToString() + "-" + this.ntopic.ToString();
        this.htmlfile += ".html";
        this.fase = "Fase " + this.nchapter.ToString() + "-" + this.ntopic.ToString();
        this.previouslink = "track" + this.nchapter.ToString()
          + "-" + nbefore.ToString() + ".html";
        this.nextlink = "track" + this.nchapter.ToString()
          + "-" + nafter.ToString() + ".html";
        this.objetivo = this.nchapter.ToString() + "." + this.ntopic.ToString() + " " + this.objetivo;
      } // endif

      this.title = temp;
    } // makeTitle().fim

    private string loadRecorte(string arquivo)
    {
      string sLinha = "";
      if (arquivo == null) arquivo = this.savefolder + "\\" + "recorte.html";
      StreamReader html_influxo = new StreamReader(arquivo);
      StringBuilder sb_recorte = new StringBuilder();

      do
      {
        sLinha = html_influxo.ReadLine();
        sb_recorte.AppendLine(sLinha);

      } while (sLinha != null);

      html_influxo.Close();
      return sb_recorte.ToString();    
    
    } // loadRecorte().fim

  } // fim da classe
} // fim do namespace
