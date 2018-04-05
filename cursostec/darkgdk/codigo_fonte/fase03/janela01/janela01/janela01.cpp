// janela01.cpp
// Esse programa ilustra configuração da janela
#include "DarkGDK.h"
void initsys();
void tst_janela01();

int nPreto = 0;
int nAzul = 0x0000FF;
int nBranco = 0xFFFFFF;


void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

initsys();  
tst_janela01();    

while ( LoopGDK ( ) ) {     
 dbSync ( );
 } // fim do while

return;
} // fim da função: DarkGDK

void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( ); dbSyncRate (60);
} // fim da função: initsys()

void tst_janela01 () {
// Esta função demonstra as principais funções de janela
char txt[255];
int nLargura, nAltura, nProfundidade;

dbSetWindowOn();				// Definindo modo janela
dbSetDisplayMode(800,600,32);   // Definindo o modo de vídeo

dbCLS(nBranco); 
dbInk(nPreto, nBranco);

// Configurando a janela
dbSetWindowTitle("janela01.cpp"); 
dbSetWindowSize (800,600); 
dbSetWindowPosition (320,20);

// Obtendo a configuração de vídeo
nLargura = dbScreenWidth(); 
nAltura = dbScreenHeight(); 
nProfundidade = dbScreenDepth();

// Configurando a fonte
dbSetTextFont ("Courier New"); 
dbSetTextSize(20);

// Exibindo a configuração de vídeo
dbPrint();
sprintf(txt, " Resolucao da tela: (%d colunas x %d linhas)", nLargura, nAltura);
dbPrint(txt);
sprintf(txt, " Capacidade de cor: %d bits RGB-Alpha", nProfundidade);
dbPrint(txt);
} // fim tst_janela01()
