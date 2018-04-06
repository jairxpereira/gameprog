// tst_imagens.cpp
// Esse programa mostra como usar as funções de imagem
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void showmousepos(void);	// Mostra posição do mouse na barra da janela
void teste_imagem(void);	// Realizada testes de imagem
void salvar_imagem(void);	// Salva a imagem da tela no diretório do programa

// Essa função desenha uma caixa na posição (xpos, ypos)
void caixa( int xpos, int ypos, int nlargura, int naltura);

// Cores
const int nPreto = 0;
const int nBranco = 0xFFFFFF;
const int nAzul = 0x0000FF;
const int nVermelho = 0xFF0000;
const int nVerde = 0x00FF00;
const int nMagenta = 0xFF00FF;


// Alças/handles para nossas imagens
const int img_fonte = 1;
const int img_nova = 3;
const int img_tela = 0;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

initsys();  

// Exibe os testes de imagem
teste_imagem();

while ( LoopGDK ( ) ) { 
	
	showmousepos();

	if (dbEscapeKey())
	{
	dbDeleteImage(img_fonte);
	dbDeleteImage(img_nova);	
	return;
	}
	
 dbSync ( );
 } // fim do while

return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( ); dbSyncRate (60);
dbCLS(nPreto); 
dbSetWindowTitle("tst_imagens.cpp"); 
dbDisableEscapeKey();
} // fim da função: initsys()

void teste_imagem(void) {
char txt[255];
int nlargura, naltura;

dbSetImageColorKey(255,0,255);
dbLoadBitmap ("c:\\gameprog\\gdkmedia\\bitmap\\magenta-transparente.bmp");
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\magenta-transparente.bmp",img_fonte);
nlargura = 259; naltura = 159;
dbPasteImage (img_fonte,0, naltura);

// Recorta e mostra um pedaço da tela
dbGetImage (img_nova,25,75,215,220);
dbPasteImage(img_nova,245,0);

// Ilustra a área que foi recortada
caixa (25,75, 190, 145);
caixa (245,0, 190,145);

// Desenha seta
dbLine (215, 185, 340, 185);
dbLine (340, 185, 340, 155);
dbLine (340, 155, 331,166);
dbLine (340, 155, 349,166);

// Mostra legenda na tela
dbText ( 228, 195, "dbGetImage (3,25,75,215,220);" );
dbText ( 228, 215, "dbPasteImage(3,245,0);" );
sprintf(txt, "dbImageExist(1) = %d", dbImageExist(img_fonte));
dbText (228,235, txt);
dbText (228,255, "// Botao direito para salvar imagem");
} // teste_imagem().fim


// ----------------------------------------------------------------------------
void showmousepos() {
char txt[255];
int xpos, ypos;

// Obtém posição do mouse
xpos = dbMouseX(); ypos = dbMouseY();

// Mostra posição do mouse na barra de título da janela
sprintf (txt, "tst_imagens.cpp - xcol: %d ypos: %d ", xpos, ypos);
dbSetWindowTitle(txt);

// Se botão direito do mouse então grave a imagem no disco como tela.png
if (dbMouseClick() == 2)
  {
  // Estampe e mostre a hora e a data na imagem
  dbText (230,280, dbGetTime());
  dbText (330,280, dbGetDate());
  dbSync();
  
  // Recorta e salva a imagem no disco
  dbGetImage (4,0,0,600,300);
  dbSaveImage("tela.png",4);
  MessageBox (0,"Ok Imagem gravada", "Gameprog", MB_OK);
  dbDeleteImage(4);
  } // endif
}// showmousepos().fim


// ----------------------------------------------------------------------------
void caixa( int xpos, int ypos, int nlargura, int naltura) {

// Variáveis de trabalho
int nEsquerda,nDireita,nTopo,nFundo;

// Obtém os quatro pontos da caixa
nEsquerda = xpos;
nTopo = ypos;
nDireita = xpos + nlargura;
nFundo = ypos + naltura;

// Liga os quatro pontos da caixa com linhas
dbLine(nEsquerda,nTopo,nEsquerda,nFundo);
dbLine(nEsquerda,nFundo,nDireita,nFundo);
dbLine(nDireita,nFundo,nDireita,nTopo);
dbLine(nDireita,nTopo,nEsquerda,nTopo);
} // caixa().fim