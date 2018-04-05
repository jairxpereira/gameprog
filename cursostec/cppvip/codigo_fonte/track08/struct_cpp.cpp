// struct_cpp.cpp
// ilustra que as estruturas em c++ pode ter metodos e propriedades
#include <iostream>
#include <string>

using namespace std;

// prototipo de nossas funcoes basicas
void inicio();
void fim();

// definindo uma estrutura ponto
struct PONTO3D
{	

	float x;
	float y;
	float z;
		
	void show(char *txt) 
	{
	cout << "\t" << txt << "(" << x << "," << y << "," << z << ")\n";
	} 
	
	void metade();

}; 

// ponto de entrada de execucao do programa
int main() {
inicio();
	
PONTO3D pos;
PONTO3D poscamera = { 50,60,30 };	
	
pos.x = 320;
pos.y = 240;
pos.z = 100;	
	
pos.show("pos: ");
pos.metade();
pos.show("pos: ");
poscamera.show("poscamera: ");
	
fim();
} // endmain

void PONTO3D::metade() {
x = x / 2.0f;
y = y / 2.0f;
z = z / 2.0f;	
} // endmethod	


//************* funcoes ******************************************************
void inicio() {
system("color f0");
system("title struct_cpp.cpp");
cout << "\n";	
} // endfunction: initsys()
	
void fim() {
cout << "\n";	system("pause"); 
} // endfunction: endsys()
