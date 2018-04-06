// test_cin
#include <iostream>
#include <string>
using namespace std;

int main() {	

	int x, y, z;
	float nsorte;	
	char spc = 32;
	
	
	string snome = "";
	char scor[255];
	system("color f0"); system("title test_cin.cpp");
	
	
	cout << "\n\t Qual seu jogo favorito? ";
 	getline (cin, snome);
	
	// Digite x,y,z com um espaco entre cada um deles
	cout << "\t Digite [x, y, z] = ";
	cin >> x >> y >> z;
	
	
	cout << "\t Digite seu nro da sorte: ";
	cin >> nsorte;
	
	cout << "\t Digite sua cor favorita: ";
 	cin >> scor;
	
	cout << "\n\n";
	cout << "\t Game: " << snome << "\n";
	cout << "\t 3D Position: [" << x << spc << y << spc << z << "]\n";
	cout << "\t Favourite color: " << scor << "\n";
	cout << "\t Favourite number: " << nsorte << "\n\n";
	
	system("pause");
	} // endmain
