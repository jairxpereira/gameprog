// Projeto prj_delegates02: arquivo Program.cs
// Mostra como chamar individualmente os métodos
// presentes em um delegate.
using System;

// Definindo um delegate
delegate void fn_calculos(int nval);


namespace prj_delegates02
{
  class Program
  {
    static void Main()
    {
      config_janela("prj_delegates02");

      // Criando uma instância de um delegate
      fn_calculos fn_ref;
    
      // Chamando diversas funções com um só delegate
      show("\n -------------------------------------");
      show("Colocando várias funções na fila");
      fn_ref = dobro;
      fn_ref += triplo;
      fn_ref += quintuplo;
      fn_ref(16);       

      pause();
      // Utilizando métodos anônimos
      show("\n\n -------------------------------------");
      show("Utilizando métodos anônimos");
      fn_ref += delegate(int nval)
      {
        Console.Write(" Método anônimo: 6x");
        int res = nval * 6;
        Console.WriteLine(" O sextuplo de {0} é {1}", nval, res);
      };
      fn_ref(2);

      pause();
      // Invocando as funções individualmente
      show("\n\n -------------------------------------");
      show("Invocando as funções individualmente");
      Delegate[] lista_metodos = fn_ref.GetInvocationList();
      int ntam = lista_metodos.Length;
      for (int ncx = 0; ncx < ntam; ncx++)
      {
        fn_calculos metodo = (fn_calculos)lista_metodos[ncx];
        metodo(100);
        metodo.Invoke(110);
      }

      // Economizando digitação com for each
      foreach (fn_calculos metodo in fn_ref.GetInvocationList())
      {
        metodo(120);       
        
      }

    
      pause();
    } // main().fim


    // Aguarda o pressionamento de qualquer tecla para prosseguir
    private static void pause()
    {
      Console.ReadKey();
    } // pause().fim

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
      Console.Write("\n");
    } // config_janela() fim   

    // Multiplica o número nval por 2
    private static void dobro(int nval)
    {
      int res = nval * 2;
      Console.WriteLine(" O dobro de {0} é {1}", nval, res);
    } // dobro().fim

    // Multiplica o número nval por 3
    private static void triplo(int nval)
    {
      int res = nval * 3;
      Console.WriteLine(" O triplo de {0} é {1}", nval, res);
    } // triplo().fim

    // Multiplica o número nval por 5
    private static void quintuplo(int nval)
    {
      int res = nval * 5;
      Console.WriteLine(" O quintuplo de {0} é {1}", nval, res);
    } // quintulo().fim

    // Mostra uma mensagem na tela
    private static void show(string mensagem)
    {
      Console.WriteLine(" {0} ", mensagem);
    } // show().fim    

  } // fim da classe
} // fim do namespace