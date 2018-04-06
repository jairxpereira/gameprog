// prj_Superficie - Arquivo: Program.cs
// Esse projeto mostra como renderizar na textura, salvar uma
// imagem da tela e configurar a função callback de reconfiguração
// do dispositivo.
// Produzido por www.gameprog.com.br
using System;
using System.Windows.Forms;

namespace prj_Superficie
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

