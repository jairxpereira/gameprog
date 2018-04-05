// Projeto tstStatic Arquivo: Ferramentas.cs
using System;

namespace tstStatic
{
  static class Ferramentas
  {

    static public int nvezes = 0;

    // Retorna o nome de rede do computador    
    public static String nome_computador()
    {   
      String nome_pc = "";
      nome_pc = Environment.MachineName;
      nvezes++;
      return nome_pc;    
    } // nome_computador().fim

    // Retorna o nome do usuário local
    public static String nome_usuario()
    {
    String usuario = "";
      usuario = Environment.UserName;
      nvezes++;
      return usuario;
    } // nome_usuario().fim

    // Método para configurar a janela
    public static void config_janela(String titulo)
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = titulo;
      Console.SetBufferSize(80, 30);
      Console.SetWindowSize(80, 30);
      Console.Clear();
      nvezes++;
    } // config_janela() fim    

  } // fim da classe
} // fim do namespace
