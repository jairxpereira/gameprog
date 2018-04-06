using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace apostilaMaker
{
  public partial class owndMain : Form
  {
    public owndMain()
    {
      InitializeComponent();
    }

    private void btnLoadFile_Click(object sender, EventArgs e)
    {

      string nome_arquivo = null;      
      dlgOpenFile.ShowDialog();
      nome_arquivo = dlgOpenFile.FileName;
      txtCSharpFile.Text = nome_arquivo;

      // btnLoadFile_Click().fim

    }

    private void owndMain_Load(object sender, EventArgs e)
    {
      this.BackColor = Color.LightGray  ;         


    }

    private void btnEscolherPasta_Click(object sender, EventArgs e)
    {
      dlgPastasBrowser.ShowDialog();
      txtOutputFolder.Text = dlgPastasBrowser.SelectedPath;

    }

    private void btnMakehtml_Click(object sender, EventArgs e)
    {

      string temp_btnText = "";
        temp_btnText = btnMakehtml.Text;

        btnMakehtml.Text = "Processando...";
        this.Update();

      HtmlMaker cshtml = new HtmlMaker();
      cshtml.aviso = lblAviso;


      cshtml.htmlfile = "temp.html";
      cshtml.savefolder = txtOutputFolder.Text;
      cshtml.title = "prj_DirectInput";
      
      cshtml.sourcefile = txtCSharpFile.Text;

      cshtml.bonitificarCodigo();

      btnMakehtml.Text = temp_btnText;

      lblAviso.Text = "Ok. Arquivo transformado em html!";
      
      
    }

    private void btnSair_Click(object sender, EventArgs e)
    {
      Application.Exit();

    }

    private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
    {

    }

    private void propriedadesToolStripMenuItem_Click(object sender, EventArgs e)
    {
      Form dlg = new dlgApostila();
      dlg.Show();

    }

    private void button1_Click(object sender, EventArgs e)
    {
      this.Text = Location.ToString();


    }

    private void btnApostilaMaker_Click(object sender, EventArgs e)
    {
      Form  dlg = new dlgApostila();      
      dlg.ShowDialog();      
    }
  }
}
