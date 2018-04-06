// matrix01.cpp
// Esse programa apresenta a criação de terreno (matrix)
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys();  
while ( LoopGDK ( ) ) { 	
dbSync ( );
 } // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("matrix01.cpp"); 

// Criação básica de um terreno com o posicionamento da câmera para visualizá-lo
dbMakeMatrix (1,1000,1000,4,3);
dbPositionCamera (950, 300, 1500);
dbPointCamera(10,-500, -500);

} // fim da função: initsys()