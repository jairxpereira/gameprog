// RolamentoTextura.cpp
// Esse programa mostra como rolar a textura através das funções shift cima, baixo,
// esquerda, direita; e mostra efeito ghost e wireframe
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void teclado();				// Interpreta o teclado
void texturizar();			// Texturiza a matrix

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys();  

// Criação básica de um terreno com o posicionamento da câmera para visualizá-lo
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbMakeMatrix (1,2000,10000,10,50);
dbPrepareMatrixTexture (1,1,2,2);
texturizar();

while ( LoopGDK ( ) ) { 
	teclado();
	dbSync ( );
 } // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetDisplayMode (800,600,32);
dbSetWindowSize (800,600);
dbSetWindowTitle("RolamentoTextura.cpp"); 
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

	// Rolagem da textura:
	if (dbUpKey()) dbShiftMatrixUp(1);
	if (dbDownKey()) dbShiftMatrixDown(1);
	if (dbLeftKey()) dbShiftMatrixLeft(1);
	if (dbRightKey()) dbShiftMatrixRight(1);	
	
	// Testando visualização wireframe
	if (!strcmp(stecla, "w")) dbSetMatrixWireframeOn(1);
	if (!strcmp(stecla, "t")) dbSetMatrixWireframeOff(1);

	// Testando efeito ghost (fantasma)
	if (!strcmp(stecla, "g")) dbGhostMatrixOn(1);
	if (!strcmp(stecla, "v")) dbGhostMatrixOff(1);

	// Resseta a textura para recuperar o bug de dbShiftMatrixLeft(1);
	if (!strcmp(stecla, "r")) texturizar();
	
	// Atualiza  e desacelera o atendimento do teclado
	dbUpdateMatrix(1);
	dbText (10,10, "w/t - Liga/Desliga visualizacao Wireframe");
	dbText (10,30, "g/v - Liga/Desliga efeito Ghost");
	dbText (10,50, "r - Re-textura para corrigir bug de dbShiftMatrixLeft(1)");
	dbSleep(100);

	// Resseta o teclado
	strcpy(stecla,"??");

} // teclado().fim