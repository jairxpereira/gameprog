// valor_default.cpp
// Demonstra valores default em funcoes
#include <iostream>
using namespace std;

void carregar_tela (int nfase = 1, int nvidas = 5);

int main()
{	
	system("color f0"); system ("title valor default");
	
	carregar_tela();
	carregar_tela(3);
	carregar_tela(5,10);
	
	cout << "\n"; system("pause");
} // endmain

void carregar_tela(int nfase, int nvidas) {	
cout << "\n";
cout << "\t A fase " << nfase << " foi carregada.";
cout << " Vc tem " << nvidas << " vidas.\n";
} // endfunction: carregar_tela()


