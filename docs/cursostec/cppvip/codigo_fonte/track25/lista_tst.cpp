// lista_tst.cpp
// Esse programa exemplica o uso de listas
#include <iostream>
#include <string>
#include <list>
using namespace std;

list<string> smetroLista; 
list<string>::iterator ncx_pos = 0;
string metro[10];

void mostrar_lista() {
for( ncx_pos = smetroLista.begin(); ncx_pos != smetroLista.end(); ++ncx_pos ) 
cout << *ncx_pos << "--"; 
cout << endl << endl;
} // fim da funcao: mostrar_lista()

int main() { 
system("color f0"); system("title lista_tst.cpp"); cout << endl;

// Nossso metro virtual....
metro[1] = "(1)SP";
metro[2] = "(2)Diadema";
metro[3] = "(3)SBC";
metro[4] = "(4)SA";
metro[5] = "(5)SC";
metro[6] = "(6)Maua";    
metro[7] = "(7)Santos";    
metro[8] = "(8)RJ";    
metro[9] = "(9)MG";  

// Vamos inserir dados na frente da lista
smetroLista.push_front( metro[4] ); 
smetroLista.push_front( metro[3] ); 
smetroLista.push_front( metro[2] ); 
smetroLista.push_front( metro[1] ); 

// Vamos inserir dados no fundo da lista
smetroLista.push_back(metro[5] ); 
smetroLista.push_back(metro[7] ); 
smetroLista.push_back(metro[8] ); 
smetroLista.push_back(metro[9] ); 

cout << "\tEsquecemos de colocar a cidade #6" << endl;
mostrar_lista();

// Opa! Esquecemos de adicionar o metro[6] na lista antes do [7]. 
// Vamos primeiro obter o iterator que aponta para a posicao aonde queremos
// inserir nosso dado. Vamos fazer uma busca linear para encontrar esta
// posicao.
cout << "\tColocamos Maua' de volta no mapa..." << endl; 
for( ncx_pos = smetroLista.begin(); ncx_pos != smetroLista.end(); ++ncx_pos ) 
if( *ncx_pos == metro[7] ) break; 

// Vamos inserir o metro[6] aonde esta' o [7]. Isso nao deleta o [7], isso...
// ...insere o [6] entre o [5] e o [7].
smetroLista.insert(ncx_pos, metro [6] ); 
mostrar_lista();

// Vamos deletar alguns itens...
cout << "\tDeletamos o metro[7], a frente e o fundo da lista...\n";
smetroLista.remove( metro[7]);
smetroLista.pop_front();
smetroLista.pop_back();

ncx_pos = smetroLista.begin();
for (int mypos=1; mypos < 3; mypos++) ncx_pos++;
smetroLista.insert ( ncx_pos, "03 - ta' hackeado!");


mostrar_lista(); 

cout << endl;
system("pause");

} // endfunction: main()
