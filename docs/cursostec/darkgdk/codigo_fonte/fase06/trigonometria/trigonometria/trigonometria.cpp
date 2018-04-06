// trigonometria.cpp
// Esse programa mostra como usar as funções de trigonometria para desenhar círculos e
// elipses
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void trigonometria(void);	// Desenha circulos e elipses
int sorteia_cor();			// Sorteia uma cor aleatória

// Cores
const int nPreto = 0;
const int nBranco = 0xFFFFFF;
const int nAzul = 0x0000FF;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

initsys();  

while ( LoopGDK ( ) ) { 
	trigonometria();	
 dbSync ( );
 } // fim do while

return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( ); dbSyncRate (60);
dbCLS(nBranco); 
dbSetWindowTitle("trigonometria.cpp"); 
dbSetTextOpaque();

dbRandomize( dbTimer() );

} // fim da função: initsys()

void trigonometria(void) {
	
//Centrodocírculoedaelipse
int xpos,ypos;

//Propriedades do ponto a ser desenhado
float xraio,yraio,angulo;

//Ponto final na tela da extremidade do circulo
int sx,sy;

//Ponto final na tela da extremidade da elipse
int dx,dy;

xpos=210;ypos=220;
	

for(angulo=0;angulo<=360;angulo+=10)
 {

	dbInk ( sorteia_cor(), nAzul);

	// Desenha circulo ao redor do olho
	xraio = 180; yraio = 180;
	sx = xpos + (xraio * dbCos(angulo) );
	sy = ypos + (yraio * dbSin(angulo) );	
	dbCircle (sx, sy, 10); dbCircle (sx, sy, 9); dbCircle (sx, sy, 8);

	// Desenha elipse do olho
	xraio = 180; yraio = 90;
	dx = xpos + (xraio * dbCos(angulo) );
	dy = ypos + (yraio * dbSin(angulo) );
	dbCircle (dx, dy, 10);	dbCircle (dx, dy, 9); dbCircle (dx, dy, 8);
	
	// Desenha a pupila
	xraio = 60; yraio = 60;
	sx = xpos + (xraio * dbCos(angulo) );
	sy = ypos + (yraio * dbSin(angulo) );	
	dbCircle (sx, sy, 10); dbCircle (sx, sy, 9); dbCircle (sx, sy, 8);
	dbLine(sx,sy, dx,dy);	

	// Mostre o angulo na tela
	dbInk (nBranco, nAzul);
	dbText (10,10, dbSpaces(20));
	dbText (10,10, "Angulo: "); dbText (100,10, dbStr (angulo));
	
	// Mostre os gráficos e espere um pouco
	dbSync(); dbSleep(100);
 } // fim do for (angulo)

} // trigonometria().fim

int sorteia_cor() {
//Variáveisdetrabalhocomcor
int ncor,r,g,b;

//Geraumacoraleatória
r=dbRnd(255);g=dbRnd(255);b=dbRnd(255);
ncor=dbRGB(r,g,b);

return ncor;
} // get_cor().fim