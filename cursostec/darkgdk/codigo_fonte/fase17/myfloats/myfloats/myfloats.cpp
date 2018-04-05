// myfloats.cpp
// Este programa ilustra como salvar e carregar(load) status de jogo(savegame)
#include "DarkGDK.h"

// Protótipo das funções
void initsys();					// inicializa o sistema
void MsgInfo(char *cText);		// Mostra uma mensagem na tela
void savegame(void);			// Salva jogo
void loadgame(void);			// Carrega jogo

// Flag para terminar o programa. 1 = terminar
int terminar = 0;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys(); 

savegame();	loadgame();

// Looping principal
while ( LoopGDK ( ) ) { 
	if (dbMouseClick() == 2) terminar = 1;
	if (terminar == 1) break;
 dbSync ( );	
 } // fim do while
return;
} // endfunction DarkGDK()

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbCLS ( 0xFFFFFF); dbInk( 0x0000FF, 0xFFFFFF );
dbSetWindowTitle("myfloats.cpp"); dbSetTextOpaque();
} // initsys().fim

// ----------------------------------------------------------------------------
void MsgInfo(char *cText) {
	MessageBox(0, cText, "myfloats.cpp", MB_OK);
}// endfuncion MsgInfo

// ----------------------------------------------------------------------------
void savegame(void) {

	char *sArquivo = "myfloats.sav";	
	char sinfo[255];
	
	if (dbFileExist(sArquivo) == 1) dbDeleteFile(sArquivo);
		
	float x = 320.10f;	float y = 240.11f;	float z = 100.12f;

	// Abre o arquivo e verifica que está ok
	dbPrint(" ");
	int hfile = 6;
	dbOpenToWrite(hfile,sArquivo);		
	if(dbFileOpen(hfile))
	{
		dbPrint(" savegame() ok - Arquivo criado/aberto com sucesso!");
	}
	else
	{
	MsgInfo(" Arquivo não foi aberto com sucesso!");
	return;
	} // endif	

	// Grava os dados
	dbWriteFloat (hfile, x);
	dbWriteFloat (hfile, y);
	dbWriteFloat (hfile, z);	
	
	// Mostra os dados gravados
	dbPrint(" ");
	dbPrint(" Dados gravados: ");
	sprintf(sinfo, " Posicao do jogador: (%f, %f, %f)",x,y,z);
	dbPrint(sinfo);

	// Fechando o arquivo
	dbCloseFile(hfile);
	dbPrint(" ");

} // endfunction: savegame()

// ----------------------------------------------------------------------------
void loadgame() {
	char *sArquivo = "myfloats.sav";
	char sinfo[255];

	if (dbFileExist(sArquivo) != 1)
	{		
		MsgInfo(" Arquivo myfloats.sav não existe");
		return;
	}
		
	float u, v, w;
	u = v = w = 0.0f;

	// Mostra variáveis antes da leitura
	dbPrint(" ");
	dbPrint(" ----------------------- loadgame() ok --------------------------");
	sprintf(sinfo, " Posicao do jogador: (%f, %f, %f)",u,v,w);	
	dbPrint(" Valores das variaveis antes da leitura:");
	dbPrint(sinfo);

	// Abre e verifica arquivo
	int hfile = 2;
	dbOpenToRead(hfile,sArquivo);
	if(dbFileOpen(hfile))
	{
		dbPrint(" ");
		dbPrint(" loadgame() ok - Arquivo aberto com sucesso para leitura!");
	}
	else 
	{
	 MsgInfo(" Arquivo não foi aberto com sucesso!");
	return;
	}
		
	dbReadFloat ( hfile, &u);
	dbReadFloat ( hfile, &v);
	dbReadFloat ( hfile, &w);	

	dbPrint(" "); dbPrint(" Variaveis depois da leitura: ");
	sprintf(sinfo, " Posicao do jogador: (%f, %f, %f)",u,v,w);		
	dbPrint(sinfo);
	
	// Fechando o arquivo...
	dbCloseFile(hfile);

} // endfunction: loadgame
