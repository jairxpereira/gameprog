﻿// prj_EntradaPontoNet - Arquivo: Tela.Designer.cs
// Esse projeto mostra como usar o teclado e mouse via 
// Framework .net - Produzido por www.gameprog.com.br
namespace prj_EntradaPontoNet
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
      this.ClientSize = new System.Drawing.Size(329, 277);
      this.Name = "Tela";
      this.Text = "prj_EntradaPontoNet";
      this.MouseUp += new System.Windows.Forms.MouseEventHandler(this.Tela_MouseUp);
      this.MouseDown += new System.Windows.Forms.MouseEventHandler(this.Tela_MouseDown);
      this.KeyUp += new System.Windows.Forms.KeyEventHandler(this.Tela_KeyUp);
      this.KeyDown += new System.Windows.Forms.KeyEventHandler(this.Tela_KeyDown);
      this.ResumeLayout(false);

    }

    #endregion
  }
}

