// Projeto prj_classe02 -  Arquivo: Vampiro.cs
// Ilustra herança simples, redefinição de métodos (new)
// Membros estáticos; chamando o construtor da classe base
using System;

namespace prj_classe02
{
  class Vampiro: Monstro
  {
    // Construtor chama construtor da classe base 
    public Vampiro() : base(22) { }

    // Repassa valor para construtor da classe base
    public Vampiro(int estrago): base(estrago) { }

    
    // Método particular do vampiro
    public void dormir()
    {
      Console.WriteLine(" O sol está chegando. O vampiro foi dormir...");
    } // dormir(0.fom


    // new indica que o método da classe base será escondido!
    // O Vampiro morde no ataque!
    new public void atacar()
    {
      string msg = "";
      msg = " * {0}({1}) te mordeu e vc perdeu {2} pontos de energia";
      Console.WriteLine(msg, m_nome, m_id, m_estrago);
    } // atacar().fim 
  } // fim da classe
} // fim do namespace
