// janela02.cpp
// Esse programa mostra como obter a lista de video disponíveis
#include "DarkGDK.h"
void initsys();
void tst_bitmap01();
int igual(char *stecla, char *txt);
void menu(void);
void carregar_mostrar_bmp(void);
void tst_copiar_bmp(int nEsquerda, int nTopo, int nDireita, int nFundo);
void animar(void);
void virar_bmp(void);
void espelhar_bmp(void);

int nciclo = 0;

// Cores
int nPreto = 0;
int nBranco = 0xFFFFFF;

int bmpFonte = 1;
int bmpDestino = 0;

bool bmpCarregado = false;



void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

initsys();  
 

while ( LoopGDK ( ) ) {     
	menu();
	tst_bitmap01();
	animar();
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
dbSetWindowTitle("bitmap01.cpp"); 
dbSetWindowSize (640,480); 
dbSetWindowPosition (20,20);

} // fim da função: initsys()

void tst_bitmap01 () {
	char *stecla;

	stecla = dbInKey(); 
	
	if (igual(stecla,"l")) {
		carregar_mostrar_bmp();		
	} // fim do if

	if (igual(stecla,"f")) {
	
	} // fim do if

	if (igual(stecla,"m")) {
	dbMirrorBitmap(1);
	dbCopyBitmap(1,0);		
	} // fim do if




} // fim tst_bitmap01()

void menu(void) {

	int dx = 10;
	int dy = 500;

	dbText( dx, dy, "l- loadbitmap('textura2x2',0)");

} // fim menu()


int igual(char *stecla, char *txt)
{
	int res=0;
	res = strcmp(stecla, txt);
	return !res;
}

void carregar_mostrar_bmp(void) {
dbLoadBitmap("c://gdkmedia//bitmap//textura.bmp",1);
dbCopyBitmap(1,0);
bmpCarregado = true;
dbSync();
} // fim loadbmp()

void tst_copiar_bmp(int nEsquerda, int nTopo, int nDireita, int nFundo) {	

	int esquerdaAlvo = 300;
	int topoAlvo = 0;
	
	int direitaAlvo = 428;
	int fundoAlvo = 120;

	
	dbCopyBitmap(bmpFonte,
			 nEsquerda, nTopo, nDireita,nFundo,
			 bmpDestino,
			 esquerdaAlvo, topoAlvo, direitaAlvo, fundoAlvo);

	dbSync();
}

void animar(void) {
	if (!bmpCarregado) carregar_mostrar_bmp();
		tst_copiar_bmp(0,0,128,120);
		dbSleep(500);
		tst_copiar_bmp(128,0,255,120);
		dbSleep(500);
		tst_copiar_bmp(0,120,128,248);
		dbSleep(500);
		tst_copiar_bmp(128,128,255,255);
		dbSleep(500);
		
		nciclo = nciclo + 1;

		if (nciclo == 2) virar_bmp();

		if (nciclo == 4) espelhar_bmp();

		if (nciclo >= 6) nciclo = 0;




}  // fim animar();

void virar_bmp() {
	dbFlipBitmap(1);
	dbCopyBitmap(1,0);		
}

void espelhar_bmp() {
	dbMirrorBitmap(1);
	dbCopyBitmap(1,0);	

}


