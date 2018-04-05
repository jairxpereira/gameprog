// Projeto prj_classe02 -  Arquivo: Ogro.cs
// Ilustra herança simples, redefinição de métodos (new)
// Membros estáticos; chamando o construtor da classe base
using System;


namespace prj_classe02
{
  class Ogro: Monstro
  {

    // Construtor chama construtor da classe base 
    public Ogro() : base(120) { }

    // Repassa valor para construtor da classe base
    public Ogro(int estrago): base(estrago) { }

  }
}
