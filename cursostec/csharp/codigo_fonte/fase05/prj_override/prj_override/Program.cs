// projeto prj_override - Arquivo: Jogador.cs
// Ilustra o uso de override para re-implementar toString()
using System;

namespace prj_override
{
  class Program
  {
    static void Main(string[] args)
    {

      config_janela("projeto prj_override");
      
      // Cria um objeto jogador
      Jogador player1 = new Jogador("Megaman", 26);
      
      // Exibe uma versão string do objeto Jogador
      Console.WriteLine("\n {0} \n", player1.ToString());
      Console.ReadKey();

    } // Main().fim

    // Método para configurar a janela
    static void config_janela(String titulo)
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = titulo;
      Console.SetBufferSize(80, 30);
      Console.SetWindowSize(80, 30);
      Console.Clear();

    } // config_janela() fim
  } // fim da classe
} // fim do namespace
