using System;

namespace prjVariaveis
{
    class Program
    {

        static void Main(string[] args)
        {
            
            // Definição de variáveis
            String fase_nome = "Boss Final";
            int nPontos = 100;
            float xpos = 320.2f;
            double pi = 3.1415;
            
            bool lGameOver = false;
            System.Boolean lFinalLocalizado = true;

            // Vamos configurar a janela de console
            Console.BackgroundColor = ConsoleColor.White;
            Console.ForegroundColor = ConsoleColor.Black;
            Console.Title = "Estrutura de decisão 02: switch";
            Console.Clear();

            
            // Vamos exibir as variáveis
            Console.WriteLine("\n");
            Console.WriteLine(" Nome da fase: " + fase_nome);
            Console.WriteLine(" Posição do jogador: " + xpos);
            Console.WriteLine(" PI: " + pi);
            Console.WriteLine(" O jogo acabou?: " + lGameOver);
            Console.WriteLine(" O final da fase foi localizado?: " + lFinalLocalizado);
            Console.WriteLine(" Pontos: " + nPontos);
            
            // Pressione ''enter'' para continuar
            Console.Read();

        }// main() fim        

    } // fim da classe Program

} // fim do namespace
