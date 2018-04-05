// bitmap01.cpp
// Esse programa testa funções de bitmap
#include "DarkGDK.h"

void initsys();						// inicializa o sisema
void tst_bitmap01();				// testa funções de bitmap
void virar_bmp(void);				// Vira a imagem bitmap
void espelhar_bmp(void);			// Espelha a imagem bitmap
void menu(void);					// Apresenta um menu de opções
void info_bmp(void);				// Mostra informações sobre o bitmap
void carregar_mostrar_bmp(void);	// Carrega e mostra o bitmap
int igual(char *stecla, char *txt); // Compara duas strings



// Copia parte de um bitmap para uma área de destino
void tst_copiar_bmp(int nEsquerda, int nTopo, int nDireita, int nFundo);

// Cores
const int nPreto = 0;
const int nBranco = 0xFFFFFF;


// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

initsys();  

carregar_mostrar_bmp(); 

while ( LoopGDK ( ) ) {     

	menu();
	tst_bitmap01();
	info_bmp();

	if (dbEscapeKey()==1) {
		MessageBox (0,"Saindo do programa", "bitmap01.cpp", MB_OK);
		dbDeleteBitmap(1);
		return;
	} // fim do if

 dbSync ( );
 } // fim do while

return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( ); dbSyncRate (60);
dbDisableEscapeKey();

dbCLS(nBranco); 
dbInk(nPreto, nBranco);
// Configurando a janela
dbSetWindowTitle("bitmap01.cpp"); 
dbSetTextOpaque();
} // fim da função: initsys()

// ----------------------------------------------------------------------------
void tst_bitmap01 () {
	char *stecla;

	stecla = dbInKey(); 
	
	if (igual(stecla,"l")) {
		carregar_mostrar_bmp();		
	} // fim do if

	if (igual(stecla,"f")) {
	virar_bmp();
	} // fim do if

	if (igual(stecla,"m")) {
		espelhar_bmp();			
	} // fim do if

	if (igual(stecla,"c")) {
		tst_copiar_bmp(0,0,127,127);		
	} // fim do if

	if (igual(stecla,"b")) {
		dbBlurBitmap(1,5);
		dbCopyBitmap(1,0);
	} // fim do if

	if (igual(stecla,"d")) {
		dbFadeBitmap(1,80);
		dbCopyBitmap(1,0);
	} // fim do if

} // fim tst_bitmap01()

// ----------------------------------------------------------------------------
void menu(void) {		
	dbSetCurrentBitmap(0);	
	dbText( 10, 300, "l- dbLoadBitmap()"); dbText( 210, 300, "d- dbFadeBitmap()");
	dbText( 10, 320, "m- dbMirrorBitmap()"); dbText( 210, 320, "b- dbBlurBitmap()");
	dbText( 10, 340, "f- dbFlipBitmap()"); dbText( 210, 340, "c- dbCopyBitmap()");	
} // fim menu()



// ----------------------------------------------------------------------------
int igual(char *stecla, char *txt) {
	int res=0;
	res = strcmp(stecla, txt);
	return !res;
} // fim igual()

// ----------------------------------------------------------------------------
void carregar_mostrar_bmp(void) {
dbLoadBitmap("c://gameprog//gdkmedia//bitmap//textura.bmp",1);
dbCopyBitmap(1,0);

} // fim loadbmp()

// ----------------------------------------------------------------------------
void tst_copiar_bmp(int nEsquerda, int nTopo, int nDireita, int nFundo) {	
	const int bmpFonte = 1;
	const int bmpDestino = 0;

	int esquerdaAlvo = 300;
	int topoAlvo = 0;	
	int direitaAlvo = 428;
	int fundoAlvo = 120;
	
	dbCopyBitmap(bmpFonte,
			 nEsquerda, nTopo, nDireita,nFundo,
			 bmpDestino,
			 esquerdaAlvo, topoAlvo, direitaAlvo, fundoAlvo);
} // fim tst_copiar_bmp


// ----------------------------------------------------------------------------
void virar_bmp() {
	dbFlipBitmap(1);
	dbCopyBitmap(1,0);		
} // fim virar_bmp()


// ----------------------------------------------------------------------------
void espelhar_bmp() {
	dbMirrorBitmap(1);
	dbCopyBitmap(1,0);	
} // fim espelhar_bmp()


// ----------------------------------------------------------------------------
void info_bmp() {
	char txt[255];
	int nlargura, nAltura, nprofundidade;
	int nvirado, nEspelhado;	
	
	// Obtendo os dados do bitmap 1
	nlargura = dbBitmapWidth(1);
	nAltura = dbBitmapHeight(1);
	nprofundidade = dbBitmapDepth(1);
	nvirado = dbBitmapFlipped(1);
	nEspelhado = dbBitmapMirrored(1);

	// Mostrando os dados
	dbSetCurrentBitmap(0);
	sprintf(txt, "Largura: %d Altura:%d Profundidade: %d", 
		nlargura, nAltura, nprofundidade);
	dbText (10,260, txt);
	sprintf(txt, "Virado: %d Espelhado: %d", nvirado, nEspelhado);
	dbText (10,280, txt);
} // fim info_bmp()
