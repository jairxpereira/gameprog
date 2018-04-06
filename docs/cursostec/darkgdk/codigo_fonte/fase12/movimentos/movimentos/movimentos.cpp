// movimentos.cpp
// Esse programa mostra como aplicar certos movimentos ao objeto
// Testamos aqui as funções dbTurnObjectLeft, dbTurnObjectRight, 
// dbRollObjectLeft, dbRollObjectRight, dbPitchObjectDown, dbPitchObjectUp
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void teclado();				// Interpreta o teclado
void texturizar();			// Texturiza a matrix
void primitiva3d();			// Desenha uma primitiva 3d para teste


// Configuração da camera
float xcam = 1005, ycam = 475, zcam = -555; 
float xcam_rot = 0, ycam_rot = 0, zcam_rot = 0; 

// Espaço para mensagens de informação
char sCmd[255]; 
char sinfo[255]; 

int nInicializado = 0;

// Configuração dos modos
int modo = 1;
int modo_especifico = 1;
int modo_geral = 4;
int terminar = 0;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys();  

// Criação básica de um terreno 
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbMakeMatrix (1,2000,10000,10,50);
dbPrepareMatrixTexture (1,1,2,2);
primitiva3d();
texturizar();

// Looping principal
while ( LoopGDK ( ) ) { 
	if (terminar == 0) teclado();
	dbSync ( );

	if (terminar == 1)
	{
		dbDeleteImage (1);	dbDeleteMatrix (1);	
		dbDeleteObject(3);
		return;
	} // endif
 } // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("movimentos.cpp"); 
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
		
	// Zera mensagem na inicilização do programa
	if (nInicializado == 0)
	{
	strcpy(sCmd, "movimentos.cpp");
	nInicializado = 1;
	}

	// Lê o teclado
	char *stecla="??";	
	stecla = dbInKey();

	// Troca de modo
	if (!strcmp(stecla, "e")) modo = modo_especifico;
	if (!strcmp(stecla, "g")) modo = modo_geral;
	if (!strcmp(stecla, "q")) terminar = 1;

	// Movimentação dos objetos
	if (dbUpKey())
	{
		if (modo == modo_especifico) dbRollObjectLeft(3,5);	
		if (modo == modo_especifico) sprintf(sCmd,"%s","dbRollObjectLeft(3,5)");	
		
		if (modo == modo_geral) 
		{
			zcam_rot--;	
			sprintf(sCmd, "dbZRotateObject(3, zcam_rot= %f )", zcam_rot);
			dbZRotateObject (3,zcam_rot);

		} // fim do if(modo_geral)	
	} // endif(upkey)

	if (dbDownKey())
	{
		if (modo == modo_especifico) dbRollObjectRight(3,5);
		if (modo == modo_especifico) sprintf(sCmd, "%s","dbRollObjectRight(3,5)");
		
		if (modo == modo_geral)
		{
			zcam_rot++;
			sprintf(sCmd, "dbZRotateObject(3, zcam_rot= %f )", zcam_rot);
		dbZRotateObject (3,zcam_rot);
		} // fim do if(modo_geral)
	} // endif(downkey)

	if (dbLeftKey())
	{
		if (modo == modo_especifico) dbPitchObjectUp(3,5);
		if (modo == modo_especifico) sprintf(sCmd, "%s", "dbPitchObjectUp(3,5)");
		
		if (modo == modo_geral) 
		{
		xcam_rot--;	
		sprintf(sCmd, "dbXRotateObject(3, xcam_rot= %f )", xcam_rot);
		dbXRotateObject(3,xcam_rot);
		} // fim do if (modo_geral)	
	} // endif (lefkey)

	if (dbRightKey())
	{
		if (modo == modo_especifico) dbPitchObjectDown(3,5);
		if (modo == modo_especifico) sprintf(sCmd, "%s","dbPitchObjectDown(3,5)");
		
		if (modo == modo_geral)
		{
		sprintf(sCmd, "dbXRotateObject (3, xcam_rot= %f )",xcam_rot );
		xcam_rot++;	
		dbXRotateObject(3,xcam_rot);		
		} // fim do if(modo_geral)
	} // endif (rightkey)
	

	if (dbKeyState(201)) {
	if (modo == modo_especifico) dbTurnObjectLeft(3, 5);
	if (modo == modo_especifico) sprintf(sCmd, "%s","dbTurnObjectLeft(3, 5)");
	
	if (modo == modo_geral) 
		{
		ycam_rot++;
		sprintf(sCmd, "dbYRotateObject(3, ycam_rot= %f )", ycam_rot);
		dbYRotateObject(3, ycam_rot);
		} // fim do if(modo_geral)
	} // endif (page_up)

	if (dbKeyState(209)) {
	if (modo == modo_especifico) dbTurnObjectRight(3,5);	// page_down;
	if (modo == modo_especifico) sprintf(sCmd, "%s","dbTurnObjectRight(3,5)");	// page_down;
	
	if (modo == modo_geral) 
		{
		ycam_rot--;	
		sprintf(sCmd, "dbYRotateObject(3, ycam_rot= %f )", ycam_rot);
		dbYRotateObject(3,ycam_rot);
		} // fim do if(modo_geral)
	} // endif (page_down)
	

	// Mostra informações na tela
	if (modo == modo_especifico) 
	{
		dbText (10,10, "modo = modo_especifico - (g) para rotacao geral - (q) Terminar");		
		dbText (10,30, "cima/baixo - esquerda/direita - page_up/page_down");
		dbText (10,50, sCmd);
	} // endif
	
	if (modo == modo_geral) 
	{
		dbText (10,10, "modo = modo_geral - (e) para rotacao especifica");
		sprintf (sinfo, "xcam_rot:%f ycam_rot:%f zcam_rot:%f", xcam_rot, ycam_rot, zcam_rot);
		dbText (10,30, sinfo);	
		dbText (10,50, sCmd);
		if (!strcmp(stecla, "m")) dbWriteToClipboard(sinfo);
	} // endif

	// Resseta o teclado
	strcpy(stecla,"??");	

} // teclado().fim

void primitiva3d() {
dbMakeObjectBox(3,50,200,200); dbPositionObject(3,816,200,175);
// Aplicando cor ao objeto
dbColorObject (3, dbRGB(0,0,255));
// Rodando o box
dbRotateObject (3,0,-25,0);
} // primitiva3d().fim

