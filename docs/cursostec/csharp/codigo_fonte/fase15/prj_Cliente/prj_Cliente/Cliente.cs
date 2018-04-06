// Projeto prj_tcpCliente -  Arquivo: Cliente.cs
// Este programa ilustra comunicação de dados via procotocolo tcp\ip
// Lado cliente - recepção de dados
// Produzido por Gameprog: www.gameprog.com.br
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace prj_tcpCliente
{
  class Cliente
  {

    static void Main(string[] args)
    {

      // Configura a janela
      config_janela("prj_tcpCliente");

      // Roda o código de recepção de dados
      avisar(" Iniciando leitura de rede: ");
      iniciar_cliente();

      // Finaliza o programa
      avisar("\n\t *** Pressione ENTER para encerrar! ***");
      Console.Read();

    } // main() fim   


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


    // Recebe dados via tcp\ip
    private static void iniciar_cliente()
    {

      // Memória para receber os dados
      string dados_chegando = "";

      // Cria uma tomada TcpCliente para conversar com o servidor
      TcpClient tomada_servidor;

      try
      {
        tomada_servidor = new TcpClient("localHost", 65000);
      }
      catch
      {
        Console.WriteLine(
        " Falha de conexão com o servidor em {0}:65000",
        "localhost");
        return;
      }

      // Cria o stream de network, fluxo_rede, e o stream de leitura
      NetworkStream fluxo_rede = tomada_servidor.GetStream();
      StreamReader leitor = new StreamReader(fluxo_rede);

      try
      {

        // Faz a leitura dos dados do servidor e mostra-os
        do
        {
          dados_chegando = leitor.ReadLine();
          if (dados_chegando != null)
          {
            Console.WriteLine( " {0}", dados_chegando);
          }// endif
        } while (dados_chegando != null);
      } // endtry

      catch
      {
        Console.WriteLine(
        " Erro de leitura do servidor");
      } // endcatch

      // Fechando a conexão
      fluxo_rede.Close();
      leitor.Close();

    } // iniciar_cliente().fim 

    // Mostra um aviso na tela
    private static void avisar(string mensagem)
    {
      Console.WriteLine(" {0}", mensagem);
    } // avisar().fim

  } // fim da classe Program
} // fim do namespace prj_tcpCliente

