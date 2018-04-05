// tst_sprites01.cpp
// Esse programa mostra como usar as funções de sprite
#include "DarkGDK.h"

// Protótipo das funções
void initsys();         // inicializa o sistema
void menu();            // Mostra um menu de opções na tela
void tst_sprite();      // Teste principal de sprites
void tst_cor_difusa();  // Testa dbSetSpriteDiffuse(r,g,b);
void tst_mirror_flip(); // Testa espelhar e virar a sprite
void mostrar_info();    // Mostrar status na tela

// Cores
const int nPreto = 0;
const int nBranco = 0xFFFFFF;
const int nAzul = 0x0000FF;

int terminar_app = 0;

// Taxa de valores rgb
int tr = 0;
int tg = 0;
int tb = 0;

// Usado para pegar distância entre dois pontos
int xpos_inicial = 0;
int ypos_inicial = 0;

// String para mostrar texto
char info[255];

// Estrutura para posicionar as sprites inicialmente
struct Posicao
{
int xpos;
int ypos;
};

Posicao sprt[11]; // Criando 11 estruturas de Posição

// ----------------------------------------------------------------------------
void DarkGDK ( void ){
// Começo da aplicação DarkGdk
initsys();
while ( LoopGDK ( ) ) {
tst_sprite();
if (terminar_app == 1) return;
dbSync ( );
} // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys(){
// Esta função inicializa o sistema
dbSyncOn( );
dbSetDisplayMode(800,600,32);
dbSetWindowSize(800,600);
dbSetWindowPosition(160,50);
dbSetWindowTitle("tst_sprites01.cpp");
} // fim da função: initsys()


// ----------------------------------------------------------------------------
void menu(){

// Variáveis de trabalho para mostrar texto
int xpos = 260;
int ypos = 10;
int coluna = xpos;
int linha = ypos;
int espaco_entrelinhas = 20;
int ncx = 0;

// Nossa lista de opções
char *slista[] = {"1- dbHideAllSprites()", "2- dbShowAllSprites()",
"3- dbHideSprite(3)", "4- dbShowSprite(3)", "q\\Botao Direito - SAIR ",
"6-dbSetSpriteDiffuse()", "7- dbSpriteAngle();dbRotateSprite()",
"8- dbScaleSprite(2)","9-dbFlipSprite(7) - dbMirrorSprite(8)", 
"0 - MoveSprite", "t - change sprite image", 
"p- dbSetSpritePriority()", "a- dbSetSpriteAlpha()"};

// Mostre a lista
// dbInk (nAzul, nBranco);
 for (ncx = 0; ncx < 13; ncx++) {
 linha = ypos + ( ncx * espaco_entrelinhas );
 dbText (coluna, linha, slista[ncx]);
 } // fim do for(ncx)

} // menu().end

