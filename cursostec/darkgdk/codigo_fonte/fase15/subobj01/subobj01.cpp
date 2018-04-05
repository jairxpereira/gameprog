// sub0bj01.cpp
// Esse programa mostra como manipular subojetos
#include "DarkGDK.h"

// Prot�tipo das fun��es
void initsys();             // inicializa o sistema
void ver_membros();			// Verifica membros do objeto 3d

// Posi��o do modelo 3d
float xobj_pos = 970, yobj_pos = 300, zobj_pos = -185;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk 

// Fixa o diret�rio de trabalho e carrega textura do modelo 3D
dbSetDir ("c:\\gameprog\\gdkmedia\\Modelos\\German");
dbLoadImage ("german.dds",2);

// Carrega modelo 3d com anima��o de ocioso
dbLoadObject ("H-German-Idle.x",1);

// Textura o modelo 3d 1 com a segunda imagem
dbTextureObject (1,2);

dbScaleLimb(1, 10, 200, 200, 200); // cabe�a
dbScaleLimb(1, 4, 200, 200, 200); // p� esquerdo
dbScaleLimb(1, 7, 200, 200, 200); // p� direito

dbRotateLimb (1, 10, 0,15,0); // cabe�a
dbOffsetLimb(1, 18, 2,2,2); // arma
dbHideLimb (1, 19); // cinto

// Configura��o inicial de exibi��o
initsys(); 

// Cria��o b�sica de um terreno 
dbMakeMatrix (1,2000,10000,10,50);

// Posiciona e escala o objeto
dbPositionObject (1,xobj_pos,yobj_pos, zobj_pos);
dbScaleObject (1,15000,15000,15000);

// Posiciona a camera
dbPositionCamera (1005, 475, -600);
dbSyncOn();
ver_membros();

// Looping principal
while ( LoopGDK ( ) )
 { 
    dbSync ( ); 
	ver_membros();
 } // fim do while
dbDeleteImage (1); dbDeleteMatrix (1);  dbDeleteObject (1);
return;
} // fim da fun��o: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta fun��o inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("subobj01.cpp"); 
dbSetTextOpaque();
dbSetAmbientLight(100);
} // initsys().fim


// ver_membros() - Verifica membros de um objeto 3d
void ver_membros()
{

 // Vari�veis para a coleta de informa��es
 char sinfo[255];
 int nqtd = 0;
 char *snome = NULL;

 // Verifica a quantidade de limbs (membros) no objeto
 dbPerformChecklistForObjectLimbs(1);
 nqtd = dbChecklistQuantity();
 
 // Configurar curso de impress�o
 dbSetCursor (1,10);

	// Obt�m o n�mero e nome dos membros
    for (int ncx=0; ncx < nqtd; ncx++) 
	{
	snome = dbChecklistString(ncx+1);
	sprintf(sinfo, " %d.%s", ncx, snome);
	dbPrint ( sinfo );
	} // for.end

} // ver_membros().fim