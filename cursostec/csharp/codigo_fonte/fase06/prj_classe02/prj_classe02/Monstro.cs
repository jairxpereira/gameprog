// Projeto prj_classe02 -  Arquivo:Monstro.cs
// Ilustra herança simples, redefinição de métodos (new)
// Membros estáticos; chamando o construtor da classe base
using System;


namespace prj_classe02
{
  sealed class Monstro
  {
   
    // atributos
    public int m_estrago;   // capacidade de fazer estrago
    public int m_id;        // identificador do objeto
    public string m_nome;   // nome do objeto
    private static int nobj = 1;    // contador de objetos

    // Construtor 01 Mostro()
    public Monstro()
    {
      
      m_estrago = 10;
      m_nome = "monstro";
      m_id = nobj;
      nobj++;
    } // fim do Construtor 01

    // Construtor 02 Monstro (int nval)
    public Monstro(int estrago)
    {
      m_estrago = estrago;
      m_nome = "monstro";
      m_id = nobj;
      nobj++;
    } // fim do construtor 02


    // atacar()
    public void atacar()
{
    string msg = ""; 
    msg = " {0}({1}) te atacou e vc perdeu {2} pontos de energia";
    Console.WriteLine(msg, m_nome, m_id, m_estrago);
} // atacar().fim

    // Retorna a quantidade de monstros criados
    public static int get_qtd()
    {
      int nqtd = 0;
      nqtd = nobj - 1;
      return nqtd;
    } // get_qtd().fim
   
  } // fim da classe
} // fim do namespace

