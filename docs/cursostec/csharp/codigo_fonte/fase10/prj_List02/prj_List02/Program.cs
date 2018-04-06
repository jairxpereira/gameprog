// Projeto prj_List02
// Este programa mostra o uso de List<T> 
// Mostra o indexer e o iterador
using System;
using System.Collections.Generic;

namespace prj_List02
{
  class Monstro 
  {
    // Nome do monstro
    public string m_nome;
    // Capacidade de fazer estrago   
    public int m_estrago;

    // Construtor
    public Monstro(string nome, int estrago)
    {
      m_nome = nome;
      m_estrago = estrago;
    } // fim do construtor

    // Exibe o nome do monstro e capacidade de fazer estrago
    public void mostrar()
    {
      Console.WriteLine(" Mostro: ({0},{1})", m_nome, m_estrago);
    } // mostrar().fim
   
  } // fim da classe Monstro  


  class Program
  {
    static void Main(string[] args)
    {

      config_janela("prj_List02");    

      // Declarando uma lista de monstros
      List<Monstro> lista_monstro = new List<Monstro>();
     
      // Adicionando monstro na lista_monstro
      Monstro lobisomem = new Monstro("Lycan", 33);
      lista_monstro.Add(new Monstro("Godzila", 10));
      lista_monstro.Add(new Monstro("Dracula", 22));
      lista_monstro.Add(new Monstro("Shrek", 120));
      lista_monstro.Add(lobisomem);

      int ntam;
      ntam = lista_monstro.Count;
      Console.WriteLine("\n");

      // Exibindo os monstros usando o indexer
      Console.WriteLine(" \n\n Exibindo monstros usando o indexer");
      for (int ncx = 0; ncx < ntam; ncx++)
        lista_monstro[ncx].mostrar();

      // Exibindo monstros usando um iterador
      Console.WriteLine(" \n\n Exibindo monstros usando um iterador");
      List<Monstro>.Enumerator iter = new List<Monstro>.Enumerator();
      iter = lista_monstro.GetEnumerator();

      while (iter.MoveNext())
      {
        Monstro monster = iter.Current;
        monster.mostrar();
      }      

      // Pausa para a leitura da tela
      Console.ReadLine();
    } // main() fim

    // Método para configurar a janela
    private static void config_janela(string titulo)
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = titulo;
      Console.SetBufferSize(80, 30);
      Console.SetWindowSize(80, 30);
      Console.Clear();
    } // config_janela() fim    

  } // fim da classe Program
} // fim do namespace prj_List02