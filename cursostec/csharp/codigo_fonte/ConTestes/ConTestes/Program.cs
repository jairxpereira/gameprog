// This example demonstrates the ConsoleColor enumeration.
using System;

class Sample
{
    public static void Main()
    {
      config_janela();

      int mysoma = soma(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

      myshow(mysoma);
      valtest(mysoma);
      myshow(mysoma);


      reftest(ref mysoma);
      myshow(mysoma);





      Console.ReadKey();
       
        } // main().fim     

    // Método para configurar a janel
    private static void config_janela()
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = " Testes gerais";
      Console.SetBufferSize(80, 30);
      Console.SetWindowSize(80, 30);
      Console.Clear();
    } // config_janela() fim   

    public static int soma(params int[] vals)
    {
      int s = 0;
      int ntam = vals.Length;
      for (int ncx = 0; ncx < ntam; ncx++)
        s = s + vals[ncx];
      return s;
    }

    private static void valtest(int nval)
    {
      Console.WriteLine("\nvaltest()");
      nval = nval + 10;
    }

  
  
  private static void reftest (ref int nval)
  {
    Console.WriteLine("\nreftest()");
    nval = nval + 10;

  }

  static void myshow(int nval) { Console.WriteLine("mysoma: "  + nval); }





} // fim da classe sample



