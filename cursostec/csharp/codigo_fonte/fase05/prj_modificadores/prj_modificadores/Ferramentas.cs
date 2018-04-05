// projeto prj_modificadores - Arquivo: Ferramentas.cs
using System;

namespace prj_modificadores
{
  class Ferramentas
  {

    static private int nvezes = 0;

    // Retorna o nome de rede do computador    
    public String nome_computador()
    {
      String nome_pc = "";
      nome_pc = Environment.MachineName;
      nvezes++;
      return nome_pc;
    } // nome_computador().fim

    // Retorna o nome do usuário local
    public String nome_usuario()
    {
      String usuario = "";
      usuario = Environment.UserName;
      nvezes++;
      return usuario;
    } // nome_usuario().fim

    // Método para configurar a janela
    public void config_janela(String titulo)
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

    
    // Retorna o contador
    public int get_contador()
    {
      return nvezes;
    }

    // Resseta o contador
    public void set_contador( int nval)
    {
    nvezes = nval;
    Console.WriteLine("\n\n O contador de uso foi modificado");
    }

    // Mostra o contador
    public void mostrar_contador()
    {
      Console.WriteLine ( " Contador: {0}", nvezes);
    }
  } // fim da classe
} // fim do namespace