// Projeto prj_tcpPoliCliente -  Arquivo: Cliente.cs
// Este programa ilustra comunicação de dados via procotocolo tcp\ip
// Lado cliente - envio e recepção de dados com foco maior na recepção
// Produzido por Gameprog: www.gameprog.com.br
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Text;

namespace prj_tcpPoliCliente
{
  class Cliente
  {

    static void Main(string[] args)
    {

      // Configura a janela
      config_janela("prj_tcpPoliCliente");

      // Roda o código de recepção de dados
      avisar(" Iniciando leitura de rede: ");
      iniciar_cliente();

      // Finaliza o programa
      avisar("\n\t *** Pressione ENTER para encerrar! ***");
      Console.Read();

    } // main() fim   

    // Recebe e envia dados via tcp\ip
    private static void iniciar_cliente()
    {
      // Memória para receber os dados
      string dados_chegando = "";
      string sComando = "";

      char[] memoria = new char[256];
      int ntam = memoria.Length;

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
      // e o stream escritor.
      NetworkStream fluxo_rede = tomada_servidor.GetStream();
      StreamReader leitor = new StreamReader(fluxo_rede);
      StreamWriter escritor = new StreamWriter(fluxo_rede);

      // Quando falso encerra o processo de leitura e gravação
      bool continuar = true;

      Console.WriteLine(" Digite 'parar' para finalizar. ");
      while (continuar == true)
      {
        // Recebe um comando do usuário
        Console.Write(" >");
        sComando = Console.ReadLine();
        if (sComando.Equals("parar")) continuar = false;

        try
        {                   
          // Transmite para o Servidor
          escritor.WriteLine(sComando);
          escritor.Flush();

        } // endtry

        // Verifica erros de gracação
        catch (Exception erro)
        {
          Console.WriteLine(
          " Erro de gravação ao servidor:\n {0}", erro.Message);
        } // endcatch

        
        // Recepção de dados do servidor
        try
        {
          int nlidos = leitor.Read(memoria, 0, ntam);
          if (nlidos > 0)
          {
            dados_chegando = montarTexto(memoria);
            Console.WriteLine(" {0}", dados_chegando);
          } // endif
        } // endtry

        // Verifica erros de leitura
        catch (Exception erro)
        {
          Console.WriteLine("Erro de leitura do servidor:\n {0}", erro.Message);
         } // endcatch

      }// endwhile

      // Fechando a conexão
      fluxo_rede.Close();
      leitor.Close();
      escritor.Close();

    } // iniciar_cliente().fim 

    // Mostra um aviso na tela
    private static void avisar(string mensagem)
    {
      Console.WriteLine(" {0}", mensagem);
    } // avisar().fim
  

    // Converte uma char[] em string
    private static string montarTexto ( char[] dados)
    {
      string txt = "";
      byte[] txt_bytes;
      txt_bytes = Encoding.UTF8.GetBytes(dados);
      txt = Encoding.UTF8.GetString(txt_bytes);
      txt = txt.Trim();
      return txt ;
    } // montarTexto().fim

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

  } // fim da classe Program
} // fim do namespace prj_tcpPoliCliente