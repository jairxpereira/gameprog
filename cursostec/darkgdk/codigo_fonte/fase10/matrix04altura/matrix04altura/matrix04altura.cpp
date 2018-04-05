// matrix04altura.cpp
// Esse programa mostra como alterar a altura de um vértice da matrix
// permitindo assim produzir elevações e depressões no terreno

#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys();  

// Criação básica de um terreno com o posicionamento da câmera para visualizá-lo
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbMakeMatrix (1,1000,1000,5,5);
dbPrepareMatrixTexture (1,1,2,2);
dbFillMatrix (1,10,1);

// Texturização individual
dbSetMatrixTile (1, 1, 1, 2);
dbSetMatrixTile (1, 2, 1, 2);
dbSetMatrixTile (1, 1, 0, 3);
dbSetMatrixTile (1, 2, 0, 4);

// Produzindo uma depressão e uma elevação
dbSetMatrixHeight (1,2,1,-60);
dbSetMatrixHeight (1,4,1,160);

// Atualização da matrix e configuração da câmera
dbUpdateMatrix (1);
dbPositionCamera (300, 200, -600);
dbRotateCamera (0,10,10);

while ( LoopGDK ( ) ) { 	
	dbSync ( );
 } // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("matrix04altura.cpp"); 
} // initsys().fim


