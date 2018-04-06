// Projeto prj_Lock - Arquivo: Program.cs
// Este programa mostra o uso de Lock no ambiente de threads
using System;
using System.Threading;

namespace prj_Lock
{
  class Program
  {  
    // Linhas paraleas de execução
    public static Thread linha01; // energia++
    public static Thread linha02; // energia++

    static void Main(string[] args)
    {
      config_janela("prj_Lock");

      // Vamos criar um novo jogador
      Jogador player01 = new Jogador();      

      // Assinala as funções às linhas de execução
      linha01 = new Thread(new ThreadStart(player01.subindo01));
      linha02 = new Thread(new ThreadStart(player01.subindo02));

      // Nomeando os threads
      linha01.Name = "subindo01()";
      linha02.Name = "subindo02()";

      // As linhas começa o trabalho em paralelo com Start()
      linha01.Start();  // energia++
      linha02.Start();  // ylin--       

      // O programa aguarda o completamento das tarefas para finalizar-se
      linha01.Join();
      linha02.Join();

      Console.WriteLine("\n\n Pressione ENTER novamente para encerrar");
      Console.Read();

    } // main() fim

    // Método para configurar a janela
    private static void config_janela(string titulo)
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = titulo;
      Console.SetBufferSize(80, 25);
      Console.SetWindowSize(80, 25);
      Console.Clear();
      Console.WriteLine("\n");

    } // config_janela() fim    

  } // fim da classe Program
} // fim do namespace prj_Lock