// modeloAnimado.cpp
// Esse programa ilustra como animar um modelo
#include "DarkGDK.h"
#include "windows.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void teclado();				// Interpreta o teclado
void texturizar();			// Texturiza a matrix

// Rotação do objeto
float xobj_rot = 0, yobj_rot = 0, zobj_rot = 0; 

// Configuração dos modos. Vamos permitir rotacionar o objeto
int modo = 5;
int modo_obj_rot = 5;
int terminar = 0;

// Controle de quadro
int nframe = 111;
int fr_inicial = 111;
int fr_final = 136;

// Controle de tempo
int TempoFinal = 0;
int TempoInicial = 0;
int TempoDecorrido = 0;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk 

// Carrega modelo e fixa pasta de trabalho
dbSetWindowTitle("Aguarde...");
dbLoadImage ("c:\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp",1);
dbSetDir ("c:\\gameprog\\gdkmedia\\Modelos\\German");

// Carrega textura do soldado
dbLoadImage ("german.dds",2);

// 0 - 50 Morrendo...
dbLoadObject ("H-German-Die.x",1);
int nframes = 0;
TempoInicial = dbTimer();

// 51-75 Atirando....
nframes = dbTotalObjectFrames(1) + 1;
dbAppendObject ("H-German-Attack1.x", 1, nframes);

// 76-86 Impacto (Soldado sendo atingido)
nframes = dbTotalObjectFrames(1) + 1;
dbAppendObject ("H-German-Impact.x", 1, nframes);

// 87-110 Ocioso 
nframes = dbTotalObjectFrames(1) + 1;
dbAppendObject ("H-German-Idle.x", 1, nframes);

// 111-135 Caminhando 
nframes = dbTotalObjectFrames(1) + 1;
dbAppendObject ("H-German-Move.x", 1, nframes);

// Texturiza o soldado
dbTextureObject (1,2);

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

	TempoFinal = dbTimer();

	if (terminar == 0) teclado();

	dbSync ( );

	if (terminar == 1)
	{
		dbDeleteImage (1);	dbDeleteMatrix (1);	
		dbDeleteObject (1);
		return;
	} // endif
 } // fim do while
return;
} // fim da função: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetWindowTitle("modeloAnimado.cpp"); 
dbDisableEscapeKey();
dbSyncRate(60);
dbSetAmbientLight(100);

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

	// Mostre total de frames se tecla = 'p'
	if (!strcmp(stecla, "p")) 
	{
	int nfram = dbTotalObjectFrames (1);
	sprintf (sinfo, "total de frames: %d", nfram);
	dbSetWindowTitle (sinfo);
	} // fim do if	

	// Morrer
	if (!strcmp(stecla, "s"))
	{			
		fr_inicial = 0;
		fr_final = 50;
		dbSetWindowTitle ("[00,50] Morrer - 's' ");
	} // endif

	// Atirando...
	if (!strcmp(stecla, "a"))
	{
		// Atirar
		fr_inicial = 51;
		fr_final = 75;
		dbSetWindowTitle ("[51,75] Atirar - 'a' ");		
	} // endif

	// Levando tiro...
	if (!strcmp(stecla, "z"))
	{		
		fr_inicial = 76;
		fr_final = 86;
		dbSetWindowTitle ("[76,86] Sendo atingido - 'z'");
	} // endif


	// ocioso
	if (!strcmp(stecla, "x"))
	{			
		fr_inicial = 87;
		fr_final = 110;
		dbSetWindowTitle ("[87,110] Ocioso - 'x'");
	} // endif


	// ocioso
	if (!strcmp(stecla, "d"))
	{		
		fr_inicial = 111;
		fr_final = 135;
		dbSetWindowTitle ("[111,135] Caminhando - 'd'");
	} // endif


	// Rotação do soldado via teclado
	if (dbUpKey()) zobj_rot++;
	if (dbDownKey()) zobj_rot--;
	if (dbLeftKey()) xobj_rot--;
	if (dbRightKey()) xobj_rot++;			
	if (dbKeyState(201)) yobj_rot++;
	if (dbKeyState(209)) yobj_rot--;			

   // Mostra informações na tela	
   sprintf (sinfo, " s - morrer\n a - atirar\n z - atingido\n x - ocioso\n d - andar ");
   dbText (10,30, sinfo);
   dbRotateObject (1,xobj_rot, yobj_rot, zobj_rot);
  
	// Resseta o teclado
	strcpy(stecla,"??");
	
	// Verifica se passou 30ms para avançar o quadro
	TempoDecorrido = TempoFinal - TempoInicial;
	if (TempoDecorrido > 30) 
	{
	nframe = nframe + 1;
	TempoInicial = dbTimer();
	}	
	
	// Se o frame for o último volte para o começo!
	if (nframe >= fr_final) nframe = fr_inicial;
	
	// Configura o quadro desejado
	dbSetObjectFrame (1, nframe);

	
} // teclado().fim