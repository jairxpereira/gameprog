// Prj_Lab01 - Arquivo: Janela.Designer.cs
// Esse projeto permite acompanhar visualmente a manipulação dos
// argumentos das matrizes de projeção, visualização e espaço mundial
// Produzido por www.gameprog.com.br
namespace prj_Lab01
{
  partial class Janela
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
      this.Tela = new System.Windows.Forms.PictureBox();
      this.chkx = new System.Windows.Forms.CheckBox();
      this.chky = new System.Windows.Forms.CheckBox();
      this.chkz = new System.Windows.Forms.CheckBox();
      this.btnUp = new System.Windows.Forms.Button();
      this.btnDown = new System.Windows.Forms.Button();
      this.btnVectorLeft = new System.Windows.Forms.Button();
      this.btnVectorCenter = new System.Windows.Forms.Button();
      this.btnVectorRight = new System.Windows.Forms.Button();
      this.btnProjection = new System.Windows.Forms.Button();
      this.btnWorld = new System.Windows.Forms.Button();
      this.btnView = new System.Windows.Forms.Button();
      this.txt_m11 = new System.Windows.Forms.TextBox();
      this.txt_m12 = new System.Windows.Forms.TextBox();
      this.txt_m13 = new System.Windows.Forms.TextBox();
      this.txt_m23 = new System.Windows.Forms.TextBox();
      this.txt_m22 = new System.Windows.Forms.TextBox();
      this.txt_m21 = new System.Windows.Forms.TextBox();
      this.txt_m33 = new System.Windows.Forms.TextBox();
      this.txt_m32 = new System.Windows.Forms.TextBox();
      this.txt_m31 = new System.Windows.Forms.TextBox();
      this.btnReset = new System.Windows.Forms.Button();
      this.label1 = new System.Windows.Forms.Label();
      this.label2 = new System.Windows.Forms.Label();
      this.label3 = new System.Windows.Forms.Label();
      this.txtWorld_m33 = new System.Windows.Forms.TextBox();
      this.txtWorld_m32 = new System.Windows.Forms.TextBox();
      this.txtWorld_m31 = new System.Windows.Forms.TextBox();
      this.txtWorld_m23 = new System.Windows.Forms.TextBox();
      this.txtWorld_m22 = new System.Windows.Forms.TextBox();
      this.txtWorld_m21 = new System.Windows.Forms.TextBox();
      this.txtWorld_m13 = new System.Windows.Forms.TextBox();
      this.txtWorld_m12 = new System.Windows.Forms.TextBox();
      this.txtWorld_m11 = new System.Windows.Forms.TextBox();
      this.txtProjet_m31 = new System.Windows.Forms.TextBox();
      this.txtProjet_m21 = new System.Windows.Forms.TextBox();
      this.txtProjet_m11 = new System.Windows.Forms.TextBox();
      this.btnSair = new System.Windows.Forms.Button();
      this.label4 = new System.Windows.Forms.Label();
      this.label5 = new System.Windows.Forms.Label();
      this.label6 = new System.Windows.Forms.Label();
      this.label7 = new System.Windows.Forms.Label();
      this.label8 = new System.Windows.Forms.Label();
      this.label9 = new System.Windows.Forms.Label();
      ((System.ComponentModel.ISupportInitialize)(this.Tela)).BeginInit();
      this.SuspendLayout();
      // 
      // Tela
      // 
      this.Tela.Location = new System.Drawing.Point(12, 12);
      this.Tela.Name = "Tela";
      this.Tela.Size = new System.Drawing.Size(356, 319);
      this.Tela.TabIndex = 0;
      this.Tela.TabStop = false;
      // 
      // chkx
      // 
      this.chkx.AutoSize = true;
      this.chkx.Location = new System.Drawing.Point(374, 16);
      this.chkx.Name = "chkx";
      this.chkx.Size = new System.Drawing.Size(33, 17);
      this.chkx.TabIndex = 1;
      this.chkx.Text = "X";
      this.chkx.UseVisualStyleBackColor = true;
      // 
      // chky
      // 
      this.chky.AutoSize = true;
      this.chky.Location = new System.Drawing.Point(442, 16);
      this.chky.Name = "chky";
      this.chky.Size = new System.Drawing.Size(33, 17);
      this.chky.TabIndex = 2;
      this.chky.Text = "Y";
      this.chky.UseVisualStyleBackColor = true;
      // 
      // chkz
      // 
      this.chkz.AutoSize = true;
      this.chkz.Checked = true;
      this.chkz.CheckState = System.Windows.Forms.CheckState.Checked;
      this.chkz.Location = new System.Drawing.Point(495, 16);
      this.chkz.Name = "chkz";
      this.chkz.Size = new System.Drawing.Size(33, 17);
      this.chkz.TabIndex = 3;
      this.chkz.Text = "Z";
      this.chkz.UseVisualStyleBackColor = true;
      // 
      // btnUp
      // 
      this.btnUp.Location = new System.Drawing.Point(109, 337);
      this.btnUp.Name = "btnUp";
      this.btnUp.Size = new System.Drawing.Size(259, 27);
      this.btnUp.TabIndex = 4;
      this.btnUp.Text = "++";
      this.btnUp.UseVisualStyleBackColor = true;
      this.btnUp.Click += new System.EventHandler(this.btnUp_Click);
      // 
      // btnDown
      // 
      this.btnDown.Location = new System.Drawing.Point(110, 372);
      this.btnDown.Name = "btnDown";
      this.btnDown.Size = new System.Drawing.Size(258, 27);
      this.btnDown.TabIndex = 5;
      this.btnDown.Text = "--";
      this.btnDown.UseVisualStyleBackColor = true;
      this.btnDown.Click += new System.EventHandler(this.btnDown_Click);
      // 
      // btnVectorLeft
      // 
      this.btnVectorLeft.Location = new System.Drawing.Point(15, 337);
      this.btnVectorLeft.Name = "btnVectorLeft";
      this.btnVectorLeft.Size = new System.Drawing.Size(88, 28);
      this.btnVectorLeft.TabIndex = 6;
      this.btnVectorLeft.Text = "Vector.Left";
      this.btnVectorLeft.UseVisualStyleBackColor = true;
      this.btnVectorLeft.Click += new System.EventHandler(this.btnVectorLeft_Click);
      // 
      // btnVectorCenter
      // 
      this.btnVectorCenter.Location = new System.Drawing.Point(15, 371);
      this.btnVectorCenter.Name = "btnVectorCenter";
      this.btnVectorCenter.Size = new System.Drawing.Size(88, 28);
      this.btnVectorCenter.TabIndex = 7;
      this.btnVectorCenter.Text = "Vector.Center";
      this.btnVectorCenter.UseVisualStyleBackColor = true;
      this.btnVectorCenter.Click += new System.EventHandler(this.btnVectorCenter_Click);
      // 
      // btnVectorRight
      // 
      this.btnVectorRight.Location = new System.Drawing.Point(15, 405);
      this.btnVectorRight.Name = "btnVectorRight";
      this.btnVectorRight.Size = new System.Drawing.Size(88, 28);
      this.btnVectorRight.TabIndex = 8;
      this.btnVectorRight.Text = "Vector.Right";
      this.btnVectorRight.UseVisualStyleBackColor = true;
      this.btnVectorRight.Click += new System.EventHandler(this.btnVectorRight_Click);
      // 
      // btnProjection
      // 
      this.btnProjection.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.btnProjection.Location = new System.Drawing.Point(374, 259);
      this.btnProjection.Name = "btnProjection";
      this.btnProjection.Size = new System.Drawing.Size(246, 28);
      this.btnProjection.TabIndex = 9;
      this.btnProjection.Text = "device.Transform.Projection";
      this.btnProjection.UseVisualStyleBackColor = true;
      this.btnProjection.Click += new System.EventHandler(this.btnProjection_Click);
      // 
      // btnWorld
      // 
      this.btnWorld.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.btnWorld.Location = new System.Drawing.Point(374, 147);
      this.btnWorld.Name = "btnWorld";
      this.btnWorld.Size = new System.Drawing.Size(246, 28);
      this.btnWorld.TabIndex = 10;
      this.btnWorld.Text = "device.Transform.World";
      this.btnWorld.UseVisualStyleBackColor = true;
      this.btnWorld.Click += new System.EventHandler(this.btnWorld_Click);
      // 
      // btnView
      // 
      this.btnView.Font = new System.Drawing.Font("Arial", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.btnView.Location = new System.Drawing.Point(374, 35);
      this.btnView.Name = "btnView";
      this.btnView.Size = new System.Drawing.Size(248, 28);
      this.btnView.TabIndex = 11;
      this.btnView.Text = "device.Transform.View";
      this.btnView.UseVisualStyleBackColor = true;
      this.btnView.Click += new System.EventHandler(this.btnView_Click);
      // 
      // txt_m11
      // 
      this.txt_m11.Location = new System.Drawing.Point(374, 69);
      this.txt_m11.Name = "txt_m11";
      this.txt_m11.Size = new System.Drawing.Size(47, 20);
      this.txt_m11.TabIndex = 12;
      // 
      // txt_m12
      // 
      this.txt_m12.Location = new System.Drawing.Point(428, 69);
      this.txt_m12.Name = "txt_m12";
      this.txt_m12.Size = new System.Drawing.Size(47, 20);
      this.txt_m12.TabIndex = 13;
      // 
      // txt_m13
      // 
      this.txt_m13.Location = new System.Drawing.Point(481, 69);
      this.txt_m13.Name = "txt_m13";
      this.txt_m13.Size = new System.Drawing.Size(47, 20);
      this.txt_m13.TabIndex = 14;
      // 
      // txt_m23
      // 
      this.txt_m23.Location = new System.Drawing.Point(481, 95);
      this.txt_m23.Name = "txt_m23";
      this.txt_m23.Size = new System.Drawing.Size(47, 20);
      this.txt_m23.TabIndex = 17;
      // 
      // txt_m22
      // 
      this.txt_m22.Location = new System.Drawing.Point(428, 95);
      this.txt_m22.Name = "txt_m22";
      this.txt_m22.Size = new System.Drawing.Size(47, 20);
      this.txt_m22.TabIndex = 16;
      // 
      // txt_m21
      // 
      this.txt_m21.Location = new System.Drawing.Point(374, 95);
      this.txt_m21.Name = "txt_m21";
      this.txt_m21.Size = new System.Drawing.Size(47, 20);
      this.txt_m21.TabIndex = 15;
      // 
      // txt_m33
      // 
      this.txt_m33.Location = new System.Drawing.Point(481, 121);
      this.txt_m33.Name = "txt_m33";
      this.txt_m33.Size = new System.Drawing.Size(47, 20);
      this.txt_m33.TabIndex = 20;
      // 
      // txt_m32
      // 
      this.txt_m32.Location = new System.Drawing.Point(428, 121);
      this.txt_m32.Name = "txt_m32";
      this.txt_m32.Size = new System.Drawing.Size(47, 20);
      this.txt_m32.TabIndex = 19;
      // 
      // txt_m31
      // 
      this.txt_m31.Location = new System.Drawing.Point(374, 121);
      this.txt_m31.Name = "txt_m31";
      this.txt_m31.Size = new System.Drawing.Size(47, 20);
      this.txt_m31.TabIndex = 18;
      // 
      // btnReset
      // 
      this.btnReset.Location = new System.Drawing.Point(109, 405);
      this.btnReset.Name = "btnReset";
      this.btnReset.Size = new System.Drawing.Size(259, 28);
      this.btnReset.TabIndex = 21;
      this.btnReset.Text = "RESET";
      this.btnReset.UseVisualStyleBackColor = true;
      this.btnReset.Click += new System.EventHandler(this.btnReset_Click);
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label1.Location = new System.Drawing.Point(534, 69);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(57, 13);
      this.label1.TabIndex = 22;
      this.label1.Text = "cam_pos";
      // 
      // label2
      // 
      this.label2.AutoSize = true;
      this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label2.Location = new System.Drawing.Point(534, 97);
      this.label2.Name = "label2";
      this.label2.Size = new System.Drawing.Size(61, 13);
      this.label2.TabIndex = 23;
      this.label2.Text = "cam_alvo";
      // 
      // label3
      // 
      this.label3.AutoSize = true;
      this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label3.Location = new System.Drawing.Point(534, 123);
      this.label3.Name = "label3";
      this.label3.Size = new System.Drawing.Size(97, 13);
      this.label3.TabIndex = 24;
      this.label3.Text = "cam_orientacao";
      // 
      // txtWorld_m33
      // 
      this.txtWorld_m33.Location = new System.Drawing.Point(481, 233);
      this.txtWorld_m33.Name = "txtWorld_m33";
      this.txtWorld_m33.Size = new System.Drawing.Size(47, 20);
      this.txtWorld_m33.TabIndex = 33;
      // 
      // txtWorld_m32
      // 
      this.txtWorld_m32.Location = new System.Drawing.Point(428, 233);
      this.txtWorld_m32.Name = "txtWorld_m32";
      this.txtWorld_m32.Size = new System.Drawing.Size(47, 20);
      this.txtWorld_m32.TabIndex = 32;
      // 
      // txtWorld_m31
      // 
      this.txtWorld_m31.Location = new System.Drawing.Point(374, 233);
      this.txtWorld_m31.Name = "txtWorld_m31";
      this.txtWorld_m31.Size = new System.Drawing.Size(47, 20);
      this.txtWorld_m31.TabIndex = 31;
      // 
      // txtWorld_m23
      // 
      this.txtWorld_m23.Location = new System.Drawing.Point(481, 207);
      this.txtWorld_m23.Name = "txtWorld_m23";
      this.txtWorld_m23.Size = new System.Drawing.Size(47, 20);
      this.txtWorld_m23.TabIndex = 30;
      // 
      // txtWorld_m22
      // 
      this.txtWorld_m22.Location = new System.Drawing.Point(428, 207);
      this.txtWorld_m22.Name = "txtWorld_m22";
      this.txtWorld_m22.Size = new System.Drawing.Size(47, 20);
      this.txtWorld_m22.TabIndex = 29;
      // 
      // txtWorld_m21
      // 
      this.txtWorld_m21.Location = new System.Drawing.Point(374, 207);
      this.txtWorld_m21.Name = "txtWorld_m21";
      this.txtWorld_m21.Size = new System.Drawing.Size(47, 20);
      this.txtWorld_m21.TabIndex = 28;
      // 
      // txtWorld_m13
      // 
      this.txtWorld_m13.Location = new System.Drawing.Point(481, 181);
      this.txtWorld_m13.Name = "txtWorld_m13";
      this.txtWorld_m13.Size = new System.Drawing.Size(47, 20);
      this.txtWorld_m13.TabIndex = 27;
      // 
      // txtWorld_m12
      // 
      this.txtWorld_m12.Location = new System.Drawing.Point(428, 181);
      this.txtWorld_m12.Name = "txtWorld_m12";
      this.txtWorld_m12.Size = new System.Drawing.Size(47, 20);
      this.txtWorld_m12.TabIndex = 26;
      // 
      // txtWorld_m11
      // 
      this.txtWorld_m11.Location = new System.Drawing.Point(374, 181);
      this.txtWorld_m11.Name = "txtWorld_m11";
      this.txtWorld_m11.Size = new System.Drawing.Size(47, 20);
      this.txtWorld_m11.TabIndex = 25;
      // 
      // txtProjet_m31
      // 
      this.txtProjet_m31.Location = new System.Drawing.Point(457, 342);
      this.txtProjet_m31.Name = "txtProjet_m31";
      this.txtProjet_m31.Size = new System.Drawing.Size(71, 20);
      this.txtProjet_m31.TabIndex = 40;
      // 
      // txtProjet_m21
      // 
      this.txtProjet_m21.Location = new System.Drawing.Point(457, 316);
      this.txtProjet_m21.Name = "txtProjet_m21";
      this.txtProjet_m21.Size = new System.Drawing.Size(71, 20);
      this.txtProjet_m21.TabIndex = 37;
      // 
      // txtProjet_m11
      // 
      this.txtProjet_m11.Location = new System.Drawing.Point(457, 290);
      this.txtProjet_m11.Name = "txtProjet_m11";
      this.txtProjet_m11.Size = new System.Drawing.Size(71, 20);
      this.txtProjet_m11.TabIndex = 34;
      // 
      // btnSair
      // 
      this.btnSair.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.btnSair.ForeColor = System.Drawing.Color.Red;
      this.btnSair.Location = new System.Drawing.Point(374, 371);
      this.btnSair.Name = "btnSair";
      this.btnSair.Size = new System.Drawing.Size(248, 60);
      this.btnSair.TabIndex = 43;
      this.btnSair.Text = "SAIR";
      this.btnSair.UseVisualStyleBackColor = true;
      this.btnSair.Click += new System.EventHandler(this.btnSair_Click);
      // 
      // label4
      // 
      this.label4.AutoSize = true;
      this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label4.Location = new System.Drawing.Point(534, 207);
      this.label4.Name = "label4";
      this.label4.Size = new System.Drawing.Size(94, 13);
      this.label4.TabIndex = 46;
      this.label4.Text = "mundo_rotacao";
      // 
      // label5
      // 
      this.label5.AutoSize = true;
      this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label5.Location = new System.Drawing.Point(534, 233);
      this.label5.Name = "label5";
      this.label5.Size = new System.Drawing.Size(88, 13);
      this.label5.TabIndex = 45;
      this.label5.Text = "mundo_escala";
      // 
      // label6
      // 
      this.label6.AutoSize = true;
      this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label6.Location = new System.Drawing.Point(534, 181);
      this.label6.Name = "label6";
      this.label6.Size = new System.Drawing.Size(71, 13);
      this.label6.TabIndex = 44;
      this.label6.Text = "mundo_pos";
      // 
      // label7
      // 
      this.label7.AutoSize = true;
      this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label7.Location = new System.Drawing.Point(534, 344);
      this.label7.Name = "label7";
      this.label7.Size = new System.Drawing.Size(74, 13);
      this.label7.TabIndex = 49;
      this.label7.Text = "corte_longe";
      // 
      // label8
      // 
      this.label8.AutoSize = true;
      this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label8.Location = new System.Drawing.Point(534, 318);
      this.label8.Name = "label8";
      this.label8.Size = new System.Drawing.Size(72, 13);
      this.label8.TabIndex = 48;
      this.label8.Text = "corte_perto";
      // 
      // label9
      // 
      this.label9.AutoSize = true;
      this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.label9.Location = new System.Drawing.Point(534, 290);
      this.label9.Name = "label9";
      this.label9.Size = new System.Drawing.Size(81, 13);
      this.label9.TabIndex = 47;
      this.label9.Text = "campo_visao";
      // 
      // Janela
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(632, 453);
      this.Controls.Add(this.label7);
      this.Controls.Add(this.label8);
      this.Controls.Add(this.label9);
      this.Controls.Add(this.label4);
      this.Controls.Add(this.label5);
      this.Controls.Add(this.label6);
      this.Controls.Add(this.btnSair);
      this.Controls.Add(this.txtProjet_m31);
      this.Controls.Add(this.txtProjet_m21);
      this.Controls.Add(this.txtProjet_m11);
      this.Controls.Add(this.txtWorld_m33);
      this.Controls.Add(this.txtWorld_m32);
      this.Controls.Add(this.txtWorld_m31);
      this.Controls.Add(this.txtWorld_m23);
      this.Controls.Add(this.txtWorld_m22);
      this.Controls.Add(this.txtWorld_m21);
      this.Controls.Add(this.txtWorld_m13);
      this.Controls.Add(this.txtWorld_m12);
      this.Controls.Add(this.txtWorld_m11);
      this.Controls.Add(this.label3);
      this.Controls.Add(this.label2);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.btnReset);
      this.Controls.Add(this.txt_m33);
      this.Controls.Add(this.txt_m32);
      this.Controls.Add(this.txt_m31);
      this.Controls.Add(this.txt_m23);
      this.Controls.Add(this.txt_m22);
      this.Controls.Add(this.txt_m21);
      this.Controls.Add(this.txt_m13);
      this.Controls.Add(this.txt_m12);
      this.Controls.Add(this.txt_m11);
      this.Controls.Add(this.btnView);
      this.Controls.Add(this.btnWorld);
      this.Controls.Add(this.btnProjection);
      this.Controls.Add(this.btnVectorRight);
      this.Controls.Add(this.btnVectorCenter);
      this.Controls.Add(this.btnVectorLeft);
      this.Controls.Add(this.btnDown);
      this.Controls.Add(this.btnUp);
      this.Controls.Add(this.chkz);
      this.Controls.Add(this.chky);
      this.Controls.Add(this.chkx);
      this.Controls.Add(this.Tela);
      this.Name = "Janela";
      this.Text = "Prj_Lab01";
      this.Load += new System.EventHandler(this.Janela_Load);
      ((System.ComponentModel.ISupportInitialize)(this.Tela)).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.PictureBox Tela;
    private System.Windows.Forms.CheckBox chkx;
    private System.Windows.Forms.CheckBox chky;
    private System.Windows.Forms.CheckBox chkz;
    private System.Windows.Forms.Button btnUp;
    private System.Windows.Forms.Button btnDown;
    private System.Windows.Forms.Button btnVectorLeft;
    private System.Windows.Forms.Button btnVectorCenter;
    private System.Windows.Forms.Button btnVectorRight;
    private System.Windows.Forms.Button btnProjection;
    private System.Windows.Forms.Button btnWorld;
    private System.Windows.Forms.Button btnView;
    private System.Windows.Forms.TextBox txt_m11;
    private System.Windows.Forms.TextBox txt_m12;
    private System.Windows.Forms.TextBox txt_m13;
    private System.Windows.Forms.TextBox txt_m23;
    private System.Windows.Forms.TextBox txt_m22;
    private System.Windows.Forms.TextBox txt_m21;
    private System.Windows.Forms.TextBox txt_m33;
    private System.Windows.Forms.TextBox txt_m32;
    private System.Windows.Forms.TextBox txt_m31;
    private System.Windows.Forms.Button btnReset;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Label label2;
    private System.Windows.Forms.Label label3;
    private System.Windows.Forms.TextBox txtWorld_m33;
    private System.Windows.Forms.TextBox txtWorld_m32;
    private System.Windows.Forms.TextBox txtWorld_m31;
    private System.Windows.Forms.TextBox txtWorld_m23;
    private System.Windows.Forms.TextBox txtWorld_m22;
    private System.Windows.Forms.TextBox txtWorld_m21;
    private System.Windows.Forms.TextBox txtWorld_m13;
    private System.Windows.Forms.TextBox txtWorld_m12;
    private System.Windows.Forms.TextBox txtWorld_m11;
    private System.Windows.Forms.TextBox txtProjet_m31;
    private System.Windows.Forms.TextBox txtProjet_m21;
    private System.Windows.Forms.TextBox txtProjet_m11;
    private System.Windows.Forms.Button btnSair;
    private System.Windows.Forms.Label label4;
    private System.Windows.Forms.Label label5;
    private System.Windows.Forms.Label label6;
    private System.Windows.Forms.Label label7;
    private System.Windows.Forms.Label label8;
    private System.Windows.Forms.Label label9;
  }
}

