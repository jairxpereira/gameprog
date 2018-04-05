// Projeto prj_classe02 -  Arquivo: Program.cs
// Ilustra herança simples, redefinição de métodos (new)
// Membros estáticos; chamando o construtor da classe base
using System;

namespace prj_classe02
{
  class Program
  {
    static void Main(string[] args)
    {
   config_janela("projeto prg_classe02");

      // Vamos criar uma quadrilha de monstros
      Monstro godzila = new Monstro();         
      Ogro shrek = new Ogro();
      Ogro fiona = new Ogro(12);
      Vampiro alucard = new Vampiro();      

      // Vamos configurar os nomes exceto godzila
      shrek.m_nome = "Shrek";
      fiona.m_nome = "Fiona";
      alucard.m_nome = "Alucard";

      // Vamos atacar 
      godzila.atacar();
      shrek.atacar();
      fiona.atacar();     
      alucard.atacar();   

      Console.WriteLine(" Quantidade de monstros: #{0}", 
        Monstro.get_qtd());

      alucard.dormir();

      // Vamos criar uma array de monstros!
      Monstro[] inimigo = new Monstro[5];
      inimigo[1] = godzila;
      inimigo[2] = shrek;
      inimigo[3] = fiona;
      inimigo[4] = alucard;

      Console.Write("\n");
      Console.Write(" * Vamos atacar todos de uma vez via inimigo[ncx].atacar()\n");
      Console.WriteLine(" * Porém, somente roda o atacar() da classe base");
      for (int ncx = 1; ncx <= 4; ncx++) inimigo[ncx].atacar();
      
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
