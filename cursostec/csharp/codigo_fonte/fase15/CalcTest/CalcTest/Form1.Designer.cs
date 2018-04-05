namespace CalcTest
{
  partial class Form1
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
      System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
      this.textBox1 = new System.Windows.Forms.TextBox();
      this.textBox2 = new System.Windows.Forms.TextBox();
      this.label1 = new System.Windows.Forms.Label();
      this.btnAdd = new System.Windows.Forms.Button();
      this.btnSubtract = new System.Windows.Forms.Button();
      this.btnMultiply = new System.Windows.Forms.Button();
      this.btnDivide = new System.Windows.Forms.Button();
      this.axCalculator = new AxCalcControl.AxCalculator();
      ((System.ComponentModel.ISupportInitialize)(this.axCalculator)).BeginInit();
      this.SuspendLayout();
      // 
      // textBox1
      // 
      this.textBox1.Location = new System.Drawing.Point(12, 16);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new System.Drawing.Size(85, 20);
      this.textBox1.TabIndex = 0;
      this.textBox1.Text = "4";
      // 
      // textBox2
      // 
      this.textBox2.Location = new System.Drawing.Point(11, 45);
      this.textBox2.Name = "textBox2";
      this.textBox2.Size = new System.Drawing.Size(85, 20);
      this.textBox2.TabIndex = 1;
      this.textBox2.Text = "2";
      // 
      // label1
      // 
      this.label1.AutoSize = true;
      this.label1.Location = new System.Drawing.Point(135, 25);
      this.label1.Name = "label1";
      this.label1.Size = new System.Drawing.Size(35, 13);
      this.label1.TabIndex = 2;
      this.label1.Text = "label1";
      // 
      // btnAdd
      // 
      this.btnAdd.Location = new System.Drawing.Point(13, 90);
      this.btnAdd.Name = "btnAdd";
      this.btnAdd.Size = new System.Drawing.Size(67, 22);
      this.btnAdd.TabIndex = 3;
      this.btnAdd.Text = "Add";
      this.btnAdd.UseVisualStyleBackColor = true;
      this.btnAdd.Click += new System.EventHandler(this.btnAdd_Click);
      // 
      // btnSubtract
      // 
      this.btnSubtract.Location = new System.Drawing.Point(102, 88);
      this.btnSubtract.Name = "btnSubtract";
      this.btnSubtract.Size = new System.Drawing.Size(67, 23);
      this.btnSubtract.TabIndex = 4;
      this.btnSubtract.Text = "Sub";
      this.btnSubtract.UseVisualStyleBackColor = true;
      this.btnSubtract.Click += new System.EventHandler(this.btnSubtract_Click);
      // 
      // btnMultiply
      // 
      this.btnMultiply.Location = new System.Drawing.Point(186, 88);
      this.btnMultiply.Name = "btnMultiply";
      this.btnMultiply.Size = new System.Drawing.Size(71, 23);
      this.btnMultiply.TabIndex = 5;
      this.btnMultiply.Text = "Multiply";
      this.btnMultiply.UseVisualStyleBackColor = true;
      this.btnMultiply.Click += new System.EventHandler(this.btnMultiply_Click);
      // 
      // btnDivide
      // 
      this.btnDivide.Location = new System.Drawing.Point(280, 90);
      this.btnDivide.Name = "btnDivide";
      this.btnDivide.Size = new System.Drawing.Size(84, 20);
      this.btnDivide.TabIndex = 6;
      this.btnDivide.Text = "Divide";
      this.btnDivide.UseVisualStyleBackColor = true;
      this.btnDivide.Click += new System.EventHandler(this.btnDivide_Click);
      // 
      // axCalculator
      // 
      this.axCalculator.Enabled = true;
      this.axCalculator.Location = new System.Drawing.Point(128, 204);
      this.axCalculator.Name = "axCalculator";
      this.axCalculator.OcxState = ((System.Windows.Forms.AxHost.State)(resources.GetObject("axCalculator.OcxState")));
      this.axCalculator.Size = new System.Drawing.Size(320, 174);
      this.axCalculator.TabIndex = 7;
      // 
      // Form1
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(383, 153);
      this.Controls.Add(this.axCalculator);
      this.Controls.Add(this.btnDivide);
      this.Controls.Add(this.btnMultiply);
      this.Controls.Add(this.btnSubtract);
      this.Controls.Add(this.btnAdd);
      this.Controls.Add(this.label1);
      this.Controls.Add(this.textBox2);
      this.Controls.Add(this.textBox1);
      this.Name = "Form1";
      this.Text = "Form1";
      this.Load += new System.EventHandler(this.Form1_Load);
      ((System.ComponentModel.ISupportInitialize)(this.axCalculator)).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();

    }

    #endregion

    private System.Windows.Forms.TextBox textBox1;
    private System.Windows.Forms.TextBox textBox2;
    private System.Windows.Forms.Label label1;
    private System.Windows.Forms.Button btnAdd;
    private System.Windows.Forms.Button btnSubtract;
    private System.Windows.Forms.Button btnMultiply;
    private System.Windows.Forms.Button btnDivide;
    private AxCalcControl.AxCalculator axCalculator;
  }
}

