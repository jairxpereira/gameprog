// Heranca_simples.cpp
// Este programa ilustra a heranca de classes
#include <iostream>
#include <string>

using namespace std;

// ------------------ Classe monstro -----------------------------------------
class Monstro {
	public:
	int m_estrago;
	string m_nome;
	
	Monstro(string snome = "'monstro'", int estrago=10): m_nome(snome), m_estrago(estrago) {}
	
	void atacar() {
		cout << "  O monstro " << m_nome << " te atacou  e vc perdeu ";
		cout << m_estrago << " pontos de energia. \n";
	} // fim do metodo atacar()
	
	
}; // fim da classe monstro

// ------------------ Classe Ogro derivada da classe monstro  -----------------
class Ogro: public Monstro {
	public:
	
	Ogro(string snome = "ogro", int estrago=12): Monstro(snome, estrago) {}
	
	void atacar() {
		cout << "  O ogro " << m_nome << " te atacou com uma pedra e vc perdeu ";
		cout << m_estrago << " pontos de energia. \n";
	} // fim do metodo atacar()
	
	
}; // fim da classe ogro

// ------------------ Classe Vampiro derivada da classe monstro  -----------------
class Vampiro: public Monstro {
	public:
	
	Vampiro(string snome = "vampiro", int estrago=22) {
		m_nome = snome;
		m_estrago = estrago;
	}
	
	void atacar() {
		cout << "  O vampiro " << m_nome << " te mordeu e vc perdeu ";
		cout << m_estrago << " pontos de energia. \n";
	} // fim do metodo atacar()
	
	void dormir() {
		cout << "  05:00 O sol vai surgir dentro de uma hora. Hora de vampiro dormir!";
		cout << "\n";
	} // fim do metodo dormir()	
}; // fim da classe vampiro

// prototipo das nossas funcoes basicas
void inicio();
void fim();

// --------------- Nosso funcao principal comeca aqui...
int main() {
	inicio();	
	
Monstro godzila("godzlila");
Ogro shrek("Shrek");
Vampiro alucard("Alucard");

godzila.atacar();
shrek.atacar();

alucard.atacar();
alucard.dormir();	
	
fim();	
} // endmain

void inicio() {
	system("title heranca_simples.cpp");
	system("color f0");	
	cout << "\n";
} // endfunction: inicio()

void fim() {
	cout << endl;
	system("pause");	
} // endfunction: fim()
