// Projeto prj_Paralelo -  Arquivo: Programa.cs
// Este programa ilustra gravação e leitura de arquivos binários
// em paralelo
using System;
using System.IO;

namespace prj_Paralelo
{
  class Program
  {

    const int arquivo_gravar = 1;
    const int arquivo_ler = 2;
    const int nulo = 0;

    static void Main(string[] args)
    {

      config_janela("prj_Paralelo");

      Disco meuhd = new Disco();

      int escolha = 0;

      escolha = menu();

      Console.Write("\n");

      if (escolha == arquivo_gravar) meuhd.gravar_dados();

      if (escolha == arquivo_ler) meuhd.ler_dados();

      Console.WriteLine("\n\t *** Pressione ENTER para encerrar! ***");

      Console.Read();

    } // main() fim 



    // menu() - Apresenta um menu com duas opções
    private static int menu()
    {
      Console.WriteLine(" \t \t Menu \n \t -------------------------\n");
      Console.WriteLine(" \t G- Gravar dados no arquivo delme.txt \n\n");
      Console.WriteLine(" \t L- Ler dados do arquivo delme.txt \n\n");
      Console.Write("\t Escolha sua opção (G, L): ");

      ConsoleKeyInfo tecla;
      tecla = (ConsoleKeyInfo)Console.ReadKey();

      if (tecla.Key == ConsoleKey.G)
      {
        // A linha Main() trava e aguarda o final do processamento das linhas.
        return arquivo_gravar;
      } // endif

      if (tecla.Key == ConsoleKey.L)
      {
        return arquivo_ler;
      } // endif

      return nulo;

    } // menu().fim


    // Método para configurar a janela
    private static void config_janela(string titulo)
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

  } // fim da classe Program
} // fim do namespace prj_Paralelo