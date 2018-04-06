// stack_tst.cpp
// Esse programa ilustra o uso da pilha
#include <iostream>
#include <string>
#include <stack>
using namespace std;

int main() { 
system("color f0"); system("title stack_tst.cpp"); cout << endl;    

// Declarando a pilha
stack<string> pilha;  		

// Nossso caminho SP - Maua e vice-versa
string caminho[6];
caminho[0] = "[1]SP  ";
caminho[1] = "[2]Diadema";
caminho[2] = "[3]SBC ";
caminho[3] = "[4]SA  ";
caminho[4] = "[5]SC  ";
caminho[5] = "[6]Maua";    

// Colocando dados da pilha...
cout << "\tEstou indo para Maua..." << endl;		
for (int ncx=0; ncx < 6; ncx++) {
cout << "\n\t";
cout << caminho[ncx];
pilha.push ( caminho[ncx] );				
} // end for
cout << "\n -------------------------------------------------";
cout << endl << endl;		

// Mostrando e retirando dados da pilha...
cout << "\tEstou voltando para SP..." << endl;		
for (int ncx=0; ncx < 6; ncx++) {
cout << "\n\t";
cout << pilha.top(); 
pilha.pop();			
} // endfor
 
cout << endl; cout << endl;
system("pause");
} // endfunction: main()
