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
  public partial class dlgApostila : Form
  {

    private Apostila track = null;


    
    public dlgApostila()
    {
      InitializeComponent();
      
      track = new Apostila();      

    }

    private void textBox2_TextChanged(object sender, EventArgs e)
    {

    }

    private void dlgApostila_Load(object sender, EventArgs e)
    {

    }

    private void btnSair_Click(object sender, EventArgs e)
    {
      this.Close();

    }

    private void btnDefault_Click(object sender, EventArgs e)
    {
      string temp = null;
      
      temp = txtPrj_Exemplo.Text;
      temp = temp.Trim();

      txtPrj_ExemploEsquema.Text = "esquema" + "_" + temp + ".png";
      txtPrj_ExemploSnapshot.Text = temp + ".png";
      txtPrj_ExemploVisaoGeralImg.Text  = temp + ".png";

    }

   
    private void btnGerarApostila_Click(object sender, EventArgs e)
    {    
      track.htmlfile = "apostila.html";
      track.savefolder = @"d:\misc\apostila";
      track.title = "Apostila";
      track.objetivo = txtObjetivo.Text;
      track.cursotec = txtCursoTec.Text;


      track.nchapter = Convert.ToInt32(txtCapitulo.Text);
      track.ntopic = Convert.ToInt32(txtTopico.Text);

      track.prj_exemplo_esquema = txtPrj_ExemploEsquema.Text ;
      track.prj_exemplo_snapshot = txtPrj_ExemploSnapshot.Text;
      track.prj_exemplo = txtPrj_Exemplo.Text;

      track.makeTitle("mdx9");

      track.sourcefile = "";

      track.gerarApostila();   
    }

    private void label1_Click(object sender, EventArgs e)
    {

    }

    private void label2_Click(object sender, EventArgs e)
    {

    }

    private void btnSalvarConfig_Click(object sender, EventArgs e)
    {
      
      ApostilaConfig config = new ApostilaConfig();
      config.capitulo = txtCapitulo.Text;
      config.objetivo = txtObjetivo.Text;
      config.prjExemplo = txtPrj_Exemplo.Text;
      config.topico = txtTopico.Text;
      config.cursotec = txtCursoTec.Text;
      config.salvar("apostila.bin");     

    } 

    private void btnCarregarConfig_Click(object sender, EventArgs e)
    {
      ApostilaConfig config = new ApostilaConfig();
      config = config.carregar("apostila.bin");

      if (config == null) return;

     
      txtCapitulo.Text = config.capitulo;
      txtObjetivo.Text = config.objetivo;
      txtPrj_Exemplo.Text = config.prjExemplo;
      txtTopico.Text= config.topico;
      txtCursoTec.Text = config.cursotec;


      btnDefault_Click(sender, e);
            
    }

    
  }
}
