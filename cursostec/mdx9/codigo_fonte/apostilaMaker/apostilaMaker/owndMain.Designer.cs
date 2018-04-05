namespace apostilaMaker
{
  partial class owndMain
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
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(owndMain));
      this.groupBox1 = new System.Windows.Forms.GroupBox();
      this.btnApostilaMaker = new System.Windows.Forms.Button();
      this.btnMakehtml = new System.Windows.Forms.Button();
      this.btnLoadFile = new System.Windows.Forms.Button();
      this.txtCSharpFile = new System.Windows.Forms.TextBox();
      this.dlgOpenFile = new System.Windows.Forms.OpenFileDialog();
      this.dlgPastasBrowser = new System.Windows.Forms.FolderBrowserDialog();
      this.groupBox2 = new System.Windows.Forms.GroupBox();
      this.btnEscolherPasta = new System.Windows.Forms.Button();
      this.txtOutputFolder = new System.Windows.Forms.TextBox();
      this.lblAviso = new System.Windows.Forms.Label();
      this.btnSair = new System.Windows.Forms.Button();
      this.Menu = new System.Windows.Forms.MenuStrip();
      this.apostilasToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.propriedadesToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
      this.button1 = new System.Windows.Forms.Button();
      this.groupBox1.SuspendLayout();
      this.groupBox2.SuspendLayout();
      this.Menu.SuspendLayout();
      this.SuspendLayout();
      // 
      // groupBox1
      // 
      this.groupBox1.Controls.Add(this.btnApostilaMaker);
      this.groupBox1.Controls.Add(this.btnMakehtml);
      this.groupBox1.Controls.Add(this.btnLoadFile);
      this.groupBox1.Controls.Add(this.txtCSharpFile);
      this.groupBox1.Location = new System.Drawing.Point(12, 62);
      this.groupBox1.Name = "groupBox1";
      this.groupBox1.Size = new System.Drawing.Size(632, 148);
      this.groupBox1.TabIndex = 0;
      this.groupBox1.TabStop = false;
      this.groupBox1.Text = "Working c# file";
      // 
      // btnApostilaMaker
      // 
      this.btnApostilaMaker.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
      this.btnApostilaMaker.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnApostilaMaker.Location = new System.Drawing.Point(415, 93);
      this.btnApostilaMaker.Name = "btnApostilaMaker";
      this.btnApostilaMaker.Size = new System.Drawing.Size(194, 42);
      this.btnApostilaMaker.TabIndex = 3;
      this.btnApostilaMaker.Text = "Transformar em Apostila";
      this.btnApostilaMaker.UseVisualStyleBackColor = false;
      this.btnApostilaMaker.Click += new System.EventHandler(this.btnApostilaMaker_Click);
      // 
      // btnMakehtml
      // 
      this.btnMakehtml.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(255)))), ((int)(((byte)(255)))));
      this.btnMakehtml.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnMakehtml.Location = new System.Drawing.Point(215, 93);
      this.btnMakehtml.Name = "btnMakehtml";
      this.btnMakehtml.Size = new System.Drawing.Size(194, 42);
      this.btnMakehtml.TabIndex = 2;
      this.btnMakehtml.Text = "Transformar em HTML";
      this.btnMakehtml.UseVisualStyleBackColor = false;
      this.btnMakehtml.Click += new System.EventHandler(this.btnMakehtml_Click);
      // 
      // btnLoadFile
      // 
      this.btnLoadFile.BackColor = System.Drawing.Color.MediumOrchid;
      this.btnLoadFile.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnLoadFile.Location = new System.Drawing.Point(14, 93);
      this.btnLoadFile.Name = "btnLoadFile";
      this.btnLoadFile.Size = new System.Drawing.Size(194, 42);
      this.btnLoadFile.TabIndex = 0;
      this.btnLoadFile.Text = "Carregar Arquivo";
      this.btnLoadFile.UseVisualStyleBackColor = false;
      this.btnLoadFile.Click += new System.EventHandler(this.btnLoadFile_Click);
      // 
      // txtCSharpFile
      // 
      this.txtCSharpFile.Location = new System.Drawing.Point(19, 37);
      this.txtCSharpFile.Multiline = true;
      this.txtCSharpFile.Name = "txtCSharpFile";
      this.txtCSharpFile.Size = new System.Drawing.Size(593, 49);
      this.txtCSharpFile.TabIndex = 1;
      this.txtCSharpFile.Text = "C:\\gameprog\\cursostec\\mdx9\\codigo_fonte\\apostilaMaker\\apostilaMaker\\HtmlMaker.cs";
      // 
      // dlgOpenFile
      // 
      this.dlgOpenFile.FileName = "*.cs";
      this.dlgOpenFile.InitialDirectory = "\\";
      this.dlgOpenFile.Title = "Abrir Arquivo c#";
      // 
      // groupBox2
      // 
      this.groupBox2.Controls.Add(this.btnEscolherPasta);
      this.groupBox2.Controls.Add(this.txtOutputFolder);
      this.groupBox2.Location = new System.Drawing.Point(12, 230);
      this.groupBox2.Name = "groupBox2";
      this.groupBox2.Size = new System.Drawing.Size(632, 148);
      this.groupBox2.TabIndex = 1;
      this.groupBox2.TabStop = false;
      this.groupBox2.Text = "Caminho da saida:";
      // 
      // btnEscolherPasta
      // 
      this.btnEscolherPasta.BackColor = System.Drawing.Color.SlateBlue;
      this.btnEscolherPasta.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnEscolherPasta.Location = new System.Drawing.Point(14, 93);
      this.btnEscolherPasta.Name = "btnEscolherPasta";
      this.btnEscolherPasta.Size = new System.Drawing.Size(194, 42);
      this.btnEscolherPasta.TabIndex = 1;
      this.btnEscolherPasta.Text = "Escolher pasta";
      this.btnEscolherPasta.UseVisualStyleBackColor = false;
      this.btnEscolherPasta.Click += new System.EventHandler(this.btnEscolherPasta_Click);
      // 
      // txtOutputFolder
      // 
      this.txtOutputFolder.Location = new System.Drawing.Point(19, 37);
      this.txtOutputFolder.Multiline = true;
      this.txtOutputFolder.Name = "txtOutputFolder";
      this.txtOutputFolder.Size = new System.Drawing.Size(593, 49);
      this.txtOutputFolder.TabIndex = 0;
      this.txtOutputFolder.Text = "d:\\misc\\apostila";
      // 
      // lblAviso
      // 
      this.lblAviso.AutoSize = true;
      this.lblAviso.Location = new System.Drawing.Point(24, 402);
      this.lblAviso.Name = "lblAviso";
      this.lblAviso.Size = new System.Drawing.Size(49, 15);
      this.lblAviso.TabIndex = 2;
      this.lblAviso.Text = "lblAviso";
      // 
      // btnSair
      // 
      this.btnSair.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(128)))), ((int)(((byte)(128)))));
      this.btnSair.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.btnSair.ForeColor = System.Drawing.Color.Black;
      this.btnSair.Location = new System.Drawing.Point(450, 404);
      this.btnSair.Name = "btnSair";
      this.btnSair.Size = new System.Drawing.Size(194, 42);
      this.btnSair.TabIndex = 3;
      this.btnSair.Text = "SAIR";
      this.btnSair.UseVisualStyleBackColor = false;
      this.btnSair.Click += new System.EventHandler(this.btnSair_Click);
      // 
      // Menu
      // 
      this.Menu.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.apostilasToolStripMenuItem});
      this.Menu.Location = new System.Drawing.Point(0, 0);
      this.Menu.Name = "Menu";
      this.Menu.Padding = new System.Windows.Forms.Padding(7, 2, 0, 2);
      this.Menu.Size = new System.Drawing.Size(677, 24);
      this.Menu.TabIndex = 4;
      this.Menu.Text = "menuStrip1";
      this.Menu.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
      // 
      // apostilasToolStripMenuItem
      // 
      this.apostilasToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.propriedadesToolStripMenuItem});
      this.apostilasToolStripMenuItem.Name = "apostilasToolStripMenuItem";
      this.apostilasToolStripMenuItem.Size = new System.Drawing.Size(62, 20);
      this.apostilasToolStripMenuItem.Text = "Apostilas";
      // 
      // propriedadesToolStripMenuItem
      // 
      this.propriedadesToolStripMenuItem.Name = "propriedadesToolStripMenuItem";
      this.propriedadesToolStripMenuItem.Size = new System.Drawing.Size(137, 22);
      this.propriedadesToolStripMenuItem.Text = "Propriedades";
      this.propriedadesToolStripMenuItem.Click += new System.EventHandler(this.propriedadesToolStripMenuItem_Click);
      // 
      // button1
      // 
      this.button1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(128)))));
      this.button1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
      this.button1.Location = new System.Drawing.Point(250, 404);
      this.button1.Name = "button1";
      this.button1.Size = new System.Drawing.Size(194, 42);
      this.button1.TabIndex = 5;
      this.button1.Text = "DEBUG";
      this.button1.UseVisualStyleBackColor = false;
      this.button1.Click += new System.EventHandler(this.button1_Click);
      // 
      // owndMain
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.BackColor = System.Drawing.SystemColors.InactiveCaptionText;
      this.ClientSize = new System.Drawing.Size(677, 453);
      this.Controls.Add(this.button1);
      this.Controls.Add(this.btnSair);
      this.Controls.Add(this.lblAviso);
      this.Controls.Add(this.groupBox2);
      this.Controls.Add(this.groupBox1);
      this.Controls.Add(this.Menu);
      this.Font = new System.Drawing.Font("Segoe UI", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
      this.ForeColor = System.Drawing.Color.Black;
      this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
      this.Location = new System.Drawing.Point(370, 20);
      this.MainMenuStrip = this.Menu;
      this.MaximizeBox = false;
      this.Name = "owndMain";
      this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
      this.Text = "apostilaMaker";
      this.Load += new System.EventHandler(this.owndMain_Load);
      this.groupBox1.ResumeLayout(false);
      this.groupBox1.PerformLayout();
      this.groupBox2.ResumeLayout(false);
      this.groupBox2.PerformLayout();
      this.Menu.ResumeLayout(false);
      this.Menu.PerformLayout();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.GroupBox groupBox1;
    private System.Windows.Forms.Button btnLoadFile;
    private System.Windows.Forms.TextBox txtCSharpFile;
    private System.Windows.Forms.Button btnApostilaMaker;
    private System.Windows.Forms.Button btnMakehtml;
    private System.Windows.Forms.OpenFileDialog dlgOpenFile;
    private System.Windows.Forms.FolderBrowserDialog dlgPastasBrowser;
    private System.Windows.Forms.GroupBox groupBox2;
    private System.Windows.Forms.Button btnEscolherPasta;
    private System.Windows.Forms.TextBox txtOutputFolder;
    private System.Windows.Forms.Label lblAviso;
    private System.Windows.Forms.Button btnSair;
    private System.Windows.Forms.MenuStrip Menu;
    private System.Windows.Forms.ToolStripMenuItem apostilasToolStripMenuItem;
    private System.Windows.Forms.ToolStripMenuItem propriedadesToolStripMenuItem;
    private System.Windows.Forms.Button button1;
  }
}

