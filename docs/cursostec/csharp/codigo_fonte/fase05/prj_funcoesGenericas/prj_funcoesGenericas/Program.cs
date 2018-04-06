// Projeto prj_funcoesGenericas - Arquivo: Program.cs
// Este programa mostra o uso de funções genéricas
using System;

namespace prj_funcoesGenericas
{
  class Program
  {
    static void Main(string[] args)
    {
           
      config_janela("prj_funcoesGenericas");
      
      // Variáveis inteiras
      int x = 320;
      int y  = 240;

      // Variáveis de ponto flutuante
      float fx = 3.1415f;
      float fy = 6.2829f;

      // Objetos da classe string
      string sx = "Programar";
      string sy = "É Legal";

      // Valores originais
      Console.WriteLine("\n");
      Console.WriteLine(" Elementos originais:");
      Console.WriteLine(" Primeiro \t Segundo");
      Console.WriteLine(" -----------------------------------------------------");
      Console.WriteLine(" {0} \t\t {1} \t\t tipo inteiro", x, y);
      Console.WriteLine(" {0} \t {1} \t tipo float", fx, fy);
      Console.WriteLine(" {0} \t {1} \t tipo objeto string", sx, sy);
      
      // Vamos permutar os conteúdo das variáveis
      permutar<int>(ref x, ref y);
      permutar<float>(ref fx, ref fy);
      permutar<String>(ref sx, ref sy);

      // Os conteúdos foram permutados!
      Console.WriteLine("\n\n");
      Console.WriteLine(" Elementos originais tiveram seus valores permutados:");
      Console.WriteLine(" Primeiro \t Segundo");
      Console.WriteLine(" -----------------------------------------------------");
      Console.WriteLine(" {0} \t\t {1}", x, y);
      Console.WriteLine(" {0} \t {1}", fx, fy);
      Console.WriteLine(" {0} \t {1}", sx, sy);     
      Console.Read();

    } // Main() fim

    // Método para configurar a janela
    private static void config_janela( string titulo)
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = titulo;
      Console.SetBufferSize(80, 30);
      Console.SetWindowSize(80, 30);
      Console.Clear();
    } // config_janela() fim    

    
    // Permuta o conteúdo de duas variáveis
    private static void permutar<Generico>(ref Generico v1, ref Generico v2)
    {
      Generico temp;
      temp = v1;
      v1 = v2;
      v2 = temp;
    } // permutar<Generico>().fim

  } // fim da classe Program
} // fim do namespace prj_funcoesGenericas
