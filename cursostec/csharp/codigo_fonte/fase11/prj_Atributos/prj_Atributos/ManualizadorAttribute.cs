// Projeto prj_Atributos - Arquivo: ManualAttribute.cs
// Este programa mostra como elaborar e mostrar atributos
using System;
using System.Reflection;

namespace prj_Atributos
{
  // É necessário o atributo AttributeUsageAttribute para construir 
  // um atributo. É necessário herdar a classe base System.Attribute.
  [AttributeUsage (AttributeTargets.Class,AllowMultiple=true)]
  public class ManualizadorAttribute: System.Attribute  
  
  {
    // Campos do atributo
    public string elemento;
    public string elemento_descr;
    public string arquivo_ajuda;
    
    // Para teste de parâmetros nomeados
    public string Autor { get;  set; }

    // Construtor da classe
    public ManualizadorAttribute(string item, string descr, string arquivo)
    {
      this.elemento = item;
      this.elemento_descr = descr;
      this.arquivo_ajuda = arquivo;
    } // Fim do construtor

    // Exibe os dados do objeto corrente.
    public void mostrar()
    {
      string info;      
      info = string.Format(" {0}: {1} - Localização:{2}\n", 
        elemento, elemento_descr, arquivo_ajuda); 
      Console.Write(info);
    } // mostrar().fim
  } // fim da classe
} // fim do namespace
