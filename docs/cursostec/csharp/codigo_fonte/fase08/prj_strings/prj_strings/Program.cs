// Projeto prj_strings
// Este programa exemplifica a utilização da classe String

using System;

namespace prj_strings
{
  class Program
  {
    static void Main(string[] args)
    {

      config_janela("prj_strings");
          
      string scaminho = @"c:\windows";

      string texto_grande = @"
      --------------------------------------
      Produzido por Gameprog
      By Jair Pereira
      Brasil - 2013";

      int ntam = texto_grande.Length;
      Console.WriteLine("\n nome: {0} ", scaminho);
      Console.WriteLine(texto_grande);
      Console.WriteLine("\t texto_grande.Length: {0} ", ntam);


      pause();
      
      // Teste de acesso aos caracteres individuais
      show(" Testando o indexer [] ");
      string empresa = "Gameprog";
      ntam = empresa.Length;
      for (int ncx = 0; ncx < ntam; ncx++)
        Console.WriteLine(" empresa[{0}] = {1}", ncx, empresa[ncx]);

      pause();

      
      // Teste de comparação de strings
      show(" Testando compareTo()");
      string s1 = "Gameprog";
      string s2 = "gameprog";

      int sts = s1.CompareTo(s2);

      Console.WriteLine(" s1: {0} s2: {1}", s1, s2);
      if (sts == 0) show("As string são iguais (s1, s2)");
      else
        show(" As strings são diferentes");
      sts = string.Compare(s1, s2);
      if (sts == 0) show(" As string são iguais (s1, s2)");
      else
        show(" As strings são diferentes");
      pause();

      // Teste de concatenação de strings
      show(" Testando operator+=()");
      s1 = "Produzido por";
      s2 = " Studio Gameprog";
      // s1 = string.Concat(s1, s2);
      s1 += s2;            
      show(s1);
      pause();

      // Vamos testar copyTo()
      show(" Testando copyTo()");
      char[] snome = new char[20];
      s1 = "Gameprog";
      s1.CopyTo(4, snome, 0, 4);      
      show(s1);
      show("  s1.CopyTo(4, snome, 0, 4);");
      Console.WriteLine(snome);
      pause();

      // Vamos testar copy()
      show(" Testando string.Copy()");
      s1 = "Gameprog";
      show(s2);
      s2 = string.Copy(s1);      
      show("  s2 = string.Copy(s1)");
      show(s2);      
      s2 = "Programar é legal!";
      show(s2); show(s1);
      pause();

      // Testando =
      // As strings produzidas são independentes
      show (" Testando operator=()");
      string s3 = "s3";
      string s4 = "s4";
      show(s3); show(s4);
      s4 = s3;
      show(s3); show(s4);
      s4 = "s4 hackeada";
      show(s3); show(s4);
      pause();

      // Vamos testar empty()
      show("Vamos testar string.Empty");
      s1 = "";
      if (s1 == string.Empty) show("A string está vazia");      
      pause();

      // Vamos testar EndsWith() \ StartsWith()
      show(@"Vamos testar EndsWith()\StartsWith()");
      bool bSiteBrasileiro = false;
      bool bWeb = false;
      string site = "www.gameprog.com.br";
      bSiteBrasileiro = site.EndsWith(".br");
      bWeb = site.StartsWith("www");
      if (bSiteBrasileiro == true) show(" O site é brasileiro!");
      if (bWeb == true) show(" O protocolo de comunição é www");
      pause();


      // Vamos testar toUpper() \ toLower()
      show(@"Vamos testar toUpper()\ toLower()");
      s1 = "Gameprog";
      s1 = s1.ToUpper();
      show(s1);
      s1 = s1.ToLower();
      show(s1);
      pause();


      // Vamos testar Trim() \ TrimStart() \ TrimEnd()
      show(@"Vamos testar TrimStart() \ TrimEnd() \ Trim()");
      s1 = "     Gameprog  ";
      Console.WriteLine("{0} {1} string original",s1, s1.Length);
      show(s1);
      
      s1 = s1.TrimStart();
      Console.WriteLine("{0} {1} TrimStart()", s1, s1.Length);
      show(s1);
   
      s1 = s1.TrimEnd();
      Console.WriteLine("{0} {1} TrimEnd()", s1, s1.Length);
      show(s1);
      
      s1 = "     Gameprog ";
      Console.WriteLine("{0} {1} string original", s1, s1.Length);
      char[] letras = new char[] {' ', 'g', 'G' };
      s1 = s1.Trim( letras);      
      Console.WriteLine("{0} {1} Trim()", s1, s1.Length);
      show(s1);
      pause();


      // Vamos testar Substring()
      show("Vamos testar Substring()");
      s2 = "";  s1 = "Gameprog";
      show(s1);
      show("s2 = s1.Substring(4, 4);");
      s2 = s1.Substring(4, 4);      
      show(s2);
      pause();

      // Vamos testar Split()
      show("Vamos testar Split()");
      s1 = "user=robocop;pwd=1234;banco=teste.sql;";
      char[] separadores = new char[] { '=', ';' };

      string[] palavras = s1.Split(separadores);
      for (int ncx = 0; ncx < palavras.Length; ncx++)
        show(palavras[ncx]);
      pause();


      // Vamos testar Join()
      show("Vamos testar Join()");
      s1 = string.Join(";", palavras);
      show(s1);
      pause();

      // Vamos testar format()
      string nome = "Bill Gates";
      int idade = 65;
      decimal salario = 2100900.85M;

      show("Testando string.Format()");
      s1 = string.Format ("Nome: {0}, Idade: {1}, Salário: {2:C2}",
        nome, idade, salario);
    show (s1);
    pause();
 
      // Vamos testar Equals()
    show("Vamos testar Equals()");
    s1 = "Brasil";
    s2 = "Brasil";
    show(s1); show(s2);
    if (s1.Equals(s2)) show("As strings são iguais!  s1.Equals(s2)");
    if (s1 == s2 ) show("As strings são iguais! s1 == s2");
    if (string.Equals(s1, s2)) show("As strings são iguais! string.Equals(s1,s2)");
    pause();

     // Vamos testar Contains() \ IndexOf();
    show("Vamos testar Contains() \\ IndexOf()");
    s1 = "Gameprog";
    s2 = "prog";
    show(s1); show(s2);
    if (s1.Contains(s2)) show("A string s2 está contida em s1");
    int npos = s1.IndexOf(s2, 0);
    Console.WriteLine("na posição {0}", npos);
    pause();


    // Vamos testar Insert() \ Replace()
    s1 = "Gameprog".ToLower();
    show(s1);
    s2 = s1.Insert(0, "www.");
    show(s2);
    s2 = s2.Insert(s2.Length, ".com.br");
    show(s2);
    s2 = s2.Replace("gameprog", "nucleoararat");
    show(s2);

    // Vamos testar  PadLeft() \ PadRight()
    show(" Testando PadLeft() \\ PadRight()");
    s1 = "Gameprog";
    s1 = s1.PadLeft(20, '-');
    show(s1);
    s1 = s1.PadRight(40, '-');
    show(s1);
    pause();
    pause();

    } // main() fim

    // Método para configurar a janel
    private static void config_janela(string titulo)
    {
      // Vamos configurar a janela
      Console.ForegroundColor = ConsoleColor.Blue;
      Console.BackgroundColor = ConsoleColor.White;
      Console.Title = titulo;
      Console.SetBufferSize(80, 30);
      Console.SetWindowSize(80, 30);
      Console.Clear();
      Console.Write("\n");
    } // config_janela() fim    

    // Apresenta uma pausa para leitura da tela
    private static void pause()
    {
      Console.WriteLine("\n pause: pressione alguma tecla para continuar...");
      Console.ReadKey();
    } // pause()

    // Imprime um objeto na tela
    private static void show(object obj)
    {
      Console.WriteLine("{0} ", obj);

    } // show().fim



  } // fim da classe Program
} // fim do namespace prj_strings
