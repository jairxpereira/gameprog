// Projeto prj_interface -  Arquivo: Program.cs
// Ilustra o uso de interfaces
using System;

namespace prj_interface
{
  class Program
  {
    static void Main(string[] args)
    {
      config_janela("projeto prj_interface");

      // Vamos criar uma quadrilha de monstros
      IMonstro godzila = new Ogro();
      Ogro shrek = new Ogro();
      
      Vampiro alucard = new Vampiro();
      alucard.X = 320;
      alucard.Y = 240;

      // Vamos configurar os nomes 
      godzila.Nome = "Godzila";
      shrek.Nome = "Shrek";
      alucard.Nome = "Alucard";

      // Vamos atacar 
      godzila.atacar();
      shrek.atacar();
      alucard.atacar();
      alucard.showpos();
      
      // Vamos criar uma array de monstros!
      IMonstro[] inimigo = new IMonstro[5];
      inimigo[1] = godzila;
      inimigo[2] = shrek;
      inimigo[3] = alucard;

      Console.Write(" ----------------------------------------------------------\n");
      Console.Write(" * Vamos atacar todos de uma vez via inimigo[ncx].atacar()\n");
      Console.WriteLine(" * Também na interface, roda o atacar() da subclasse");
     
      for (int ncx = 1; ncx <= 3; ncx++)
      {
        inimigo[ncx].atacar();

        IPosition obj_pos = inimigo[ncx] as IPosition;
        if ( obj_pos != null) Console.WriteLine(" IPosition implementada: ");
        if (obj_pos != null) obj_pos.showpos();   

      } // fim do for

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
