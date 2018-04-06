	// string_elemento.cpp
	// Ilustra acesso a cada elemento da string
	#include <iostream>
	#include <string>

	using namespace std;
 
	int main() {
	system("color f0"); system("title elemento da string"); cout << "\n";	
	
	string snome = "gameprog";
	int ntam, item, nsize;	
	
	// obtem o tamanho da string
	ntam = snome.length();
	nsize = snome.size();
	
	// mostra o tamanho
	cout << "ntam: " << ntam << "\t nsize: " << nsize << endl;
	
	// acessa cada elemento
	for (item = 0; item < ntam; item++)
		cout << snome[item] << "  ";
		
	cout << endl;
		
	// mostra a posicao de cada elemento
	for (item = 0; item < ntam; item++)
		cout << item << "  "; cout << endl;
		
		// acessa cada elemento
	for (item = 0; item < ntam; item++)
		cout << snome.at(item) << "  ";
		
	cout << "\n\n";	
	
	
	system("pause");
	} // endmain
