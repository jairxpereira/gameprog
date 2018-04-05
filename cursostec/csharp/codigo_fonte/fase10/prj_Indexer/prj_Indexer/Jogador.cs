// Projeto prj_Indexer - Arquivo: Jogador.cs
// Este programa mostra como elaborar indexer e iterador
using System;
using System.Collections.Generic;

namespace prj_Indexer
{
  public class Jogador
  {

    // Atributos públicos do jogador
    public string m_nome;     // nome do jogador
    public int m_idade;       // idade do jogador
    
    // Construtor da classe
    public Jogador(string nome, int idade)
    {
      this.m_nome = nome;
      this.m_idade = idade;
    } // fim do construtor

    // Exibe os dados básicos do jogador
    public void mostrar() 
    {
      Console.WriteLine(" Jogador: ({0},{1})", m_nome, m_idade);

    } // mostrar().fim
  } // fim da classe
} // fim do namespace
