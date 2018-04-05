// operator_overload2.cpp
// Sobrecarregando o operador de insercao e os parenteses
#include <iostream>
#include <string>

using namespace std;

void inicio();
void fim();

// -------------------  Declaracao da classe monstro -------------------------
class Monstro {
public:
int m_estrago;
string m_nome;

Monstro(string sn = "monstro", int est = 10): m_nome(sn), m_estrago(est) {}

int operator() (int nval) {
	int temp;
	temp = m_estrago;
	m_estrago = nval;
	return temp;			
} // fim do metodo operator()	

friend ostream& operator<< (ostream &tela, Monstro &monstro);	


}; // fim da classe monstro


// -------------------  sobrecarregando o operador de insercao ---------------
ostream& operator<< (ostream &tela, Monstro &monstro) {
char txt[255];
sprintf(txt, "(monstro:%s, estrago:%d)", 
monstro.m_nome.c_str(), monstro.m_estrago);
tela << txt;
return tela;
} // fim do metodo: operator<<()

// -------------------- inicio da funcao principal ---------------------------
int main() {
inicio();	

Monstro monstro_ness("Ness", 33);

cout << "\t" << monstro_ness << "\n";

int old_estrago = monstro_ness(999);

cout << "\t capacidade de estrago anterior: " << old_estrago << "\n";
cout << "\t" << monstro_ness << "\n";	

fim();	
} // endmain


// ------------------ funcoes basicas ----------------------------------------
void inicio() {
system("color f0"); system ("title operator_overload2.cpp");
cout << "\n";	
} // endfunction: inicio()

void fim() {
cout << endl;
system("pause");
} // endfunction: inicio()
