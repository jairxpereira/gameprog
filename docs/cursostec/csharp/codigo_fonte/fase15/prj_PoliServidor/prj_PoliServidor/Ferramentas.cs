// Projeto prj_PoliServidor - Arquivo: Ferramentas.cs
// Este programa testa comunicação assíncrona de dados e 
// múltiplas conexões clientes
using System;
using System.Text;

namespace prj_PoliServidor
{
  static class Ferramentas
  {

    // Transforma texto em uma array de bytes
    public static byte[] montarBytes(string texto)
    {
      // Variáveis para o trabalho de conversão
      char[] txt_char;    // string para char[]
      byte[] txt_byte;    // char[] para byte[]
      txt_char = texto.ToCharArray();
      txt_byte = Encoding.UTF8.GetBytes(txt_char);
      return txt_byte;
    } // montarBytes().fim

    // Mostra o comando que chegou do cliente
    public static void mostrar_comando(string sComando, int ncliente)
    {
      sComando = sComando.Trim();
      Console.WriteLine(" Cliente: #{0} \t Comando: {1}",
        ncliente, sComando);
    } // mostrar_comando().fim

    // Interpreta os comandos vindo do cliente
    public static string interpretar_cmd(string comando, int nId)
    {

      // Resposta padrão para comandos não identificados
      string resposta = "Comando não encontrado!";
      int ncomando = 0;

      // Limpeza das strings 
      comando = comando.Trim();
      string brancos = "             ";

      // Faz a interpretação dos comandos
      if (comando.Equals("windir")) ncomando = 1;
      if (comando.Equals("olá")) ncomando = 2;
      if (comando.Equals("ola")) ncomando = 2;
      if (comando.Equals("parar")) ncomando = 3;

      // Prepara uma resposta conforme a interpretação realizada
      switch (ncomando)
      {
        case 1:
          // Pega o diretório aonde está instalado o sistema
          resposta = Environment.GetEnvironmentVariable("SystemRoot") + brancos;
          break;
        case 2:
          // Os espaços limpam o buffer anterior
          resposta = "Olá usuário #" + nId + brancos;
          break;
        case 3:
          resposta = "Até logo, usuário #" + nId + brancos;
          break;
      }// endswitch  

      return resposta;
    } // interpretar_cmd().fim
  } // fim da classe
} // fim do namespace
