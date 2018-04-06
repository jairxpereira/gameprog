// memoria.cpp
// ilustra alocacao de memoria 
#include <iostream>

using namespace std;

void inicio();
void fim();

// ponto de entrada de execucao do programa
int main() {
inicio();


// reservamos memoria para dois inteiros e definimos seus valores iniciais 320,240
int *xcol = new int (320);
int *ylin = new int (240);


// reservamos memoria para uma lista de 10 inteiros
int *nlista = new int[10];

// definimos os valores iniciais de nossa lista de inteiros 1 - 10
for (int ncx=0; ncx < 10; ncx++) {
*(nlista + ncx) = ncx + 1;
} // endfor

cout << "\t xcol: " << *xcol;
cout << "\t ylin: " << *ylin << "\n\n";

cout << "\t";
// aqui mostramos o conteudo de nossa lista de inteiros
for (int ncx=0; ncx < 10; ncx++)
cout << *(nlista + ncx) << " ";

cout << "\n";

delete xcol;
delete ylin;
delete[] nlista;
	
fim();
} // endmain


//************* funcoes ******************************************************
void inicio() {
system("color f0");
system("title memoria_01");
cout << "\n";	
} // endfunction: initsys()
	
void fim() {
cout << "\n";	system("pause"); 
} // endfunction: endsys()
