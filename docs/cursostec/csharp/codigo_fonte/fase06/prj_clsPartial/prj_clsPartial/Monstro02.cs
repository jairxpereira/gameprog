// Projeto prj_clsPartial -  Arquivo: Monstro02.cs 
// Ilustra a implementação de uma classe em vários arquivos
using System;

namespace prj_clsPartial
{
  partial class Monstro
  {
    
    // O monstro ganha fala no segundo arquivo!
    public void falar()
    {
      Console.WriteLine("\n Monstro.falar() ok - Arquivo: Monstro02.cs");
      Console.WriteLine(" Acesso aos atributos Ok: {0}",m_nome);     
    } // atacar().fim 

  } // fim da classe
} // fim do namespace
