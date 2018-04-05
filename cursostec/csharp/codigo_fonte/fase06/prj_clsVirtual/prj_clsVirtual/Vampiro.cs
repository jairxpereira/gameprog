﻿// Projeto prj_clsVirtual -  Arquivo: Vampiro.cs 
// Ilustra o uso de método virtual
using System;

namespace prj_clsVirtual
{
  class Vampiro : Monstro
  {
    // Construtor chama construtor da classe base 
    public Vampiro() : base(22) { }

    // O Vampiro morde no ataque!
    public override void atacar()
    {
      string msg = "";
      msg = " (Classe Vampiro) {0} te mordeu.";
      Console.Write(msg, m_nome);
      msg = " Vc perdeu {0} pontos de saúde.\n";
      Console.WriteLine(msg, m_estrago);
    } // atacar().fim 
  } // fim da classe
} // fim do namespace
