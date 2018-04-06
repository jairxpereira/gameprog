// cls_generica.cpp
// Este programa ilustra o uso de classe generica
#include <iostream>

using namespace std;

// definicao da classe generica Megafone
template <typename tipo_geral>
class Megafone {	
public:

tipo_geral m_dado;

Megafone (tipo_geral dado);

void diga(int nvezes = 1);

}; // fim da classe

// definicao do construtor
template <typename tipo_geral>
Megafone<tipo_geral>::Megafone(tipo_geral dado): m_dado(dado) {}

// definicao do metodo diga
template <typename tipo_geral>
void Megafone<tipo_geral>::diga (int nvezes) {
if (nvezes > 1)	for (int ncx=0; ncx < nvezes; ncx++) cout << m_dado;
else cout << m_dado << "\n";	
cout << "\n";
} // fim do metodo diga()

// prototipo das nossas funcoes basicas
void inicio();
void fim();

// --------------- Nossa funcao principal comeca aqui...
int main() {
inicio();	

// Instanciamento de um objeto de classe generica
Megafone<string> linha("-");
Megafone<string> aviso("\tPress start to play");
Megafone<int> credito(2);

// uso normal dos metodos
linha.diga(40); aviso.diga(); 
cout << "\tCredits: "; credito.diga();
linha.diga(40);

fim();	
} // endmain

// -------------------------- funcoes ----------------------------------------
void inicio() {
system("title cls_generica.cpp");
system("color f0");	
cout << "\n";
} // endfunction: inicio()

void fim() {
cout << endl;
system("pause");	
} // endfunction: fim()
