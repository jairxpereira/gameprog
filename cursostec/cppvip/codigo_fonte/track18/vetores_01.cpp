// vetores_01.cpp
// Ilustra o uso de vetores
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void inicio();
void fim();

// -------------------- inicio da funcao principal ---------------------------
int main() {
inicio();	

vector<string> inventario(5);
vector<string>::iterator ncx_iter;

int ntam;
int nitem = 0;
int ncapacidade = 0;
bool lvazio;

// Assinalando os itens nas posicoes reservadas
inventario[0] = "faca";
inventario[1] = "canivete";
inventario[2] = "botas";

// Anexando dados no final do vetor
inventario.push_back("espada");
inventario.push_back("escudo");
inventario.push_back("capa");

inventario.resize(10);
ntam = inventario.size();
inventario.reserve(100);
ncapacidade = inventario.capacity();
lvazio = inventario.empty();

cout << "\t vetor.tamanho: " << ntam << "\n";
cout << "\t vetor.capacidade: " << ncapacidade << "\n";
cout << "\t vetor.vazio? " << boolalpha << lvazio << "\n";
cout << "------------------------------------------ \n";


// Acessando os itens via iterator
for (ncx_iter = inventario.begin(); ncx_iter != inventario.end(); ncx_iter++) 
{

  cout << "\t item: " << nitem << "\t";
	cout << *ncx_iter <<  "\n";	
	nitem++;
}

// Acessando os itens via indice
cout << "------------------------------------------ \n \t";
cout << inventario[1].c_str() << " tem " ;
cout << inventario[1].size() << " letras \n\n";

fim();	
} // endmain


// ------------------ funcoes basicas ----------------------------------------
void inicio() {
system("color f0"); system ("title vetores_01.cpp");
cout << "\n";	
} // endfunction: inicio()

void fim() {
cout << endl;
system("pause");
} // endfunction: inicio()
