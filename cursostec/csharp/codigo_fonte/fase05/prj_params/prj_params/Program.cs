// Projeto prj_params - Arquivo:Program.cs
// Ilustra o uso de lista variável de parâmetros
using System;

namespace prj_params
{
  class Program
  {
    static void Main(string[] args)
    {
      config_janela("projeto prj_params");

      mostrar_objetos(11, 12, 13,14);
      mostrar_objetos ("Dom", "Seg", "Ter");
      mostrar_objetos("Dom", 12, "Seg", 14);
      Console.ReadKey();
    } // Main( )


    // ****** Mostra uma lista variável de objetos ************
    public static void mostrar_objetos ( params Object[] lista)
    {
      int ntam = lista.Length;
      Console.Write("\n");
      for (int ncx = 0; ncx < ntam; ncx++)
      {
        Console.WriteLine(" {0}",lista[ncx]);
      } // for.fim

    } // mostrar_objetos().fim


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
