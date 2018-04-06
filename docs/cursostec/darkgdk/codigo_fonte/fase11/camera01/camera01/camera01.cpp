// camera01.cpp
// Esse programa mostra como manipular a camera default
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void teclado();				// Interpreta o teclado
void texturizar();			// Texturiza a matrix

// Configuração da camera
float xcam = 1005, ycam = 475, zcam = -555; 
float xcam_rot = 0, ycam_rot = 0, zcam_rot = 0; 

// Configuração dos modos
int modo = 1;
int modo_mover = 0;
int modo_cam = 1;
int modo_cam_rot = 4;
int terminar = 0;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys();  

// Criação básica de um terreno com o posicionamento da câmera para visualizá-lo
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbMakeMatrix (1,2000,10000,10,50);
dbPrepareMatrixTexture (1,1,2,2);
texturizar();

// Looping principal
while ( LoopGDK ( ) ) { 
	if (terminar == 0) teclado();
	dbSync ( );

	if (terminar == 1)
	{
		dbDeleteImage (1);	dbDeleteMatrix (1);			
		return;
	} // endif
 } // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("camera01.cpp"); 
dbSetTextOpaque();
dbDisableEscapeKey();
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
dbPositionCamera (1005, 475, -600);

} // texturizar().fim


// ----------------------------------------------------------------------------
// teclado() - Lê o teclado e executa comandos do usuário
void teclado() {
	char sinfo[255];

	// Lê o teclado
	char *stecla="??";	
	stecla = dbInKey();

	if (dbEscapeKey()) terminar = 1;

	// Troca de modo
	if (!strcmp(stecla, "0")) modo = modo_mover;
	if (!strcmp(stecla, "c")) modo = modo_cam;
	if (!strcmp(stecla, "r")) modo = modo_cam_rot;

	// Movimentação dos objetos
	if (dbUpKey())
	{
		if (modo == modo_cam) zcam++;
		if (modo == modo_cam_rot) zcam_rot++;
	} // endif

	if (dbDownKey())
	{
		if (modo == modo_cam) zcam--;
		if (modo == modo_cam_rot) zcam_rot--;		
	} // endif

	if (dbLeftKey())
	{
		if (modo == modo_cam) xcam--;
		if (modo == modo_cam_rot) xcam_rot--;	
	} // endif

	if (dbRightKey())
	{
		if (modo == modo_cam) xcam++;
		if (modo == modo_cam_rot) xcam_rot++;		
	} // endif
	

	if (dbKeyState(201)) {
	if (modo == modo_cam) ycam++;	// page_up;
	if (modo == modo_cam_rot) ycam_rot++;
	} // endif

	if (dbKeyState(209)) {
	if (modo == modo_cam) ycam--;	// page_down;
	if (modo == modo_cam_rot) ycam_rot--;	
	} // endif		
	
	// Testando função de movimento
	if (!strcmp(stecla, "u")) modo = 0;
	if (!strcmp(stecla, "u")) dbMoveCamera (5.0f);
	
	// Mostra informações na tela
	if (modo == modo_cam) 
	{
		dbText (10,10, "modo = modo_cam - (r) para modo rotacionar - (u) - mover");
		sprintf (sinfo, "xcam:%f ycam:%f zcam:%f", xcam, ycam, zcam);
		dbText (10,30, sinfo);	
		if (!strcmp(stecla, "m")) dbWriteToClipboard(sinfo);
	} // endif
	
	if (modo == modo_cam_rot) 
	{
		dbText (10,10, "modo = modo_cam_rot - (c) para modo posicionar camera");
		sprintf (sinfo, "xcam_rot:%f ycam_rot:%f zcam_rot:%f", xcam_rot, ycam_rot, zcam_rot);
		dbText (10,30, sinfo);	
		if (!strcmp(stecla, "m")) dbWriteToClipboard(sinfo);
	} // endif

	// Resseta o teclado
	strcpy(stecla,"??");

	if (modo > modo_mover) dbPositionCamera (xcam, ycam, zcam);
	dbRotateCamera (xcam_rot, ycam_rot, zcam_rot);	

} // teclado().fim