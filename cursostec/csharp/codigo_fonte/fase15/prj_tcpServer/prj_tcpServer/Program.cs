// Projeto prj_tcpServer -  Arquivo: Program.cs
// Este programa ilustra comunicação de dados via procotocolo tcp\ip
// Lado servidor - transmissão de dados
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace prj_tcpServer
{
  class Program
  {
    static void Main(string[] args)
    {

      config_janela("prj_tcpServer");

      iniciar_servidor();

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


    // Roda o código de estabelecimento de conexão 
    private static void iniciar_servidor()
    {      
     // Define um objeto endereço de ip
      IPAddress endereco = IPAddress.Parse("192.168.0.101");      

      // Define um listener (ouvinte) para o endereço de ip em uma
      // porta específica
      int porta = 65000;
      TcpListener porteiro = new TcpListener(endereco, porta);

      avisar("Aguardando conexão...");
      porteiro.Start();

      // Se um cliente conectar, aceite a conexão e retorne um novo 
      // soquete nomeado 'tomada' 
      Socket tomada = porteiro.AcceptSocket();

      avisar("Cliente conectado.");

      // Vamos enviar dados por uma tomada particular       
      EnviarDados(tomada);
      avisar("Disconectando...");

      // Fecha a conexão
      tomada.Close();
      porteiro.Stop();

      avisar("Saindo...");

    } // iniciar_servidor().fim


    // Método auxiliar para enviar os dados
    private static void EnviarDados(Socket tomadaCliente)
    {

      string[] dados = new string[5];
      dados[0] = "linha 01";
      dados[1] = "linha 02";
      dados[2] = "linha 03";
      dados[3] = "linha 04";
      dados[4] = null;

      // Cria um stream fluxo de rede, fluxo_rede, um stream escritor
      // para escrever neste fluxo de rede.
      NetworkStream fluxo_rede = new NetworkStream(tomadaCliente);
      StreamWriter escritor = new StreamWriter(fluxo_rede);

      // Envia um conjunto de strings pelo fluxo de rede
      for (int ncx = 0; ncx < 5; ncx++)
      {
        Console.WriteLine(" Enviando {0}", dados[ncx]);
        escritor.WriteLine(dados[ncx]);
        escritor.Flush();
      } // endfor

      // Fechando os streams     
      fluxo_rede.Close();
      escritor.Close();
    } //().fim
    
    // Mostra uma mensagem na tela
    private static void avisar(string mensagem)
    {
      Console.WriteLine(" {0}", mensagem);
    } // avisar().fim
  } // fim da classe Program
} // fim do namespace prj_tcpServer

