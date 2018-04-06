// janela02.cpp
// Esse programa mostra como obter a lista de video dispon�veis
#include "DarkGDK.h"
void initsys();
void tst_janela02();

// Cores
int nPreto = 0;
int nBranco = 0xFFFFFF;

void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk

initsys();  
tst_janela02();    

while ( LoopGDK ( ) ) {     
 dbSync ( );
 } // fim do while

return;
} // fim da fun��o: DarkGDK

void initsys() {    
// Esta fun��o inicializa o sistema
dbSyncOn( ); dbSyncRate (60);
dbSetWindowOn();				// Definindo modo janela
dbSetDisplayMode(800,600,32);   // Definindo o modo de v�deo

dbCLS(nBranco); 
dbInk(nPreto, nBranco);

// Configurando a janela
dbSetWindowTitle("janela02.cpp"); 
dbSetWindowSize (800,600); 
dbSetWindowPosition (320,20);

} // fim da fun��o: initsys()

void tst_janela02 () {
// Esta fun��o obt�m a lista de modos de video dispon�veis
char txt[255];

// Propriedades de v�deo
int nLargura, nAltura, nProfundidade;

int ncx;	// Nosso contador b�sico
int nqtd;	// Aqui vai a quantidade total de modos de v�deo

dbPerformChecklistForDisplayModes();	// Pesquisa modos de v�deo...
nqtd = dbChecklistQuantity();			// ...e retorna quantidade total dispon�vel

// Cabe�alho de apresenta��o da lista
dbPrint(); dbPrint(" #ncx: (largura, altura, profundidade)");
dbPrint("------------------------------------------");

 for (ncx=1; ncx < nqtd; ncx++) {
 // Obt�m largura, altura e profunidade do modo de v�deo #ncx
 nLargura = dbChecklistValueA(ncx);
 nAltura = dbChecklistValueB(ncx);
 nProfundidade = dbChecklistValueC(ncx);

 // Mostra capacidade de v�deo
 sprintf(txt, " #%d: (%d, %d, %d)", ncx, nLargura, nAltura, nProfundidade);
 dbPrint (txt);
 } // fim do for

} // fim tst_janela02()