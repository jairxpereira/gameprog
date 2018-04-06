// Projeto prj_Indexer - Arquivo: Program.cs
// Este programa mostra como elaborar indexer e iterador
using System;

namespace prj_Indexer
{
  class Program
  {
    static void Main(string[] args)
    {     

      // Configuração da janela de trabalho
      config_janela("prj_Indexer");
      
      // Vamos construir o elenco do time do Barcelona
      Jogador[] atletas = new Jogador[3]
        {
            new Jogador("Neimar", 23),
            new Jogador("Messi", 40),
            new Jogador("Ronaldo", 38),
        };

      // Constrói o Barcelona com o elenco acima
      Time barcelona = new Time(atletas);
      
      // Mostra o elenco do time Barcelona
      Console.WriteLine("\n\n -------- Barcelona ---- ");
       foreach (Jogador jg in barcelona)jg.mostrar();

      // Vamos construir e mostrar o time do Palmeiras
      Time Palmeiras = new Time(4);
      Jogador marcos = new Jogador("Marcos",45);
      Jogador edmundo = new Jogador("Edmundo",46);
      Jogador mazinho = new Jogador("Mazinho",48);

      Palmeiras.ColocarJogador(marcos);
      Palmeiras.ColocarJogador(edmundo);
      Palmeiras.ColocarJogador(mazinho);
      Console.WriteLine("\n\n -------- Palmeiras ---- ");
      foreach (Jogador jg in Palmeiras) jg.mostrar();

      // Utilizando o indexer para recuperar e reconfigurar um objeto 
      Jogador quarto = Palmeiras[3];
      quarto.m_nome = " * Jair Pereira";
      quarto.m_idade = 42;
      Palmeiras[3] = quarto;
      
      // Utilizando o indexer para mudar o nome do segundo jogador
      Palmeiras[1].m_nome = " * Romario";      
      Console.WriteLine("\n\n *** Alterado via indexer (Palmeiras) ***");
      foreach (Jogador jg in Palmeiras) jg.mostrar();
    
      // Pausa para a leitura    
      Console.Read();

    } // main() fim

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
    } // config_janela() fim    

  } // fim da classe Program
} // fim do namespace prj_Indexer
