// Projeto testEnum
// Este programa testa enum 
using System;


 namespace testEnum
 {

    public enum NivelDificuldade
    {
        Facil,
        Medio,
        Dificil,
        Expert
 
    } // fim da enumeração NivelDificuldade

    public enum Personagem
    {
        Arqueiro = 1,
        Guerreiro,
        Feiticeiro,
        Cavaleiro,
        Mago

    } // fim da enumeração Personagem



    class Program
    {
        static void Main()
        {

            String sNivel = " Escolha o nível de dificuldade do jogo:";
            String sPersonagem = " Escolha seu personagem:";
            
            String[] listaPersonagem = Personagem.GetNames(typeof(Personagem));
            String[] listaDificuldade = NivelDificuldade.GetNames(typeof(NivelDificuldade));
            int ndificuldade = (int) NivelDificuldade.Expert ;
            int npersonagem = (int) Personagem.Mago;

            config_janela();

            // Mostra a lista de níveis de dificuldade
            Console.WriteLine("\n" + sNivel);            

            for (int ncx = 0; ncx < listaDificuldade.Length; ncx++)
                Console.WriteLine(" {0}- {1} ", ncx, listaDificuldade[ncx]);

            Console.WriteLine(" >> " + ndificuldade);            
            
            
            // Mostra a lista de personagens
            Console.WriteLine("\n" + sPersonagem);
          
            for (int ncx = 0; ncx < listaPersonagem.Length; ncx++)
                Console.WriteLine(" {0}- {1} ", ncx+1,listaPersonagem[ncx]);
            Console.WriteLine(" >> " + npersonagem);            
            
            
            // Obtendo o valor inteiro pela string
            int nMago =  (int)Enum.Parse(typeof(Personagem), "Mago");
            Console.WriteLine("\n Código numérico do Mago: " + nMago);
          
            // Vamos esperar a leitura da tela
            Console.Read(); 

        } // main() fim

        
        // Método para configurar a janel
        private static void config_janela()
        {
            // Vamos configurar a janela
            Console.ForegroundColor = ConsoleColor.Blue;
            Console.BackgroundColor = ConsoleColor.White;
            Console.Title = " Testando enum";           
            Console.SetBufferSize(80, 30);
            Console.SetWindowSize(80, 30);
            Console.Clear();
        } // config_janela() fim       

    } // fim da classe Program
} // fim do namespace testEnum
