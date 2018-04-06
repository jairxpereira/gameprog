 // Projeto testMainArgs
 // Testando o acesso aos argumentos da linha de comando

 using System;

 namespace testMainArgs
 {
    class Program
    {
        static void Main(string[] args)
        {

            config_janela();

            int ntam = args.Length;
            int ncx = 0;

            for (ncx = 0; ncx < ntam; ncx++)
            {
            
                // Mostra os argumentos da linha de comando
                Console.WriteLine(args[ncx]);

                // Reage de acordo com o argumento digitado
                if (args[ncx] == "\\debug")
                     Console.WriteLine(" Operando em modo debug!\n");

                if (args[ncx] == "energia:1000")
                Console.WriteLine(" Agora vc tem muita energia extra!");

            } // fim do for

            Console.Read();

        } // main() fim

        // Método para configurar a janel
        private static void config_janela()
        {
            // Vamos configurar a janela
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.BackgroundColor = ConsoleColor.White;
            Console.Title = " Testando acesso de argumentos da linha de comando";
            Console.SetBufferSize(80, 30);
            Console.SetWindowSize(80, 30);
            Console.Clear();
        } // config_janela() fim    

    } // fim da classe Program
} // fim do namespace testMainArgs