// ----------------------------------------------------------------------------
void tst_sprite(){

dbSetCurrentBitmap(0);
menu();

int xcol, ylin;

dbSetImageColorKey (255,255,255);
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\badboy_br.png",1);
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\badboy.png",2);

// Vamos criar posições aleatórias para nossas futuras sprites
for (int ncx=1; ncx < 10; ncx++)
{
sprt[ncx].xpos = dbRnd(350)+400;
sprt[ncx].ypos = dbRnd(500);
}

// Vamos configurar precisamente o posicionamento de certas sprites
// Sprite original para referência com as propriedades originais
sprt[1].xpos = 524; sprt[1].ypos = 290;

// A sprite 2 é nosso jogador principal
sprt[2].xpos = 525; sprt[2].ypos = 500;

// Sprites do teste de dbSetSpriteDiffuse()
sprt[3].xpos = 0; sprt[3].ypos = 310;
sprt[4].xpos = 0; sprt[4].ypos = 360;
sprt[5].xpos = 0; sprt[5].ypos = 420;
sprt[6].xpos = 0; sprt[6].ypos = 480;

// Imagens do teste de mirror e flip
sprt[7].xpos = 400; sprt[7].ypos = sprt[3].ypos - 20;
sprt[8].xpos = 400; sprt[8].ypos = sprt[4].ypos + 35;
sprt[9].xpos = 400; sprt[9].ypos = sprt[5].ypos + 80;

// Vamos replicar a mesma imagem em várias sprites para 
// ilustrar os diversos efeitos sempre mostrando a imagem
// original
for (int ncx=1; ncx < 10; ncx++)
{
dbSprite (ncx, sprt[ncx].xpos, sprt[ncx].ypos, 1);
}

// Posição do jogador
xcol = 525;
ylin = 500;
dbPositionMouse (xcol,ylin);

// Testa dbSetSpriteDiffuse()
tst_cor_difusa();

// Controla leitura do teclado
while (dbMouseClick() != 2) {

 char *tecla = dbInKey();

 // Testa esconder e mostrar sprites
 if (!strcmp(tecla,"1")) dbHideAllSprites();
 if (!strcmp(tecla,"2")) dbShowAllSprites();
 if (!strcmp(tecla,"3")) dbHideSprite(3);
 if (!strcmp(tecla,"4")) dbShowSprite(3);

 if (!strcmp(tecla,"q")) {
 terminar_app = 1;
 break;
 } // endif

 // Testa dbSetSpriteDiffuse()
 if (!strcmp(tecla,"6")) {
 tst_cor_difusa();
 } // endif

 
 // Testa dbSpriteAngle() e dbRotateSprite()
 if (!strcmp(tecla,"7")) {
 dbSleep(100);
 int angulo = dbSpriteAngle(2) + 15;
 if (angulo >= 360) angulo = 0;
 dbRotateSprite(2, angulo );
 }// endif

 // Testa dbScaleSprite()
 if (!strcmp(tecla,"8")) {
 dbSleep(100);
 int fator = dbRnd(200);
 dbScaleSprite (2,fator);
 }// endif

 // Testa dbFlipSprite() e dbMirrorSprite()
 if (!strcmp(tecla,"9")) {
 tst_mirror_flip();
 }// endif

 // Move a sprite conforme configuração de dbSpriteAngle()
 if (!strcmp(tecla,"0")) {
 dbMoveSprite (2,5);
 }// endif

 // Troca imagem da sprite
 if (!strcmp(tecla,"t")) {
 dbSleep(100);
 if (dbSpriteImage(2) ==1 ) dbSetSpriteImage (2,2);
 else dbSetSpriteImage (2,1);
 }// endif

 // Testa dbSetSpritePriority() - Prioridade de exibição
 if (!strcmp(tecla,"p")) {
 dbSetSpritePriority (2,1);
 }// endif

 // Testa efeito de transparência com dbSetSpriteAlpha()
 if (!strcmp(tecla,"a")) {
 dbSetSpriteAlpha (2,60);
 }// endif

 // Obtém posicionamento do mouse
 xcol = dbMouseX();
 ylin = dbMouseY();

 
 // Controla movimentação da sprite(2) - nosso 'player'
 if (dbDownKey()==1) 
	 dbOffsetSprite (2,dbSpriteOffsetX(2), dbSpriteOffsetY(2)-2 );

 if (dbUpKey()==1) 
	 dbOffsetSprite (2,dbSpriteOffsetX(2),dbSpriteOffsetY(2)+2);

 if (dbRightKey()==1) 
	 dbOffsetSprite (2,dbSpriteOffsetX(2)-2 ,dbSpriteOffsetY(2));

 if (dbLeftKey()==1) 
	 dbOffsetSprite (2,dbSpriteOffsetX(2)+2,dbSpriteOffsetY(2));

 dbPasteSprite (2,xcol, ylin);

 // Memoriza a posição do mouse para testarmos com stretch
 if (!dbMouseClick() == 1) {
 xpos_inicial = xcol;
 ypos_inicial = ylin;
 } // endif

 // O botão esquerdo testa esticamento com dbStretchSprite()
 if (dbMouseClick() == 1) {
 dbStretchSprite (2, xcol - xpos_inicial, ylin - ypos_inicial);
 } // endif

 menu();
 mostrar_info();
 dbSync();
} // endwhile (leitura do teclado)

// Vamos liberar a memória
for (int item=1; item < 10; item++) {
if (dbImageExist(item)) dbDeleteImage (item);
if (dbSpriteExist(item)) dbDeleteSprite (item);
} // fim do if

dbCLS(0); 
dbCenterText (400,300, "Pressione a tecla <ESC> para finalizar");
dbSync();
dbWaitKey();
} // endfunc: tst_sprite


