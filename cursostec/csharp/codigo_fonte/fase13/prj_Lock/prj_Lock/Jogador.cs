// Projeto prj_Lock - Arquivo: Jogador.cs
// Este programa mostra o uso de Lock no ambiente de threads
using System;
using System.Threading;

namespace prj_Lock
{
  class Jogador
  {
    private int energia;

    public Jogador()
    {
      this.energia = 0;
    } // fim do construtor
  
    // Aumenta o valor de energia
    public void subindo01()
    {
      
      try
      {
        while (energia < 10)
        {
          lock (this)
          {

            energia++;
            mostrar(" subindo01():");
          } // endlock

          Thread.Sleep(0);
        } // endwhile
      } // endtry

      catch (ThreadAbortException)
      {
        Console.WriteLine(" {0} finalizado antes do final! ", 
          Thread.CurrentThread.Name);
        Console.WriteLine(" Ambiente foi limpo!");
      } // endcatch
    } //subindo01().fim


    // Aumenta o valor de energia
    public void subindo02()
    {
      
      try
      {

        while (energia < 10)
        {
          lock (this)
          {
            energia++;
            mostrar(" subindo02():");
          } // endlock          
          
          Thread.Sleep(0);

        } // endwhile
      } // endtry

      catch (ThreadAbortException)
      {
        Console.WriteLine(" {0} finalizado antes do final! ", 
          Thread.CurrentThread.Name);
        Console.WriteLine(" Ambiente foi limpo!");
      } // endcatch

    } // subindo02()   


    // Mostra um texto e a variável temp
    public void mostrar(string txt)
    {
      Console.Write("{0} {1} \n", txt, energia);
    } // mostrar()

  } // fim da classe

} // fim do namespace
