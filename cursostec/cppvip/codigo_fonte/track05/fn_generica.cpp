// fn_generica.cpp
// Demonstra o uso de funções genéricas
#include <iostream>
#include <string>

using namespace std;

// protótipo das funções genéricas
template <typename tipo_geral> void diga (tipo_geral nval);

template <typename tipo_geral>
void diga (string txt, tipo_geral nval);

int main() {
	system("color f0"); system ("title fn_generica.cpp");

	int x = 320;
	float npi = 3.1415f;
	int energia = 99;
	string msg = "\t Quantidade de energia: ";

	cout << "\n";

	diga(x);
	diga (npi);
	diga ("Teste com string \n");

	diga (msg, energia);
	diga ("\t npi: ", npi);


	cout << "\n"; system("pause");
} // endmain

//******************* implementação das funções genéricas
template <typename tipo_geral>
void diga (tipo_geral nval) {
cout << "\t Argumento: " << nval << "\n";
} // endfunction: diga(tipo_geral)

template <typename tipo_geral>
void diga (string txt, tipo_geral nval) {
cout << txt << nval << "\n";
} // endfunction: diga (string, tipo_geral)
