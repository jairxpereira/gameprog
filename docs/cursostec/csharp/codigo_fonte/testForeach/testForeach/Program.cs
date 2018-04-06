 // Projeto testForeach
 // Este programa testa a instrução foreach

 using System;

 namespace testForeach
 {
    class Program
    {
        static void Main(string[] args)
        {
            String[] listaCores = ConsoleColor.GetNames(typeof (ConsoleColor));
            config_janela();
            
            foreach (string cor in listaCores)
                Console.WriteLine(cor);

            Console.Read();
        
        } // main() fim

        // Método para configurar a janel
        private static void config_janela()
        {
            // Vamos configurar a janela
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.BackgroundColor = ConsoleColor.White;
            Console.Title = " Testando foreach";
            Console.SetBufferSize(80, 30);
            Console.SetWindowSize(80, 30);
            Console.Clear();
        } // config_janela() fim    

    } // fim da classe Program
 } // fim do namespace testForeach
