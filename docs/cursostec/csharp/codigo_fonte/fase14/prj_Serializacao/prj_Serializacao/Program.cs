// Projeto prj_Serializacao: arquivo: Program.cs
// Este programa testa gravação e leitura de arquivos
// pelo processo serialização e desserialização.
// Produzido por www.gameprog.com.br
using System;

namespace prj_Serializacao
{
  class Program
  {
    const int arquivo_gravar = 1;
    const int arquivo_ler = 2;
    const int nulo = 0;

    static void Main(string[] args)
    {
      config_janela("prj_Serializacao");

      // Cria um jogador para ser salvo 
      Jogador megaman = new Jogador("Megaman");
      megaman.vidas = 15; megaman.energia = 999;
      megaman.fase = 12; megaman.subfase = 4;
      megaman.mostrar();
           
      // Usuário seleciona gravar ou carregar 
      int escolha = 0;
      escolha = menu();

      Console.Write("\n");

      // Grave se o usuário escolheu gravar
      if (escolha == arquivo_gravar) 
        megaman.salvar("jogador.bin");

      // Carregue o arquivo se o jogador escolheu ler
      if (escolha == arquivo_ler)
      {
        
        // Cria um jogador
        Jogador mega = new Jogador("mega");
        
        // Mostra os valores iniciais
        mega.mostrar();
        
        // Carrega nova configuração do jogador do disco
        mega  = mega.carregar("jogador.bin");
        Console.WriteLine(" Dados atualizados do disco:");        
        mega.mostrar();
      } // endif

      Console.WriteLine("\n\t Pressione ENTER para encerrar!");    

      // Pausa para a leitura!
      Console.Read();

    } // main() fim


    // menu() - Apresenta um menu com duas opções
    private static int menu()
    {
      Console.WriteLine(" \n \t Menu - Arquivo: jogador.bin\n \t" + 
        "---------------------------------------\n");
      
      Console.WriteLine(" \t G- Gravar dados no arquivo \n");
      Console.WriteLine(" \t L- Ler dados do arquivo \n\n");
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


    // Método para configurar a janel
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
} // fim do namespace prj_Serializacao
