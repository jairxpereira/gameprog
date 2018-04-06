// Projeto prg_permuta - Arquivo: Program.cs
// Ilustra duas formas de passagem de argumentos
// Ilustra também function overloading
using System;

namespace prj_permuta
{
  class Program
  {
    static void Main(string[] args)
    {

      String caixa = "vazio";
      String mochila = "faca";
      String item_descricao;
      int item = 0;

      config_janela("projeto prj_permuta");
      mostrar_string("Conteúdo dos recipientes", "caixa", "mochila");
      mostrar_string("--------------------------------------------",
      caixa, mochila);
      
      // Passagem por valor
      permuta_string(caixa, mochila);
      mostrar_string("\n 1.Passagem por valor:", caixa, mochila);

      // Passagem por referência
      permuta_string(ref caixa, ref mochila);
      mostrar_string("2.Passagem por referência:", caixa, mochila);
      
      // Testando out
      mostrar_string("--------------------------------------------");
      for (item = 0; item < 3; item++)
      {
        pegar_mensagem(item, out item_descricao);
        mostrar_string("",item.ToString(),item_descricao);

      }

          
      Console.Read();
    } // Main().fim
    

    // ***********************************************************
    // Permuta o conteúdo de duas strings passadas por referência
    static void permuta_string(ref String txt01, ref String txt02)
    {
      String temp = "";
      temp = txt01;
      txt01 = txt02;
      txt02 = temp;
    } // permuta_string(ref, ref).fim

    // Permuta o conteúdo de duas strings passadas por valor.
    // *** Não emite o resultado para a função que a chamou.
    static void permuta_string(String txt01, String txt02)
    {
      String temp = "";
      temp = txt01;
      txt01 = txt02;
      txt02 = temp;
    } // permuta_string().fim

    // Mostra uma mensagem e duas strins
    static void mostrar_string(String msg, String txt01, String txt02)
    {
    Console.WriteLine ("\n {0}\n {1} {2}", msg, txt01, txt02 );

    } // mostrar_string().fim


    // Mostra uma mensagem 
      static void mostrar_string(String msg)
    {
      Console.WriteLine(" {0}\n", msg);

    } // mostrar_string().fim


    // Coloca uma mensagem variável recebida por referência
    static void pegar_mensagem (int item, out String msg)
    {
      switch (item)
        {
        
        case 1:
          msg = "Isto é uma faca!";
          break;
        
        case 2:
          msg = "Isto é uma mochila!";
          break;
         
        default:
          msg = "Nada de especial!";
          break;
        } // fim do switch

    } // pegar_mensagem().fim


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
