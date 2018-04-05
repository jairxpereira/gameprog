// Projeto prj_clsPartial -  Arquivo: Program.cs 
// Ilustra a implementação de uma classe em vários arquivos
using System;

namespace prj_clsPartial
{
  class Program
  {
    static void Main(string[] args)
    {
      config_janela("projeto prj_clsPartial");

      Monstro godzila = new Monstro();

      godzila.m_nome ="Godzila";
      godzila.atacar();
      godzila.falar();

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
