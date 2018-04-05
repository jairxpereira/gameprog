// Projeto prj_Queue
// Este programa mostra o uso de Queue<T>
using System;
using System.Collections.Generic;

namespace prj_Queue
{
  class Cliente 
  {
    // Nome do cliente
    public string m_nome;
    // Código de identificação
    public int m_codigo;

    // Construtor
    public Cliente(string nome, int codigo)
    {
      m_nome = nome;
      m_codigo = codigo;
    } // fim do construtor

    // Exibe o nome do cliente e código de identificação
    public void mostrar()
    {
      Console.WriteLine(" Cliente: ({0},{1})", m_nome, m_codigo);
    } // mostrar().fim    
  } // fim da classe cliente  


  class Program
  {
    static void Main(string[] args)
    {

      config_janela("prj_Queue");

      // Declarando uma fila de inteiros
      Queue<int> fila_int = new Queue<int>();      

      // Declarando uma fila de clientes
      Queue<Cliente> fila_cliente = new Queue<Cliente>();     

      // Adicionando cliente na fila_cliente
      Cliente pedro = new Cliente("Pedro", 133);
      fila_cliente.Enqueue(new Cliente("Paulo", 140));
      fila_cliente.Enqueue(new Cliente("Marieta", 622));
      fila_cliente.Enqueue(new Cliente("Gustavo", 920));
      fila_cliente.Enqueue(pedro);
      
      // Adicionando inteiros na fila_int
      fila_int.Enqueue(10);
      fila_int.Enqueue(77);
      fila_int.Enqueue(1);
      fila_int.Enqueue(13);
      fila_int.Enqueue(45);

      // Mostrando conteúdo da fila_int
      Console.Write("\n");
      foreach (int nval in fila_int)
      {
        Console.Write(" {0}", nval);
      }

      // Mostrando os clientes da fila_cliente
      Console.Write("\n\n");
      foreach (Cliente pessoa in fila_cliente)
      {
        pessoa.mostrar();
      }


      // Vamos ''atender'' os clientes no while...
      while ( fila_cliente.Count > 0)
      {
      
        Console.Write(" \n\n Primeiro da fila: ");
        fila_cliente.Peek().mostrar();
        Console.Write(" Atendido: ");
        fila_cliente.Dequeue().mostrar();
      } // endwhile
      
      // Pausa para a leitura da tela
      Console.Read();   
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
} // fim do namespace prj_Queue