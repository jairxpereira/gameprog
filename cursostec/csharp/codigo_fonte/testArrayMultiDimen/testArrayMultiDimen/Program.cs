// Projeto testArrayMultiDimen
// Este programa testa array multidimensionais

using System;

namespace testArrayMultiDimen
{
    class Program
    {
        static void Main(string[] args)
        {
            config_janela();
            String[] listaMonstro = { "Vampiro  ", 
                                      "Lobisomem", 
                                      "Godzila  ", 
                                      "Ogro     " };

            // Primeira forma de declarar uma array bidimensional
            int[,] listaPosicao = 
            { {320,240,100}, {321, 241, 100},{322, 242, 100}, {323, 243, 103}};

            // Segunda forma de declarar uma array bidimensional
            int[,] OlhandoPara = new int [4,3] 
            { { 325, 245, 105 }, { 326, 246, 106 }, { 327, 247, 107 }, { 328, 248, 108 } };

            
            // Modificando o elemento[0] da array OlhandoPara...
            OlhandoPara[0, 0] = 329; OlhandoPara[0, 1] = 249; OlhandoPara[0, 2] = 109;            

            // Legenda
            Console.Write("\nMonstro \t  Pos          Olhando para a posição\n" +
                "=====================================================\n");

            // Exibe os dados das arrays
            for (int ncx = 0; ncx < 4; ncx++)
            {

             Console.Write("{0}",listaMonstro[ncx]);                
             
              Console.Write("\t({0},{1},{2})", 
               listaPosicao[ncx, 0], listaPosicao[ncx, 1], listaPosicao[ncx, 2]);
             
              Console.Write("\t({0},{1},{2})\n", 
                OlhandoPara[ncx, 0], OlhandoPara[ncx, 1], OlhandoPara[ncx, 2]);


            } // fim do for
     


            Console.Read();

        } // main() fim

        // Método para configurar a janel
        private static void config_janela()
        {
            // Vamos configurar a janela
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.BackgroundColor = ConsoleColor.White;
            Console.Title = " Testando array bidimensionais";
            Console.SetBufferSize(80, 30);
            Console.SetWindowSize(80, 30);
            Console.Clear();
        } // config_janela() fim    

    } // fim da classe Program
} // fim do namespace testArrayMultiDimen
