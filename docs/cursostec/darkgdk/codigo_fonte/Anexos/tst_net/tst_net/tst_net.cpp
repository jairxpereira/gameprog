// tst_net.cpp 
// Esse programa ilustra acesso a arquivos remoto via protocolo FTP
#include "DarkGDK.h"
void initsys();
void tst_net();
void showlist (char *slista[], int nlista, int xcol, int ylin); 
const int branco = 0xffffff;
const int azul = 0x0000ff;


char sUsername[255];
int id = 0;

char* criar_nome_usuario(char *snome);
char *msg = NULL;

void msginfo( char *text);
void msginfo( char *text, char *title);

void mostrar_conex(void);		// Mostra tipos de conexões disponível
void mostrar_sessao(void);		// Mostra sessões disponíveis
void mostrar_jogador(void);		// Mostra jogadores da sessão
void enviar_lista_arquivo();	// Enviar lista de arquivos
void salvar_arquivo(int nval);


void DarkGDK ( void )
{

    initsys();
    tst_net();
     

    while ( LoopGDK ( ) )
    {           
        dbSync ( );
    }
 
    return;
} // DarkGdk().end


void initsys() {
dbSyncOff();
dbSetDisplayMode(640,480,32);
dbSetWindowOn();
dbInk (azul, branco);
dbCLS(branco);
dbPositionMouse (1,1);
dbSetWindowTitle("tst_net.cpp");
dbSetWindowPosition(320,50);
dbText (10,70,"Aguarde. Conectando em rede...");
dbSync();

} // initsys().end

void tst_net() {

criar_nome_usuario(sUsername);


// Vamos fazer uma conexão de rede
id = dbDefaultNetGame("chat", sUsername, 2, 0);

int cnx_sucesso = 0;

cnx_sucesso = dbNetGameExists();

char *slista[] = {"1- dbPerformChecklistForNetConnections()", 
"2- dbPerformChecklistForNetSessions()", 
"3- dbPerformChecklistForNetPlayers()", 
"Botao esquerdo - Envia oi para user 02", "q- break ",
"4- Enviar lista de arquivo"};

dbSetTextOpaque();
dbText (10,70, dbSpaces(40));
if (cnx_sucesso == 1) dbText (10,70, dbStr(id)  );
else dbText (10,70, "Falha na conexao");

int whois = 0;

while (dbMouseClick() != 2) {

 // Faz leitura do teclado
 char *tecla = dbInKey();

if (dbMouseClick() == 1 ) 
{
	
	dbSendNetMessageString (2, "Oi user 02" );
} // Tentativa de mandar mensagem

whois = dbNetMessagePlayerFrom();

if (dbNetMessageType() == 3){
if (whois == 2) msg = dbNetMessageString();
msginfo (msg);
}


showlist (&slista[0], 6, 200, 10);



if (!strcmp(tecla,"1")) {
	mostrar_conex();
	
}//endif

if (!strcmp(tecla,"2")) {
	mostrar_sessao();
} //endif

if (!strcmp(tecla,"3")) {
	mostrar_jogador();
} //endif

    if  (!strcmp(tecla,"4")) 
	{
		enviar_lista_arquivo();
    } // endif

    if  (!strcmp(tecla,"q"))break;

    if  (!strcmp(tecla,"6")) {
        //upload file        
    } // endif

 // Resseta teclado
 strcpy (tecla, "??");  

// Pega tipo de arquivo: 0:arquivo 1:Dir
dbText(10,200, "dbNetGameNowHosting()");
dbText(10,220, "-------------------");
// Limpa os dados anteriores
dbText(10,240, dbSpaces(40));
dbText(10,240, dbStr (dbNetGameNowHosting() )); 

// Pega tamanho do arquivo
dbText (200,200, "dbNetMessageType()" );
dbText (200,220, "------------------" );
// Limpa os dados anteriores
dbText (200,240, dbSpaces(40));
dbText (200,240, dbStr (dbNetMessageType() )); 

// Pega nome do arquivo
dbText (390,200, "dbNetMessageString()" );
dbText (390,220, "------------------" );
// Limpa os dados anteriores
if (dbNetMessageType() == 3) {
dbText (390,240, dbSpaces(40));
dbText (390,240, msg ); 
msginfo("pausa para leitura");

dbGetNetMessage();
if (dbNetMessageType() == 1)
{
	int myword = 0;
	myword = dbNetMessageInteger();
	salvar_arquivo(myword);
}

if (!strcmp("notepad", msg) ) 
ShellExecute (0, "open", "c:\\windows\\notepad.exe", NULL, NULL, SW_SHOWNORMAL);
} // Verifica string

// Pega progresso do download: -1 completo
dbText(10,280, "dbNetGameExists()");
dbText(10,300, "-------------------");
// Limpa os dados anteriores
dbText(10,320, dbSpaces(40));
dbText(10,320, dbStr( dbNetGameExists())); 

// Pega status da conexão 1:conectado 0:desconectado
dbText(200,280, "dbNetMessageExists()");
dbText(200,300, "-------------------");
// Limpa os dados anteriores
dbText(200,320, dbSpaces(40));
dbText(200,320, dbStr ( dbNetMessageExists())); 

// Obtém nome da pasta
dbText(390,280, "dbNetGameLost()");
dbText(390,300, "-------------------");
// Limpa os dados anteriores
dbText(390,320, dbSpaces(40));
dbText(390,320, dbStr ( dbNetGameLost() )); 


// Verifica se houve erro: 0:Ok 1:erro
dbText(10,360, "dbNetMsgPlayerFrom()");
dbText(10,380, "-------------------");
// Limpa os dados anteriores
dbText(10,400, dbSpaces(40));
dbText(10,400, dbStr ( dbNetMessagePlayerFrom() )); 

// Pega nome do erro
dbText(200,360, "dbNetBufferSize()");
dbText(200,380, "-------------------");
// Limpa os dados anteriores
dbText(200,400, dbSpaces(40));
dbText(200,400, dbStr(dbNetBufferSize())); 

// Faz leitura da mensagem da rede
dbGetNetMessage();

} // endwhile

// Desconecta
dbCLS(branco); dbCenterText (320,240, "dbFreeNetGame()");
dbFreeNetGame();
dbCLS(branco); dbCenterText (320,240, "Pressione ESC para sair.");
dbWaitKey();
dbSync();

} // endfunc: tst_net()


