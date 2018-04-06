using System;


namespace TesteFor
{
    class Program
    {
        static void Main(string[] args)
        {
            int ncx;

            // Configuração da janela
            Console.BackgroundColor = ConsoleColor.White;
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.Clear();
            Console.Title = "Teste do for/while";


            // Teste do for
            Console.WriteLine("\n\n Teste do for");
            for (ncx = 0; ncx < 5; ncx++)
            {
                Console.WriteLine(" ncx: " + ncx);
            } // fim do for
         
           
            // Teste do while
            Console.WriteLine("\n\n Teste do while");
            ncx = 100;
            while (ncx >= 95)
            {
                Console.WriteLine(" ncx: " + ncx);
                ncx = ncx - 1;
            } // fim do while

            Console.Read();
        
        } // main() fim
    } // fim da classe
} // fim do namespace
