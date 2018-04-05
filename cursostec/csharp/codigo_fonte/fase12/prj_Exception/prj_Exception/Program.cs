// Projeto prj_Exception - Arquivo: Program.cs
// Este programa ilustra o uso de exceções
using System;
using System.IO;

namespace prj_Exception
{
  class Program
  {
    static void Main(string[] args)
    {

      config_janela("prj_Exception");

      // Variáveis de trabalho
      double resultado = 0;
      double x = 3;
      
      // Vamos forçar um divisão por zero
      double y = 0;

      // Levantando uma exceção por conta própria
      try
      {      
        if (y == 0) throw new DivideByZeroException();
        resultado = x / y;
        Console.WriteLine(" resultado = {0}", resultado); 
      } // endtry

      // Pega e trata a correção
      catch (DivideByZeroException)
      {
        Console.WriteLine(" Tentativa de divisão por zero");
        Console.WriteLine(" Geralmente o problema é tratado dentro de catch(){}");
      } // endcatch

      finally
      {
        Console.WriteLine(" finally{} faz ajustes finais em qualquer situação!:");
        Console.WriteLine(" Valores da operação: x:{0}  y:{1}", x, y);        
     } //end finally
      // **********************************************************************

    
      // Descomente a linha abaixo para derrubar esta aplicação!
      // File.Copy("zzz.txt", "yyy.txt");
      
      // catch(){} pode ser usado sem argumentos
      try
      {
        File.Copy("zzz.txt", "yyy.txt");
      } // endtry
      
      catch
      {
        Console.WriteLine("\n Ocorreu um problema na operação de cópia de arquivo!");
      } // endcatch
      // **********************************************************************

    
      // catch() pode pegar uma exceção específica
      try
      {
        File.Copy("zzz.txt", "yyy.txt");
      } // endtry

      catch (FileNotFoundException erro)
      {
        Console.WriteLine("\n");
        Console.WriteLine(erro.Message);
      } // endcatch

      // **********************************************************************

      // catch() pode pegar uma exceção geral
      try
      {
        File.Copy("zzz.txt", "yyy.txt");
      } //endtry

      catch (SystemException erro)
      {
        Console.WriteLine("\n");
        Console.WriteLine(erro.Message);
        Console.WriteLine("\t Rastro da pilha (StackTrace):");
        Console.WriteLine(" *****************************************");
        Console.WriteLine(erro.StackTrace);
      } // endcatch

      Console.Read();

    } // main() fim

    // Método para configurar a janela
    private static void config_janela(string  titulo)
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = titulo;
      Console.SetBufferSize(80, 30);
      Console.SetWindowSize(80, 30);
      Console.Clear();
      Console.WriteLine("");
    } // config_janela() fim    

  } // fim da classe Program
} // fim do namespace prj_Exception
