// terrain01.cpp - Esse programa mostra como construir um simples terreno
#include "DarkGDK.h" 
void initsys(void);				// inicializa o sistema
void construir_terreno(void);	// configura e mostra o terreno

// Faz a leitura do teclado e atualiza a visualização
void atualizar_visao(void);		

#define nTerreno		1		// handle do terreno

void DarkGDK ( void ) { 

	initsys();
	construir_terreno();

 // Ajustando a camera
  dbPositionCamera ( 385, 23, 100 ); 


 // Looping principal
  while ( LoopGDK ( ) ) 
  { 
	atualizar_visao();
	
	// Atualize a tela
    dbSync ( ); 


 }// endwhile
}// endfunction: darkgdk

//-----------------------------------------------------------------------------
void initsys(void) {
 dbSyncOn ( ); 
 dbSyncRate ( 60 ); 
 dbSetWindowTitle("terrain01.cpp");
}// endfunction: initsys()


void construir_terreno(void) {

	// Vamos nomear os números para ficar mais legível nosso programa 
	#define img_textura		1		// textura ou mapa de cor do terreno
	#define img_detalhe		2		// textura de detalhamento 


	// Carregando as imagens de trabalho
	dbSetDir("c:\\gameprog\\gdkmedia\\bitmap");
	dbLoadImage ( "mapa_cor.jpg", img_textura ); 
	dbLoadImage ( "detalhes.jpg", img_detalhe ); 

	// inicializando o processo de construção de terreno
	dbSetupTerrain ( ); 

	// Obtendo o handle para o terreno
	dbMakeObjectTerrain ( nTerreno ); 

	// Determinando o mapa de altura
	dbSetTerrainHeightMap ( nTerreno, "mapa_altura.bmp" ); 

	// Ajustando a escala do terreno
	// Mais largo no eixo X e Z; menor no eixo Y
	float escala_x, escala_y, escala_z;
	escala_x = 3.0f; escala_y = 0.6f; escala_z = 3.0f;
	dbSetTerrainScale ( nTerreno, escala_x, escala_y, escala_z ); 

	// Ajustando a iluminação do terreno
	float xdir, ydir, zdir;
	float red, green, blue, intensidade;
	xdir = 1.0f;	ydir = -0.25f;	zdir = 0.0f;
	red = 0.55f;	green = 1.0f;	blue = 0.0f;
	intensidade = 0.2f;
	dbSetTerrainLight ( nTerreno, xdir, ydir, zdir, red, green, blue, intensidade ); 

	// Determinando a textura difusa e a textura de detalhe
	dbSetTerrainTexture ( nTerreno, img_textura, img_detalhe ); 

	// Tudo pronto, agora mostre o terreno
	dbBuildTerrain ( nTerreno ); 

}// endfunction: construir_terreno()

void atualizar_visao() {
// Vamos controlar a camera com as setas
	float nVelocidade = 2.0f;
	float nVelocidadeGiroLateral = 2.0f;
	int nCamera = 0;	// Camera default
    dbControlCameraUsingArrowKeys ( nCamera, nVelocidade, nVelocidadeGiroLateral );            

    // Encontre a altura do terreno na posição da camera
    float xcam, zcam, nAltura;
	xcam = dbCameraPositionX();
	zcam = dbCameraPositionZ();
	nAltura = dbGetTerrainGroundHeight ( nTerreno, xcam, zcam);    

	// Vamos recolocar a camera um pouco acima do chão
    nAltura = nAltura + 10.0f;
	dbPositionCamera ( xcam, nAltura, zcam); 

	// Atualize o terreno
	dbUpdateTerrain ( ); 

} // endfunction: atualizar_visao()