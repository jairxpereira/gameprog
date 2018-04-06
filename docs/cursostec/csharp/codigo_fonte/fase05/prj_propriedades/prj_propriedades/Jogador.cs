// projeto prj_propriedades - Arquivo: Jogador.cs
// Ilustra o uso de propriedades
using System;

namespace prj_propriedades
{
  public class Jogador
  {

    // Atributos comuns
    public string nome;
    public int idade;

    // Atributos particulares acessado via propriedades
    private int m_vidas;
    private int m_energia;

    // Construtor
    public Jogador(string snome, int nidade)
    {
      nome = snome;
      idade = nidade;
    } // fim do construtor


    // Propriedade Vidas acessa m_vidas
    public int  Vidas
    {
      get { return m_vidas; }
      set { m_vidas = value; }
    }
    
    // Propriedade Energia acessa m_energia
    public int Energia
    {
      set 
      { 
        if ( value <= 100) m_energia = value;

        if (value > 100)
        {
          m_energia = 99;
          Console.Write("\n Energia.set(value): valor não permitido!: ");
          Console.WriteLine(value.ToString());
               } // fim do if      
      } // fim do set
      
      
      get {
        if (m_energia < 10)
        {
          Console.Write("\n Energia.get(): energia < 10");
          Console.WriteLine("- Perto do Game Over!");
         } // fim do if
        return m_energia;
       } // fim do get   
    } // Energia.propriedade.fim
   
    
    public override string ToString()
    {
      string resultado = "";
      resultado = "status: ( nome:" + nome + ", ";
      resultado += "vidas:" + m_vidas.ToString() + ", ";
      resultado += "energia:" + m_energia.ToString() + " )";
         return resultado;
    } // toString().fim

    public void mostrar_status()
    {
      Console.WriteLine(" {0} ", this.ToString());
    } // mostrar_status().fim

  } // fim da classe
} // fim do namespace
