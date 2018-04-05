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
		PONTO *caminho;		
		
		Monstro () {
			caminho = new PONTO[3]; 	} 
			
		~Monstro () {
			cout << "\t destrutor() foi chamado.\n";
			delete[] caminho;
			fim();
		}
		
		void mostrar_caminho()
		{
			for (int ncx=0; ncx < 3; ncx++)
			{
				cout << "\t (" << caminho[ncx].x;
				cout << "," << caminho[ncx].y << ") \n";
			} // endfor						
		} // endmethod	 
		
		void config_caminho (int nponto, int x, int y) {
			caminho[nponto]. x = x;
			caminho[nponto]. y = x;			
		} // endmethod
		
}; // endclass

int main() {
	
	inicio();
	int x, y;

	// Criando um objeto da classe monstro
	Monstro godzila;
	
	for (int nponto = 0; nponto < 3; nponto++) {
		x = rand() % 800;
		y = rand() % 600;
		godzila.config_caminho (nponto, x, y);		
	} // endfor
	
	cout << " O caminho do godzila: \n";
	godzila.mostrar_caminho();	
	
	fim();
} // endmain


//************* funcoes ******************************************************
void inicio() {
	system("color f0");
	system("title destrutor.cpp");
	cout << "\n";	
	} // endfunction: initsys()
	
	void fim() {
	cout << "\n";	system("pause");
	} // endfunction: endsys()
