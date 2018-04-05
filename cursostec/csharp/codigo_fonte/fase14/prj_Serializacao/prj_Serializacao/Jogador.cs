// Projeto prj_Serializacao: arquivo: Jogador.cs
// Este programa testa gravação e leitura de arquivos
// pelo processo serialização e desserialização.
// Produzido por www.gameprog.com.br
using System;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

namespace prj_Serializacao
{
  // A classe precisa ser assinalada como serializável
  [Serializable]
  class Jogador
  {
    
    // Dados do jogador
    public string jogador_nome;
    public int energia;
    public int vidas;
    public int fase;
    public int subfase;

    // Construtor
    public Jogador(string nome)
    {
      jogador_nome = nome;
      energia = 100;
      vidas = 7;
      fase = 19;
      subfase = 3;

    } // fim do construtor

    // Exibe os dados do jogador
    public void mostrar()
    {
      Console.WriteLine("\n Jogador: {0}", jogador_nome);
      Console.Write(" Energia: {0} \t", energia);
      Console.Write(" Vidas: {0} \t\n", vidas);
      Console.Write(" Fase: {0} \t", fase);
      Console.Write(" Subfase: {0}\n", subfase);
    } // mostrar().fim

    
    // Grava os dados de configuração
    public void salvar(string arquivo_nome)
    {
      // Cria um arquivo
      FileStream arquivo = new FileStream(arquivo_nome, FileMode.Create);
      
      // Cria um formatador
      BinaryFormatter tipobin = new BinaryFormatter();       

      // Grava o objeto no disco
      tipobin.Serialize(arquivo, this);

      // Verifica se o arquivo foi criado com sucesso
      if (File.Exists(arquivo_nome))
        Console.WriteLine(" Arquivo salvo com sucesso!");
      else
        Console.WriteLine(" Falha no processo de gravação.");      
    } // salvar().fim

    public Jogador carregar(string arquivo_nome)
    {

      // Verifica se o arquivo existe...
      if (File.Exists(arquivo_nome))
        Console.WriteLine(" Ok arquivo localizado....");
      else
      {
        Console.WriteLine(" Arquivo não localizado");
        return null;

      } // end else
      
      
      Jogador obj_config;

      // Abre o arquivo
      FileStream arquivo = new FileStream(arquivo_nome, FileMode.Open);
      
      // Cria o formatador
      BinaryFormatter tipobin = new BinaryFormatter();     

      // Carrega o objeto do arquivo. O cast é necessário.
      obj_config = (Jogador) tipobin.Deserialize(arquivo);    

      return obj_config;           

    } // carregar().fim

  } // fim da classe
} // fim do namespace
