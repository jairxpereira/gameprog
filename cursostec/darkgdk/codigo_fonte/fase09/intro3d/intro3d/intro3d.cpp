// intro3d.cpp
// Esse programa é um teste de camera
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void teclado();				// Interpreta o teclado
void texturizar();			// Texturiza a matrix

float xcam = 1005, ycam = 475, zcam = -555; 
float xobj = 950, yobj = 220, zobj = 175;  
float xlig = 945, ylig = 485, zlig = 180;

float xcam_rot = 0, ycam_rot = 0, zcam_rot = 0; 
float xobj_rot = 0, yobj_rot = 0, zobj_rot = 0; 


int modo = 1, modo_cam = 1, modo_obj = 2, modo_lig = 3;
int modo_cam_rot = 4, modo_obj_rot = 5;


// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys();  

// Criação básica de um terreno com o posicionamento da câmera para visualizá-lo
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbMakeMatrix (1,2000,10000,10,50);
dbPrepareMatrixTexture (1,1,2,2);
texturizar();

dbMakeObjectCube (1,50);
dbPositionObject (1,xobj, yobj, zobj);

dbMakeLight(1);
dbMakeObjectSphere (2,10);
dbPositionLight (1,xlig, ylig, zlig);
dbPositionObject (2,xlig, ylig, zlig);

dbColorLight (1, dbRGB(0,255,0));
dbColorAmbientLight ( dbRGB(0,255,0) ); 
dbSetAmbientLight (10) ;

while ( LoopGDK ( ) ) { 
	teclado();
	dbSync ( );
 } // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetDisplayMode (800,600,32);
dbSetWindowSize (800,600);
dbSetWindowTitle("Intro3d.cpp"); 
dbSetTextOpaque();
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

	// Troca de modo
	if (!strcmp(stecla, "0")) modo = 0;
	if (!strcmp(stecla, "c")) modo = modo_cam;
	if (!strcmp(stecla, "o")) modo = modo_obj;
	if (!strcmp(stecla, "l")) modo = modo_lig;

	if (!strcmp(stecla, "1")) modo = modo_cam_rot;
	if (!strcmp(stecla, "2")) modo = modo_obj_rot;

	// Movimentação dos objetos
	if (dbUpKey())
	{
		if (modo == modo_cam) zcam++;
		if (modo == modo_cam_rot) zcam_rot++;
		if (modo == modo_obj_rot) zobj_rot++;

		if (modo == modo_obj) zobj++;
		if (modo == modo_lig) zlig++;

	} // endif

	if (dbDownKey())
	{
		if (modo == modo_cam) zcam--;
		if (modo == modo_cam_rot) zcam_rot--;
		if (modo == modo_obj_rot) zobj_rot--;

		if (modo == modo_obj) zobj--;
		if (modo == modo_lig) zlig--;
	} // endif

	if (dbLeftKey())
	{
		if (modo == modo_cam) xcam--;
		if (modo == modo_cam_rot) xcam_rot--;
		if (modo == modo_obj_rot) xobj_rot--;

		if (modo == modo_obj) xobj--;
		if (modo == modo_lig) xlig--;
	} // endif

	if (dbRightKey())
	{
		if (modo == modo_cam) xcam++;
		if (modo == modo_cam_rot) xcam_rot++;
		if (modo == modo_obj_rot) xobj_rot++;

		if (modo == modo_obj) xobj++;
		if (modo == modo_lig) xlig++;
	} // endif
	

	if (dbKeyState(201)) {
	if (modo == modo_cam) ycam++;	// page_up;
	if (modo == modo_cam_rot) ycam_rot++;
	if (modo == modo_obj_rot) yobj_rot++;

	if (modo == modo_obj) yobj++;	// page_up;
	if (modo == modo_lig) ylig++;
	} // endif

	if (dbKeyState(209)) {
	if (modo == modo_cam) ycam--;	// page_up;
	if (modo == modo_cam_rot) ycam_rot--;
	if (modo == modo_obj_rot) yobj_rot--;

	if (modo == modo_obj) yobj--;	// page_up;
	if (modo == modo_lig) ylig--;
	} // endif	
	
	
	// Resseta a textura para recuperar o bug de dbShiftMatrixLeft(1);
	if (!strcmp(stecla, "r")) texturizar();

	// Testando move's functions
	if (!strcmp(stecla, "w")) modo = 0;	if (!strcmp(stecla, "s")) modo = 0;
	if (!strcmp(stecla, "a")) modo = 0; if (!strcmp(stecla, "d")) modo = 0;
	if (!strcmp(stecla, "x")) modo = 0;	if (!strcmp(stecla, "u")) modo = 0;

	if (!strcmp(stecla, "w")) dbMoveObject (1,5.0f); 
	if (!strcmp(stecla, "s")) dbMoveObjectUp (1,5.0f);
	if (!strcmp(stecla, "a")) dbMoveObjectLeft (1,5.0f);
	if (!strcmp(stecla, "d")) dbMoveObjectRight (1,5.0f);
	if (!strcmp(stecla, "x")) dbMoveObjectDown (1,5.0f);

	if (!strcmp(stecla, "u")) dbMoveCamera (5.0f);

	
	// Atualiza  e desacelera o atendimento do teclado		
	if (modo == modo_cam) 
	{
		dbText (10,10, "modo = modo_cam");
		sprintf (sinfo, "xcam:%f ycam:%f zcam:%f", xcam, ycam, zcam);
		dbText (10,30, sinfo);	
		if (!strcmp(stecla, "m")) dbWriteToClipboard(sinfo);

	} // endif


	// Atualiza  e desacelera o atendimento do teclado		
	if (modo == modo_cam_rot) 
	{
		dbText (10,10, "modo = modo_cam_rot");
		sprintf (sinfo, "xcam_rot:%f ycam_rot:%f zcam_rot:%f", xcam_rot, ycam_rot, zcam_rot);
		dbText (10,30, sinfo);	
		if (!strcmp(stecla, "m")) dbWriteToClipboard(sinfo);

	} // endif

	if (modo == modo_obj) 
	{
		dbText (10,10, "modo = modo_obj");
		sprintf (sinfo, "xobj:%f yobj:%f zobj:%f", xobj, yobj, zobj);
		dbText (10,50, sinfo);
		if (!strcmp(stecla, "m")) dbWriteToClipboard(sinfo);
	} // endif	


	if (modo == modo_obj_rot) 
	{
		dbText (10,10, "modo = modo_obj_rot");
		sprintf (sinfo, "xobj_rot:%f yobj_rot:%f zobj_rot:%f", xobj_rot, yobj_rot, zobj_rot);
		dbText (10,50, sinfo);
		if (!strcmp(stecla, "m")) dbWriteToClipboard(sinfo);
	} // endif	

	if (modo == modo_lig) 
	{
		dbText (10,10, "modo = modo_lig");
		sprintf (sinfo, "xlig:%f ylig:%f zlig:%f", xlig, ylig, zlig);
		dbText (10,70, sinfo);
		if (!strcmp(stecla, "m")) dbWriteToClipboard(sinfo);
	} // endif	

	// Resseta o teclado
	strcpy(stecla,"??");

	if (modo > 0) dbPositionCamera (xcam, ycam, zcam);
	dbRotateCamera (xcam_rot, ycam_rot, zcam_rot);
	dbRotateObject (1,xobj_rot, yobj_rot, zobj_rot);

	if (modo > 0) dbPositionObject (1,xobj, yobj, zobj);
	dbPositionLight (1,xlig, ylig, zlig);
	dbPositionObject (2,xlig, ylig, zlig);

} // teclado().fim