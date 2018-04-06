#include <iostream>
#include <string>
#include <queue>

using namespace std;

// ----------------- Nossa funcao principal comeca aqui ------------------------
int main() { 
system("color f0"); system("title fila_simples.cpp");
  
queue<string> filaClientes;
  
string cliente[6];

cliente[0] = "Pedro";
cliente[1] = "Paulo";
cliente[2] = "Charles";
cliente[3] = "Samantha";
cliente[4] = "Jorge";
cliente[5] = "Sampaio";

// Chegou o cliente 2, 4 e 1
filaClientes.push ( cliente[2] );
filaClientes.push ( cliente[4] );
filaClientes.push ( cliente[1] );

cout << "\n\tEstes clientes chegaram nesta ordem: \n";
cout << "\t-------------------------------------- \n";

cout << "\t" << cliente[2];
cout << "\t" << cliente[4];
cout << "\t" << cliente[1] << "\n\n";

// Quem esta' no fim da fila?
cout << "\t Ultimo cliente: " << filaClientes.back() << "\n\n";

// Vamos atender quem chegou na ordem
for (int ncx = 0; !filaClientes.empty(); ncx++) {

// verifica quem esta' na frente
cout << "  Tamanho da fila: " << filaClientes.size() << " clientes --- ";
cout << filaClientes.front();
cout << " foi atendido e foi embora. \n";
// manda cliente embora
filaClientes.pop();

} // end for ncx

cout << "  Tamanho da fila: " << filaClientes.size() << " clientes --- ";
if (filaClientes.empty()) cout << "O banco esta' vazio! \n\n";

cout << "\n"; system("pause");
} // ---------------------- fim da funcao main() ------------------------------


