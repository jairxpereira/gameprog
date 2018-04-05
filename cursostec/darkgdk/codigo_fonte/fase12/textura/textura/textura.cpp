// textura.cpp
// Esse programa ilustra como texturizar os objetos
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void primitivas();			// Cria formas primitivas
void teclado();				// Leitura do teclado
void carregar_textura();	// Carrega imagens de textura
void texturizar();			// Texturiza os objetos
int terminar = 0;

// Identificação dos objetos
const int obj_piso = 1;
const int obj_esfera = 2;
const int obj_retangulo = 3;
const int obj_caixa  = 4;
const int obj_cilindro = 5;
const int obj_cone = 6;

// Identificação das texturas
const int txt_piso = 1;
const int txt_esfera = 2;
const int txt_retangulo = 3;
const int txt_caixa  = 4;
const int txt_cilindro = 5;
const int txt_cone = 6;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys();  

carregar_textura();
primitivas();
texturizar();

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
		for (int ncx=1; ncx <= 6; ncx++)
		{
			dbDeleteObject(ncx);
			dbDeleteImage(ncx);
		} // endfor (deletar objetos)

		return;
	} // endif
 } // fim do while
return;
} // DarkGDK().fim

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("textura.cpp"); 
dbSetAmbientLight(100);
dbSetDisplayMode(640,480,32);
dbSetWindowSize(640,480);
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
// Criação dos objetos 3D primitivos
dbMakeObjectCube(obj_caixa,50);
dbMakeObjectSphere(obj_esfera,50);
dbMakeObjectBox(obj_retangulo,50,200,200);
dbMakeObjectCone (obj_cone,100);
dbMakeObjectCylinder (obj_cilindro,100); 
dbMakeObjectPlain (obj_piso,2800,2500); 

// Posicionamento dos objetos
dbPositionObject(obj_caixa,590,220,182);
dbPositionObject(obj_esfera,702,220,175);
dbPositionObject(obj_retangulo,816,200,175);
dbPositionObject (obj_cone,1005, 220, 175);
dbPositionObject (obj_cilindro,1205, 220, 175);
dbPositionObject (obj_piso,800,-220,175);

// Corrigindo a visualização do cilindro
dbSetObjectCull (obj_cilindro, 0);

// Corrigindo a textura do piso
dbScaleObjectTexture(obj_piso, 5.0f, 5.0f);

// Aplicando escala no cilindro e rodando a caixa
dbScaleObject (obj_cilindro,100,200,100);
dbRotateObject (obj_caixa,0,-25,0);

// Vamos rodar o piso
dbRotateObject (obj_piso,0,90,90);

} // primitivas().fim

void carregar_textura()
{
	dbSetDir ("c:\\gameprog\\gdkmedia\\textura");
	dbLoadImage ("grass3.jpg",			txt_piso);
	dbLoadImage ("pjbasesky.jpg",		txt_esfera);
	dbLoadImage ("archpart7.jpg",		txt_retangulo);
	dbLoadImage ("x_support.tga",		txt_caixa);
	dbLoadImage ("concrete.jpg",		txt_cilindro);
	dbLoadImage ("ceilingtech02.jpg",	txt_cone);
} // carregar_textura().end

void texturizar()
{
	dbTextureObject(obj_piso,		txt_piso);
	dbTextureObject(obj_esfera,		txt_esfera);
	dbTextureObject(obj_retangulo,	txt_retangulo);
	dbTextureObject(obj_caixa,		txt_caixa);
	dbTextureObject(obj_cilindro,	txt_cilindro);
	dbTextureObject(obj_cone,		txt_cone);

} // texturizar().end
