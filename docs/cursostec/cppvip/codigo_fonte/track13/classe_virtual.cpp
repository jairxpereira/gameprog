// classe_virtual.cpp
// Este programa ilustra o uso de classe virtual abstrata
#include <iostream>

using namespace std;

// ------------------ Classe monstro -----------------------------------------
class Monstro {
public:
int m_estrago;
int m_id;
static int nobj;

Monstro(int estrago=10): m_estrago(estrago)
 { m_id =  nobj;
 	  nobj++; }

  virtual void atacar() = 0;
 
 }; // fim da classe monstro


// inicializacao da propriedade estatica
int Monstro::nobj = 1;

// ------------------ Classe Ogro derivada da classe monstro  -----------------
class Ogro: public Monstro {
public:

// construtor
Ogro(int estrago=12): Monstro(estrago) { } 

void atacar() {
	cout << "  O ogro #" << m_id << " te atacou com uma pedra e vc perdeu ";
	cout << m_estrago << " pontos de energia. \n";
 } // fim do metodo atacar()	
}; // fim da classe ogro

// ------------------ Classe Vampiro derivada da classe monstro  -----------------
class Vampiro: public Monstro {
public:

// construtor
Vampiro(int estrago=22) { m_estrago = estrago; } 

void atacar() {
	cout << "  O vampiro #" << m_id << " te mordeu e vc perdeu ";
	cout << m_estrago << " pontos de energia. \n";
 } // fim do metodo atacar()
}; // fim da classe vampiro

// prototipo das nossas funcoes basicas
void inicio();
void fim();

// --------------- Nossa funcao principal comeca aqui...
int main() {
inicio();		

Monstro *ptr_monstros[3];	

ptr_monstros[0] = new Ogro;
ptr_monstros[1] = new Ogro;
ptr_monstros[2] = new Vampiro;
ptr_monstros[3] = new Vampiro;

cout << "\n--- Parte 02: vampiros e ogros via ponteiros :-) -------------- \n";
for (int ncx =0; ncx < 4; ncx++) ptr_monstros[ncx]->atacar();	

delete[] ptr_monstros;
fim();	
} // endmain

// -------------------------- funcoes ----------------------------------------
void inicio() {
system("title classe_virtual.cpp");
system("color f0");	
cout << "\n";
} // endfunction: inicio()

void fim() {
cout << endl;
system("pause");	
} // endfunction: fim()
