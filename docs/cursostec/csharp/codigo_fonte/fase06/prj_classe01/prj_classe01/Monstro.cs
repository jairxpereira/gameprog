// Projeto prj_classe01: Arquivo: Monstro.cs
// Ilustra a construção de uma classe simples
using System;

namespace prj_classe01
{
  class Monstro
  {
    
public int m_energia;
public int m_estrago;

public Monstro ()
{
 m_energia = 100;
 m_estrago = 10;
} // Fim do Construtor


    public void atacar()
 {
 Console.WriteLine ( "\t Vc foi atacado e perdeu " +  
   m_estrago.ToString() + " pontos de energia. \n\n");
 } // atacar().gom
  } // fim da classe Monstro
} // Fim do namespace


