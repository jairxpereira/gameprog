// Projeto prj_Reflection01 - Arquivo: Program.cs
// Mostra como usar System.Reflection
using System;
using System.Reflection;

namespace prj_Reflection01
{
  class Program
  {

    public static void Main()
    {
      config_janela("prj_Reflection01");

      // /campos para contagem dos itens
      int qtd_classes = 0;
      int qtd_interfaces = 0;
      int qtd_enums = 0;

      int linha = 0;

      // Carrega a assembly
      Assembly lib = Assembly.Load("mscorlib");

      // Obtém os diversos tipos dentro da assembly (classes, interfaces, etc)
      Type[] entidades = lib.GetTypes();

      // Verifica a quantidade de tipos dentro da assembly
      int ntam = entidades.Length;

      // Exibe os diversos tipos existentes
      Console.WriteLine(" Tipos presentes em mscorlib");
      Console.WriteLine(" --------------------------------------------------");
      int nlimite = 25;
      for (int ncx = 0; ncx < nlimite; ncx++)
      {
        Type entidade = entidades[ncx];
        Console.WriteLine("\t {0}", entidade.ToString());
        // Contagem de classes, interfaces e enumerações
        if (entidade.IsInterface) qtd_interfaces++;
        if (entidade.IsClass) qtd_classes++;
        if (entidade.IsEnum) qtd_enums++;
      } //endfor each

      // Exibe algumas estatísticas
      Console.WriteLine("\n\n Contagem: \n Classes              #:{0}", qtd_classes);
      Console.WriteLine(" Interfaces           #:{0}", qtd_interfaces);
      Console.WriteLine(" Enumerações          #:{0}", qtd_enums);
      Console.WriteLine(" Total de entidades   #:{0}\n\n", ntam);

      pause();
      // Mostra membros presentes em System.Console
      Type console = lib.GetType("System.Console");
      MemberInfo[] membros = console.GetMembers();
      Console.WriteLine("\n Membros presentes em System.Console");
      Console.WriteLine(" --------------------------------------------------");
      foreach (MemberInfo mi in membros)
      {

        // Exibe membro e tipo do membro
        Console.Write(" {0}", mi.MemberType);
        Console.Write(" \t{0}\n", mi.ToString());

        // Pula uma linha pra facilitar a leitura
        linha++;
        if (linha % 5 == 0) Console.Write("\n");
        if (linha % 20 == 0) pause();

      } // endforeach

      pause();
      // Mostra métodos presentes em System.Console
      membros = console.GetMethods();
      Console.WriteLine("\n Métodos presentes em System.Console");
      Console.WriteLine(" --------------------------------------------------");
      foreach (MemberInfo mi in membros)
      {

        // Exibe membro e tipo do membro
        Console.Write(" {0}", mi.MemberType);
        Console.Write(" \t{0}\n", mi.ToString());

        // Pula uma linha pra facilitar a leitura
        linha++;
        if (linha % 5 == 0) Console.Write("\n");
        if (linha % 20 == 0) pause();

      } // endforeach


      pause();
      // Mostra métodos dentro de certos critérios de System.Console
      membros = console.FindMembers(MemberTypes.Method, 
        BindingFlags.Public | BindingFlags.Static,
        Type.FilterNameIgnoreCase, "get*");

      Console.WriteLine("\n Métodos que começam com get...");
      Console.WriteLine(" --------------------------------------------------");
      foreach (MemberInfo mi in membros)
      {
        // Exibe membro e tipo do membro
        Console.Write(" {0}", mi.MemberType);
        Console.Write(" \t{0}\n", mi.ToString());
        // Pula uma linha pra facilitar a leitura
        linha++;
        if (linha % 5 == 0) Console.Write("\n");
        if (linha % 20 == 0) pause();
      } // endforeach

      pause(); pause();

      
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
      Console.SetBufferSize(120, 2345);
      Console.SetWindowSize(120, 40);
      Console.Clear();
      Console.Write("\n");
    } // config_janela() fim   
  } // fim da classe Program
} // fim do namespace


