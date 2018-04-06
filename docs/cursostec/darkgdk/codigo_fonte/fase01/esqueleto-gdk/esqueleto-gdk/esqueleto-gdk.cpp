// Sempre que usar a Dark GDK você deve garantir a inclusão desse arquivo 
#include "DarkGDK.h"
void initsys();


//  Eis aqui o ponto de entrada da sua aplicação
void DarkGDK ( void ) {


	initsys();	

	
	// Nosso looping principal
	while ( LoopGDK ( ) ) {
		
		
		dbText (50,50, "DarkGdk");
		
		// Atualize a tela. 
		dbSync ( );

	} // fim do while principal
	
	
	// Retorne ao Sistema Windows
	return;
} // fim da função: DarkGDK

void initsys() {

	int nBranco = 0xFFFFFF;
	int nPreto = 0;
	dbCLS(nBranco);
	dbInk(nPreto, nBranco);
	dbSetWindowTitle ("esqueleto-gdk.cpp");
	

	// Configurando o video para a maxima performance a 60 fps
	dbSyncOn   ( );
	dbSyncRate ( 60 );

} // fim da função: initsys()
