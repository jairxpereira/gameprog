// Projeto prj_Pastas
// Este programa mostra como andar pelo sistema de arquivos
using System;
using System.IO;

namespace prj_Pastas
{
  class Program
  {
    static void Main(string[] args)
    {
      config_janela("prj_Pastas");     

      // Pega o caminho da pasta do sistema. Geralmente, C:\WINDOWS
      string windir = Environment.GetEnvironmentVariable("SystemRoot");

      // Monta um objeto de informações sobre a pasta do sistema
      DirectoryInfo pasta_Sistema = new DirectoryInfo(windir);

      int npasta = 0;

      // Mostra todas subpastas presentes na pasta do Sistema
      foreach (DirectoryInfo subpasta in pasta_Sistema.GetDirectories())
      {
        Console.WriteLine(" {0}.[{1}]", npasta, subpasta.Name);
        npasta++;
        if (subpasta.Name.Contains("Media")) mostrar_arquivos(subpasta);

      } // endforeach

      // Mostra os arquivos da pasta de sistema
      mostrar_arquivos(pasta_Sistema);

      // Pausa para a leitura do texto final
      Console.Read();

    } // Main().fim

    // Exibe os arquivos da pasta  
    private static void mostrar_arquivos(DirectoryInfo pasta)
    {
      int narquivo = 0;

      foreach (FileInfo arquivo in pasta.GetFiles())
      {
        Console.WriteLine(" \t{0}. {1}", narquivo, arquivo.Name);
        narquivo++;
        
      } // endfor each
    } // mostrar_arquivos().fim

    // Método para configurar a janela
    private static void config_janela(string titulo)
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = titulo;
      Console.SetBufferSize(80, 250);
      Console.SetWindowSize(80, 25);
      Console.Clear();
      Console.Write("\n");
    } // config_janela() fim    

  } // fim da classe Program
} // fim do namespace prj_Pastas