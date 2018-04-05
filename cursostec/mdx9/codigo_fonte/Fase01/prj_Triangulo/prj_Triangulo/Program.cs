// Prj_Triangulo - Arquivo: Program.cs
// Esse projeto ilustra como renderizar um triângulo
// Produzido por www.gameprog.com.br
using System;
using System.Windows.Forms;

namespace prj_Triangulo
{
  static class Program
  {

    static void Main()
    {
      using (Tela tela = new Tela())
      {
        // Mostre a tela
        tela.Show();

        // Inicialize o dispositivo gráfico
        tela.initGfx();

        // Rode a aplicação adequadamente
        Application.Run(tela);

      } // end using 
    } // Main().fim
  } // fim da classe
} // fim do namespace

