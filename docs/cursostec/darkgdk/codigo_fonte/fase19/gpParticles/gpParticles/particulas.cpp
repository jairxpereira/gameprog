// particulas.cpp
// Esse programa mostra o uso do sistema de partículas
#include "DarkGDK.h"
#include "windows.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void teclado();				// Interpreta o teclado
void texturizar();			// Texturiza a matrix
void gpParticles();			// Testa Partículas

// Configuração da camera
float xcam = 1005, ycam = 475, zcam = -555;
float xcursor = 975, ycursor = 535, zcursor = -320;
float xcam_rot = 0, ycam_rot = 0, zcam_rot = 0;

// Configuração dos modos
int modo = 6;
int modo_cam = 1;
int modo_cam_rot = 4;
int modo_cursor = 6;
int terminar = 0;

const int img_fire = 3;
const int obj_cursor = 2;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

// Criação básica de um terreno com o posicionamento da câmera para visualizá-lo
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\fire.bmp",img_fire);

// Carrega solda e sua textura
dbSetDir ("c:\\gameprog\\gdkmedia\\Modelos\\German");
dbLoadImage ("german.dds",2);
dbLoadObject ("H-German-Idle.x",1);

// Texturiza o soldado
dbTextureObject (1,2);

// Nosso cursor 3D
dbMakeObjectSphere(obj_cursor,10);

initsys();

// Faz o terreno do cenário
dbMakeMatrix (1,2000,10000,10,50);
dbPrepareMatrixTexture (1,1,2,2);
texturizar();

// Ajusta escala do objeto e ponto de apoio
dbScaleObject (1,12000,12000,12000);
dbFixObjectPivot(1);

// Ajusta câmera e posiciona objeto na cena
dbPositionCamera (1005, 475, -600);
dbPositionObject (1, 970, 300, -185);

dbSyncOn();

// Looping principal
while ( LoopGDK ( ) ) {
	if (terminar == 0) teclado();
	dbSync ( );
	if (terminar == 1)
	{
		dbDeleteImage (1);	dbDeleteImage(img_fire);
		dbDeleteImage(2);
		dbDeleteMatrix (1);
		dbDeleteObject (1);dbDeleteObject (obj_cursor);
		return;
	} // endif
 } // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("particulas.cpp");
dbSetTextTransparent();
dbDisableEscapeKey();
dbSyncRate(60);
dbSetAmbientLight(100);
dbPositionMouse(1,1);
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

	// Lê o teclado
	char *stecla="??";
	stecla = dbInKey();

	if (dbEscapeKey()) terminar = 1;

	if (dbMouseClick() == 1) gpParticles();

	// Troca de modo
	if (!strcmp(stecla, "c")) modo = modo_cam;
	if (!strcmp(stecla, "r")) modo = modo_cam_rot;
	if (!strcmp(stecla, "f")) modo = modo_cursor;

	// Movimentação dos objetos
	if (dbUpKey())
	{
		if (modo == modo_cam) zcam++;
		if (modo == modo_cam_rot) zcam_rot++;
		if (modo == modo_cursor) zcursor += 5;

	} // endif

	if (dbDownKey())
	{
		if (modo == modo_cam) zcam--;
		if (modo == modo_cam_rot) zcam_rot--;
		if (modo == modo_cursor) zcursor -= 5;
	} // endif

	if (dbLeftKey())
	{
		if (modo == modo_cam) xcam--;
		if (modo == modo_cam_rot) xcam_rot--;
		if (modo == modo_cursor) xcursor -= 5;
	} // endif

	if (dbRightKey())
	{
		if (modo == modo_cam) xcam++;
		if (modo == modo_cam_rot) xcam_rot++;
		if (modo == modo_cursor) xcursor += 5;
	} // endif


	if (dbKeyState(201)) {
	if (modo == modo_cam) ycam++;	// page_up;
	if (modo == modo_cam_rot) ycam_rot++;
	if (modo == modo_cursor) ycursor += 5;
	} // endif

	if (dbKeyState(209)) {
	if (modo == modo_cam) ycam--;	// page_down;
	if (modo == modo_cam_rot) ycam_rot--;
	if (modo == modo_cursor) ycursor -= 5;
	} // endif


	// Mostra informações na tela
	if (modo == modo_cam)
	{
		dbText (10,10, "modo = modo_cam - (r) para modo rotacionar (f) cursor");
		sprintf (sinfo, "xcam:%f ycam:%f zcam:%f", xcam, ycam, zcam);
		dbText (10,30, sinfo);
		dbText (10,50, "(clique) - aciona sistema de particulas");
	} // endif

	if (modo == modo_cam_rot)
	{
		dbText (10,10, "modo = modo_cam_rot - (c) posicionar camera (f) cursor");
		sprintf (sinfo, "xcam_rot:%f ycam_rot:%f zcam_rot:%f", xcam_rot, ycam_rot, zcam_rot);
		dbText (10,30, sinfo);
		dbText (10,50, "(clique) - aciona sistema de particulas");
	} // endif

		if (modo == modo_cursor)
	{
		dbText (10,10, "modo = modo_cursor - (c,r) para posicionar ou rotacionar a camera");
		sprintf (sinfo, "xcursor:%f ycursor:%f zcursor:%f ", xcursor, ycursor, zcursor);
		dbText (10,30, sinfo);
		dbText (10,50, "(clique) - aciona sistema de particulas");
		// dbPointCamera (xcursor, ycursor, zcursor);
		dbPositionObject(obj_cursor,xcursor, ycursor, zcursor);
		} // endif

	// Resseta o teclado
	strcpy(stecla,"??");

	dbPositionCamera (xcam, ycam, zcam);
	dbRotateCamera (xcam_rot, ycam_rot, zcam_rot);

} // teclado().fim

void gpParticles()
{
	// Criação de partículas
	int partic_sys  = 1;

	// Quantidade máxima de partículas
	int partic_max = 50;

	// Raio de emissão das partículas
	float raio = 20.0f;

	// Cor das partículas
	int r,g,b;
	r= g = b = 255;
	
	// Frequência de emissão das partículas
	float partic_tempo = 0.01f;

	// Gravidade da queda
	float partic_gravidade = 2.0f;

	// Quantidade de partículas na emissão
	int partic_qtd = 10;
	
	// 1- Liga piso 0 - Desliga piso
	int lPiso = 0;

	// 0-5 Modo ghost
	int modo_ghost = 2;

	// Cria o sistema de partículas
	dbMakeParticles ( partic_sys , img_fire, partic_max, raio);
	
	// Configura cor, posição e taxa de emissão
	dbColorParticles ( partic_sys, r, g, b );
	dbPositionParticles ( partic_sys, xcursor, ycursor, zcursor);
	dbSetParticleEmissions ( partic_sys, partic_qtd );

	// Configura velocidade de emissão e gravidade
	dbSetParticleSpeed ( partic_sys, partic_tempo );
	dbSetParticleGravity ( partic_sys, partic_gravidade );

	// Configura efeito piso e efeito fantasma (ghost)
	dbSetParticleFloor(partic_sys, lPiso);
	dbGhostParticlesOn(partic_sys, modo_ghost);

} // gpParticles().fim
