// Projeto prj_Dicionario - Arquivo: Program.cs
// Este programa testa a classe Dictionary<T, U>
using System;
using System.Collections.Generic;

namespace prj_Dicionario
{
  class Program
  {
    static void Main(string[] args)
    {

      config_janela("prj_Dicionario");

      // Variáveis de trabalho
      string usuario = "";
      string senha = "";
      string contrasenha = "";
      string spapel = "comum";
      
      bool ok_usuario = false;    // usuário válido ?
      bool ok_senha = false;      // senha válida ?
      bool ok_admin = false;      // administrador do sistema ?


      // Nível de acesso: Visitante(0), Convidado(1), Cliente(2), Administrador(3)
      int nivel_acesso = 0;      

      // Declaração do dicionário de dados
      Dictionary<String, String> acesso = new Dictionary<string, string>();

      Dictionary<String, String> papel = new Dictionary<string, string>()
      {
        {"Jair", "Administrador"},
        {"Pedro", "comum"},
        {"Charles", "Auditor"},
        {"Leadbeater","Administrador"}    
      };      

      // Colocando usuário e senha no dicionário (chave e valor)
      acesso.Add("Jair","s4c5");
      acesso.Add("Pedro", "fsg7");
      acesso.Add("Charles", "tx45");
      acesso.Add("Leadbeater", "ghjky");

      // Pega o nome do usuário
      Console.Write(" Nome de usuário: ");
      usuario = Console.ReadLine();

      // Verifica se usuário está no dicionário de dados e pega a senha
      // armazenada para futura comparação.
      ok_usuario = acesso.TryGetValue(usuario, out contrasenha);    

      // Se o usuário existe o nivel de acesso deve crescer
      if (ok_usuario) nivel_acesso++;
      if (ok_usuario) show("Olá, " + usuario);

      // Usuário pode ter digitado nome errado ou não existe mesmo!
      if (!ok_usuario) show("Digitação errada ou usuário inexistente!");
      
      // Se o usuário existe, vamos verificar a senha dele...
      if (ok_usuario)
      {

        // Vamos pegar a senha
        Console.Write("\n Senha: ");
        senha = Console.ReadLine();
        
        // Verifica se senha existe e se estiver ok aumenta o nível de acesso
        ok_senha = senha.Equals(contrasenha);     
        if (ok_senha) nivel_acesso++;      
        if (ok_senha) show("Acesso ok");

        // Acesso negado se senha não existir
        if (!ok_senha) show(" Erro de senha: acesso negado");        
      
      } // endif (ok_usuario)

      // Verifica se usuário está na lista de papéis
      ok_usuario = papel.TryGetValue(usuario, out spapel);

      if (ok_usuario) 
      {
       if (spapel.Equals("Administrador")) ok_admin = true;
       if (spapel.Equals("Auditor")) ok_admin = true;
      }; // endif (ok_usuario)

      // Se o papel do usuário for auditor ou administrado o nível
      // de acesso deve crescer mais ainda...
      if (ok_admin) nivel_acesso++;     

      // Mostre o papel e o nível de acesso
      show("\n");
      if (nivel_acesso == 0) show("Nível de acesso: Visitante");
      if (nivel_acesso == 1) show("Nível de acesso: Convidado");
      if (nivel_acesso == 2 ) show("Nível de acesso: Cliente");
      if (nivel_acesso > 2) show("Nível de acesso: Administrador");      
      Console.Write (" Papel: {0} \n", spapel);
      pause();

    } // main() fim

    // Pause para a leitura da tela
    private static void pause()
    {
      Console.Write("\n\t Pressione ENTER para continuar... \n");
      Console.Read();
    }

    // Mostra uma mensagem na tela
    private static void show(string txt)
    {
      Console.WriteLine(" {0}",txt);

    } // show().fim


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
      Console.WriteLine("\n\n");
    } // config_janela() fim    

  } // fim da classe Program
} // fim do namespace prj_Dicionario