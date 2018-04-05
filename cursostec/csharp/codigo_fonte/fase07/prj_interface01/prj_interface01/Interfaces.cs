// Projeto prj_interface -  Arquivo:Interfaces.cs
// Ilustra o uso de interfaces
using System;

namespace prj_interface
{
  interface IMonstro
  {

    // Interfaces não podem ter campos (atributos), apenas 
    // propriedades e métodos.

    // Todo monstro IMonstro tem que ter nome e fazer estrago!
    int Estrago   { get; set; } // capacidade de fazer estrago
    string Nome  { get; set; }  // nome do objeto   
    
    // atacar()
    void atacar();
  } // fim da classe


  interface IPosition
  {
    // Controle de posição do objeto
    int X { get; set; }
    int Y { get; set; }
    
    void showpos();     // Mostrar posição do objeto
  
  } // fim da interface
} // fim do namespace

