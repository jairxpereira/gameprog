// showtextfile.cpp
// Ilustra leitura e gravacao de arquivos textos
// usando sintaxe alternativa
// checando se fim de arquivo e se arquivo existe

#include <iostream>		// permite usar cin e cout
#include <fstream>		// permite ler e gravar arquivos
#include <string>			// vamos usar strings

using namespace std;

// -------------------- inicio da funcao principal ---------------------------
int main() {
system("color f0"); system("title showtextfile.cpp"); cout << "\n";

// Declarando variaveis
string slinha;

// abrindo o arquivo...
ifstream hfile("xsave_text.cpp");	

// O arquivo existe? 
if (!hfile) {
cout << "erro na abertura do arquivo. Saindo... \n";
system("pause");
return -1;
}	// endif

// Lendo os dados...
while (!hfile.eof()) {
getline (hfile, slinha);
cout << slinha << "\n";
} // endwhile

// fechando o arquivo
hfile.close();

cout << "\n"; system("pause");
} // endmain
