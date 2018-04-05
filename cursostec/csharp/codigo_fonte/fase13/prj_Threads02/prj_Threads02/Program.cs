// Projeto prj_Threads02 - Arquivo: Program.cs
// Este programa mostra como criar uma aplicação multi-tarefa
using System;
using System.Threading;

namespace prj_Threads02
{
  class Program
  {

    // Variáveis de trabalho
    private static int xcol = 0;
    private static int ylin = 1000;

    // Linhas paraleas de execução
    public static Thread linha01; // xcol++
    public static Thread linha02; // ylin--

    static void Main(string[] args)
    {

      config_janela("prj_Threads02");

      menu();        

      // Assinala as funções às linhas de execução
      linha01 = new Thread(new ThreadStart(subindo));
      linha02 = new Thread(new ThreadStart(caindo));      

      // As linhas começa o trabalho em paralelo com Start()
      linha01.Start();  // xcol++
      linha02.Start();  // ylin--   

      linha01.IsBackground = true;
      linha02.IsBackground = true;   

      linha01.Name = "subindo()";
      linha02.Name = "caindo()";   
   
      ConsoleKeyInfo tecla;
      tecla = (ConsoleKeyInfo) Console.ReadKey();

      if (tecla.Key == ConsoleKey.J)
      {
        // A linha Main() trava e aguarda o final do processamento das linhas.
        linha01.Join();
        linha02.Join();   
      } // endif

      if (tecla.Key == ConsoleKey.Escape)
      {
        linha01.Abort();
        linha02.Abort();       
      } // endif


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
    } // config_janela() fim    


    // Aumenta o valor de xcol
    private static void subindo()
    {
      
      try
      {
       for (int ncx = 0; ncx < 1000; ncx++)
       {
        xcol++;
        mostrar(" +++ subindo(): ", 1, 1);
        Thread.Sleep(0);  
         
       } // endfor

      } // endtry

      catch (ThreadAbortException)
      {
        Console.WriteLine(" {0} finalizado antes do final! ", Thread.CurrentThread.Name);
        Console.WriteLine(" Ambiente foi limpo!");
      } // 
    } //subindo()


    // Decresce o valor de ylin
    private static void caindo()
    {
      try
      {
        for (int ncx = 0; ncx < 1000; ncx++)
        {
          ylin--;
          mostrar(" --- caindo()  :", 3, 1);
          Thread.Sleep(0);

        } // endfor

      } // endtry

      catch (ThreadAbortException)
      {
        Console.WriteLine(" {0} finalizado antes do final! ", Thread.CurrentThread.Name);
        Console.WriteLine(" Ambiente foi limpo!");
      } //

    } // caindo()
    
    // Mostra opções acionadas via teclado
    private static void menu()
    {
      Console.CursorTop = 11;
      Console.CursorLeft = 1;

      Console.WriteLine("\n Escape - aborta a execução das linhas" + 
        " com tratamento de exceção");
     
      Console.WriteLine(" j - Main() trava e aguarda o final do" + 
        " processamento das linhas de execução");

      Console.WriteLine(" ENTER - Main() encerra suas atividades" +
        " encerrando as linhas de background");

      Console.CursorTop = 1;
      Console.CursorLeft = 1;

    } // menu().fim
   

    // Mostra um texto na posição (linha, coluna)
    private static void mostrar(string txt, int linha, int coluna)
    {
      // Define posições fixas para exibir mensagens
      Console.CursorTop = linha;
      Console.CursorLeft = coluna;

      Console.Write("{0} ( {1},{2} ) \n", txt, xcol, ylin);

      // Reduz velocidade de execução das coisas
       Thread.Sleep(100);
    } // mostrar()
    
  } // fim da classe Program
} // fim do namespace prj_Threads01