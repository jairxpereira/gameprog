// Projeto prj_PoliServidor - Arquivo: Program.cs
// Este programa testa comunicação assíncrona de dados 
// e múltiplas conexões clientes
using System;
using System.IO;
using System.Net;
using System.Net.Sockets;

namespace prj_PoliServidor
{
  class Servidor
  {
    static void Main(string[] args)
    {
      config_janela("prj_PoliServidor");

      iniciar_servidor();

    } // main().fim

    // Roda o código de monitoramento e estabelecimento das conexões
    private static void iniciar_servidor()
    {
      // Define um objeto endereço de ip      
      IPAddress endereco = IPAddress.Parse("127.0.0.1");

      // Define um listener (ouvinte) para o endereço de ip em uma
      // porta específica
      TcpListener porteiro = new TcpListener(endereco, 65000);

      avisar("Esperando conexão...");
      porteiro.Start();

      // Continua monitorando enquando os dados vem e vão
      for (; ; )
      {
        // Se um cliente conectar, aceite a conexão e retorne
        // um novo soquete nomeado tomada_cliente enquanto o 
        // 'porteiro' continua ouvindo
        Socket tomada_cliente = porteiro.AcceptSocket();
        avisar("\n Cliente conectado Ok");

        // Inicia um novo atendimento a cada nova conexão
        Atendimento conexao_ativa = new Atendimento(tomada_cliente);
        conexao_ativa.iniciarLeitura();
      } // endfor 
    } // iniciar_servidor().fim


    // Mostra uma mensagem na tela
    private static void avisar(string mensagem)
    {
      Console.WriteLine(" {0}", mensagem);
    }

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
} // fim do namespace prj_PoliServidor
