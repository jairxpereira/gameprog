// tst_Sound.cpp
// Esse programa mostra como usar as funções de som
#include "DarkGDK.h"

// Protótipo das funções
void initsys();			// inicializa o sistema
void tst_som();			// Testa funções de som
void menu();			// Mostra um menu de opções na tela

// Cores
const int nPreto = 0;
const int nBranco = 0xFFFFFF;
const int nAzul = 0x0000FF;
int terminar_app = 0;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

initsys();  

// Carrega um som para teste
dbLoadSound ("c:\\gameprog\\gdkmedia\\som\\amostra_som.wav",1);

while ( LoopGDK ( ) ) { 
	menu();
	tst_som();

	if (terminar_app == 1) return;
		
 dbSync ( );
 } // fim do while

return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbCLS(nBranco); 
dbSetWindowTitle("tst_som.cpp"); 
dbSetTextOpaque();
} // fim da função: initsys()

// ----------------------------------------------------------------------------
void menu() {
// Variáveis de trabalho para mostrar texto
int xpos = 260;
int ypos = 10;	
int coluna = xpos;
int linha = ypos;
int espaco_entrelinhas = 20;
int ncx = 0;
	
// Nossa lista de opções
char *slista[8] = {"1- dbPlaySound(1)", 
"4- dbStopSound(1)", 
"q- para sair ou botao direito do mouse",
"6- dbLoopSound(1)", 
"8- dbPauseSound(1)", 
"9- dbResumeSound(1)",
"a- dbSetSoundVolume(1,70)", 
"--------------------------------------"}; // fim da lista

// Mostre a lista
dbInk (nAzul, nBranco);
for (ncx = 0; ncx < 8; ncx++) {
	linha = ypos +  ( ncx * espaco_entrelinhas );
	dbText (coluna, linha, slista[ncx]);
} // fim do for(ncx)


} // menu().end


// ----------------------------------------------------------------------------
void tst_som() {		
// Execute enquanto não for pressionado "q" ou o botão direito do mouse
while (dbMouseClick() != 2) {
 char *tecla = dbInKey();

 if (!strcmp(tecla,"1")) dbPlaySound (1);		
	
 if (!strcmp(tecla,"4")) dbStopSound (1);		

 if (!strcmp(tecla,"q"))break;

 if (!strcmp(tecla,"6")) dbLoopSound (1);	

 if (!strcmp(tecla,"8")) dbPauseSound(1);	
	
 if (!strcmp(tecla,"9")) dbResumeSound(1);
		
 if (!strcmp(tecla,"a")) dbSetSoundVolume(1,70); 

 dbInk (nPreto, nBranco);
 dbText (10,10,dbStr (dbSoundExist(1) )); dbText (50,10, "dbSoundExist(1)" );
 dbText (10,30,dbStr (dbSoundPlaying(1)  )); dbText (50,30, "dbSoundPlaying(1)" );
 dbText (10,50,dbStr (dbSoundLooping(1)  )); dbText (50,50, "dbSoundLooping(1)" );
 dbText (10,70,dbStr (dbSoundPaused(1)  )); dbText (50,70, "dbSoundPaused(1)" ); 
 dbText (10,90, "    "); // Limpe o espaço antes de imprimir
 dbText (10,90,dbStr (dbSoundVolume(1)  )); dbText (50,90, "dbSoundVolume(1)" );
 dbSync();   

 } // endwhile

// Delete os arquivos utilizados
if (dbSoundExist(1)) dbDeleteSound (1);

terminar_app = 1;	
} // tst_som().end