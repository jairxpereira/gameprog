// primitivas.cpp
// Esse programa mostra a criação e manipulação básica de formas 3D primitivas.
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void primitivas();			// Cria formas primitivas
void teclado();				// Leitura do teclado
int terminar = 0;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys();  

primitivas();

// Configuração da camera
dbPositionCamera (979.0f, 475.0f, -254.0f);
dbRotateCamera (29.0f, -3.0f, -6.0f);

// Looping principal
while ( LoopGDK ( ) ) { 
	
	teclado();
	
	dbSync ( );

	if (terminar == 1)
	{
		// Vamos deletar os objetos
		for (int obj=0; obj <= 6; obj++) dbDeleteObject(obj);

		return;
	} // endif
 } // fim do while
return;
} // DarkGDK().fim

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("primitivas.cpp"); 
} // initsys().fim

// Leitura do teclado
void teclado() {	

 char *stecla = "??";
 stecla = dbInKey();

 // Vamos encerrar se a tecla "q" for pressionada
 if (strcmp(stecla, "q") == 0) terminar = 1;
 strcpy (stecla,"??");
 dbText (10,10, "Pressione 'q' para sair");

} // teclado().fim

// ----------------------------------------------------------------------------
void primitivas() {
// Criação e posicionamento dos objetos 3D primitivos
dbMakeObjectCube(1,50); dbPositionObject(1,590,220,182);
dbMakeObjectSphere(2,50); dbPositionObject(2,702,220,175);
dbMakeObjectBox(3,50,200,200); dbPositionObject(3,816,200,175);
dbMakeObjectCone (4,100); dbPositionObject (4,1005, 220, 175);
dbMakeObjectCylinder (5,100); dbPositionObject (5,1205, 220, 175);
dbMakeObjectPlain (6,2800,2500); dbPositionObject (6,800,-220,175);

// Aplicando cor nesses objetos
dbColorObject (1, dbRGB(255,0,0));
dbColorObject (2, dbRGB(0,255,0));
dbColorObject (3, dbRGB(0,0,255));
dbColorObject (4, dbRGB(255,255,0));
dbColorObject (5, dbRGB(255,0,255));
dbColorObject (6, dbRGB(0,64,0));

// Aplicando escala no cilindro e rodando o box
dbScaleObject (5,100,200,100);
dbRotateObject (3,0,-25,0);

// Vamos rodar o piso
dbRotateObject (6,0,90,90);

} // primitivas().fim