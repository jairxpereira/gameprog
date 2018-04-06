// Projeto prj_interface -  Arquivo: Ogro.cs
// Ilustra o uso de interfaces
using System;

namespace prj_interface
{
  class Ogro : IMonstro
  {
    // campos
    private int m_estrago;   // capacidade de fazer estrago
    private string m_nome;   // nome do objeto   
   
    // Construtor 
    public Ogro() 
    {
      m_estrago = 120; 
      m_nome = "ogro";
    }

    // Vamos implementar os membros conforme contrato com IMonstro
    public void atacar()
    {
      string msg = "";
      Console.Write("\n");

      msg = " (Classe Ogro) {0} ataca.";
      Console.Write(msg, m_nome);
      msg = " Vc perde {0} pontos de energia.";
      Console.WriteLine(msg, m_estrago);
    }// atacar().fim

    // get/set sobre m_estrago
    public int Estrago
    {    
     set { m_estrago = value; }
     get { return m_estrago; }    
    } // fim da propriedade;

    // get/set sobre m_nome
    public string Nome
    {
      set { m_nome = value; }
      get { return m_nome; }
    } // fim da propriedade;

  } // fim da classe
} // fim do namespace
