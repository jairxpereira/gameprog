// teclado01.cpp
// Esse programa ilustra o tratamento do teclado
#include "DarkGDK.h"
void initsys();
void tst_teclado01();

// Cores
int nPreto = 0;
int nAzul = 0x0000FF;
int nBranco = 0xFFFFFF;

// Coordenadas b�sicas de posicionamento (xpos, ypos) para desenho
int xpos = 160;
int ypos = 120;

void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk

initsys();   

while ( LoopGDK ( ) ) {    
	tst_teclado01();
 dbSync ( );
 } // fim do while

return;
} // fim da fun��o: DarkGDK

void initsys() {    
// Esta fun��o inicializa o sistema
dbSyncOn( ); dbSyncRate (60);

// Estabelecendo a configura��o de v�deo
dbSetWindowOn();				
dbSetDisplayMode(640,480,32);   
dbCLS(nBranco); 
dbInk(nPreto, nBranco);

// Configurando a janela
dbSetWindowTitle("teclado01.cpp"); 
dbSetWindowSize (640,480); 
dbSetWindowPosition (320,20);
} // fim da fun��o: initsys()

void tst_teclado01 () {
// Esta fun��o ilustra uso do teclado

// Usando teclas especiais
const int tecla_F3 = 61;
const int tecla_F4 = 62;
int nscancode = 0;
nscancode = dbScanCode();
if (nscancode == tecla_F3) dbText (20,20, "F3 pressionado...");
if (nscancode == tecla_F4) dbText (40,40, "F4 pressionado...");

// Usando teclas normais do teclado
char *stecla = dbInKey();
if (!strcmp(stecla,"c")) dbText (250,20, "'c' pressionado...");
if (!strcmp(stecla,"a")) dbText (270,40, "'a' pressionado...");

// Testando o mouse
const int btnDireito = 2;
const int btnEsquerdo = 1;
if (dbMouseClick() == btnDireito)
	dbText (dbMouseX(), dbMouseY(), "Botao direito pressionado");

// Repare nesta sintaxe...
if (dbUpKey()==1) ypos = ypos - 5;      // Movimento para cima
if (dbDownKey()==1) ypos = ypos + 5;    // Movimento par abaixo

// Repara nesta sintaxe simplificada
if (dbRightKey()) xpos = xpos + 5 ;     // Movimento para a direita
if (dbLeftKey()) xpos = xpos - 5;       // Movimento para a esquerda

// Desenhando com o bot�o esquerdo do mouse
if (dbMouseClick()== btnEsquerdo) {
	xpos = dbMouseX();
	ypos = dbMouseY();
 } // fim do if

// Desenha efetivamente o 'o' na tela
dbText (xpos, ypos, "o");



} // fim tst_janela01()