// Projeto prj_clsInterna -  Arquivo: Program.cs
// Ilustra o uso de classe interna
using System;

namespace prj_clsInterna
{
  class Program
  {
    static void Main(string[] args)
    {
      config_janela("projeto prj_clsInterna");

      // Vamos criar um jogador
      Jogador player1 = new Jogador();
      player1.nome = "Megaman";
      player1.mostrar_status();

      // Vamos criar uma mochila para o jogador
      Jogador.Mochila mochila = new Jogador.Mochila( player1);
      
      // O Jogador achou dois itens
      mochila.adicionar("faca");
      mochila.adicionar("espada");

      // Mostre os itens e a interação entre as classes!
      mochila.mostrar_itens();
      player1.mostrar_status();
     
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
      Console.Write("\n");
    } // config_janela() fim
  } // fim da classe
} // fim do namespace
