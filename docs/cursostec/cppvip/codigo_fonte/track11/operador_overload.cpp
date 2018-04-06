// operator_overload.cpp
// ilustra sobrecarregamento de operadores (operator overload)
#include <iostream>


using namespace std;

// prototipo de nossas funcoes basicas
void inicio();
void fim();

class Ponto {
	public:
		
	int mx;
	int my;	
	
	Ponto (int x =0 , int y =0): mx(x), my(y){} 	
	
	void info();	
	Ponto operator+ (int nval);
	Ponto operator+ (const Ponto &ldir);	
	Ponto& operator= (const Ponto &ldir);
	
	friend Ponto operator+ (int nval, const Ponto &ldir);
	
}; // fim da classe: Ponto


void Ponto::info()
{
	
	cout << "(" << mx << "," << my << ")\t";
	
}


Ponto Ponto::operator+ (int nval)
{
	Ponto res;
	res.mx = this->mx + nval;
	res.my = this->my + nval;
	return res;
} // fim do metodo operator+(int)

Ponto& Ponto::operator= (const Ponto &ldir)
{
	mx = ldir.mx;
	my = ldir.my;	
	return *this;
} // fim do metodo operator=(Ponto&)


Ponto Ponto::operator+ (const Ponto &ldir)
{
	Ponto res;
	res.mx = mx + ldir.mx;
	res.my = my + ldir.my;	
	return res;
} // fim do metodo operator+(Ponto&)

Ponto operator+ (int nval, const Ponto &ldir )
{
	Ponto res;
	res.mx = ldir.mx + nval;
	res.my = ldir.my + nval;
	return res;
} // fim do metodo operator+(int)

// ponto de entrada da execucao de nosso programa
int main() {
	inicio();
	
	Ponto pnt_a(310,230);
	Ponto pnt_b(80,60);
	Ponto pntsoma;
	
	cout << " pnt_a = ";	pnt_a.info();		
	cout << " pnt_b = ";	pnt_b.info();
	cout << "\n";	

	cout << " pnt_a + 10 = "; pnt_a.info();
	
	pnt_a = pnt_a + pnt_b;	
	cout << " pnt_a + pnt_b = "; pnt_a.info();
	
	fim();
} // endmain


//************* funcoes ******************************************************
void inicio() {
	system("color f0");
	system("title operator_overload.cpp");
	cout << "\n";	
} // endfunction: initsys()
	
	void fim() {
	cout << "\n\n";	system("pause");
} // endfunction: endsys()
