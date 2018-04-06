using System;

namespace prj_Exception02
{
  class HackeadoException: System.Exception
  {
    public HackeadoException() : base("Os campos do objeto foram hackeados!") 
    { } // fim do primeiro construtor

    public HackeadoException(string mensagem): base(mensagem)
    { } // fim do segundo construtor
  } // fim da classe
} // fim do namespace
