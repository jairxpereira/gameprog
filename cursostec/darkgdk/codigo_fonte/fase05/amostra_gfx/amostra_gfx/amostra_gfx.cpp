// amostra_gfx.cpp
// Esse programa exemplifica como aplicar efeitos especiais sobre a imagem 2D
#include "DarkGDK.h"

// Prot�tipo das fun��es
void initsys();					// inicializa o sistema
void gfx_teste();				// Teste de efeito gr�fico
int rgb_efeito(int *pImagem);	// Retorna um tom de cinza e muda o branco para azul

// Cores
const int nPreto = 0;
const int nBranco = 0xFFFFFF;
const int nAzul = 255;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk

initsys();  

gfx_teste();

while ( LoopGDK ( ) ) {     
	
 dbSync ( );
 } // fim do while

return;
} // fim da fun��o: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta fun��o inicializa o sistema
dbSyncOn( ); dbSyncRate (60);
dbCLS(nBranco); 
dbSetWindowTitle("amostra_gfx.cpp"); 
} // fim da fun��o: initsys()


// ----------------------------------------------------------------------------
void gfx_teste(void) {
	
	// Vari�veis de trabalho
	int naltura, nlargura, ncx;	
	const int nbmp_fonte = 1;
	const int nbmp_tela = 0;
	const int nbmp_gfx = 3;	
	
	int *pImagem = 0;		// Ponteiro para acessar mem�ria com imagem
	
	// Carrega e mostra o bitmap que vai ser manipulado
	dbLoadBitmap ("c:\\gameprog\\gdkmedia\\bitmap\\gfx_sample.bmp", nbmp_fonte);
	dbCopyBitmap(nbmp_fonte, nbmp_tela);

	// Acessa configura��o do bitmap
	naltura = dbBitmapHeight(nbmp_fonte);
	nlargura = dbBitmapWidth(nbmp_fonte);
		
	// Esse comando cria um bloco de mem�ria-bitmap a partir de um bitmap
	dbMakeMemblockFromBitmap(1, nbmp_fonte);

	// Obt�m o endere�o do bloco de mem�ria
	pImagem = (int *) dbGetMemblockPtr(1);

	// Vamos pular o cabe�alho do bloco
	pImagem++;	// pula primeira posi��o: largura do bitmap
	pImagem++;	// pula segunda posi��o: altura do bitmap
	pImagem++;	// pula terceira posi��o: profundidade de cor
	
	
	// Vamos hacker o bloco de mem�ria-bitmap
	for (ncx=0; ncx < ( naltura * nlargura ); ncx++)
	{	
		// Passa a cor do ponto para rgb_efeito() que retorna esse valor alterado
		*pImagem = rgb_efeito ( pImagem);
		
		// Avan�a o ponteiro para a frente
		pImagem++;		

	}

	// Esse comando cria um bitmap a partir de bloco de mem�ria-bitmap
	dbMakeBitmapFromMemblock(nbmp_gfx,1);

	// Vamos mostrar nosso bitmap que sofreu um efeito gr�fico
	dbCopyBitmap(nbmp_gfx,0,0,nlargura, naltura, nbmp_tela,nlargura+10,0,nlargura*2, naltura );

	// Vamos liberar a mem�ria do sistema
	dbDeleteMemblock(1);
	dbDeleteBitmap(nbmp_fonte);
	dbDeleteBitmap(nbmp_gfx);

} // gfx_teste().fim


// ----------------------------------------------------------------------------
int rgb_efeito(int *pImagem) {
	
	// Var�aveis de trabalho
	int soma = 0;
	int media = 0;
	int ncor, r, g, b;	

	// Converte um branco para um tom de azul
	if (*pImagem == 0xFFFFFF)
	{
	*pImagem = nAzul;
	return *pImagem;
	} // endif	

	// Extrai os valores RGB
	r = dbRGBR(*pImagem);
	g = dbRGBR(*pImagem);
	b = dbRGBR(*pImagem);

	// Processa a cor
	soma = r + g + b;
	media = soma / 3;
	ncor = dbRGB(media, media, media);

	return ncor;
} // rgb_efeito().fim


