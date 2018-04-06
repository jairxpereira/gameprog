// desenho2d01.cpp
// Esse programa testa funções de desenho 2d
#include "DarkGDK.h"

void initsys();						// inicializa o sistema
void tst_desenho2d();				// Testa funções 2d

// Cores
const int nPreto = 0;
const int nBranco = 0xFFFFFF;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

initsys();  

while ( LoopGDK ( ) ) {     
	tst_desenho2d();
 dbSync ( );
 } // fim do while

return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( ); dbSyncRate (60);
dbCLS(nBranco); 
dbSetWindowTitle("desenho2d01.cpp"); 
} // fim da função: initsys()


// ----------------------------------------------------------------------------
void tst_desenho2d() {
	// variáveis de trabalho
	char txt[255];
	int cor, r, g, b;
	int x = 371, y = 21;

	// Elenco de cores básicas
	int nAzul = dbRGB(0,0,255);
	int nVerde = dbRGB(0,255,0);
	int nVermelho = dbRGB(255,0,0);
	int nMagenta = dbRGB(255,0,255);

	dbInk(nPreto, nBranco);

	// Desenha olho com linha preta e fundo branco
	dbCircle(160,120,80);
	dbCircle(160,120,30);
	dbEllipse (160,120,160,80);
	dbLine (0,120,320,120);	

	// Desenha um pontinho no olho
	dbDot(150,110); dbDot(151,110);
	dbDot(150,111); dbDot(151,111);
	
	// Desenha sobrancelha azul
	dbInk(nAzul, nBranco);
	dbBox (10,10,320,30);
	
	// Desenha caixa multicolorida
	dbBox (370,20, 470,250,	nAzul, nVerde, nVermelho, nMagenta);
	
	// Verificação de cor de determinado ponto (x,y);
	cor = dbPoint (x, y);
	r = dbRGBR(cor);
	g = dbRGBG(cor);
	b = dbRGBB(cor);	
	sprintf (txt, "Cor no ponto (%d,%d): (%d, %d, %d)", x, y, r, g, b);
	// Sinaliza o ponto verificado
	dbCircle (x,y,20); 	dbCircle (x,y,10); dbLine (x,y,250,230);
	dbText (20,230, txt);

} // fim tst_desenho2d()