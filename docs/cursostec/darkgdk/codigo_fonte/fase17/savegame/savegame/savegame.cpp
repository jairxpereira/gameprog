// savegame.cpp
// Este programa ilustra como salvar e carregar(load) status de jogo(savegame)
#include "DarkGDK.h"

// Protótipo das funções
void initsys();					// inicializa o sistema
void MsgInfo(char *cText);		// Mostra uma mensagem na tela
void savegame(void);			// Salva jogo
void loadgame(void);			// Carrega jogo

// Flag para terminar o programa. 1 = terminar
int terminar = 0;

// Elenco de cores
#define nBranco		0xFFFFFF

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys(); 

savegame();
loadgame();

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
dbCLS ( nBranco); dbInk( 0x0000FF, nBranco );
dbSetWindowTitle("savegame.cpp"); dbSetTextOpaque();
} // initsys().fim

// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
void MsgInfo(char *cText) {
	MessageBox(0, cText, "savegame.cpp", MB_OK);
}// endfuncion MsgInfo

void savegame(void) {

	char *sArquivo = "savegame.sav";	
	char sinfo[255];
	
	if (dbFileExist(sArquivo) == 1) dbDeleteFile(sArquivo);
		
	char *sNome = "Jogador01";	// Jogador01
	WORD nVidas = 0x4242;		// 16.962			- codificado em ascii: BB
	long nPontos = 0x43434343;	// 1.128.481.603	- codificado em ascii: CCCC	
	int nSaude = 0x44 ;			// 68				- codificado em ascii: D

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
	dbWriteString (hfile, sNome);
	dbWriteWord (hfile, nVidas);
	dbWriteLong (hfile, nPontos);
	dbWriteByte (hfile, nSaude);

	// Mostra os dados gravados
	dbPrint(" ");
	dbPrint(" Dados gravados: ");
	sprintf(sinfo, 
		" Nome:%s Vidas:%d Saude:%d Pontos:%li", 
		sNome, nVidas, nSaude, nPontos);
	dbPrint(sinfo);

	// Fechando o arquivo
	dbCloseFile(hfile);
	dbPrint(" ");

} // endfunction: savegame()


void loadgame() {
	char *sArquivo = "savegame.sav";
	char sinfo[255];

	if (dbFileExist(sArquivo) != 1)
	{		
		MsgInfo(" Arquivo savegame.sav não existe");
		return;
	}
		
	WORD nv = 0;
	int np = 0;
	unsigned char sn[13]="\0";
	BYTE ns = 0;

	// Mostra variáveis antes da leitura
	dbPrint(" ");
	dbPrint(" ----------------------- loadgame() ok --------------------------");
	sprintf(sinfo, " Nome: %s Vidas: %d Saude: %d Pontos: %li",
		sn, nv, ns, np, ns);	
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

	int ntam = strlen("jogador01");
	for (int ncx=0; ncx < ntam; ncx++) dbReadByte(hfile, &sn[ncx]);
	dbSkipBytes(hfile,2);
	
	//Esta função não está funcionado: ReadString()
	
	dbReadWord ( hfile, &nv);
	dbReadLong (hfile, &np);
	dbReadByte (hfile, &ns);	

	dbPrint(" "); dbPrint(" Variaveis depois da leitura: ");
	sprintf(sinfo, " Nome: %s Vidas: %d Saude: %d Pontos: %li",
		sn, nv, ns, np, ns);	
	dbPrint(sinfo);
	
	// Fechando o arquivo...
	dbCloseFile(hfile);

} // endfunction: loadgame
