// saveloadbin.cpp
// Ilustra leitura e gravacao de arquivos binarios
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

int loadgame()	
{	
	
ifstream hfile("binfile.dat", ios::binary); 
	
	// arquivo existe?
	if (!hfile)
	{
	cout << "\t *** erro na abertura do arquivo *** \n";
	hfile.close();
	return -1;
	} // endif		
	
// faz a leitura dos dados
// cuidado na hora de ler a string
char  temp[255];
hfile.read ( (char *) temp, 6);		
m_nome.assign(temp);

hfile.read ( (char *) &m_fase, sizeof(int));
hfile.read ( (char *) &m_estagio, sizeof(int));
hfile.read ( (char *) &m_energia, sizeof(int));		
cout << "\t .loadgame() ok \n";		

hfile.close();
return 1;		
	
} // ::loadgame().end

int savegame()
{	
ofstream hfile("binfile.dat",ios::binary); 
	
	// arquivo existe?
if (!hfile)
	{
	cout << "\t *** erro na abertura do arquivo *** \n";
	hfile.close();
	return -1;
	} // endif		
	
// Salvando os dados - repare no cuidado da gravacao da string
// A string Mario ocupa 5 letras + um byte para a marca de fim de string
hfile.write ( m_nome.c_str(), m_nome.size()+1);		
hfile.write ( (char *) &m_fase, sizeof(int));
hfile.write ( (char *) &m_estagio, sizeof(int));
hfile.write ( (char *) &m_energia, sizeof(int));	
cout << "\t .savegame() ok \n";
hfile.close();
return 1;		
	
} // ::savegame().end	

}; // fim da classe config
// --------------------------------------------------------------------------

// Prototipo das nossas funcoes basicas
int menu(); 


// -------------------- inicio da funcao principal ---------------------------
int main() {
system("color f0"); system("title saveloadbin.cpp"); cout << "\n";	

int nEscolha;
const int carregar = 1;
const int gravar = 2;
int sts = 0;

Config jogo_situacao (7,3,45, "Mario");

// gera um valor aleatorio na faixa 0-100 diferente a cada rodado do programa
srand (time(0));
jogo_situacao.m_energia = rand() % 100;

nEscolha = menu();

if ( nEscolha == gravar) {
sts = jogo_situacao.savegame();
jogo_situacao.mostrar();
} // endif gravando dados no disco


if ( nEscolha == carregar) {
jogo_situacao.reset();

cout << "\n\tDados atuais do registro:  \n";
jogo_situacao.mostrar();

cout << "\n\tAgora, dados carregados do arquivo: \n";
sts = jogo_situacao.loadgame();
jogo_situacao.mostrar();

} // endif carregando dados do disco


cout << "\n"; system("pause"); 
} // endmain

// ************ Implementacao das funcoes declaradas *************************
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
