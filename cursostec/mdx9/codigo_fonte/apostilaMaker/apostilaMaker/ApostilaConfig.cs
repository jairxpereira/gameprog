using System;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Windows.Forms;


namespace apostilaMaker
{
  [Serializable]
  class ApostilaConfig
  {
    public string capitulo;
    public string topico;
    public string objetivo;
    public string prjExemplo;
    public string cursotec;    


    public void salvar( string arquivo_nome)
    {
      // Cria um arquivo
      FileStream arquivo = new FileStream(arquivo_nome, FileMode.Create);

      // Cria um formatador
      BinaryFormatter tipobin = new BinaryFormatter();

      // Grava o objeto no disco
      tipobin.Serialize(arquivo, this);

      // Verifica se o arquivo foi criado com sucesso
      if (File.Exists(arquivo_nome))

        MessageBox.Show("Arquivo salvo com sucesso!");

      else
        MessageBox.Show("Falha no processo de gravação!");

      arquivo.Close();
     
    }  // salvarConfig()


    public ApostilaConfig carregar(string arquivo_nome)
    {

      // Verifica se o arquivo existe...
      if (!File.Exists(arquivo_nome))       
      {
        MessageBox.Show("Arquivo não localizado","ApostilaConfig.Carregar()");
        return null;
      } // end else


      ApostilaConfig  obj_config;

      // Cria um arquivo
      FileStream arquivo = new FileStream(arquivo_nome, FileMode.Open);

      // Cria um formatador
      BinaryFormatter tipobin = new BinaryFormatter();

      // Carrega o objeto do arquivo. O cast é necessário.
      obj_config = (ApostilaConfig )tipobin.Deserialize(arquivo);

      arquivo.Close();

      return obj_config;

    } // carregar().fim


  } // fim da classe



}
