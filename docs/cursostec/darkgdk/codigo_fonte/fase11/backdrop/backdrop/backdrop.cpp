// backdrop.cpp
// Esse programa mostra como manipular o backdrop e a janela de visualização
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void teclado();				// Interpreta o teclado
void texturizar();			// Texturiza a matrix

int terminar = 0;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys();  

// Criação básica de um terreno 
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbMakeMatrix (1,2000,10000,10,50);
dbPrepareMatrixTexture (1,1,2,2);
texturizar();

// Looping principal
while ( LoopGDK ( ) ) { 
	if (terminar == 0) teclado();
	dbSync ( );

	if (terminar == 1)
	{
		dbDeleteImage (1);	dbDeleteMatrix (1);			
		return;
	} // endif
 } // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("backdrop.cpp"); 
dbSetTextOpaque();
dbDisableEscapeKey();
dbSetCameraView (20,50,620, 460);
} // initsys().fim


// ----------------------------------------------------------------------------
// texturizar() - Aplica aleatóriamente a textura na matrix
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
dbPositionCamera (1005, 475, -600);
} // texturizar().fim


// ----------------------------------------------------------------------------
// teclado() - Lê o teclado e executa comandos do usuário
void teclado() {
	
	// Lê o teclado
	char *stecla="??";	
	stecla = dbInKey();

	if (dbEscapeKey()) terminar = 1;	

	if (!strcmp(stecla, "1")) dbColorBackdrop ( dbRGB (255,0,0) );
	if (!strcmp(stecla, "2")) dbColorBackdrop ( dbRGB (0,255,0) );
	if (!strcmp(stecla, "3")) dbClearCameraView (0);
	if (!strcmp(stecla, "0")) dbBackdropOff();
	if (!strcmp(stecla, "9")) dbBackdropOn();

	if (dbKeyState(201)) {
	dbTurnCameraLeft(1);	// page_up
	} // endif

	if (dbKeyState(209)) {
	dbTurnCameraRight(1);	// page_down;
	} // endif		
	
	// Resseta o teclado
	strcpy(stecla,"??");	

	// Mostra informação
	dbText (10,10, "9/0- Liga/Desliga o backdrop  2/1- Verde/Vermelho 3-Limpa a janela");
	dbText (10,30, "page-up/page_down gira a camera");

} // teclado().fim