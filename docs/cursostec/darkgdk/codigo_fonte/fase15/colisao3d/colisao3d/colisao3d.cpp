// colisao3d.cpp
// Esse programa ilustra o uso de detecção de colisão da DarkGdk
#include "DarkGDK.h"
#include "windows.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void teclado();				// Interpreta o teclado
void texturizar();			// Texturiza a matrix

// Variáveis de trabalho
int terminar = 0;
const int som_arrastar = 1;

//coordenada dos objetos
float xpos = 400, ypos = 10, zpos = 300;
float xbox = 400, ybox = 10, zbox = 350;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

// Carrega textura do terreno
dbSetWindowTitle("Aguarde...");
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbLoadSound ("c:\\gameprog\\gdkmedia\\som\\arrastar.wav",som_arrastar);

// Inicializa o sistema
initsys();

// Prepara o terreno
dbMakeMatrix (1,2000,10000,10,50);
dbPrepareMatrixTexture (1,1,2,2);
texturizar();

//preparando os objetos
dbMakeObjectSphere (1,10);
dbPositionObject (1,xpos,ypos,zpos);
dbMakeObjectCube (2,30);
dbPositionObject (2,xbox,ybox,zbox);
dbTextureObject (2,1);

// Posiciona camera na cena
dbPositionCamera (400, 50, 250);

// Liga detecção de colisão para o objeto 1
dbSetObjectCollisionOn (1);

dbSyncOn();

// Looping principal
while ( LoopGDK ( ) ) {

		if (terminar == 0) teclado();

	dbSync ( );

	if (terminar == 1)
	{
		dbDeleteImage (1);	dbDeleteMatrix (1);
		dbDeleteObject (1);
		return;
	} // endif
 } // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("colisao3d.cpp");
dbSetTextTransparent();
dbDisableEscapeKey();
dbSyncRate(60);
} // initsys().fim


// ----------------------------------------------------------------------------
// texturizar() - Aplica aleatóriamente a textura na matrix
void texturizar() {
int linha, coluna;
for (coluna = 0; coluna < 10; coluna++)
{
	for (linha = 0; linha < 50; linha++)
	{
		int tile = dbRnd(4) + 1;
		dbSetMatrixTile (1, coluna, linha, tile);
	} // linha
} //coluna

dbUpdateMatrix (1);

} // texturizar().fim


// ----------------------------------------------------------------------------
// teclado() - Lê o teclado e executa comandos do usuário
void teclado() {

char sinfo[255];
if (dbEscapeKey()) terminar = 1;

// Movimentação do ponto de foco da luz
if (dbUpKey())zpos += 5;
if (dbDownKey()) zpos -= 5;

if (dbLeftKey()) xpos -= 5;
if (dbRightKey()) xpos += 5;

// Mostra informações na tela
dbText (10,10, "Controles: <esc> terminar \t <setas cima,baixo> mover a esfera");
sprintf (sinfo, "xbox:%f ybox:%f zbox:%f ", xbox, ybox, zbox);
dbText (10,30, sinfo);

if (dbObjectCollision(1,2) > 0)
{
 dbPlaySound (som_arrastar);
 for (int ncx=1; ncx < 20; ncx++) 
 {
   zbox++; dbPositionObject (2,xbox,ybox,zbox);
 }
 
} // endif

//movendo os objetos
dbPositionObject (1,xpos,ypos,zpos);
dbPositionObject (2,xbox,ybox,zbox);

} // teclado().fim