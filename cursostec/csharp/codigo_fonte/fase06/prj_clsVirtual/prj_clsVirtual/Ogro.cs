// Projeto prj_clsVirtual -  Arquivo: Ogro.cs
// Ilustra o uso de método virtual
using System;

namespace prj_clsVirtual
{
  class Ogro : Monstro
  {
    // Construtor chama construtor da classe base 
    public Ogro() : base(120) { }

    public override void atacar()
    {
      string msg = "";
      Console.Write("\n");
      
      // Vamos aproveitar o trabalho anterior!
      base.atacar();

      msg = " (Classe Ogro) {0} ataca de novo com pedras e...";
      Console.WriteLine(msg, m_nome);
      msg = " ...vc perde mais {0} pontos de energia.\n";
      Console.WriteLine(msg, m_estrago);
    }// atacar().fim
  } // fim da classe
} // fim do namespace
