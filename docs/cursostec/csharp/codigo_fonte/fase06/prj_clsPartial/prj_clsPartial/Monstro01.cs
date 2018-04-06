// Projeto prj_clsPartial -  Arquivo: Monstro01.cs 
// Ilustra a implementação de uma classe em vários arquivos
using System;

namespace prj_clsPartial
{
  partial class Monstro
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
    public void atacar()
    {
      string msg = "";
      msg = " Arquivo Monstro01.cs - {0} atacou ";
      Console.Write(msg, m_nome);
      msg = "e vc perde {0} pontos.";
      Console.WriteLine(msg, m_estrago);

    } // atacar().fim
  } // fim da classe
} // fim do namespace

