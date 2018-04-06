// string01.cpp
// Esse programa ilustra o uso de funções de texto
// Sempre que usar a Dark GDK você deve garantir a inclusão desse arquivo 
#include "DarkGDK.h"
void initsys();
void tst_texto_01();


//  Eis aqui o ponto de entrada da sua aplicação
void DarkGDK ( void ) {


	initsys();	

	
	// Nosso looping principal
	while ( LoopGDK ( ) ) {
		
		
		tst_texto_01();

		
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
	dbSetWindowTitle ("string01.cpp");
	

	// Configurando o video para a maxima performance a 60 fps
	dbSyncOn   ( );
	dbSyncRate ( 60 );

} // fim da função: initsys()


void tst_texto_01() {

// configuração padrão das fontes
int nPreto = 0;
int nAzul = 0x0000FF;
int nBranco = 0xFFFFFF;
dbInk(nPreto, nBranco);
dbSetTextFont("Courier New"); dbSetTextSize(20);
dbSetTextToNormal(); dbSetTextTransparent();

dbText (100,10, "dbText(100,10) efeito");
dbCenterText (320,40, "dbCenter(320,40) efeito");

dbSetTextFont("Verdana");
dbText (100,70, "dbSetTextFont('Verdana') efeito");
dbSetTextFont("Courier New");

dbSetTextToItalic();
dbText (100,100, "dbSetTextToItalic() efeito");

dbSetTextToNormal();
dbText (10,130, "dbSetTextToNormal() efeito");

dbSetTextToNormal();
dbSetTextToBold();
dbText (100,170, "dbSetTextToBold() efeito");

dbSetTextToNormal();
dbSetTextToBoldItalic();
dbText (10,200, "dbSetTextToBoldItalic() efeito");

dbSetTextToNormal();
dbSetTextSize(40);
dbText (10,250, "dbSetTextSize(40) efeito");
dbSetTextSize(20);

dbInk (nBranco, nAzul);
dbSetTextOpaque();
dbText (10,290, "dbSetTextOpaque() efeito");

dbInk (nAzul, nBranco);
dbSetTextTransparent();
dbText (10,320, "dbSetTextTransparent() efeito");
}

