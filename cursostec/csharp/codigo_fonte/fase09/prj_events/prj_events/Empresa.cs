// Projeto prj_events - Arquivo: Empresa.cs
// Mostrar como rodar métodos de forma paralela (multitarefa)
using System;
using System.Threading;

namespace prj_events
{
  class Empresa
  {
    // Executa quando o trabalho do vendedor for iniciado
    public static void VendedorTrabalhoIniciado()
    {
      Console.WriteLine(@" Empresa.VendedorTrabalhoIniciado():
      Vendedor começa o trabalho.");
    } // VendedorTrabalhoIniciado().fim

    // Executa quando o trabalho do vendedor for terminado
    public static int VendedorTrabalhoTerminado()
    {
      Thread.Sleep(4000);
      Console.WriteLine("\n");
      Console.WriteLine(@" Empresa.VendedorTrabalhoTerminado():
      Empresa recompensa o trabalho completo do Vendedor!");
      return 7;
    } // VendedorTrabalhoTerminado().fim
  } // fim da classe
} // fim do namespace
