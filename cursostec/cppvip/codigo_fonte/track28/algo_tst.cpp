// algo_tst.cpp
// Esse programa ilustra o uso dos utilitarios do arquivo <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


// ***************************************************************************
// Classe de servico de impressao de numeros inteiros
class Impressora_virtual {
public:	
	int m_pularLinha;
	
	Impressora_virtual (int config = 0): m_pularLinha(config) {}

// Vamos imprimir numeros inteiros 
void operator()(int nval)			
 {		if (m_pularLinha == 1) cout << "\t\t";
		 cout << nval << " | ";
		 if (m_pularLinha == 1) cout << endl;
		 
 } // fim do metodo operator()
}; // fim da classe impressora virtual


// ***************************************************************************
// Classe geradora de numeros aleatorios
class Sorteador { 
private: 
int m_min; 
int m_max; 

public: 
Sorteador(int nmin, int nmax): m_min(nmin), m_max(nmax) {} 

// Vamos retornar um numero aleatorio faixa (m_mim, m_max)
int operator()()
 { 
return m_min + rand() % (m_max - m_min + 1);
 }  // fim do metodo operator()
}; // fim da classe: Sorteador

// ---------------- O programa principal comeca aqui -------------------------
int main() { 
system("color f0"); system("title algo_tst.cpp"); cout << endl;    
  
Impressora_virtual impressora;
Sorteador sorteador(2, 4);   
Sorteador xsorteador(2000,4000);

// Vamos criar uma lista para 15 numeros
vector<int> lstPlacar ; 
lstPlacar.resize(15); 

// O objeto sorteador() vai gerar numeros entre (2,4)
cout << "\nRecheando lista com numeros aleatorios: \n";
srand(time(0)); 
generate(lstPlacar.begin(), lstPlacar.end(), sorteador); 

// O objeto impressora(nval) vai imprimir numeros assim: nval | nval |...
for_each(lstPlacar.begin(), lstPlacar.end(), impressora); 

// Vamos contar frequencia do numero 3 na lista
int nfrequencia = count (lstPlacar.begin(), lstPlacar.end(), 3);
cout << "\n\nNumero 3 apareceu " << nfrequencia;
cout << " vezes na lista. Vamos troca'-lo por 99\n";

// Vamos substituir o nro 3 pelo nro 99 na lista
replace(lstPlacar.begin(), lstPlacar.end(), 3,99); 
for_each(lstPlacar.begin(), lstPlacar.end(), impressora); 

string sname = "gameprog 1 2 3"; 

cout << "\n\n\tA string '" << sname << "' ao reverso fica '";
reverse(sname.begin(), sname.end());
cout << sname << "'" << endl;

// Vamos gerar uma lista de placar com numeros maiores
cout << "\tLista desordenada dos placares de hoje: \n";
generate(lstPlacar.begin(), lstPlacar.end()-10, xsorteador); 
// O objeto impressora(nval) vai imprimir numeros assim: nval | nval |...
Impressora_virtual ximpressora(1);
for_each(lstPlacar.begin(), lstPlacar.end()-10, ximpressora); 

cout << "\n\tOs melhores placares de hoje: " << endl;
sort(lstPlacar.begin(), lstPlacar.end()-10); 
for_each(lstPlacar.begin(), lstPlacar.end()-10, ximpressora);
cout << "\tO melhor placar de hoje: " << lstPlacar[4] << " pontos. \n\n";

impressora(10);
ximpressora(100); ximpressora(100);
cout << xsorteador() << "\n" << sorteador() << endl;
cout << endl; system("pause");  
} // fim da funcao: main()
