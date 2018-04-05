// Projeto prj_PoliServidor - Arquivo: Atendimento.cs
// Este programa testa comunicação assíncrona de dados e 
// múltiplas conexões clientes
using System;
using System.IO;

// Serviços de recodificação de texto
using System.Text;

using System.Net;
using System.Net.Sockets;

namespace prj_PoliServidor
{
  class Atendimento
  {
    // Buffer de memória para receber e enviar dados
    private byte[] buffer;
    
    // Objetos para manipular o fluxo de dados
    private Socket tomada;
    private NetworkStream fluxo_rede;

    // Delegates para receber as funções que vão notificar quando
    // o processo de leitura e escrita estiverem completos.
    private AsyncCallback avisoLeituraCompleta;
    private AsyncCallback avisoGravacaoCompleta;   
    
    // Controle do número de conexões 
    private int ncliente = 0;
    static int contador = 0;

    // Construtor 
    public Atendimento(Socket tomada_cliente)
    {      
      // Contabiliza a conexão que chegou e inicializa o buffer
      contador++;
      ncliente = contador;
      buffer = new byte[256];

      // Inicializa os objetos de manipulação do fluxo de dados
      tomada = tomada_cliente;      
      fluxo_rede = new NetworkStream(tomada_cliente);

      // Configura os delegates
      avisoLeituraCompleta = new AsyncCallback(this.quandoLeituraCompleta);
      avisoGravacaoCompleta = new AsyncCallback(this.quandoGravacaoCompleta);
    } // fim do construtor
   
    // Inicia o trabalho de leitura do cliente
    public void iniciarLeitura()
    {
      fluxo_rede.BeginRead(buffer, 0, buffer.Length, avisoLeituraCompleta, null);
    } // StartRead().fim        

    // Chamado quando o processo de leitura está completo
    // Pega o comando, interpreta-o e manda a resposta ao cliente
    private void quandoLeituraCompleta(IAsyncResult ar)
    {
      // Variáveis de trabalho para guardar tamanho e bytes lidos
      int ntam = 0;
      int nLidos;

      // Strings para o processamento de comandos
      string sComando = "";
      string resposta = "";
      
     // Finaliza o trabalho de leitura
      nLidos = fluxo_rede.EndRead(ar);      

      if (nLidos > 0)
      {
        
        // Transforma o comando em string e mostra-o
        sComando = Encoding.UTF8.GetString(buffer, 0, nLidos);
        Ferramentas.mostrar_comando(sComando, this.ncliente);
      
        // Obtém a resposta correspondente ao comando
        resposta = Ferramentas.interpretar_cmd(sComando, this.ncliente);

        // Transforma a resposta em bytes para serem enviados
        byte[] msg_byte = Ferramentas.montarBytes(resposta);
        
        // Pega tamanho em bytes da string convertida
        ntam = msg_byte.Length;

        // Envia a resposta formatada em bytes
        fluxo_rede.BeginWrite(msg_byte, 0, ntam, avisoGravacaoCompleta, null);

      } // endif
      // Fecha a conexão se não tiver dados lidos
      else
      {      
        Console.WriteLine(" Conexão de leitura caiu");
        fluxo_rede.Close();
        tomada.Close();
        fluxo_rede = null;
        tomada = null;
      }// end else
    } //OnReadComplete().fim   
   
    // Depois de gravar a resposta continue lendo
    private void quandoGravacaoCompleta(IAsyncResult ar)
    {
      // Finaliza o gravação (envio) de dados no fluxo de rede
      fluxo_rede.EndWrite(ar);     

      // Recomece um processo de leitura
      fluxo_rede.BeginRead(buffer, 0, buffer.Length, avisoLeituraCompleta, null);
    }// quandoGracacaoCompleta().fim   
  
  } // fim da classe
} // fim do namespace
