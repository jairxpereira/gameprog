// autoreparo.cpp
// Este programa ilustra tratamento de erro
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

// ------------------ classe Autoreparo -----------------------------------------
class Autoreparo { 
public: 

Autoreparo (string sErro): m_msgErro(sErro) {}

// metodo informarErro()
void informarErro()
{
cout << m_msgErro << endl; 
} 

private: 
string m_msgErro;

}; // fim da classe Autoreparo


// ------------------  dividir (x,y)  -----------------------------------------
float dividir(float x, float y) { 
float resultado = 0;

if( y == 0.0f )   
throw Autoreparo("dividir(x,y): Divisao por zero evitada! \n"); 

resultado = x / y;

return resultado;

} // fim da funcao: Dividir (x,y)


// ------------------  Nosso programa principal comeca aqui... ---------------
int main() { 
system ("color f0"); system("title autoreparo.cpp"); cout << endl;


float dy = 0.0f;
float resultado = 0.0f;

// Codigo sem tratamento de excessao
resultado = dividir (12.0f, 3.0f); 
cout << "12/3 = " << resultado << "\n";

// Codigo com tratamento de possiveis excessao
try
{ 
cout << "dividir(12,0)\n";
resultado = dividir(12.0f, 0.0f); 
cout << "12 / 0 = " << resultado << endl;
} // endtry

catch(Autoreparo& reparo)
{ 
reparo.informarErro();
} // endcatch


cout << "Erro proposital adiante... divisao por zero" << endl; system("pause"); 
try
{
dy  = 0.0f;
if (dy == 0) throw Autoreparo("Evitei uma divisao por zero!: (33/0)");
resultado = 33/dy;
}

catch (Autoreparo &reparo)
{
reparo.informarErro();
}

cout << "\n\nTestando assert. Erro proposital adiante!";
cout << "\nO programa vai quebrar feio! \n\n";
system("pause");
dy = 0.0f;
assert (dy > 0);

cout << "Fim do programa... Essa linha nao roda...";
cout << endl; system("pause");
} // fim do programa: main()

