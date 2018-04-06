// Projeto prj_Exception02 - Arquivo:Program.cs
// Este programa mostra a definição de uma exceção particular
using System;

namespace prj_Exception02
{
  class Program
  {
    static void Main(string[] args)
    {

      config_janela("prj_Exception02");

      // Variáveis de trabalho
      int energia = 100;
      int nvidas = 10;

      // Verifica se energia foi hackeada      
      try
      {
        int nval = energia;
        if (nval > 99) throw new HackeadoException();        
      } // endtry

      catch(HackeadoException erro)
      {
        Console.WriteLine(" {0}", erro.Message);
        Console.WriteLine(" Jogador foi excluído da partida.");
      } // endcatch
      // **********************************************************************

      
      // Verifica se nvidas foi hackeada
      try
      {
        int nval = nvidas;
        if (nval > 9) throw new HackeadoException("O valor nvidas foi hackeado!");
      } // endtry

      catch (HackeadoException erro)
      {
        Console.WriteLine(" {0}", erro.Message);
        nvidas = 1;
        Console.WriteLine(" O valor nvidas foi restaurado para o menor valor!");
      } // endcatch
      // **********************************************************************

      
      // Melhor do que criar uma exceção é usar uma genérica
      try
      {
        
        if (nvidas > 9 || energia > 99) throw new ApplicationException ("\n Configuração ruim!");
      } // endtry

      catch (ApplicationException erro)
      {
        Console.WriteLine(" {0}", erro.Message);
        nvidas = 7;
        energia = 10;
        Console.WriteLine(" Configuração restaurada para valores padrões.");
      } // endcatch
      // **********************************************************************

      Console.Read();

    } // main() fim

    // Método para configurar a janel
    private static void config_janela(string titulo)
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = titulo;
      Console.SetBufferSize(80, 30);
      Console.SetWindowSize(80, 30);
      Console.Clear();
      Console.WriteLine("");
    } // config_janela() fim    

  } // fim da classe Program
} // fim do namespace prj_Exception02
