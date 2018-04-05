// Projeto prj_Pilha - Arquivo: Program.cs
// Este programa testa a classe Stack<T>
using System;
using System.Collections.Generic;

namespace prj_Pilha
{
  class Program
  {
    static void Main(string[] args)
    {

      config_janela("prj_Pilha");
      
      // Declarando uma pilha de dados
      Stack<int> pilha_int = new Stack<int>();
      Stack<String> func_pilha = new Stack<String>();
      
      // Colocando dados na pilha
      pilha_int.Push(13);
      pilha_int.Push(27);
      pilha_int.Push(17);
      pilha_int.Push(83);

      // Simulando funções chamando funções
      func_pilha.Push("mostrar_dobro()");
      func_pilha.Push("retornar_dobro()");
      func_pilha.Push("converter_numero()");
      func_pilha.Push("verificar_numero()");
      
      Console.WriteLine("\n\n Ordem de entrada: 13, 27, 17, 83");

      // Pop() remove os elementos da pilha
      Console.Write(" Ordem de saída: ");
      while (pilha_int.Count > 0)
      {
        int nval = pilha_int.Pop();
        Console.Write ("{0} ", nval);
      } // endwhile      


      // Mostrando as funções na ordem que foram chamadas
      Console.WriteLine("\n\n Chamadas entrando dentro de chamadas: ");
      Console.WriteLine(" Main() chama mostrar_dobro() que chama");
      Console.WriteLine(" retornar_dobro() que chama");
      Console.WriteLine(" converter_numero() que chama");
      Console.WriteLine(" verificar_numero() que chama");

      // Pop() remove os elementos da pilha
      Console.Write("\n Ordem de retorno: \n");
      while (func_pilha.Count > 0)
      {
        string sfunc = func_pilha.Pop();
        Console.Write(" {0}\n", sfunc);
      } // endwhile      

      Console.Read();

    } // main() fim

    // Método para configurar a janel
    private static void config_janela(string titulo)
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = titulo;
      Console.SetBufferSize(80, 30);
      Console.SetWindowSize(80, 30);
      Console.Clear();
    } // config_janela() fim    

  } // fim da classe Program
} // fim do namespace prj_Pilha