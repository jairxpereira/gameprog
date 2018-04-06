// Programa: queue_tst.cpp 
// Este programa ilustra o conceito de trocas de mensagens numericas entre  	
// objetos utilizando filas para armazenar eventos ocorridos.
#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <queue>

using namespace std;

// Eventos de videogame
#define 	msg_jogador_atacado         			1
#define 	msg_vida_extra_encontrada   			2
#define		msg_municao_encontrada      			3
#define		msg_kitsaude_encontrado     			4
#define		msg_gatilho_video_encontrado			5

void tratar_evento ( int nEvento);

// -------------------------- Classe Jogador ---------------------------------
class Jogador {
	public:
		
	int m_vidas;
	int m_energia;
	int m_municao;	
	
	Jogador(int vidas = 5, int energia = 99, int municao = 50) {
		m_vidas = vidas;
		m_energia = energia;
		m_municao = municao;		
	} // fim do construtor
	
	void mostrar() {
	char txt[255];
	sprintf (txt,"Situacao do jogador: ( vidas:%d energia:%d municao:%d )",
	m_vidas, m_energia, m_municao);
	cout << "\t" << txt << "\n";
	} // fim do metodo mostrar()
	
	void perder_energia( int nqtd) {
		m_energia = m_energia - nqtd;
		cout << "\t*** Vc perdeu " << nqtd << " pontos energia *** \n";
	} // fim do perder_energia()
	
	void ganhar_energia( int nqtd) {
		m_energia = m_energia + nqtd;
		cout << "\t*** Vc ganhou " << nqtd << " pontos de energia ***\n";
	} // fim do ganhar_energia()
	
	void ganhar_vida( int nqtd) {
		m_vidas = m_vidas + nqtd;
		cout << "\t*** Vc ganhou " << nqtd << " vidas extras. ***\n";
	} // fim do metodo ganhar_vida()
	
	void aumentar_municao( int nqtd) {
		m_municao = m_municao + nqtd;
		cout << "\t*** Vc ganhou " << nqtd << " cargas de municao extra ***\n";
	} // fim do metodo aumentar_municao()	
	
	void tocar_video ( int nvideo) {		
		cout << "\t*** O video #" << nvideo << " foi tocado e mostrou uma cena...***\n";
	} // fim do metodo tocar_video()
	
}; // ------------------ fim da classe Jogador ---------------------------------

// Vamos criar um jogador publico
Jogador rambo;

// ----------------- Nossa funcao principal comeca aqui ------------------------
int main() { 
system("color f0"); system("title queue_tst.cpp");
  
queue<int> msgEventos;
  
string legenda[6];

legenda[0] = "0 - reservado                    ";
legenda[1] = "1 - msg_jogador_atacado          ";
legenda[2] = "2 - msg_vida_extra_encontrada    ";
legenda[3] = "3 - msg_municao_encontrada       ";
legenda[4] = "4 - msg_kitsaude_encontrado      ";
legenda[5] = "5 - msg_gatilho_video_encontrado ";

int evento_surpresa;
int evento_ocorrido = 0;

// Vamos sortear e mostrar os eventos
srand ( time(0));
cout << "\n\t *** Eventos enfileirados nesta ordem: ***\n";
for (int ncx = 0; ncx < 4; ncx++) {
evento_surpresa = (rand() % 5) + 1;
msgEventos.push( evento_surpresa );
cout << "\t " << legenda[evento_surpresa] << "\n";
} // endfor
cout << "\n";

// Mostrar o jogador antes dos eventos serem processados
rambo.mostrar();
     
// Vamos processar os eventos ocorridos na sequencia que aconteceram
cout << "\t--------------- Processando eventos -------------------------- \n"; 
for (int ncx = 0; ncx < 4; ncx++) {
evento_ocorrido = msgEventos.front(); 
cout << "\t"; cout << legenda [evento_ocorrido];
cout << "\t fila.tamanho:" << msgEventos.size() << "\n";

tratar_evento ( evento_ocorrido);
msgEventos.pop();    
} // endfor
      
// Foi tratado todos os eventos?
cout << "\t--------------------------------------------------------------- \n";
if (msgEventos.empty()) cout << "\t --- A fila agora esta' vazia! ---\n";
rambo.mostrar();

cout << "\n"; system("pause");
} // ---------------------- fim da funcao main() ------------------------------


// --------------------- tratar_evento() -------------------------------------
void tratar_evento ( int nEvento) {
	
	switch (nEvento) 
	{
		case 	msg_jogador_atacado:         			
		rambo.perder_energia(10);
		break;
		
		case 	msg_vida_extra_encontrada:  		
		rambo.ganhar_vida(3);
		break;
		
		case	msg_municao_encontrada:      			
		rambo.aumentar_municao(10);
		break;		
		
		case	msg_kitsaude_encontrado:     			
		rambo.ganhar_energia(15);
		break;
		
		case	msg_gatilho_video_encontrado:
		rambo.tocar_video(7);
		break;
		
		default:
		cout << "Esse evento nao existe: #" << nEvento << "\n";			
			
	} // fim do switch nEvento	
	
} // ------------------ fim da funcao tratar_evento() ------------------------

