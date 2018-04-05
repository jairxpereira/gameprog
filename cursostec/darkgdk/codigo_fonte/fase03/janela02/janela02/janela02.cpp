// janela02.cpp
// Esse programa mostra como obter a lista de video disponíveis
#include "DarkGDK.h"
void initsys();
void tst_janela02();

// Cores
int nPreto = 0;
int nBranco = 0xFFFFFF;

void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

initsys();  
tst_janela02();    

while ( LoopGDK ( ) ) {     
 dbSync ( );
 } // fim do while

return;
} // fim da função: DarkGDK

void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( ); dbSyncRate (60);
dbSetWindowOn();				// Definindo modo janela
dbSetDisplayMode(800,600,32);   // Definindo o modo de vídeo

dbCLS(nBranco); 
dbInk(nPreto, nBranco);

// Configurando a janela
dbSetWindowTitle("janela02.cpp"); 
dbSetWindowSize (800,600); 
dbSetWindowPosition (320,20);

} // fim da função: initsys()

void tst_janela02 () {
// Esta função obtém a lista de modos de video disponíveis
char txt[255];

// Propriedades de vídeo
int nLargura, nAltura, nProfundidade;

int ncx;	// Nosso contador básico
int nqtd;	// Aqui vai a quantidade total de modos de vídeo

dbPerformChecklistForDisplayModes();	// Pesquisa modos de vídeo...
nqtd = dbChecklistQuantity();			// ...e retorna quantidade total disponível

// Cabeçalho de apresentação da lista
dbPrint(); dbPrint(" #ncx: (largura, altura, profundidade)");
dbPrint("------------------------------------------");

 for (ncx=1; ncx < nqtd; ncx++) {
 // Obtém largura, altura e profunidade do modo de vídeo #ncx
 nLargura = dbChecklistValueA(ncx);
 nAltura = dbChecklistValueB(ncx);
 nProfundidade = dbChecklistValueC(ncx);

 // Mostra capacidade de vídeo
 sprintf(txt, " #%d: (%d, %d, %d)", ncx, nLargura, nAltura, nProfundidade);
 dbPrint (txt);
 } // fim do for

} // fim tst_janela02()