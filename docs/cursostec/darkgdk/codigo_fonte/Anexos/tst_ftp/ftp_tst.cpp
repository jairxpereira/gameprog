// tst_ftp.cpp 
// Esse programa ilustra acesso a arquivos remoto via protocolo FTP
#include "DarkGDK.h"
void initsys();
void tst_ftp();
void showlist (char *slista[], int nlista, int xcol, int ylin); 
const int branco = 0xffffff;
const int azul = 0x0000ff;


void DarkGDK ( void )
{

    initsys();
    tst_ftp();
     

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
dbSetWindowTitle("tst_ftp.cpp");
dbSetWindowPosition(320,50);
dbText (10,70,"Aguarde. Conectando ftp...");
dbSync();

} // initsys().end

void tst_ftp() {

bool lUploaded = false;
int cnx_sucesso = 0;

char *slista[] = {"1- ftp find next", "2- download full size", 
"3- ftp find first", "4- download each 1024 bytes", "q- break ",
"6- upload file"};

dbFTPConnect ("ftp.gameprog.com.br", "jairxpereira", "myr2d2");
dbFTPSetDir("//images");
dbFTPFindFirst();

cnx_sucesso = dbGetFTPStatus();
dbSetTextOpaque();
dbText (10,70, dbSpaces(40));
if (cnx_sucesso == 1) dbText (10,70, "Conectado");
else dbText (10,70, "Falha na conexao");

while (dbMouseClick() != 2) {

showlist (&slista[0], 6, 200, 10);

char *tecla = dbInKey();

if (!strcmp(tecla,"1")) {
dbFTPFindNext();
dbSleep (70);
}//endif

if (!strcmp(tecla,"2")) {
dbFTPGetFile ( dbGetFTPFileName(), dbGetFTPFileName() );
} //endif


if (!strcmp(tecla,"3"))dbFTPFindFirst();

    if  (!strcmp(tecla,"4")) 
	{
    // download every 1024 bytes
        dbFTPGetFile ( dbGetFTPFileName(), dbGetFTPFileName(),1024  );

        for (; dbGetFTPProgress()!= -1;)
		{        
        
		dbText(10,280, "dbGetFTPProgress()");
		dbText(10,300, "-------------------");
		// Limpa os dados anteriores
		dbText(10,320, dbSpaces(40));
		dbText(10,320, dbStr(dbGetFTPProgress())); 
        dbFTPProceed ();
        if (dbUpKey()==1) break;
        dbSleep (100);
        } //endfor
    } // endif

    if  (!strcmp(tecla,"q"))break;

    if  (!strcmp(tecla,"6")) {
        //upload file
        if (!lUploaded) dbFTPPutFile ("tst.html");
        if (!lUploaded) dbPrint ("ok");	
        lUploaded = true;	
    } // endif
  

// Pega tipo de arquivo: 0:arquivo 1:Dir
dbText(10,200, "dbGetFTPFileType()");
dbText(10,220, "-------------------");
// Limpa os dados anteriores
dbText(10,240, dbSpaces(40));
dbText(10,240, dbStr(dbGetFTPFileType())); 

// Pega tamanho do arquivo
dbText (200,200, "dbGetFTPFileSize()" );
dbText (200,220, "------------------" );
// Limpa os dados anteriores
dbText (200,240, dbSpaces(40));
dbText (200,240,dbStr (dbGetFTPFileSize())); 

// Pega nome do arquivo
dbText (390,200, "dbGetFTPFileName()" );
dbText (390,220, "------------------" );
// Limpa os dados anteriores
dbText (390,240, dbSpaces(40));
dbText (390,240, dbGetFTPFileName()); 

// Pega progresso do download: -1 completo
dbText(10,280, "dbGetFTPProgress()");
dbText(10,300, "-------------------");
// Limpa os dados anteriores
dbText(10,320, dbSpaces(40));
dbText(10,320, dbStr(dbGetFTPProgress())); 

// Pega status da conexão 1:conectado 0:desconectado
dbText(200,280, "dbGetFTPStatus()");
dbText(200,300, "-------------------");
// Limpa os dados anteriores
dbText(200,320, dbSpaces(40));
dbText(200,320, dbStr(dbGetFTPStatus())); 

// Obtém nome da pasta
dbText(390,280, "dbGetFTPDir()");
dbText(390,300, "-------------------");
// Limpa os dados anteriores
dbText(390,320, dbSpaces(40));
dbText(390,320, dbGetFTPDir()); 


// Verifica se houve erro: 0:Ok 1:erro
dbText(10,360, "dbGetFTPFailure()");
dbText(10,380, "-------------------");
// Limpa os dados anteriores
dbText(10,400, dbSpaces(40));
dbText(10,400, dbStr(dbGetFTPFailure())); 

// Pega nome do erro
dbText(200,360, "dbGetFTPError()");
dbText(200,380, "-------------------");
// Limpa os dados anteriores
dbText(200,400, dbSpaces(40));
dbText(200,400, dbGetFTPError()); 

} // endwhile

// Desconecta
dbFTPDisconnect();
dbCLS(branco); dbCenterText (320,240, "Pressione ESC para sair.");
dbWaitKey();

dbSync();

} // endfunc: tst_ftp()


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





