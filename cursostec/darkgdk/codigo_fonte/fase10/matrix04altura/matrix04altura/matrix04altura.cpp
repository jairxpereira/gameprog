// matrix04altura.cpp
// Esse programa mostra como alterar a altura de um v�rtice da matrix
// permitindo assim produzir eleva��es e depress�es no terreno

#include "DarkGDK.h"

// Prot�tipo das fun��es
void initsys();				// inicializa o sistema

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk
initsys();  

// Cria��o b�sica de um terreno com o posicionamento da c�mera para visualiz�-lo
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbMakeMatrix (1,1000,1000,5,5);
dbPrepareMatrixTexture (1,1,2,2);
dbFillMatrix (1,10,1);

// Texturiza��o individual
dbSetMatrixTile (1, 1, 1, 2);
dbSetMatrixTile (1, 2, 1, 2);
dbSetMatrixTile (1, 1, 0, 3);
dbSetMatrixTile (1, 2, 0, 4);

// Produzindo uma depress�o e uma eleva��o
dbSetMatrixHeight (1,2,1,-60);
dbSetMatrixHeight (1,4,1,160);

// Atualiza��o da matrix e configura��o da c�mera
dbUpdateMatrix (1);
dbPositionCamera (300, 200, -600);
dbRotateCamera (0,10,10);

while ( LoopGDK ( ) ) { 	
	dbSync ( );
 } // fim do while
return;
} // fim da fun��o: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta fun��o inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("matrix04altura.cpp"); 
} // initsys().fim


