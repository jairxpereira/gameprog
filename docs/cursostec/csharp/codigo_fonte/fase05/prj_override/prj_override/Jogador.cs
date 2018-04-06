// projeto prj_override - Arquivo: Jogador.cs
// Ilustra o uso de override para re-implementar toString()
using System;

namespace prj_override
{
  class Jogador
  {

    public string nome;
    public int idade;
    
    public Jogador( string snome, int nidade)
    {
      nome = snome;
      idade = nidade;
    } // fim do construtor

    public override string ToString()
    {
      string valor_antigo = "";
      string dados_novos = "";
      string resultado = "";
      
      valor_antigo = base.ToString();
      dados_novos = "." + nome + "." + idade.ToString();
      resultado =  valor_antigo + dados_novos;      
      
      return resultado;
           
    } // toString().fim
  } // fim da classe
} // fim do namespace
