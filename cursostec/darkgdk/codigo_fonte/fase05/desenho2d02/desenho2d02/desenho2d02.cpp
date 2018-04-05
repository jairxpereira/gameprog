// desenho2d02.cpp
// Esse programa ilustra considerações técnicas sobre processamento de
// imagens 2D.
#include "DarkGDK.h"

// Protótipo das funções
void initsys();								// inicializa o sistema
void imagem_vetorial(void);					// Primeiro método de desenhar um quadrado
void imagem_rasterizada(void);				// Segundo método de desenhar um quadrado
void rasterizada_com_tabela_de_cores(void);	// Terceiro método de desenhar um quadrado
void rasterizada_compactada(void);			// Quarto método de desenhar um quadrado

// Cores
const int nPreto = 0;
const int nBranco = 0xFFFFFF;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

initsys();  

// Ativa geração de números aleatórios diferentes a cada rodada do programa
// Utilizado para gerar cores diferentes
dbRandomize(dbTimer());

// Testando vários métodos de produzir imagens
imagem_vetorial();
imagem_rasterizada();
rasterizada_com_tabela_de_cores();
rasterizada_compactada();

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
dbSetWindowTitle("desenho2d02.cpp"); 
} // fim da função: initsys()


void imagem_vetorial(void) {

	// Propriedades da imagem vetorizada
	int dados[6] = {160, 120, 5, 0, 0, 255 };	
	
	// Variáveis de trabalho
	int xpos, ypos, ntamanho;
	int ncor, r, g, b;

	// Carregando a informação da imagem para as variáveis de trabalho
	xpos = dados[0];
	ypos = dados[1];
	ntamanho = dados[2];
	r = dados[3];
	g = dados[4];
	b = dados[5];	
	
	// Legenda
	dbInk( nPreto, nBranco);
	dbText(xpos + 20, ypos, "<-- imagem_vetorial()");
	
	// Desenhando a imagem vetorizada
	ncor = dbRGB(r,g,b);
	dbInk (ncor, 0);
	dbBox (xpos, ypos, xpos + ntamanho, ypos + ntamanho);

} // quadrado01().fim


void imagem_rasterizada(void) {
	
	// Dados de cor literais da imagem rasterizada
	int dados [25][3] = { 
		{0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255},
		{0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255},
		{0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255},
		{0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255},
		{0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}, {0,0,255}
	}; // fim da array

	// Variáveis de trabalho
	int xpos, ypos;
	int ncor, r, g, b;
	int linha, coluna;

	// Ponteiro para acessar a memória aonde a imagem está localizada
	int *pImagem;

	xpos = 80;
	ypos = 60;	

	// Legenda
	dbInk( nPreto, nBranco);
	dbText(xpos + 20, ypos, "<-- imagem_rasterizada()");

	// Acessa a localização da imagem na memória
	pImagem = dados[0];

	// Acessa os dados da imagem e coloca-os na tela
	for (linha=0; linha < 5; linha++)
	{
		for (coluna = 0; coluna < 5; coluna++)
		{	
			// Obtém valores rgb dos 3 primeiros inteiros
			r = *pImagem; pImagem++;
			g = *pImagem; pImagem++;
			b = *pImagem; pImagem++;
			ncor = dbRGB(r,g,b);

			// Desenha ponto
			dbInk( ncor, 0);
			dbDot (xpos + linha, ypos + coluna);
		} // fim do for(coluna)
	} // fim do for(linha)

} // imagem_rasterizada().fim

void rasterizada_com_tabela_de_cores(void) {
	
	
	// O valor 255 simboliza uma posição numa tabela de cores que pode representar
	// qualquer cor conforme nossa necessidade e conveniência
	int dados [5][5] = { 
		255,255,255,255,255,
		255,255,255,255,255,
		255,255,255,255,255,
		255,255,255,255,255,
		255,255,255,255,255	
	}; // fim da array

	// Variáveis de trabalho
	int cor_tabela[256];	
	int xpos, ypos;
	int ncor, r, g, b;
	int linha, coluna;

	// Gera uma cor aleatória
	r = dbRnd(255);	g = dbRnd(255);	b = dbRnd(255);

	// Joga essa cor na posição 255 da tabela de cores
	cor_tabela[255] = dbRGB(r,g,b);

	// Localização da imagem
	xpos = 40;	ypos = 30;

	// Legenda
	dbInk( nPreto, nBranco);
	dbText(xpos + 20, ypos, "<-- rasterizada_com_tabela_de_cores()");

	// Ponteiro para acessar a memória aonde a imagem está localizada
	int *pImagem;

	// Acessa a memória aonde a imagem está localizada
	pImagem = dados[0];

	// Desenha a imagem
	for (linha=0; linha < 5; linha++)
	{
		
		for (coluna = 0; coluna < 5; coluna++)
		{	
			
			// *pImagem retorna o valor numérico que representa a posição de uma
			// cor na tabela
			ncor = cor_tabela [ *pImagem ]; 
			pImagem++;

			// Desenha ponto
			dbInk( ncor, 0);
			dbDot (xpos + linha, ypos + coluna);
		} // fim do for(coluna)
	} // fim do for(linha)
} // rasterizada_com_tabela_de_cores().fim

void rasterizada_compactada(void) {
	
	// Dados de uma imagem rasterizada compactada
	// [5][2] representa uma matriz bidimensional de 10 inteiros
	// {5,1} o primeiro inteiro representa a quantidade de pontos consecutivos que
	// tem a cor apontada pelo segundo número em uma tabela
	int dados [5][2] = { 
		5,1,
		5,1,
		5,1,
		5,1,
		5,1		
	}; // fim da array

	// Tabela e variáveis de trabalho
	int cor_tabela[256];	
	int xpos, ypos;
	int ncor, r, g, b;
	int linha = 0;
	int coluna = 0;

	// Gera uma cor aleatória e coloca-a na posição 1 da tabela
	r = dbRnd(255);
	g = dbRnd(255);
	b = dbRnd(255);
	cor_tabela[1] = dbRGB(r,g,b);

	// Posição da imagem
	xpos = 20;
	ypos = 15;

	// Legenda
	dbInk( nPreto, nBranco);
	dbText(xpos + 20, ypos-5, "<-- rasterizada_compactada()");
	
	// Variáveis de trabalho
	int nqtd = 0;
	int repete_cor = 0;	
	int ncor_tabela_pos = 0;

	// Desenha a imagem descompactando...
	for (linha=0; linha < 5; linha++)
	{
			nqtd = dados[linha][0];
			ncor_tabela_pos = dados[linha][1];
			ncor = cor_tabela [ ncor_tabela_pos ]; 
			
			for (repete_cor=0; repete_cor < nqtd; repete_cor++)
			{
			// Desenha ponto
			dbInk( ncor, 0);
			dbDot (xpos + linha, ypos + coluna);
			coluna++;
			} // fim do for(coluna)
			coluna = 0;

	} // fim do for(linha)

} // rasterizada_compactada().fim





