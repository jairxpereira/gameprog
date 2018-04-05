// Projeto prj_events - Arquivo: Gerente.cs
// Mostrar como rodar métodos de forma paralela (multitarefa)
using System;
using System.Threading;

namespace prj_events
{
  class Gerente
  {

    // Executa quando o trabalho do vendedor for terminado
    public int TrabalhoCompleto()
    {
      Thread.Sleep(3000);
      Console.WriteLine(@" gerente.TrabalhoCompleto():
      gerente recompensa o trabalho do vendedor");
      return 6; 
    } // TrabalhoCompleto().fim

  } // fim da classe
} // fim do namespace
