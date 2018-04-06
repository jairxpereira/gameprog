// deque_tst.cpp
// Esse programa exemplica o uso de filas com dupla extremidade
#include <iostream>
#include <string>
#include <deque>
using namespace std;

deque<string> filaDupla; 
string cidade[10];

void mostrar_filaDupla() {
for(int  ncx = 0; ncx < filaDupla.size(); ++ncx ) 
cout << filaDupla[ncx] << "--"; 
cout << endl << endl;
} // fim da funcao: mostrar_filaDupla()

int main() { 
system("color f0"); system("title deque_tst.cpp"); cout << endl;

// Nosssa lista de cidades preferidas
cidade[1] = "(1)SP";	cidade[2] = "(2)Diadema";	cidade[3] = "(3)SBC";
cidade[4] = "(4)SA";	cidade[5] = "(5)SC";			cidade[6] = "(6)Maua";    

// Vamos inserir dados na frente da fila
filaDupla.push_front( cidade[4] ); 
filaDupla.push_front( cidade[3] ); 
filaDupla.push_front( cidade[2] ); 

// Vamos inserir dados no fundo da fila
filaDupla.push_back(cidade[5] ); 
filaDupla.push_back(cidade[6] ); 

cout << "\tFila original: " << endl;
mostrar_filaDupla();

cout << "\tFila com adicao de dados nos extremos" << endl;
filaDupla.push_front ( cidade[1] );
filaDupla.push_back ( "(?) Sorocaba" );
mostrar_filaDupla();

// Vamos deletar alguns itens...
cout << "\tExtremos deletados com .pop_front() e pop.back():\n";
filaDupla.pop_front();
filaDupla.pop_back();
mostrar_filaDupla();

cout << "\tAcessando e modificando elementos pelo operator[]" << endl;
filaDupla[03] = "(0?) hackeado!";

mostrar_filaDupla(); 

cout << filaDupla.front(); cout << filaDupla.back();

cout << endl;
system("pause");

} // endfunction: main()
