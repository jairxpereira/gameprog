// fn_overload.cpp
// Demonstra sobrecarregamento de funcoes ( function overload )
#include <iostream>
#include <string>

using namespace std;

void diga (int nval);
void diga (float nval);
void diga (string txt, int nval);


int main() {	
	system("color f0"); system ("title function overload");
	
	int x = 320;
	float npi = 3.1415f;
	int energia = 99;	
	string msg = "\t Quantidade de energia: ";
	
	cout << "\n";
	
	diga(x);
	diga (npi);
	diga (msg, energia);
	
	cout << "\n"; system("pause");
} // endmain


void diga (int nval) {
cout << "\t Argumento inteiro: " << nval << "\n";	
} // endfunction: diga(int)


void diga (float nval) {
cout << "\t Argumento float: " << nval << "\n";			
} // endfunction: diga (float)

void diga (string txt, int nval) {
cout << txt << nval << "\n";		
} // endfunction: diga (string, int)

