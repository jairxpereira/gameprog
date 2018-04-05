// projeto tstStatic - Arquivo: Program.cs
// Esse projeto ilustra como usar classes e métodos estáticos
using System;

namespace tstStatic
{
  class Program
  {
    
    static void Main(string[] args)
    {

      Ferramentas.config_janela("projeto tstStatic");
      
      Console.WriteLine("\n Nome do usuário: " + 
        Ferramentas.nome_usuario());

      Console.WriteLine(" Nome do computador: " +
        Ferramentas.nome_computador());

      Console.WriteLine(" Contagem de uso das ferramentas: " +
        Ferramentas.nvezes);
      
      Console.Read();

    } // Main().fim
  } // class.fim
} // namespace.fim
