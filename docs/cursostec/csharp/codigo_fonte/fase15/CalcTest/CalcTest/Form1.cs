using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace CalcTest
{
  public partial class Form1 : Form
  {
    public Form1()
    {
      InitializeComponent();
    }

    // declare the WinAPI method you wish to P/Invoke
    [DllImport("edrlib.dll", EntryPoint = "HelloWorld",
    ExactSpelling = false, CharSet = CharSet.Unicode,
    SetLastError = true)]
    static extern void HelloWorld();

    private void Form1_Load(object sender, EventArgs e)
    {

    }

    private void btnAdd_Click(object sender, EventArgs e)
    {
      double x, y, z;

      x = Double.Parse(textBox1.Text);
      y = Double.Parse(textBox2.Text);
      z = axCalculator.Add(ref x, ref y);
      label1.Text = z.ToString();


      Form1.HelloWorld();






    }

    private void btnSubtract_Click(object sender, EventArgs e)
    {
      double x, y, z;

      x = Double.Parse(textBox1.Text);
      y = Double.Parse(textBox2.Text);
      z = axCalculator.Subtract (ref x, ref y);
      label1.Text = z.ToString();
    }

    private void btnMultiply_Click(object sender, EventArgs e)
    {
      double x, y, z;

      x = Double.Parse(textBox1.Text);
      y = Double.Parse(textBox2.Text);
      z = axCalculator.Multiply (ref x, ref y);
      label1.Text = z.ToString();
    }

    private void btnDivide_Click(object sender, EventArgs e)
    {
      double x, y, z;

      x = Double.Parse(textBox1.Text);
      y = Double.Parse(textBox2.Text);
      z = axCalculator.Divide (ref x, ref y);
      label1.Text = z.ToString();
    }
  }
}
