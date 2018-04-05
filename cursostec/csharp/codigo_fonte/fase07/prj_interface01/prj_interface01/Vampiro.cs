// Projeto prj_interface -  Arquivo: Vampiro.cs 
// Ilustra o uso de interfaces
using System;

namespace prj_interface
{
  class Vampiro : IMonstro, IPosition
  {

    // campos particulares do vampiro
    private int m_estrago;   // capacidade de fazer estrago
    private  string m_nome;   // nome do objeto   

    private int xpos;      // posição x do vampiro no mundo
    private int ypos;      // posição y do vampiro no mundo   
    
    // Construtor chama construtor da classe base 
    public Vampiro() 
    {
      m_estrago = 22;
      m_nome = "vampiro";
    }

    // Vamos seguir o contrato da interface IMonstro
    public void atacar()
    {
      string msg = "";
      msg = "\n (Classe Vampiro) {0} te mordeu.";
      Console.Write(msg, m_nome);
      msg = " Vc perdeu {0} pontos de saúde.";
      Console.WriteLine(msg, m_estrago);
    } // atacar().fim 


    // Vamos seguir o contrato da interface IMonstro
    public int Estrago
    {
      set { m_estrago = value; }
      get { return m_estrago; }
    } // fim da propriedade;

    public string Nome
    {
      set { m_nome = value; }
      get { return m_nome; }
    } // fim da propriedade;


    // Vamos seguir o contrato da interface IPosition
    public int X
    {
      set { xpos = value; }
      get { return xpos; }
    } // fim da propriedade;

    public int Y
    {
      set { ypos = value; }
      get { return ypos; }
    } // fim da propriedade;

    public void showpos()
    {
      string spos = "";
      spos = "( " + xpos.ToString() + ", ";
      spos += ypos.ToString() + ")";
      Console.WriteLine(" {0}.posição = {1} \n", m_nome, spos);      
    } // showpos().fim

  } // fim da classe
} // fim do namespace
