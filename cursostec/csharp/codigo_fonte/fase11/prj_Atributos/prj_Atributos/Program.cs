// Projeto prj_Atributos - Arquivo: Program.cs
// Este programa mostra como elaborar e mostrar atributos
using System;
using System.Reflection;

namespace prj_Atributos
{
 
  class Program
  {
    static void Main(string[] args)
    {

      // Configura a janela
      config_janela("prj_Atributos");
      
      // Produz um objeto jogador
      Jogador atacante = new Jogador("Neimar", 23);
     atacante.mostrar(); mostrar("");
           
      // Criando os objetos para o trabalho de recuperar atributos
      object[] lista_atributos;
      MemberInfo info = typeof(Jogador);

      // Obtém a lista de atributos
      lista_atributos = info.GetCustomAttributes(typeof(ManualizadorAttribute), false);      
      
     // Exibe os atributos na tela
      foreach (object atributo in lista_atributos)
      {
        // Faz um casting do objeto obtido para o tipo ManualAttribute
        ManualizadorAttribute manual = (ManualizadorAttribute)atributo;        
        
        // Mostra autor de tiver sido definido
        if (manual.Autor != null) mostrar(manual.Autor);        
        
        // Exibe as informações do objeto corrente
        manual.mostrar();
      } // endfor        
  
      Console.Read();

    } // main() fim

    // Exibe um texto na tela
    private static void mostrar(string txt)
    {
      Console.WriteLine(" {0}", txt);
    } // mostrar().fim

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
} // fim do namespace prj_Atributos
