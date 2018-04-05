// prj_Mouse01 - Arquivo: Tela.cs
// Esse projeto mostra como usar o mouse via DirectInput
// Exemplo 01 - Produzido por www.gameprog.com.br
using System;
using System.Windows.Forms;

namespace prj_Mouse01
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

