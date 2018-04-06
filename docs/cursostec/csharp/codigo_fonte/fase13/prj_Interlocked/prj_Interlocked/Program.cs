// Projeto prj_Interlocked - Arquivo: Program.cs
// Este programa mostra o uso da classe Interlocked
using System;
using System.Threading;

namespace prj_Interlocked
{
  class Program
  {

    // Variáveis de trabalho
    private static int xcol = 0; 

    // Linhas paraleas de execução
    public static Thread linha01; // xcol++
    public static Thread linha02; // xcol++

    static void Main(string[] args)
    {

      config_janela("prj_Interlocked");

      // Assinala as funções às linhas de execução
      linha01 = new Thread(new ThreadStart(subindo01));
      linha02 = new Thread(new ThreadStart(subindo02));
      
      // Nomeando os threads
      linha01.Name = "subindo01()";
      linha02.Name = "subindo02()";

      // As linhas começa o trabalho em paralelo com Start()
      linha01.Start();  // xcol++
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


    // Aumenta o valor de xcol
    private static void subindo01()
    {
      int temp = 0;
      try
      {
        while (xcol < 10)
        {
         
          // xcol++
          temp = Interlocked.Increment(ref xcol);          
          mostrar(" subindo01():", temp);
          Thread.Sleep(0);
        } // endwhile
      } // endtry

      catch (ThreadAbortException)
      {
        Console.WriteLine(" {0} finalizado antes do final! ", Thread.CurrentThread.Name);
        Console.WriteLine(" Ambiente foi limpo!");
      } // endcatch
    } //subindo01().fim


    // Aumenta o valor de xcol
    private static void subindo02()
    {
      int temp = 0;

      try
      {

        while (xcol < 10)
        {

          // xcol++
          temp = Interlocked.Increment(ref xcol);         
          mostrar(" subindo02():", temp);
          Thread.Sleep(0);

        } // endwhile
      } // endtry

      catch (ThreadAbortException)
      {
        Console.WriteLine(" {0} finalizado antes do final! ", Thread.CurrentThread.Name);
        Console.WriteLine(" Ambiente foi limpo!");
      } // endcatch
    } // subindo02()   


    // Mostra um texto e a variável temp
    private static void mostrar(string txt, int temp) 
    {  
      Console.Write("{0} {1} \n", txt, temp);
      
      // Estranhamente, esse Sleep ajuda na sincronia das linhas
      // Coloque 0 aqui e ocorre dessincronia na aplicação
      Thread.Sleep(1);
    } // mostrar()

  } // fim da classe Program
} // fim do namespace prj_Interlocked