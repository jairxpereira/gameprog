// projeto prj_modificadores - Arquivo: Program.cs
// Esse projeto ilustra o uso de modificadores de acesso
using System;

namespace prj_modificadores
{
  class Program
  {

    static void Main(string[] args)
    {
      // tools é um objeto da classe Ferramentas
      Ferramentas tools = new Ferramentas();

      tools.config_janela("projeto prj_modificadores");

      Console.WriteLine("\n Nome do usuário: " +
        tools.nome_usuario());

      Console.WriteLine(" Nome do computador: " +
        tools.nome_computador());

      Console.WriteLine(" Contagem de uso das ferramentas: " +
      tools.get_contador());

      tools.set_contador(5);

      tools.mostrar_contador();  

      Console.Read();

    } // Main().fim
  } // class.fim
} // namespace.fim