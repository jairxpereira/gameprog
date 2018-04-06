// xsave_text.cpp
// Ilustra leitura e gravação de arquivos textos
// usando sintaxe alternativa
// checando se fim de arquivo e se arquivo existe

#include <iostream>     // permite usar cin e cout
#include <fstream>      // permite ler e gravar arquivos
#include <string>       // vamos usar strings

using namespace std;

// -------------------- inicio da função principal ---------------------------
int main() {
system("color f0"); system("title xsave_text.cpp"); cout << "\n";

// Declarando variáveis
int fase;
int subfase, energia;
string sjogador;

// abrindo o arquivo...
ifstream hfile("savegame.txt");

// O arquivo existe?
if (!hfile) {
cout << "erro na abertura do arquivo. Saindo... \n";
system("pause");
return -1;
}   // endif

// Lendo os dados...
while (!hfile.eof()) {
hfile >> sjogador;
hfile >> energia;
hfile >> fase;
hfile >> subfase;
} // endwhile

// mostrando os dados
cout << "\t Nome do jogador: " << sjogador << "\n";
cout << "\t energia: " << energia << "\t";
cout << "\t fase: " << fase << "-" << subfase << "\n\n";

// fechando o arquivo
hfile.close();

// Aproveitando o mesmo object ifstream para teste de arquivo inexistente
hfile.open ("badfile.txt");
if (!hfile) cout << "\t o arquivo badfile.txt nao existe. Saindo... \n\n";
hfile.close();

cout << "\n"; system("pause");
} // endmain
