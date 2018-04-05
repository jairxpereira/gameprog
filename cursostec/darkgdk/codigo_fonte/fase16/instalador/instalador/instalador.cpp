// instalador.cpp
// Este programa ilustra como criar e deletar diret�rios e
// copiar, renomear e deletar arquivos
#include "DarkGDK.h"

// Prot�tipo das fun��es
void initsys();					// inicializa o sistema
void MsgInfo(char *cText);		// Mostra uma mensagem na tela
void scan_dir03(int nteste);	// Testa fun��es de sistema de arquivos

void tst_copiar (int nlinha);	// Realiza teste de c�pia
void tst_renomear(int nlinha);	// Realiza teste de renomea��o de arquivos
void tst_deletar(int nlinha);	// Realiza teste de dele��o de arquivos

// tipo de arquivo
#define tipo_arquivo	0
#define tipo_pasta		1
#define tipo_eof		-1

// Flag para terminar o programa. 1 = terminar
int terminar = 0;

// tipo de teste
#define const_copiar		1
#define const_renomear		2
#define const_deletar		3

// Elenco de cores
#define nBranco		0xFFFFFF

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk
initsys(); 

if (dbPathExist("c:\\gdkTeste") == 1)
 {
 dbCD("c:\\Gameprog\\gdkMedia\\instalador"); dbDeleteDirectory("c:\\gdkTeste");
 if (dbPathExist("c:\\gdkTeste") == 1) scan_dir03(const_deletar);
 } // endif

dbMakeDirectory("c:\\gdkTeste");
MsgInfo("O diretorio c:\\gdkTeste foi criado. \nConfira a existencia dele.");

MsgInfo("Testando copiar"); scan_dir03(const_copiar);

MsgInfo("Testando renomear"); scan_dir03(const_renomear);

MsgInfo("Testando deletar"); scan_dir03(const_deletar);

// Looping principal
while ( LoopGDK ( ) ) { 
	if (terminar == 1) break;
 dbSync ( );	
 } // fim do while
return;
} // endfunction DarkGDK()

// ----------------------------------------------------------------------------
void initsys() {    
// Esta fun��o inicializa o sistema
dbSyncOn( );
dbCLS ( nBranco); dbInk( 0, nBranco );
dbSetWindowTitle("Instalador.cpp"); dbSetTextOpaque();
} // initsys().fim

// ----------------------------------------------------------------------------

void scan_dir03( int nteste) {
int ntipo, nlinha;

// Legenda dos dados de arquivo
dbText (10, 10, "Arquivo");

// Inicia o processo de escaneamento do diret�rio
dbCD("c:\\Gameprog\\gdkMedia\\instalador");
if (nteste == const_renomear) dbCD("c:\\gdkTeste");
if (nteste == const_deletar) dbCD("c:\\gdkTeste");

dbFindFirst();
ntipo = dbGetFileType();
if (ntipo == tipo_eof) return; 
nlinha = 60;

// Continua o processo de escaneamento do diret�rio
for (;;)
 {
 dbFindNext();
 ntipo = dbGetFileType();
  
 if (ntipo == tipo_arquivo)
   {  
	  if (nteste == const_copiar) tst_copiar( nlinha);
	  if (nteste == const_renomear) tst_renomear( nlinha);
	  if (nteste == const_deletar) tst_deletar( nlinha);
	   nlinha = nlinha + 20;
   } // endif
  
  if (ntipo == tipo_eof) break;  
 
  dbSync();
 

 } // endfor

 if (nteste == const_copiar)
	 MsgInfo("Os arquivos foram copiados! \nVerifique a pasta c:\\gdkTeste");

 if (nteste == const_renomear)
	 MsgInfo("Os arquivos foram renomeados!. \nVerifique a pasta c:\\gdkTeste");

  if (nteste == const_deletar)
  {
	 MsgInfo("Os arquivos foram deletados!. \nVerifique a pasta c:\\gdkTeste");
	 dbCD("c:\\Gameprog\\gdkMedia\\instalador");
	 dbDeleteDirectory("c:\\gdkTeste");
	 MsgInfo("O diretorio c:\\gdkTeste foi deletado. \nConfira isto.");
	 terminar = 1;
  } // endif 
} // endfunction scan_dir03()

// ----------------------------------------------------------------------------
void tst_copiar(int nlinha) {
// Esta fun��o realiza c�pia de arquivos
char *cArquivo, sinfo[255];

// Obt�m detalhes do arquivo
cArquivo = dbGetFileName();

// Mostra o nome da pasta ou arquivo
dbText (10, nlinha, cArquivo);

sprintf(sinfo,"c:\\gdkTeste\\%s",cArquivo);
dbCopyFile(cArquivo, sinfo);
dbText(300, nlinha, "copiado");
} // endfunction detalhar()

// ----------------------------------------------------------------------------
void MsgInfo(char *cText) {
	MessageBox(0, cText, "Instalador", MB_OK);
}// endfuncion MsgInfo


// ----------------------------------------------------------------------------
void tst_renomear(int nlinha) {
// Essa fun��o renomeia arquivos
char *cArquivo;
char sinfo[255];

// Obt�m detalhes do arquivo
cArquivo = dbGetFileName();

// Mostra o nome do arquivo
dbText (10, nlinha, cArquivo);

sprintf(sinfo,"hackeado-%s",cArquivo);
dbRenameFile(cArquivo, sinfo);
dbText(300, nlinha, " renomeado ");
} // endfunction: renomear


// ----------------------------------------------------------------------------
void tst_deletar(int nlinha) {
// Essa fun��o deleta arquivos
char *cArquivo;

// Obt�m detalhes do arquivo
cArquivo = dbGetFileName();

// Mostra o nome do arquivo
dbText (10, nlinha, cArquivo);

dbDeleteFile(cArquivo);
dbText(300, nlinha, "*** deletado *** ");
}// endfunction: deletar()