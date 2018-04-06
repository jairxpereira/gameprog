// globvars.cpp
// Demonstra o acesso a variáveis globais homônimas às locais
#include <iostream>

using namespace std;

// Variável global
int contador = 30;

int main() {    
system("color f0"); system ("title globvars.cpp");

// Variável local
int contador = 0;

cout << "\n Var. contador local     - var. contador global" << endl;
cout << " ------------------------------------------------" << endl;
for (contador =1; contador <=7; contador++)
{
cout << " contador: " << contador << "\t\t - ";
cout << "::contador: " << ::contador << endl;
}

cout << "\n";
cout << "\n"; system("pause");
} // endmain
