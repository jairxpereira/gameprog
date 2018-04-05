// arquivo_texto.cpp
// Ilustra leitura e gravacao de arquivos textos

#include <iostream>		// permite usar cin e cout
#include <fstream>		// permite ler e gravar arquivos
#include <string>			// vamos usar strings
#include <cstdlib>		// vamos gerar valor de energia aleatorio
#include <ctime>			// vamos gerar valores aleatorios sempre diferentes

using namespace std;


// ****************** classe Config para dados de configuracao do jogo ********
class Config {
	public:
	int m_fase;
	int m_estagio;
	int m_energia;
	string m_nome;

	// Nosso construtor
	Config (int fase = 1, int estagio = 0,  int hp = 100, string snome = "Player")
	{
		m_fase = fase;
		m_estagio = estagio;
		m_energia = hp;
		m_nome = snome;
	} // ::Config().end

	// Mostra dados de status do jogo
	void mostrar()
	 {
			char txt[255];
			sprintf (txt, "\t(jogador:%s energia:%d tela:%d estagio:%d)",
			m_nome.c_str(), m_energia, m_fase, m_estagio);
			cout << txt << "\n";
		} // ::mostrar().end

	// Resseta para os valores originais os dados de status do jogo
	void reset()
	{
		m_fase = 1;
		m_estagio = 0;
		m_energia = 100;
		m_nome = "Player";

	}	// ::reset().end


}; // fim da classe config
// --------------------------------------------------------------------------

// Prototipo das nossas funcoes basicas
void inicio();
int menu();
void savegame (Config &cfg, string snome_arquivo);
void loadgame (Config &cfg, string snome_arquivo);
void mostra(Config &cfg);
void fim();


// -------------------- inicio da funcao principal ---------------------------
int main() {
inicio();
int nEscolha;
const int carregar = 1;
const int gravar = 2;


Config jogo_situacao (7,3,45, "Mario");

// gera um valor aleatorio na faixa 0-100 diferente a cada rodado do programa
srand (time(0));
jogo_situacao.m_energia = rand() % 100;

nEscolha = menu();

if ( nEscolha == gravar) {
	savegame(jogo_situacao, "savegame.txt");
	jogo_situacao.mostrar();
} // endif gravando dados no disco


if ( nEscolha == carregar) {
	jogo_situacao.reset();

	cout << "\n\tDados atuais do registro:  \n";
	jogo_situacao.mostrar();

	cout << "\n\tAgora, dados carregados do arquivo: \n";
	loadgame(jogo_situacao, "savegame.txt");
	jogo_situacao.mostrar();

} // endif carregando dados do disco


fim();
} // endmain

// ************ Implementacao das funcoes definidas *************************
void inicio() {
system("color f0"); system("title arquivo_texto.cpp");
cout << "\n";
} // fim da funcao inicio()

void fim() {
cout << "\n"; system("pause");
} // fim da funcao fim()

// --------------- n = menu() gera um menu de escolhas -----------------------
int menu() {
int nEscolha = 0;
string txt_carregar = "\t 1- Carregar arquivo \n";
string txt_gravar = "\t 2- Gravar arquivo \n";
string txt_escolher = "\n\t------------------------ \n\t Digite sua escolha: ";

cout << txt_carregar;
cout << txt_gravar;
cout << txt_escolher;
cin >> nEscolha;
return nEscolha;
} //  fim da funcao menu()


// --------------- savegame() - grava no disco configuracao do jogo ----------
void savegame (Config &cfg, string snome_arquivo)
{
ofstream hfile;
hfile.open(snome_arquivo.c_str());
hfile << cfg.m_nome << "\n";
hfile << cfg.m_energia << "\n";
hfile << cfg.m_fase <<  "\n";
hfile << cfg.m_estagio << "\n";
hfile.close();
cout << "\n \t savegame() ok" << "\n";
} // savegame().fim


// --------------- loadgame() - grava no disco configuracao do jogo ----------
void loadgame (Config &cfg, string snome_arquivo)
{
ifstream hfile;
hfile.open(snome_arquivo.c_str());
hfile >> cfg.m_nome;
hfile >> cfg.m_energia;
hfile >> cfg.m_fase;
hfile >> cfg.m_estagio;
hfile.close();
cout << "\t loadgame() ok" << "\n";
} // loadgame().fim
