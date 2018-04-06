// Projeto prj_Indexer - Arquivo: Time.cs (Time de futebol)
// Este programa mostra como elaborar indexer e iterador
using System;
using System.Collections.Generic;

namespace prj_Indexer
{
  public class Time: System.Collections.IEnumerable
  {
    // Uma array para estocar jogadores
    private Jogador[] lista_atleta;
    
    // Um jogador 'vazio' para evitar valores nulos na array
    static Jogador jg_nulo = new Jogador("vazio", 0);

    // O contador acompanha o crescimento da array e serve de índice
    // para controlar o posicionamento de entrada dos objetos na coleção.
    private int contador = 0;
    
    // Esse construtor define um time com qualquer quantidade
    // de jogadores
    public Time(int jogador_qtd)
    {
      contador = 0;

      // Alocamento do espaço para os jogadores
      lista_atleta = new Jogador[jogador_qtd];
            
      // Inicializa a lista de jogadores para evitar 
      // valores nulos na array
      for (int ncx = 0; ncx < jogador_qtd; ncx++)
      {
        lista_atleta[ncx] = jg_nulo;
      } // endfor    
    } // fim do construtor Time(jogador_qtd)

    
    // Esse construtor define um time a partir de uma array externa
    public Time(Jogador[] lista)
    {
      lista_atleta = new Jogador[lista.Length];

      for (int ncx = 0; ncx < lista.Length; ncx++)
      {
        lista_atleta[ncx] = lista[ncx];
      } //  endfor
    } // fim do construtor Time(Jogador[])


    // Adiciona um jogador na lista do time
    public void ColocarJogador(Jogador jg)
    {
      lista_atleta[contador] = jg;
      if (contador < lista_atleta.Length) contador++;
    } 

    // O indexer '[]' recupera um objeto jogador
    public Jogador this[int posicao]
    {
      // get() retorna um objeto jogador
      get { return lista_atleta[posicao]; }

      // set() recebe um objeto jogador e joga na posição dada
      set { lista_atleta[posicao] = value; }
    
    } // Indexer().fim


    // Este aqui é o iterador implementação da interface IEnumerable
    // que possui apenas a função GetEnumerator()
    public System.Collections.IEnumerator GetEnumerator()
    {
      return new Numerador(lista_atleta);
    } // GetEnumerator()
 
  } // fim da classe Time

  // A interface IEumerator determina a impplementação de
  // MoveNext(), Reset() e Current
  public class Numerador : System.Collections.IEnumerator
  {
    // Uma lista local para se referir a lista do time
    public Jogador[] lista_local;

    // Enumeradores devem apontar para antes do primeiro elemento 
    // até a primeira chamada de MoveNext()    
    int ndx = -1;

    // Contrutor da classe Numerador
    // Recebe uma lista externa e repassa a referência para a 
    // lista local.
    public Numerador(Jogador[] lista)
    {
      lista_local = lista;
    } // fim do contrutor Numerador(Jogador[])

    // Método MoveNext()
    public bool MoveNext()
    {
      ndx++;
      // Retorna verdadeiro enquanto o indíce é menor que o 
      // tamanho da lista de jogadores
      return (ndx < lista_local.Length);    
    } // MoveNext()

    // Resseta a posição do índice para antes do primeiro elemento
    public void Reset()
    {
      ndx = -1;
    } // Reset().fim

    // Current retorna o objeto apontado atualmente por ndx
    public object Current
    {
      get { return lista_local[ndx]; }
    } // Current.fim
  } // fim da classe Numerador
} // fim do namespace