void showlist (char *slista[], int nlista, int xcol, int ylin) {
//*** showlist - Mostras lista de opções

int ncx = 0;
char *stemp;

int leapline = 20;

dbSetTextOpaque();

for (ncx = 0; ncx < nlista; ncx++)
{
 stemp = slista[ncx];
 dbInk (azul, branco);
 dbText (xcol, ylin, stemp);
 ylin = ylin + leapline;
 dbSync();
 } // endfor
} // endfunc: showlist

char* criar_nome_usuario(char *snome)
{
// Essa função cria um nome aletório de usuário
strcat (snome, "nome-");
dbRandomize (dbTimer());
strcat (snome, dbStr ( dbRnd(5000)) );
return snome;
}

void msginfo(char *text)
{
// Essa função mostrar um texto na tela
MessageBox (0, text, "tst_net", MB_OK);
}

void msginfo(char *text, char *title)
{
// Essa função mostrar um texto na tela com título

MessageBox (0, text, title, MB_OK);
}

void mostrar_conex(void) 
{
// Essa função mostra os tipos de conexões disponíveis

	int ncx = 0;
	int nqtd = 0;
	char *rede = NULL;

	dbPerformChecklistForNetConnections();
	nqtd = dbChecklistQuantity();
	
	for (ncx=1; ncx <= nqtd; ncx++)
	{
		rede = dbChecklistString( ncx);
	msginfo( rede, dbStr(ncx) );		
	} // endfor

} // mostrar_conex


void mostrar_sessao(void) 
{
	// Essa função mostra a lista de sessões abertas
	int ncx = 0;
	int nqtd = 0;
	char *sessao = NULL;

	dbPerformChecklistForNetSessions();
	nqtd = dbChecklistQuantity();

	if (nqtd == 0) msginfo ("Zero (0) sessões", 
		"dbPerformChecklistForNetSessions()");
	
	for (ncx=1; ncx <= nqtd; ncx++)
	{
		sessao = dbChecklistString( ncx);
	msginfo( sessao, dbStr(ncx) );		
	} // endfor

} // mostrar_conex


void mostrar_jogador(void) 
{
	// Essa função mostra os jogadores da sessão
	int ncx = 0;
	int nqtd = 0;
	char *jogador = NULL;

	dbPerformChecklistForNetPlayers();

	nqtd = dbChecklistQuantity();
	
	for (ncx=1; ncx <= nqtd; ncx++)
	{
		jogador = dbChecklistString( ncx);
	msginfo( jogador, dbStr(ncx) );		
	} // endfor

} // mostrar_conex

void enviar_lista_arquivo()
{
	
// Vamos mostrar os arquivos da pasta c:\Gameprog
int ncx=0;
char *cArquivo;
int ntam = 0;
dbPerformCheckListForFiles();
ntam = dbChecklistQuantity();
for (ncx=1; ncx <= ntam; ncx++)
 {
 cArquivo =  dbChecklistString (ncx); 
 dbSendNetMessageString (2, cArquivo);
 } // endfor 
 dbSendNetMessageString (2, "arquivo");
}// enviar_lista_arquivo().end


void salvar_arquivo(int nval)
{
	dbPrint ( dbStr(nval) );


}// salvar_arquivo().end











