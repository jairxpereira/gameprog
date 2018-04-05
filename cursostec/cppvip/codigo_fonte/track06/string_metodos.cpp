	// string_metodos.cpp
	// Exemplifica o uso de alguns metodos do objeto string
	#include <iostream>
	#include <string>

	using namespace std;
	void inicio();
	void fim();
 
	int main() {
	
	inicio();
	int ntam, npos, nitem, nqtd;
	string snome = "Super CastleVania IV";		
	ntam = snome.length();	

	
	// mostra os caracteres da string snome
	for (nitem=0; nitem < ntam; nitem++)
		cout << snome.at (nitem) << " ";
		cout << endl;
		
	// mostra a posicao dos caracteres
	for (nitem=0; nitem < ntam; nitem++) {		
		if (nitem >= 10) cout << nitem-10 << " ";
		else cout << nitem << " ";
	 } //endfor
			
	cout << "\n\n";
			
	// pesquisa por Castle e retorna a posicao. -1 caso nao encontre
	npos = snome.find( "Castle" );
	
	// retira uma substring de 6 letras comecando em npos
	nqtd = 6;
	string subtxt = snome.substr (npos,nqtd);		
	cout << subtxt << " comeca em " << npos << "\n";
	
	// Substitui 6 letras de snome, comecando na posicao 6
	int npos_inicial = 6; nqtd = 6;
	snome.replace (npos_inicial,nqtd, "Mario");	
	cout << snome << "\n\n";		
		
	fim();
	} // endmain
	
	void inicio() {
	system("color f0");
	system("title string.metodos()");
	cout << "\n";	
	} // endfunction: initsys()
	
	void fim() {
	cout << "\n";	system("pause");
	} // endfunction: endsys()

