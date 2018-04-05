// Projeto prj_clsVirtual -  Arquivo: Program.cs
// Ilustra o uso de método virtual
using System;

namespace prj_clsVirtual
{
  class Program
  {
    static void Main(string[] args)
    {
      config_janela("projeto prj_clsVirtual");

      // Vamos criar uma quadrilha de monstros
      Monstro godzila = new Monstro();
      Ogro shrek = new Ogro();
      Vampiro alucard = new Vampiro();

      // Vamos configurar os nomes 
      godzila.m_nome = "Godzila";
      shrek.m_nome = "Shrek";
       alucard.m_nome = "Alucard";

      // Vamos atacar 
      godzila.atacar();
      shrek.atacar();
      alucard.atacar();

      // Vamos criar uma array de monstros!
      Monstro[] inimigo = new Monstro[5];
      inimigo[1] = godzila;
      inimigo[2] = shrek;
      inimigo[3] = alucard;

      Console.Write(" ----------------------------------------------------------\n");
      Console.Write(" * Vamos atacar todos de uma vez via inimigo[ncx].atacar()\n");
      Console.WriteLine(" * Com virtual\\override agora roda o atacar() da subclasse");
      for (int ncx = 1; ncx <= 3; ncx++) inimigo[ncx].atacar();

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
