	// string02.cpp
	// Esse programa mostra como usar a fun��o dbPerformChecklistForFonts()
	// Sempre que usar a Dark GDK voc� deve garantir a inclus�o desse arquivo 
	#include "DarkGDK.h"
	void initsys();
	void tst_texto_02();

	//  Eis aqui o ponto de entrada da sua aplica��o
	void DarkGDK ( void ) {
	initsys();      
	
	tst_texto_02();
	while ( LoopGDK ( ) ) {     
	dbSync ( );
	 } // fim do while     
	
	return;
	} // fim da fun��o: DarkGDK
	
	// ----------------------------------------------------------------------------
	// Inicializa��o b�sica do sistema
	void initsys() {
	int nBranco = 0xFFFFFF;
	int nPreto = 0;
	dbCLS(nBranco);
	dbInk(nPreto, nBranco);
	dbSetWindowTitle ("string02.cpp");  
	// Configurando o video para a maxima performance a 60 fps
	dbSyncOn   ( );
	dbSyncRate ( 60 );
	} // fim da fun��o: initsys()
	
	// ----------------------------------------------------------------------------
	// txt_texto_02() Segunda bateria de testes de texto
	void tst_texto_02() {

	int nqtd;		// Quantidade de fontes no sistema
	int ncx;		// Nosso contador b�sico
	char txt[255];	// Mem�ria tempor�ria para texto
	
	dbPerformChecklistForFonts();
	nqtd = dbChecklistQuantity();

	sprintf(txt, "(...) Quantidade de fontes no sistema: %d", nqtd);
	dbText (10,100,txt);

	for (ncx=1; ncx < 7; ncx++) dbPrint ( dbChecklistString (ncx) );

	} // fim da fun��o: tst_texto_02()
	
