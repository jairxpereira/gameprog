// shader01.cpp
// Esse programa mostra como utilizar shaders
#include "DarkGDK.h"

// Prot�tipo das fun��es
void initsys();             // inicializa o sistema
void tst_shader(int obj);		// Testa de shader 01

// Posi��o do modelo 3d
float xobj_pos = 1020, yobj_pos = 300, zobj_pos = 0;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk 

const int obj_caixa_01 = 1;
const int obj_caixa_02 = 2;
const int obj_caixa_03 = 3;
const int obj_caixa_04 = 4;


// Configura��o inicial de exibi��o
initsys(); 

// Cria��o b�sica da matriz
dbMakeMatrix (1,2000,10000,10,50);

// Vamos fazer uma caixa e texturizar com um shader
dbMakeObjectBox (obj_caixa_01, 200,200,200);
tst_shader(obj_caixa_01);

// Posiciona a caixa no mundo
dbPositionObject (obj_caixa_01, xobj_pos, yobj_pos, zobj_pos);

// Vamos produzir objetos de apoio para mostrar os passos do shader
dbMakeObjectBox (obj_caixa_02, 200, 200, 200);
dbMakeObjectBox (obj_caixa_03, 200, 200, 200);
dbMakeObjectBox (obj_caixa_04, 200, 200, 200);
dbPositionObject (obj_caixa_02, 700, 550, 200);
dbPositionObject (obj_caixa_03, 1020, 550, 200);
dbPositionObject (obj_caixa_04, 1350, 550, 200);
dbSetDir ("c:\\gameprog\\gdkmedia\\shader");
dbLoadImage ("ground.jpg", 2); dbTextureObject (obj_caixa_02, 2);
dbLoadImage ("door1.jpg", 3); dbTextureObject (obj_caixa_03, 3);
tst_shader(obj_caixa_04);

// Posiciona a camera
dbPositionCamera (1005, 475, -500);
dbSyncOn();

// Looping principal
while ( LoopGDK ( ) )
 { 
    // Gire a caixa_01 para a esquerda
	 dbTurnObjectLeft (obj_caixa_01, 1);

	 dbSync ( ); 
 } // fim do while
dbDeleteMatrix (1);  dbDeleteObject (1);
return;
} // fim da fun��o: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta fun��o inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("shader01.cpp"); 
dbSetAmbientLight(100);
} // initsys().fim


void tst_shader(int obj) 
{
// Essa fun��o carrega um arquivo de efeito, reconfigura um atributo
// aplica o efeito no objeto especificado por obj
const int obj_fx = 1;
dbSetDir ("c:\\gameprog\\gdkmedia\\shader");
dbLoadEffect ( "DetailMapping.dbs", obj_fx, 1 );

dbSetObjectEffect ( obj, obj_fx );
dbSetEffectConstantFloat ( obj_fx, "detailScale", 1.0f );
}
