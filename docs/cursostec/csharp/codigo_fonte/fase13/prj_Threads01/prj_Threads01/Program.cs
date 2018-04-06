// Projeto prj_Threads01
// Este programa mostrar como criar uma aplicação multi-tarefa
using System;
using System.Threading;

// Vamos usar MessageBox.Show() desse namespace...
using System.Windows.Forms;

namespace prj_Threads01
{
  class Program
  {

    // Variáveis de trabalho
    private static int xcol = 0;
    private static int ylin = 1000;

    // Linhas paraleas de execução
    public static Thread linha01; // xcol++
    public static Thread linha02; // ylin--
    public static Thread linha03; // verificar_usuario()

    static void Main(string[] args)
    {

      config_janela("prj_Threads01");

      // Assinala as funções às linhas de execução
      linha01 = new Thread(new ThreadStart(subindo));
      linha02 = new Thread(new ThreadStart(caindo));
      linha03 = new Thread(new ThreadStart(verificar_usuario));

      // As linhas começa o trabalho em paralelo com Start()
      linha01.Start();  // xcol++
      linha02.Start();  // ylin--
      linha03.Start();  // usuário quer fechar a aplicação?      
      
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
      for (int ncx = 0; ncx < 1000; ncx++)
      {
        xcol++;
        mostrar(" +++ subindo(): ", 1, 1);
      } // endfor
    } //subindo()


    // Decresce o valor de ylin
    private static void caindo()
    {         
        for (int ncx = 0; ncx < 1000; ncx++)
        {
          ylin--;
          mostrar(" --- caindo()  :", 3, 1);
        } // endfor
    } // caindo()

    // Mostra um texto na posição (linha, coluna)
    private static void mostrar(string txt, int linha, int coluna)
    {
      // Define posições fixas para exibir mensagens
      Console.CursorTop = linha;
      Console.CursorLeft = coluna;
      
      Console.Write("{0} ( {1},{2} ) \n", txt, xcol, ylin);
     
      // Reduz velocidade de execução das coisas
      Thread.Sleep(300);
    } // mostrar()

    
    // Verifica se usuário quer interromper processo
    private static void verificar_usuario()
    {

      DialogResult res = DialogResult.No;

      string mensagem = "Quer terminar a aplicação?";
      string titulo = "Testando threads";

      while (res == DialogResult.No)
      {

        if (xcol % 50 == 0)
        {
          res = MessageBox.Show(mensagem, titulo, MessageBoxButtons.YesNo);
        } // endif

        if (res == DialogResult.Yes)
        {
          linha01.Abort();
          linha02.Abort();         
        } // endif
      }// endwhile
      mostrar("Pressione ENTER para encerrar", 10, 10);

    } // verificar_teclado()
  } // fim da classe Program
} // fim do namespace prj_Threads01
