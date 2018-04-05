// Prj_Janela - Arquivo: Program.cs
// Esse projeto ilustra como inicializar o motor gráfico do DirectX 9
// Produzido por www.gameprog.com.br
using System;
using System.Windows.Forms;

namespace prj_IndexBuffer
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

