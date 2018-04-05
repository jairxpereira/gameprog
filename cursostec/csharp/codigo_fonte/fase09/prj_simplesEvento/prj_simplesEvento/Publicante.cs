// Projeto prj_simplesEvento; Aruivo Publicante.cs
// Este programa ilustra o uso de eventos
using System;

// Assinatura das funções tratadoras dos eventos
delegate void aoSair_Manipulador();
delegate void noClick_Manipulador();

namespace prj_simplesEvento
{
  class Publicante
  {
    // Declaração de dois eventos
    static event aoSair_Manipulador naSaida;
    static event noClick_Manipulador noClick;

    // Executa os eventos aoSair()
    static void tratarEventos_aoSair()
    {
      if (naSaida != null) naSaida();
      show(" \n Fim do programa. Pressione enter para continuar");
      pause(); pause();
      
      // Entregando o controle ao sistema operacional
      Environment.Exit(1);

    } // tratarEventos_aoSair().fim

    
    // Executa os eventos noClick()
    static void tratarEventos_noClick()
    {
      if (noClick != null) noClick();
    } // tratarEventos_noClick().fim

    
    // Função principal
    static void Main(string[] args)
    {
      // Vamos criar um assinante dos eventos
      Assinante sistema = new Assinante();
     
      // Vamos conectar as funções do assinante aos eventos
      naSaida += new aoSair_Manipulador(sistema.limpeza);      
      noClick += new noClick_Manipulador(sistema.mostrarMensagem);

      // Configurando um tratamento rápido de evento
      noClick += delegate(){
      show (" Resposta rápida ao evento noClick()!");
      };    

     
      mostrar_menu:
      config_janela("prj_simplesEvento");
      show("\n [MENSAGEM] [SAIR] \n");
      show(" 1- Clicar no botão MENSAGEM");
      show(" 2- Clicar no botão SAIR \n\n");
      show(" Digite sua opção: ");

      // Os eventos são produzidos externamente pelo usuário
      const int tecla_1 = 49;
      const int tecla_2 = 50;            
      int ntecla = Console.Read();        
      
     // Vamos despachar os eventos para o lugar certo
      switch (ntecla)
      {
        case tecla_1:
          tratarEventos_noClick();
          pause();
         break;

        case tecla_2:
          tratarEventos_aoSair();
          pause();
        break;      
      } // endswitch

      pause();
      if (ntecla != tecla_2) goto mostrar_menu;
      
      pause();

    } // Main().fim


    // Pausa para a leitura da tela
    private static void pause()
    {
      Console.ReadLine();
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
    } // config_janela() fim  
  

    // Mostra uma mensagem na tela
    private static void show( string txt)
    {
      Console.WriteLine( "{0} ", txt);
    } // show().fim

  } // fim da classe Program
} // fim do namespace prj_simplesEvento
