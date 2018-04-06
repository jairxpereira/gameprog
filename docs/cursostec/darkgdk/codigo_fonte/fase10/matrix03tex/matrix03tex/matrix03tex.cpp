// matrix03tex.cpp
// Esse programa mostra como texturizar individualmente cada polígono
// do terreno (matrix)
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys();  

// Criação básica de um terreno com o posicionamento da câmera para visualizá-lo
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbMakeMatrix (1,1000,1000,4,3);
dbPrepareMatrixTexture (1,1,2,2);
dbFillMatrix (1,10,1);

dbSetMatrixTile (1, 1, 1, 2);
dbSetMatrixTile (1, 2, 1, 2);
dbSetMatrixTile (1, 1, 0, 3);
dbSetMatrixTile (1, 2, 0, 4);

dbUpdateMatrix (1);
dbPositionCamera (500, 200, -600);

while ( LoopGDK ( ) ) { 	
	dbSync ( );
 } // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("matrix03tex.cpp"); 
} // initsys().fim

