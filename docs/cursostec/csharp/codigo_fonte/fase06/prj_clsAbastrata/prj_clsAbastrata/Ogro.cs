// Projeto prj_clsAbstrata -  Arquivo: Ogro.cs
// Ilustra o uso de classe abstrata
using System;

namespace prj_clsAbstrata
{
  class Ogro : Monstro
  {
    // Construtor chama construtor da classe base 
    public Ogro() : base(120) { }
    public Ogro(int nval) : base(nval) { }

    public override void atacar()
    {
      string msg = "";
      Console.Write("\n");

      // Vamos aproveitar o trabalho anterior!
     
      msg = " (Classe Ogro) {0} ataca de novo com pedras e...";
      Console.WriteLine(msg, m_nome);
      msg = " ...vc perde mais {0} pontos de energia.\n";
      Console.WriteLine(msg, m_estrago);
    }// atacar().fim
  } // fim da classe
} // fim do namespace
