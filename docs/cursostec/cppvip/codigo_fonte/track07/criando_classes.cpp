// destrutor.cpp
// ilustra o uso de destrutores
#include <iostream>
#include <cstdlib>

using namespace std;

// prototipo de nossas funcoes basicas
void inicio();
void fim();

struct PONTO {
	int x;
	int y;	
}; // end struct

// Vamos criar uma classe Monstro para criar objetos monstro
class Monstro
{
	public:
		Ponto *caminho;		
		
		Monstro () {
			Ponto *caminho = new Ponto[10]; 	} 
			
		~Monstro () {
			cout << "destrutor() foi chamado.\n";
			delete[] caminho;
		}
		
		void mostre_caminho() {
			for (int ncx=0; ncx < 10; ncx++) {
				cout << "(" << caminho->x;
				cout << "," << caminho->y << ") \n";	
			} // endfor						
		} // endmethod	
		
}; // endclass

int main() {
	
	inicio();
	
	int energia, estrago;
	
	// Criando um objeto da classe monstro
	Monstro godzila;
	
	for (int ncx = 0; ncx < 10; ncx++) {
		godzila.caminho->x = random() % 800;
		godzila.caminho->y = random() % 600;
	} // endfor
	

	
	// Obtendo valores das propriedades do objeto monstro
	energia = godzila.m_energia;
	estrago = godzila.m_estrago;	
	cout << "\t m_energia: " << energia << "\n";
	cout << "\t m_estrago: " << estrago << "\n";	
	
	// Vamos atacar
	godzila.atacar();
	
	
	// Reconfigurando e mostrando as propriedades
	godzila.m_energia = 99;
	godzila.m_estrago = 999;
	cout << "\t m_energia: " << godzila.m_energia << "\n";
	cout << "\t m_estrago: " << godzila.m_estrago << "\n";	
	godzila.atacar();	
	
	fim();
} // endmain


//************* funcoes ******************************************************
void inicio() {
	system("color f0");
	system("title criando classes");
	cout << "\n";	
	} // endfunction: initsys()
	
	void fim() {
	cout << "\n";	system("pause");
	} // endfunction: endsys()
