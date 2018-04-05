// Projeto prj_Paralelo -  Arquivo: Disco.cs
// Este programa ilustra gravação e leitura de arquivos binários
// em paralelo
using System;
using System.IO;

// Vamos usar Enconding.ASCII.GetString() para converter uma
// array de bytes numa só string
using System.Text;

namespace prj_Paralelo
{
  class Disco
  {

    // O delegate que vai receber o método callback que avisa 
    // quando a operação de leitura ou gravação está completa.
    private AsyncCallback Mensageiro;
    
    // Objetos de trabalho
    private Stream arquivo;
    private Byte[] dados;
    
    // Construtor
    public Disco()
    {
      // Define dados como uma array de 10 bytes
      dados = new Byte[10];
    } // fim do construtor

    // gravar_dados() - Grava dados no arquivo delme.txt
    public void gravar_dados()
    {
      // Dados para serem gravados
      Byte[] lista = { 71, 97, 109, 101, 112, 114, 111, 103, 10, 13 };

      // Inicializa os dados a serem gravados
      for (int ncx = 0; ncx < lista.Length; ncx++)
        dados[ncx] = lista[ncx];

      // Abre o arquivo para gravação
      arquivo = File.OpenWrite("delme.txt");

      Mensageiro = new AsyncCallback(this.quandoGravacaoCompleta);

      // Iniciando o processo de gravar os dados
      arquivo.BeginWrite(dados, 0, dados.Length, Mensageiro, null);

    } // gravar_dados().fim

    // ler_dados() - Lê dados do arquivo delme.txt
    public void ler_dados()
    {
      // Passando o método-recado para o Mensageiro
      Mensageiro = new AsyncCallback(this.quandoLeituraCompleta);

      // Abre o arquivo para leitura
      arquivo = File.OpenRead("delme.txt");

      // Faz leitura dos dados
      arquivo.BeginRead(dados, 0, 10, Mensageiro, null);

    } // ler_dados().fim

    void quandoLeituraCompleta(IAsyncResult oResultadoParalelo)
    {

      int nlido_qtd = 0;

      // Finaliza a operação de leitura
      nlido_qtd = arquivo.EndRead(oResultadoParalelo);

      // Avisos
      Console.WriteLine("\n\t Quantidade de bytes lidos: {0}", nlido_qtd);
      Console.Write("\t Leitura de dados Ok: \n\t ");
      
      // Converte os bytes numa string
      String txt = Encoding.ASCII.GetString(dados);
      Console.WriteLine(txt);

      // fecha o arquivo
      arquivo.Close();

    } // quandoLeituraCompleta().fim

    void quandoGravacaoCompleta(IAsyncResult oResultadoParalelo)
    {
      // Fecha o processo de leitura paralela
      arquivo.EndWrite(oResultadoParalelo);
     
      if (oResultadoParalelo.IsCompleted == true)
        Console.WriteLine("\t Gravação Ok");

      arquivo.Close();

    } // quandoGravacaoCompleta().fim

  } // fim da classe
} // fim do namespace
