// memoria_02.cpp
// ilustra alocacao de memoria por outra funcao
#include <iostream>

using namespace std;

void inicio();
void fim();

int *getLista(int ntam);

// ponto de entrada de execucao do programa
int main() {
inicio();

int *mylist = NULL;
int ntam = 12;

mylist = getLista( ntam );
for (int ncx=0; ncx < ntam; ncx++)
cout << *(mylist + ncx) << " ";

cout << "\n";

delete[] mylist;
	
fim();
} // endmain

//************* funcoes ******************************************************
void inicio() {
system("color f0");
system("title memoria_02");
cout << "\n";	
} // endfunction: initsys()
	
void fim() {
cout << "\n";	system("pause"); 
} // endfunction: endsys()

//************* getLista() ***************************************************
int* getLista (int ntam) {
int* nlista = new int[ntam];
for (int ncx=0; ncx < ntam; ncx++) {
	*(nlista + ncx) = ncx + 1;
	} // endfor	
return nlista;	
} // endfunction: getLista()


