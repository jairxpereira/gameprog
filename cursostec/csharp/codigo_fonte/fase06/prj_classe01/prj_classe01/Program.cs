// Projeto prj_classe01: Arquivo:Program.cs
// Ilustra a construção de uma classe simples
using System;

namespace prj_classe01
{
  class Program
  {
    static void Main(string[] args)
    {
      config_janela("projeto prg_classe01");

      int energia, estrago;

      // Criando um objeto da classe monstro
      Monstro godzila = new Monstro();
      
      // Obtendo valores das propriedades do objeto monstro
      energia = godzila.m_energia;
      estrago = godzila.m_estrago;
      Console.WriteLine ( "\n m_energia: {0} " , energia);
      Console.WriteLine ( " m_estrago: {0} \n",  estrago );

      // Vamos atacar
      godzila.atacar();

      // Reconfigurando e mostrando as propriedades
      godzila.m_energia = 99;
      godzila.m_estrago = 999;
      Console.WriteLine ( " m_energia: {0}" , godzila.m_energia );
      Console.WriteLine ( " m_estrago: {0} \n" , godzila.m_estrago );

      godzila.atacar();
      Console.ReadKey();

    } // Main().fim

    // Método para configurar a janela
    static void config_janela(String titulo)
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = titulo;
      Console.SetBufferSize(80, 30);
      Console.SetWindowSize(80, 30);
      Console.Clear();
    } // config_janela() fim
  } // fim da classe
} // fim do namespace
