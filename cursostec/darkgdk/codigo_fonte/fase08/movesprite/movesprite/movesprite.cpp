// movesprite.cpp
// Esse programa mostra como movimentar as sprites
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void tst_sprite();			// Movimenta a sprite

// termina a aplicação se igual a 1
int terminar_app = 0;

// Memória para exibição de texto
char sinfo[255];

// Coordenadas (xcol,ylin)= posição (dx,dy)= deslocamento
int xcol = 320;		int ylin = 240;
int dx = 0;			int dy = 0;

// Direção do movimento
float angulo = 0.0f;

// Flags de movimentação
bool modo_linear = false;	
bool modo_angular = true;
bool modo_mover = modo_angular;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys();  

// Cria uma sprite #1 com a imagem #1 e coloca-a em (xcol,ylin)
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\badboy_br.png",1);
dbSprite (1, xcol, ylin, 1);

while ( LoopGDK ( ) ) { 
 tst_sprite();
 if (terminar_app == 1) return;	
 dbSync ( );
 } // fim do while
return;
} // fim da função: DarkGDK



// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbInk (0x0000FF, 0xFFFFFF);
dbBackdropColor(0xFFFFFF);
dbSetWindowTitle("movesprite.cpp"); 
dbSetTextOpaque();
} // fim da função: initsys()


// ----------------------------------------------------------------------------
void tst_sprite() {

// Tecla espaço inverte movimentação
if (dbSpaceKey() == 1) modo_mover = !modo_mover;	 

// Movimentação linear
if (modo_mover == modo_linear)
{
 dbSetWindowTitle("movesprite.cpp - modo linear");
 dbCircle(xcol, ylin, 10);
 if (dbDownKey()==1) 
     dbOffsetSprite (1,dbSpriteOffsetX(1), dbSpriteOffsetY(1)-2);

 if (dbUpKey()==1) 
	dbOffsetSprite (1,dbSpriteOffsetX(1),dbSpriteOffsetY(1)+2);

 if (dbRightKey()==1) 
	dbOffsetSprite (1,dbSpriteOffsetX(1)-2 ,dbSpriteOffsetY(1));

 if (dbLeftKey()==1) 
	dbOffsetSprite (1,dbSpriteOffsetX(1)+2,dbSpriteOffsetY(1)); 
 } // endif - fim do movimento linear


// Movimentação movimentação angular
if (modo_mover == modo_angular)
{
 dbSetWindowTitle("movesprite.cpp - modo angular");
 dbCircle(xcol, ylin, 10);
 if (dbUpKey() == 1) dbMoveSprite (1,2.0f);	
 if (dbDownKey() == 1) dbMoveSprite (1,-2.0f);	
 
 if (dbRightKey() == 1)
   {
     angulo = angulo + 5;
	 dbRotateSprite(1, angulo);	
   } // endif - rightkey
	
 if (dbLeftKey() == 1)
   {
     angulo = angulo - 5;
	 dbRotateSprite(1, angulo);
   } // endif: leftkey

}// endif - movimento angular

 if (dbMouseClick() == 2) terminar_app = 1;	

 // Mostra coordenadas na tela
 dx = dbSpriteOffsetX(1);
 dy = dbSpriteOffsetY(1);
 xcol = dbSpriteX(1);
 ylin = dbSpriteY(1);
 
 sprintf (sinfo, "(dx:%d, dy:%d) (xcol:%d, ylin: %d) Angulo: %dº",
	 dx, dy, xcol, ylin, (int) angulo);

 dbText (10,10, sinfo);
} // endfunction tst_sprite()