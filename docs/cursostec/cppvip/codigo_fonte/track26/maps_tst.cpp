// maps_tst.cpp
// Esse programa ilustra o uso da estrutura map
#include <iostream>
#include <string>
#include <map>
using namespace std;

int main() { 
system("color f0"); system("title maps_tst.cpp"); cout << endl;

// Declarando um mapa e seu iterator
map<string, int> config;
map<string, int>::iterator ncx_pos;

// Vamos localizar adiante o valor dessa chave
string spropriedade = "video_largura";   

// Inserindo dados em um mapa
config["video_largura"] = 800;
config["video_altura"] = 600; 	 
config["som_efeitos"] = 1;
config["som_musica"] = 1;   
config["som_volume"] = 100;
config["jogo_dificuldade"] = 20;       

// Acessando e mostrando o valor de uma chave conhecida
cout << "\tjogo_dificuldade: ";
cout << config["jogo_dificuldade"] << endl;   

// Localizando a posicao de uma chave para exibicao de seu valor
ncx_pos = config.find(spropriedade);   
cout << "\tconfig.find(''video_largura''): " << ncx_pos->second << endl;
cout << "-------------------------------------------------------------- \n\n";
  

cout << "\tncx->first \t ncx->second \n";
cout << "\t-----------      -----------\n";
// Vamos mostrar todas as chaves e seus valores
for (ncx_pos = config.begin(); ncx_pos != config.end(); ncx_pos++)
    cout << "\t" << ncx_pos->first << "\t" << ncx_pos->second << endl;

cout << endl;
system("pause");

} // fim da funcao: main()
