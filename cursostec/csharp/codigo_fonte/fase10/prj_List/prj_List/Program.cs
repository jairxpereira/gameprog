// Projeto prj_List
// Este programa mostra o uso de List<T>
using System;
using System.Collections.Generic;

namespace prj_List
{
  class Monstro: IComparable<Monstro>
  {  
    // Nome do monstro
    public string m_nome;
    // Capacidade de fazer estrago   
    public int m_estrago;

    // Construtor
    public Monstro( string nome, int estrago)
    {
    m_nome = nome;
    m_estrago = estrago;
    } // fim do construtor

    // Exibe o nome do monstro e capacidade de fazer estrago
    public void mostrar()
    {
      Console.WriteLine (" Mostro: ({0},{1})", m_nome, m_estrago);    
    } // mostrar().fim

    public int CompareTo( Monstro y)
    {
      int res = 0;
      res = this.m_estrago - y.m_estrago;
      return res;    
    } // CompareTo().fim
  } // fim da classe Monstro  
  
  
  class Program
  {
    static void Main(string[] args)
    {

      config_janela("prj_List");
      
      // Declarando uma lista de inteiros
      List<int> lista_int= new List<int>();

      // Segunda forma de declarar uma lista
      List<int> outra_lista = new List<int> {14,15,6,22,30 };

      // Declarando uma lista de monstros
      List<Monstro> lista_monstro = new List<Monstro>();

      // Segunda forma de declarar uma lista de monstros   
      List<Monstro> inimigos = new List<Monstro>() 
      { 
        new Monstro("Curupira", 122),
        new Monstro("Alucard",23),
        new Monstro ("Fiona", 11) 
      };

      // Adicionando monstro na lista_monstro
      Monstro lobisomem = new Monstro("Lycan", 33);
      lista_monstro.Add ( new Monstro ("Godzila", 10));
      lista_monstro.Add ( new Monstro ("Dracula", 22));
      lista_monstro.Add ( new Monstro ("Shrek", 120));
      lista_monstro.Add(lobisomem);    

      // Adicionando inteiros na lista_int
      lista_int.Add(10);
      lista_int.Add(77);
      lista_int.Add(1);
      lista_int.Add(13);
      lista_int.Add(45);

      // Mostrando conteúdo da lista lista_int
      Console.Write("\n");
      foreach (int nval in lista_int)
      {
        Console.Write(" {0}",nval);
      }

      // Mostrado conteúdo da outra_lista
      Console.Write("\n");
      foreach (int nval in outra_lista)
      {
        Console.Write(" {0}", nval);
      }

      // Mostrando os monstros da lista_monstro
      Console.Write("\n\n");
      foreach (Monstro monstrinho  in lista_monstro)
      {
        monstrinho.mostrar();
      }

      // Monstrando os monstros da lista inimigos
      Console.Write("\n\n");
      foreach (Monstro monstrinho in inimigos)
      {
        monstrinho.mostrar();
      }

      // Reordenando a lista de números e monstros
      lista_int.Sort();
      outra_lista.Sort();
      lista_monstro.Sort();
      
      // Mostrando os monstros da lista_monstro
      Console.Write("\n\n");
      foreach (Monstro monstrinho in lista_monstro)
      {
        monstrinho.mostrar();
      }

      
      // Mostrando agora uma lista organizada lista_int
      Console.Write("\n");
      foreach (int nval in lista_int)
      {
        Console.Write(" {0}", nval);
      }

      // Mostrando agora uma lista organizada outra_lista
      Console.Write("\n");
      foreach (int nval in outra_lista)
      {
        Console.Write(" {0}", nval);
      }
      
      // Removendo itens
      // O Lobisomen morreu
      lista_monstro.Remove(lobisomem);
      lista_monstro.RemoveAt(1);
      lista_int.Remove(45);      
    
      // Mostrando a lista lista_monstro
      Console.Write("\n\n");
      foreach (Monstro monstrinho in lista_monstro)
      {
        monstrinho.mostrar();
      } // endfor each
      Console.Write(" O Lobisomem morreu!\n");
      
      // Mostrando conteúdo da lista lista_int
      Console.Write("\n");
      foreach (int nval in lista_int)
      {
        Console.Write(" {0}", nval);
      }
      Console.WriteLine("\n");    


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
} // fim do namespace prj_List