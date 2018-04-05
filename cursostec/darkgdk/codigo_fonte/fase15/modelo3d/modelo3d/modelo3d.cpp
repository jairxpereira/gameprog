// Modelo3d.cpp
// Esse programa mostra como carregar um modelo 3d
#include "DarkGDK.h"

// Prot�tipo das fun��es
void initsys();				// inicializa o sistema
void texturizar();			// Texturiza a matrix

// Posi��o do modelo 3d
float xobj_pos = 970, yobj_pos = 300, zobj_pos = -185;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk 

// Carrega a textura do terreno (matrix)
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);

// Fixa o diret�rio de trabalho e carrega textura do modelo 3D
dbSetDir ("c:\\gameprog\\gdkmedia\\Modelos\\German");
dbLoadImage ("german.dds",2);

// Carrega modelo 3d com anima��o de ocioso
dbLoadObject ("H-German-Idle.x",1);

// Textura o modelo 3d 1 com a segunda imagem
dbTextureObject (1,2);

// Configura��o inicial de exibi��o
initsys(); 

// Cria��o b�sica de um terreno com o posicionamento da c�mera
dbMakeMatrix (1,2000,10000,10,50);
dbPrepareMatrixTexture (1,1,2,2);
texturizar();

// Posiciona e escala o objeto
dbPositionObject (1,xobj_pos,yobj_pos, zobj_pos);
dbScaleObject (1,15000,15000,15000);

// Posiciona a camera
dbPositionCamera (1005, 475, -600);
dbSyncOn();

// Looping principal
while ( LoopGDK ( ) )
 { 
	dbSync ( );	
 } // fim do while
dbDeleteImage (1); dbDeleteMatrix (1);	dbDeleteObject (1);
return;
} // fim da fun��o: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta fun��o inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("Modelo3d.cpp"); 
dbSetTextOpaque();
dbSetAmbientLight(100);
} // initsys().fim


// ----------------------------------------------------------------------------
// texturizar() - Aplica aleat�riamente a textura na matrix
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
