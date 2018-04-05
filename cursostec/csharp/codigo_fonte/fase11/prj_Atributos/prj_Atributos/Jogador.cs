// Projeto prj_Atributos - Arquivo: Jogador.cs
// Este programa mostra como elaborar e mostrar atributos
using System;
using System.Reflection;

namespace prj_Atributos
{
  // Os atributos devem preceder o item que qualificam
  [Manualizador("Jogador()", "classe", "track11-1.html", 
    Autor="Produzido por Gameprog")]

  [Manualizador("m_nome   ", "nome do jogador", "#track11")]
  [ManualizadorAttribute("m_idade  ", "idade do jogador", "tópico 1")]  
  class Jogador
  {
    
    // Campos do objeto
    private string m_nome;  
    private int m_idade;

    // Construtor da classe
    public Jogador(string nome, int idade)
    {
      m_nome = nome;
      m_idade = idade;

    } // fim do construtor

    // Exibe dados do jogador
    public void mostrar()
    {
      string info;
      info = string.Format(" Jogador ({0},{1}) \n", m_nome, m_idade);
      Console.Write(info);
    } // mostrar().fim
  } // fim da classe
} // fim do namespace
