// Projeto prj_Texto -  Arquivo: Programa.cs
// Este programa ilustra gravação e leitura de arquivos textos
using System;
using System.IO;

namespace prj_Texto
{
  class Program
  {

    const int arquivo_gravar = 1;
    const int arquivo_ler = 2;
    const int nulo = 0;

    static void Main(string[] args)
    {

      config_janela("prj_Texto");

      int escolha = 0;

      escolha = menu();

      Console.Write("\n");

      if (escolha == arquivo_gravar) gravar_dados();

      if (escolha == arquivo_ler) ler_dados();

      Console.WriteLine("\n\t Pressione ENTER para encerrar!");

      Console.Read();

    } // main() fim

    // gravar_dados() - Grava dados no arquivo texto.txt
    private static void gravar_dados()
    {
      // Dados para serem gravados
      string jogo = "Megaman";
      int idade = 26;      
     
      // Abre o arquivo para gravação
      StreamWriter txt_fluxo = new StreamWriter("texto.txt", false);
      
      // Gravando os dados...
      txt_fluxo.WriteLine("Jogo: {0}     Idade: {1}", jogo, idade);
      txt_fluxo.WriteLine("Jogo: Castlevania Idade: 27");      

      // Fechando o arquivo
      txt_fluxo.Close();

      Console.WriteLine(" \t Gravação de dados Ok");
    } // gravar_dados().fim


    // ler_dados() - Lê dados do arquivo texto.txt
    private static void ler_dados()
    {
      // Buffer de memória para receber os dados
      string linha = null;

      // Acessa o arquivo texto
      FileInfo arquivo = new FileInfo("texto.txt");

      // Abre o arquivo para leitura
      StreamReader txt_fluxo = arquivo.OpenText();
      
      // Faz leitura dos dados
      Console.WriteLine("\n\t Leitura ok: ");
      do
      {
        linha = txt_fluxo.ReadLine();
        Console.WriteLine("\t {0}", linha);

      } while (linha != null);
      
      // Fecha o arquivo
      txt_fluxo.Close();      

    } // ler_dados().fim


    // menu() - Apresenta um menu com duas opções
    private static int menu()
    {
      Console.WriteLine(" \t \t Menu \n \t -------------------------\n");
      Console.WriteLine(" \t G- Gravar dados no arquivo texto.txt \n\n");
      Console.WriteLine(" \t L- Ler dados do arquivo texto.txt \n\n");
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
} // fim do namespace prj_Texto