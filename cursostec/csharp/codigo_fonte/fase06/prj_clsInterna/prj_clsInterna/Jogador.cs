// Projeto prj_clsInterna -  Arquivo: Jogador.cs
// Ilustra o uso de classe interna
using System;

namespace prj_clsInterna
{
  class Jogador
  {
    // atributos
    public string nome;   // nome do objeto
    public int energia; // Quantidade energia
    private int itens_qtd; // Quantidade de itens na mochila

    // Construtor 01 Mostro()
    public Jogador()
    {  
      nome = "player1";
      energia = 99;
    } // fim do Construtor 01

    public override string ToString()
    {
      string dados_novos = " ( ";
      dados_novos += "nome:" + nome + ", ";
      dados_novos += "energia:" + energia.ToString() + ", ";
      dados_novos += "itens:" + itens_qtd.ToString() + " )"; 
      return dados_novos;
    } // toString().fim

    public void mostrar_status()
    {
      Console.WriteLine("\n Jogador: {0} - status: ", nome);
      Console.WriteLine(this.ToString());
    } // mostrar_status().fim

    internal class Mochila
    {      
      // atributos públicos
      public int contador = 0;
      public string[] slot;
      Jogador dono = null;

      public Mochila( Jogador jog)
      {
        slot = new string[7];
        dono = jog;         
      } // fim do construtor

      public void adicionar (string s_item)
      {
        slot [ contador ] = s_item;
        contador++;
        if (contador > 6) contador = 6;
        dono.itens_qtd = contador;        
      } // adicionar().fim

      public void mostrar_itens()
      {
        Console.WriteLine("\n Dono da mochila: {0} - Itens:", this.dono.nome);
        for (int ncx = 0; ncx < this.contador; ncx++)
          Console.WriteLine(" {0}", this.slot[ncx]);        
      } // mostrar_itens()

    } // final da classe interna Mochila; 
  } // fim da classe mais externa Jogador
} // fim do namespace

