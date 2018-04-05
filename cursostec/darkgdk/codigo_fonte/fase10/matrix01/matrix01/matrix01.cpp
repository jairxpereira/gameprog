// matrix01.cpp
// Esse programa apresenta a cria��o de terreno (matrix)
#include "DarkGDK.h"

// Prot�tipo das fun��es
void initsys();				// inicializa o sistema

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk
initsys();  
while ( LoopGDK ( ) ) { 	
dbSync ( );
 } // fim do while
return;
} // fim da fun��o: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta fun��o inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("matrix01.cpp"); 

// Cria��o b�sica de um terreno com o posicionamento da c�mera para visualiz�-lo
dbMakeMatrix (1,1000,1000,4,3);
dbPositionCamera (950, 300, 1500);
dbPointCamera(10,-500, -500);

} // fim da fun��o: initsys()