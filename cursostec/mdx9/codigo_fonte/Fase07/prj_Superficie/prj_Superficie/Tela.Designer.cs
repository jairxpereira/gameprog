// prj_Superficie - Arquivo: Tela.Designer.cs
// Esse projeto mostra como renderizar na textura, salvar uma
// imagem da tela e configurar a função callback de reconfiguração
// do dispositivo.
// Produzido por www.gameprog.com.br

namespace prj_Superficie
{
  partial class Tela
  {
    /// <summary>
    /// Required designer variable.
    /// </summary>
    private System.ComponentModel.IContainer components = null;

    /// <summary>
    /// Clean up any resources being used.
    /// </summary>
    /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
    protected override void Dispose(bool disposing)
    {
      if (disposing && (components != null))
      {
        components.Dispose();
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
      // Tela
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(632, 453);
      this.Name = "Tela";
      this.Text = "prj_Superficie";
      this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Tela_KeyDown);
      this.ResumeLayout(false);

    }

    #endregion
  }
}

