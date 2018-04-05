// Projeto testArray
// Este programa testa arrays

using System;

namespace testArray
{
    class Program
    {
        static void Main(string[] args)
        {

            config_janela();

            String[] listaMonstro = { "Vampiro", "Lobisomem", "Godzila", "Ogro    " };

            // Primeira forma de declarar arrays: declarando quantidade de itens
            int[] nSaudePonto = new int[4];
            nSaudePonto[0] = 15; nSaudePonto[1] = 16;               
            
            // Segunda forma: assinalando valores aos elementos
            int[] nMonstroQtd = { 10, 20, 30, 40 };

            // Terceira forma
            int[] nEnergiaMonstro = new int[] { 66, 77, 88, 99 };            

            // Legenda
            Console.Write("\nMonstro \tQtd \tEnergia\n" +
                "===================================\n");
            
            // Exibe os dados das arrays
            for (int ncx = 0; ncx < 4; ncx++)           
                Console.Write("{0} \t{1} \t{2}\n",
                    listaMonstro[ncx], nMonstroQtd[ncx], nEnergiaMonstro[ncx]);
     
            // Pausa para visualizar os dados
            Console.Read();

        } // main() fim

        // Método para configurar a janel
        private static void config_janela()
        {
            // Vamos configurar a janela
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.BackgroundColor = ConsoleColor.White;
            Console.Title = " Testando arrays";
            Console.SetBufferSize(80, 30);
            Console.SetWindowSize(80, 30);
            Console.Clear();
        } // config_janela() fim    

    } // fim da classe Program
} // fim do namespace testArray
