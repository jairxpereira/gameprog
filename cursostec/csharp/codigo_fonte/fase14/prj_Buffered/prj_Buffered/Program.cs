// Projeto prj_Buffered -  Arquivo: Programa.cs
// Este programa ilustra gravação e leitura de arquivos binários
// com buffer de suporte para melhor performance.
using System;
using System.IO;

namespace prj_Buffered
{
  class Program
  {

    const int arquivo_gravar = 1;
    const int arquivo_ler = 2;
    const int nulo = 0;

    static void Main(string[] args)
    {

      config_janela("prj_Buffered");

      int escolha = 0;

      escolha = menu();

      Console.Write("\n");

      if (escolha == arquivo_gravar) gravar_dados();

      if (escolha == arquivo_ler) ler_dados();

      Console.WriteLine("\n\t Pressione ENTER para encerrar!");

      Console.Read();

    } // main() fim

    // gravar_dados() - Grava dados no arquivo delme.txt
    private static void gravar_dados()
    {
      // Dados para serem gravados
      Byte[] dados = { 71, 97, 109, 101, 112, 114, 111, 103, 10, 13 };

      // Abre o arquivo para gravação
      Stream arquivo = File.OpenWrite("delme.txt");

      // Acrescenta uma camada de memória extra
      BufferedStream mem_arquivo = new BufferedStream(arquivo);
      
      // Gravando os dados...
      mem_arquivo.Write(dados, 0, dados.Length);      

      // Garantindo a gravação dos dados
      mem_arquivo.Flush();

      // Fechando o arquivo
      mem_arquivo.Close();  

      Console.WriteLine(" \t Gravação de dados Ok");
    } // gravar_dados().fim


    // ler_dados() - Lê dados do arquivo delme.txt
    private static void ler_dados()
    {
      // Buffer de memória da aplicação para receber os dados
      Byte[] dados = new Byte[10];

      // Abre o arquivo para leitura
      Stream arquivo = File.OpenRead("delme.txt");

      // Acrescenta uma camada de memória extra
      BufferedStream mem_arquivo = new BufferedStream(arquivo);

      // Recupera os dados via leitura bufferizada     
      mem_arquivo.Read(dados, 0, dados.Length);

      // Mostra os bytes na Tela
      Console.Write("\n\n\t Leitura de dados Ok: \n\t");
      foreach (Byte dado in dados)
      {
        Console.Write(" {0}, ", dado);
      }
      Console.Write("\n");

      // Fecha o arquivo
      mem_arquivo.Close();

    } // ler_dados().fim


    // menu() - Apresenta um menu com duas opções
    private static int menu()
    {
      Console.WriteLine(" \t \t Menu \n \t -------------------------\n");
      Console.WriteLine(" \t G- Gravar dados no arquivo delme.txt \n\n");
      Console.WriteLine(" \t L- Ler dados do arquivo delme.txt \n\n");
      Console.Write("\t Escolha sua opção (G, L): ");

      ConsoleKeyInfo tecla;
      tecla = (ConsoleKeyInfo)Console.ReadKey();

      if (tecla.Key == ConsoleKey.G)
      {
        // A linha Main() trava e aguarda o final do processamento das linhas.
        return arquivo_gravar;
      } // endif

      if (tecla.Key == ConsoleKey.L)
      {
        return arquivo_ler;
      } // endif

      return nulo;

    } // menu().fim


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
} // fim do namespace prj_Buffered
