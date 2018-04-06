// Prj_Lab01 - Arquivo: Program.cs
// Esse projeto permite acompanhar visualmente a manipulação dos
// argumentos das matrizes de projeção, visualização e espaço mundial
// Produzido por www.gameprog.com.br
using System;
using System.Windows.Forms;

namespace prj_Lab01
{
  static class Program
  {

    static void Main()
    {
      using (Janela tela = new Janela())
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

