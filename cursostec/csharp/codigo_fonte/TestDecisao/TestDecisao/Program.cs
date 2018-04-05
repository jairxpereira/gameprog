// Projeto: TestDecisao01
// Testando a estrutura de decisão com o if
using System;

namespace TestDecisao
{
    class Program
    {
        static void Main(string[] args)
        {
            int nvidas = 0;
            int nEnergia = 10;
            int npontos = 15000;
            bool lKitMedicoEncontrado = true;

            // Vamos configurar a janela de console
            Console.BackgroundColor = ConsoleColor.White;
            Console.ForegroundColor = ConsoleColor.Black;
            Console.Title = "Estrutura de decisão 01: if";
            Console.Clear();

            if (lKitMedicoEncontrado) nEnergia = nEnergia + 30;  
            Console.WriteLine("\n Nível de energia: " + nEnergia );
            
            if (nEnergia <= 40) Console.WriteLine(" Sua energia está baixa!");

            if (npontos > 10000)
            {
                nvidas = nvidas + 1;
                Console.WriteLine(" Vc ganhou uma vida extra!");
            } // fim do if

            Console.Read();

        } // main() fim
    } // fim da classe
} // fim do nameSpace

