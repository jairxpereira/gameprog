// Projeto prj_events - Arquivo: Vendedor.cs
// Mostrar como rodar métodos de forma paralela (multitarefa)
using System;
using System.Threading;

// Assinatura para os eventos e handlers (funções tratadoras)
delegate void TrabalhoIniciado();
delegate void TrabalhoProgredindo();
delegate int TrabalhoCompleto();

namespace prj_events
{

  class Vendedor
  {

    // Comissão do vendedor (R$)
    private int ncomissao;
    
    // Eventos da classe Vendedor
    public event TrabalhoIniciado iniciado;
    public event TrabalhoProgredindo progredindo;
    public event TrabalhoCompleto terminado;

    public void RealizarTrabalho()
    {
      Console.WriteLine("\n");
      Console.WriteLine(" Vendedor: trabalho começou");
      if (iniciado != null) iniciado();

      Console.WriteLine("\n Vendedor: trabalho progredindo");
      if (progredindo != null) progredindo();

      Console.WriteLine("\n Vendedor: trabalho completo");
      if (terminado != null)
      {

        foreach (TrabalhoCompleto tc_metodo in terminado.GetInvocationList())
        {
          tc_metodo.BeginInvoke(new AsyncCallback(TrabalhoAvaliado), tc_metodo);
        } // endfor each
      } // endif

    } // RealizarTrabalho().end

    
    // Função chamada quando o tratamento dos eventos são finalizados
    void TrabalhoAvaliado(IAsyncResult res)
    {
      TrabalhoCompleto tc_metodo = (TrabalhoCompleto)res.AsyncState;
      ncomissao += tc_metodo.EndInvoke(res);
      Console.WriteLine(" Vendedor.TrabalhoAvaliado(): comissão= " + ncomissao);
    } // TrabalhoAvaliado().fim

    static void Main()
    {

      config_janela("prj_events");
            
      // Vamos criar os objetos
      Vendedor pedro = new Vendedor();
      Gerente gerente = new Gerente();      

      // Pedro se prepara para notificar o gerente e a empresa do andamento 
      // do seu trabalho
      pedro.terminado += new TrabalhoCompleto(gerente.TrabalhoCompleto);
      pedro.terminado += new TrabalhoCompleto(Empresa.VendedorTrabalhoTerminado);
      pedro.iniciado += new TrabalhoIniciado(Empresa.VendedorTrabalhoIniciado);
   
      // Pedro realizar o seu trabalho e produz os eventos durante isso
      pedro.RealizarTrabalho();

      // Isso executa de maneira não-linear.
      Console.WriteLine("\n Main(): Vendedor completou o trabalho!");
      Console.WriteLine("\n *** Pressione enter para encerrar. *** \n");
      Console.ReadLine();
    } // Main().fim


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
  } // fim da classe
} // fim do namespace
