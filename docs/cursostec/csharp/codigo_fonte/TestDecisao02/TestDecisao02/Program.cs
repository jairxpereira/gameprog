// Projeto: TestDecisao02
// Testando a estrutura de decisão com o switch
using System;

namespace TestDecisao
{
    class Program
    {
        static void Main(string[] args)
        {

            int nfinal;
            // Vamos configurar a janela de console
            Console.BackgroundColor = ConsoleColor.White;
            Console.ForegroundColor = ConsoleColor.Black;
            Console.Title = " Estrutura de decisão 02: switch";
            Console.Clear();


            for (nfinal = 0; nfinal < 5; nfinal++ )
            {

                switch (nfinal)
                {
                    case 1:
                        Console.WriteLine(nfinal + "::Mostrar video Final ruim");
                        break;

                   case 2:
                        Console.WriteLine(nfinal + "::Mostrar video Final médio");
                        break;
                       

                    case 3:
                        Console.WriteLine(nfinal + "::Mostrar video Final ótimo");
                        break;

                    default:
                        Console.WriteLine(nfinal + "::congratulations!");
                        break;
                } // fim do switch
            } // fim do for

            Console.Read();

        } // main() fim
    } // fim da classe
} // fim do nameSpace

