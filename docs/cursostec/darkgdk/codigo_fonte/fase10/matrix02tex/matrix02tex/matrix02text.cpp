// matrix02tex.cpp
// Esse programa mostra como texturizar um terreno (matrix)
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void trocar_textura();		// Troca e atualiza a textura da matrix
int nTile = 2;				// Representa um tipo de textura numa imagem

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys();  

// Criação básica de um terreno com o posicionamento da câmera para visualizá-lo
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbMakeMatrix (1,1000,1000,4,3);
dbPrepareMatrixTexture (1,1,2,2);
dbFillMatrix (1,10,nTile);
dbUpdateMatrix (1);
dbPositionCamera (500, 200, -600);

while ( LoopGDK ( ) ) { 	
	trocar_textura();
	dbSync ( );
 } // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("matrix02tex.cpp"); 
} // initsys().fim


// ----------------------------------------------------------------------------
void trocar_textura() {

	char *stecla = "0";
	float nAltura = 0;

	// Leitura do teclado
	stecla = dbInKey();	

	// Reconfigura a textura conforme a tecla pressionada
	if (!strcmp("1", stecla)) nTile = 1;
	if (!strcmp("2", stecla)) nTile = 2;
	if (!strcmp("3", stecla)) nTile = 3;
	if (!strcmp("4", stecla)) nTile = 4;

	nAltura = nTile * 15;

	// Troca a textura e atualiza a matrix
	if (stecla[0] != 0) {		
		dbFillMatrix (1, nAltura, nTile);
		dbUpdateMatrix (1);
		strcpy (stecla, "0");	// Neutraliza memória e efeito da tecla digitada
	} // endif

	dbText (10,10, "Pressione 1-2-3-4 para mudar a textura");

} // trocar_textura().fim