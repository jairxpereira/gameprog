// luz01.cpp
// Esse programa mostra comandos b�sicos de luz
#include "DarkGDK.h"
#include "windows.h"

// Prot�tipo das fun��es
void initsys();			// inicializa o sistema
void teclado();			// Interpreta o teclado
void texturizar();		// Texturiza a matrix
void menu();			// Mostrar comandos para controle de luz

// Flag ou bandeira para terminar a aplica��o
int terminar = 0;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk

// Carrega e texturiza um modelo 3D
dbSetDir ("c:\\gameprog\\gdkmedia\\Modelos\\German");
dbLoadImage ("german.dds",2);
dbLoadObject ("H-German-Idle.x",1);
dbTextureObject (1,2);

// Inicializa o ambiente gr�fico
initsys();

// Prepara o terreno
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbMakeMatrix (1,2000,10000,10,50);
dbPrepareMatrixTexture (1,1,2,2);
texturizar();
dbSyncOn();

// Ajusta escala do objeto 
dbScaleObject (1,12000,12000,12000);


// Ajusta c�mera e posiciona objeto na cena
dbPositionCamera (1005, 475, -600);
dbPositionObject (1, 970, 300, -185);

// Looping principal
while ( LoopGDK ( ) ) {
 if (terminar == 0) teclado();
	dbSync ( );

	if (terminar == 1)
	{
		dbDeleteImage (1);	dbDeleteMatrix (1);
		dbDeleteObject (1);
		return;
	} // endif
 } // fim do while
return;
} // fim da fun��o: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {
// Esta fun��o inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("luz01.cpp");
dbDisableEscapeKey();
dbSyncRate(60);
} // initsys().fim


// ----------------------------------------------------------------------------
// texturizar() - Aplica aleat�riamente a textura na matrix
void texturizar() {
int linha, coluna;
for (coluna = 0; coluna < 10; coluna++)
{
	for (linha = 0; linha < 50; linha++)
	{
		int tile = dbRnd(4) + 1;
		dbSetMatrixTile (1, coluna, linha, tile);
	} // linha
} //coluna

dbUpdateMatrix (1);

} // texturizar().fim


// ----------------------------------------------------------------------------
// teclado() - L� o teclado e executa comandos do usu�rio
void teclado() {
	
	// L� o teclado
	char *stecla="??";
	stecla = dbInKey();

	if (dbEscapeKey()) terminar = 1;

	// Liga e desliga a luz com sua influ�ncia
	if (!strcmp(stecla, "1")) dbHideLight(0);
	if (!strcmp(stecla, "2")) dbShowLight(0);
    
	// Define intensidade da luz
	if (!strcmp(stecla, "3")) dbSetAmbientLight(100);
	if (!strcmp(stecla, "4")) dbSetAmbientLight(20);

	// Define as cores da luz ambiente
	if (!strcmp(stecla, "5")) dbColorAmbientLight( 0xFF0000 );
	if (!strcmp(stecla, "6")) dbColorAmbientLight( 0x00FF00 );
	if (!strcmp(stecla, "7")) dbColorAmbientLight( 0x0000FF );	

	// Resseta o teclado
	strcpy(stecla,"??");

	// Mostra informa��es de op��es
	menu();

} // teclado().fim


void menu(){

// Vari�veis de trabalho para mostrar texto
int xpos = 10;
int ypos = 10;
int coluna = xpos;
int linha = ypos;
int espaco_entrelinhas = 20;
int ncx = 0;

// Nossa lista de op��es
char *slista[] = {"1- dbHidelight(0)",
"2- dbShowLight(0)", "3- dbSetAmbientLight(100)",
"4- dbSetAmbientLight(20)", 
"5- dbColorAmbientLight(0xFF0000) - vermelho",
"6- dbColorAmbientLight(0x00FF00) - verde",
"7- dbColorAmbientLight(0x0000FF) - azul)"} ;

// Mostre a lista
// dbInk (nAzul, nBranco);
 for (ncx = 0; ncx < 7; ncx++) {
 linha = ypos + ( ncx * espaco_entrelinhas );
 dbText (coluna, linha, slista[ncx]);
 } // fim do for(ncx)
} // menu().end