void mostrar_info(void){
dbText (10,10,dbStr (dbSpriteOffsetX(2) )); 
	dbText (50,10, "dbSpriteOffsetX(2)" );

dbText (10,30,dbStr (dbSpriteOffsetY(2) )); 
	dbText (50,30, "dbSpriteOffsetY(2)" );

dbText(10,50,dbStr (dbSpriteScaleX(2) )); 
	dbText (50,50, "dbSpriteScaleX(2)" );

dbText (10,70,dbStr (dbSpriteScaleY(2) )); 
	dbText (50,70, "dbSpriteScaleY(2)" );

dbText (10,90,dbStr (dbSpriteWidth(6) )); 
	dbText (50,90, "dbSpriteWidth(6)" );

dbText (10,110,dbStr (dbSpriteHeight(6) )); 
	dbText (50,110, "dbSpriteHeight(6)" );

dbText (10,130,dbStr (dbSpriteImage(9) )); 
	dbText (50,130, "dbSpriteImage" );

dbText (10,150,dbStr (dbSpriteMirrored(9) )); 
	dbText (50,150, "dbSpriteMirrored" );


dbText (10,170,dbStr (dbSpriteX(1) )); 
	dbText (50,170, "dbSpriteX (1)" );

dbText (10,190,dbStr (dbSpriteY(1) )); 
	dbText (50,190, "dbSpriteY (1)" );

dbText (10,210,dbStr (dbSpriteRed(6) ));
	dbText (50,210, "dbSpriteRed (6)" );

dbText (10,230,dbStr (dbSpriteGreen(6) ));
	dbText (50,230, "dbSpriteGreen (6)" );

dbText (10,250,dbStr (dbSpriteBlue(6) )); 
	dbText (50,250, "dbSpriteBlue (6)" );

dbText (10,270,dbStr (dbSpriteExist(6) )); 
	dbText (50,270, "dbSpriteExist (6)" );

dbText (10,290,dbStr (dbSpriteAngle(2) )); 
	dbText (50,290, "dbSpriteAngle (2)" );

// Mostra configuração da função dbSetSpriteDiffuse();
sprintf(info, "dbSetSpriteDiffuse(3, %d, %d, %d)",tr,0,0);
dbText (120, sprt[3].ypos+20, info);
sprintf(info, "dbSetSpriteDiffuse(4, %d, %d, %d)",0,tg,0);
dbText (120, sprt[4].ypos+20, info);
sprintf(info, "dbSetSpriteDiffuse(5, %d, %d, %d)",0,0,tb);
dbText (120, sprt[5].ypos+20, info);
sprintf(info, "dbSetSpriteDiffuse(6, %d, %d, %d)",tr,tg,tb);
dbText (120, sprt[6].ypos+20, info);

// Identifica a imagem original
dbText (575, 395, "Imagem original");

// Mostra a posição do mouse na janela
sprintf(info, "tst_sprite01.cpp - mouse: %d , %d", 
		dbMouseX(), dbMouseY());
dbSetWindowTitle (info);
}

void tst_cor_difusa(void){
// Vamos desacelerar a teclagem
dbSleep(100);
// Gera cor aleatória
tr = dbRnd(255); tg = dbRnd(255); tb = dbRnd(255);
// Configura individualmente cada canal de cor
dbSetSpriteDiffuse (3,tr,0,0);
dbSetSpriteDiffuse (4,0,tg,0);
dbSetSpriteDiffuse (5,0,0,tb);
dbSetSpriteDiffuse (6,tr,tg,tb);
} // tst_cor_difusa().fim

void tst_mirror_flip(){
dbSleep(100);
dbFlipSprite(7);
dbMirrorSprite(8);
dbFlipSprite(9);
dbMirrorSprite(9);
} // tst_mirror_flip().fim


