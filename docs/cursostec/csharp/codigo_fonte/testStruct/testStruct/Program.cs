// Projeto testStruct
// Este programa testa struct
using System;


 namespace testStruct
 {    
    
    struct Monstro
    {
        public int energia;
        public int tipo;       
        
    } // fim da estrutura Monstro

    struct Ponto
    {
        public int x;
        public int y;

        public Ponto (int a, int b)
        {
            x = a;
            y = b;

        } // fim do construtor
    } // fim da estrutura Ponto 
    
    
    class Program
    {
        static void Main(string[] args)
        {

            Monstro vampiro;
            vampiro.energia = 100;
            vampiro.tipo = 2;
            Ponto pos_vampiro = new Ponto(320, 240);

            // Vamos configurar a janela de console
            Console.BackgroundColor = ConsoleColor.White;
            Console.ForegroundColor = ConsoleColor.Black;
            Console.Title = " Estrutura de dados";
            Console.Clear();

            // Vamos mostrar os dados...
            Console.WriteLine("\n Monstro.tipo: " + vampiro.tipo);
            Console.WriteLine(" Monstro.energia: " + vampiro.energia);
            Console.WriteLine(" pos_vampiro.x: " + pos_vampiro.x);
            Console.WriteLine(" pos_vampiro.y: " + pos_vampiro.y);
            Console.Read();

        } // main() fim
    } // fim da classe Programa
 } // fim do nameSpace
