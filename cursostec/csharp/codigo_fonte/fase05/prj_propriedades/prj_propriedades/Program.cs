// projeto prj_propriedades - Arquivo: Program.cs
// Ilustra o uso de propriedades
using System;

namespace prj_propriedades
{
  class Program
  {
    static void Main(string[] args)
    {
      int energia_qtd = 0;
      config_janela("projeto prj_propriedades");
            
      // Vamos criar um novo jogador
      Jogador player1 = new Jogador("Megaman", 26);
      player1.Energia = 1;
      player1.Vidas = 1;
      
      // Código de verificação executado na obtenção da propriedade
      energia_qtd = player1.Energia; // Energia.get()
      player1.mostrar_status();

      // Código de validação executado na configuração da propriedade
      player1.Energia = 120; // Energia.set(value)
      player1.Vidas = 1;
      player1.mostrar_status();
        
      // Aguarda pressionamento da tecla
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
