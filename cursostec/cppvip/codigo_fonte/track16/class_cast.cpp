// class_cast.cpp
// esse programa ilustra o type casting de uma classe
#include <iostream>
#include <string>

using namespace std;

// prototipo das funcoes basicas
void inicio();
void fim();


// declaracao da classe monstro
class Monstro {
public:
int m_estrago;
string m_nome;

Monstro(string snome = "monstro", int estrago = 10)
{
m_estrago = estrago;
m_nome = snome;
} // fim do construtor

operator string() {
	char txt[255];
	sprintf (txt, "(monstro:%s, estrago:%d)", m_nome.c_str(), m_estrago);
	string stemp = txt;
	return stemp;	
} // fim do casting para string

}; // fim da classe monstro

// inicio da funcao principal
int main() {
inicio();

int x = 3;	int y = 2;	float z = 0.0f;

Monstro montro_ness("Ness",99);	
string info_monstro;

string res_impreciso  = "\t x=3 \t y=2 \t x / y ==> ";

string res_preciso = "\t (float) x / y ==>  ";

string res_cast_monstro = "\t (string) montro_ness ==> ";

string cast_exotico = "\t static_cast<float> (x) / y ==> ";			

z = x / y; cout << res_impreciso << z << "\n\n";

z = (float) x / y; cout << res_preciso << z << "\n\n";	

info_monstro = (string) montro_ness;	
cout << res_cast_monstro << info_monstro << "\n\n";	

z = static_cast<float> (x) / y;
cout << cast_exotico << z << "\n\n";	

fim();
} // endmain


// implementacao das funcoes basicas
void inicio() {
system("color f0"); system ("title class_cast.cpp");
cout << "\n";	
} // endfunction

void fim() {
cout << endl;	system("pause");
} // endfunction
