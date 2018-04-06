// Projeto prj_clsAbstrata -  Arquivo:Monstro.cs
// Ilustra o uso de classe abstrata
using System;

namespace prj_clsAbstrata
{
  abstract class Monstro
  {

    // atributos
    public int m_estrago;   // capacidade de fazer estrago
    public string m_nome;   // nome do objeto

    // Construtor 01 Mostro()
    public Monstro()
    {

      m_estrago = 10;
      m_nome = "monstro";
    } // fim do Construtor 01

    // Construtor 02 Monstro (int nval)
    public Monstro(int estrago)
    {
      m_estrago = estrago;
      m_nome = "monstro";
    } // fim do construtor 02


    // atacar()
    abstract public void atacar();

  } // fim da classe
} // fim do namespace

