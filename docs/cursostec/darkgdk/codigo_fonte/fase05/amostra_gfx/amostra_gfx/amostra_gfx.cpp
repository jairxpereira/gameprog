// amostra_gfx.cpp
// Esse programa exemplifica como aplicar efeitos especiais sobre a imagem 2D
#include "DarkGDK.h"

// Protótipo das funções
void initsys();					// inicializa o sistema
void gfx_teste();				// Teste de efeito gráfico
int rgb_efeito(int *pImagem);	// Retorna um tom de cinza e muda o branco para azul

// Cores
const int nPreto = 0;
const int nBranco = 0xFFFFFF;
const int nAzul = 255;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

initsys();  

gfx_teste();

while ( LoopGDK ( ) ) {     
	
 dbSync ( );
 } // fim do while

return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( ); dbSyncRate (60);
dbCLS(nBranco); 
dbSetWindowTitle("amostra_gfx.cpp"); 
} // fim da função: initsys()


// ----------------------------------------------------------------------------
void gfx_teste(void) {
	
	// Variáveis de trabalho
	int naltura, nlargura, ncx;	
	const int nbmp_fonte = 1;
	const int nbmp_tela = 0;
	const int nbmp_gfx = 3;	
	
	int *pImagem = 0;		// Ponteiro para acessar memória com imagem
	
	// Carrega e mostra o bitmap que vai ser manipulado
	dbLoadBitmap ("c:\\gameprog\\gdkmedia\\bitmap\\gfx_sample.bmp", nbmp_fonte);
	dbCopyBitmap(nbmp_fonte, nbmp_tela);

	// Acessa configuração do bitmap
	naltura = dbBitmapHeight(nbmp_fonte);
	nlargura = dbBitmapWidth(nbmp_fonte);
		
	// Esse comando cria um bloco de memória-bitmap a partir de um bitmap
	dbMakeMemblockFromBitmap(1, nbmp_fonte);

	// Obtém o endereço do bloco de memória
	pImagem = (int *) dbGetMemblockPtr(1);

	// Vamos pular o cabeçalho do bloco
	pImagem++;	// pula primeira posição: largura do bitmap
	pImagem++;	// pula segunda posição: altura do bitmap
	pImagem++;	// pula terceira posição: profundidade de cor
	
	
	// Vamos hacker o bloco de memória-bitmap
	for (ncx=0; ncx < ( naltura * nlargura ); ncx++)
	{	
		// Passa a cor do ponto para rgb_efeito() que retorna esse valor alterado
		*pImagem = rgb_efeito ( pImagem);
		
		// Avança o ponteiro para a frente
		pImagem++;		

	}

	// Esse comando cria um bitmap a partir de bloco de memória-bitmap
	dbMakeBitmapFromMemblock(nbmp_gfx,1);

	// Vamos mostrar nosso bitmap que sofreu um efeito gráfico
	dbCopyBitmap(nbmp_gfx,0,0,nlargura, naltura, nbmp_tela,nlargura+10,0,nlargura*2, naltura );

	// Vamos liberar a memória do sistema
	dbDeleteMemblock(1);
	dbDeleteBitmap(nbmp_fonte);
	dbDeleteBitmap(nbmp_gfx);

} // gfx_teste().fim


// ----------------------------------------------------------------------------
int rgb_efeito(int *pImagem) {
	
	// Varíaveis de trabalho
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


