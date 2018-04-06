// Projeto prj_Reflection02 - Arquivo: Program.cs
// Mostra como invocar indiretamente um método
using System;
using System.Reflection;

namespace prj_Reflection02
{
  class Program
  {

    public static void Main()
    {
      config_janela("prj_Reflection02");

      // Carrega a assembly 
      Assembly lib = Assembly.Load("mscorlib");

      // Carrega o namespace System.Math
      Type mat_modulo = lib.GetType("System.Math");
      
      // Vamos chamar indiretamente a função nval = Pow ( nBase, nExpoente)
      // que retorna o valor de uma potência
      
      // Vamos estocar os tipos dos dados numa array
      Type[] tipo_argumentos = new Type[2];
      tipo_argumentos[0] = Type.GetType("System.Double"); // nBase
      tipo_argumentos[1] = Type.GetType("System.Double"); // nExpoente

      // Pega o método com a assinatura abaixo
      MethodInfo potencia = mat_modulo.GetMethod("Pow", tipo_argumentos);
      
      // Vamos estocar os valores numa array
      object[] valor_argumentos = new object[2];
      
      // Alimenta os valores de ( nBase, nExpoente )
      valor_argumentos[0] = 5;
      valor_argumentos[1] = 3;

      // O método Pow() retorna um double
      double resultado = 0;
      
      // Invoca o método fazendo um casting do objeto de retorno
      resultado = (double) potencia.Invoke(mat_modulo, valor_argumentos);

      // Exibe o resultado
      Console.WriteLine(" {0} ^ {1} = {2}", 
        valor_argumentos[0], valor_argumentos[1], resultado);   

      pause();
   

    } // Main().fim


    // Pausa para a leitura
    private static void pause()
    {
      Console.Read();
    } // pause().fim


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
} // fim do namespace