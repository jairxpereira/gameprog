// utilidades.cpp
// Demonstra o uso de dbTimer(), dbRandomize() e dbRnd()
#include "DarkGDK.h"

// Rel�gio multifuncional do monstro
// Controla tempo de aparecimento do monstro e quantidade
struct Relogio
{
	int tmpInicial;	  // tempo inicial
	int tmpFinal;     // tempo final
	int tmpDecorrido; // tempo decorrido
	int gatilho;      // gatilho de controle do disparo do evento
	int limite;       // Limite de monstros na tela
	int qtd;          // Quantidade de monstros na tela
};


// Prot�tipo das fun��es
void initsys();						 // inicializa o sistema
void utilidade();					 // Testa fun��es �teis
void coloca_monstro(int monstro);	 // Coloca monstro na tela
bool verifica_relogio(Relogio *rel); // Verifica relogio do monstro

// Nossos monstrinhos imagin�rios
int monstro_a = 1;
int monstro_b = 2;

// Cores
const int nPreto	= 0;
const int nBranco	= 0xFFFFFF;
const int nAzul		= 0x0000FF;
const int nVermelho = 0xFF0000;
const int nVerde	= 0x00FF00;

// Rel�gios dos monstros a e b
Relogio rel_ma;
Relogio rel_mb;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk

initsys();  

// Configura rel�gio do monstro A
rel_ma.tmpInicial	= dbTimer();
rel_ma.gatilho		= 500;
rel_ma.tmpDecorrido = 0;
rel_ma.limite		= 7;
rel_ma.qtd			= 0;

// Configura rel�gio do monstro B
rel_mb.tmpInicial	= dbTimer();
rel_mb.gatilho		= 800;
rel_mb.tmpDecorrido = 0;
rel_mb.limite		= 12;
rel_mb.qtd			= 0;

while ( LoopGDK ( ) ) { 

utilidade();
 dbSync ( );
 } // fim do while

return;
} // fim da fun��o: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta fun��o inicializa o sistema
dbSyncOn( ); dbSyncRate (60);
dbCLS(nBranco); 
dbSetWindowTitle("utilidades.cpp"); 
dbSetTextOpaque();

// Inicializa gerador de n�meros aleat�rios
dbRandomize( dbTimer() );

} // fim da fun��o: initsys()

void utilidade() {	
 // Coloca monstro se gatilho de tempo foi atingido!
 if (verifica_relogio(&rel_ma) == true)
	coloca_monstro(monstro_a);

 // Coloca monstro se gatilho de tempo foi atingido!
 if (verifica_relogio(&rel_mb))
	coloca_monstro(monstro_b);
	
} // utilidade().fim


void coloca_monstro(int monstro)
{
int xpos, ypos;
// Gera uma posi��o aleat�rio com dbRnd()
xpos = dbRnd(600);
ypos = dbRnd(460);

 // Coloca monstro A
 if (monstro == 1)
 {
 dbInk (nPreto, nVermelho);
 dbText (xpos, ypos, "monstro_a");
 }// endif

 // Coloca monstro B
 if (monstro == 2)
 {
 dbInk (nPreto, nVerde);
 dbText (xpos, ypos, "monstro_b");
 } // endif
} // coloca_monstro().fim


bool verifica_relogio(Relogio *rel)
{
 // Encerre aqui se a quantidade alcan�ou o limite 
 if (rel->qtd >= rel->limite)
  {
	  return false;
  } // endif

 // Calcula tempo decorrido deltaTempo = tempoFinal - tempoInicial
 rel->tmpFinal = dbTimer();	
 rel->tmpDecorrido = rel->tmpFinal - rel->tmpInicial;

  // Avisa 'verdadeiro' se o tempo de gatilho foi atingido
  if (rel->tmpDecorrido >= rel->gatilho)
  {
  rel->tmpInicial = dbTimer();
  rel->qtd++;
  return true;
  } // endif
  else
  {
  return false;
  } // else
} // verifica_relogio().fim
