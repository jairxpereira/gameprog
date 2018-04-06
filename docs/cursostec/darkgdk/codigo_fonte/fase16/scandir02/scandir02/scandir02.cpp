// scandir02.cpp
// Este programa ilustra como escanear passo a passo os arquivos do diret�rio
#include "DarkGDK.h"

// Prot�tipo das fun��es
void initsys();				// inicializa o sistema
void scan_dir02();			// Testa fun��es de sistema de arquivos
void detalhar (int nlinha); // mostra detalhes do arquivo

// tipo de arquivo
#define tipo_arquivo	0
#define tipo_pasta		1
#define tipo_eof		-1

// Elenco de cores
#define nAzul  0x000080
#define nBranco  0xFFFFFF
#define nVermelho  0x800000
#define nVerde  0x008000

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk
initsys(); 
scan_dir02();

// Looping principal
while ( LoopGDK ( ) ) { 
 dbSync ( );	
 } // fim do while
return;
} // endfunction DarkGDK()

// ----------------------------------------------------------------------------
void initsys() {    
// Esta fun��o inicializa o sistema
dbSyncOn( );
dbSetDisplayMode (800,600,32); dbSetWindowSize(800,600);
dbCLS ( nBranco); dbInk( nAzul, nBranco );
dbSetWindowTitle("scandir02.cpp"); dbSetTextOpaque();
} // initsys().fim

// ----------------------------------------------------------------------------

void scan_dir02() {
int ntipo, ncx, nlinha;

// Legenda dos dados de arquivo
dbText (10, 10, "Arquivo");
dbText (180, 10, "Tamanho");
dbText(300, 10, "cDtCriacao");
dbText(540,10, "cDtModificacao");

// Inicia o processo de escaneamento do diret�rio
dbCD("c:\\Gameprog");
dbFindFirst();
ntipo = dbGetFileType();
detalhar(40);
nlinha = 60;
if (ntipo == tipo_eof) return; 

// Continua o processo de escaneamento do diret�rio
for (ncx=0; ncx <= 30; ncx++)
 {
 dbFindNext();
 ntipo = dbGetFileType();
  if (ntipo == tipo_arquivo || ntipo == tipo_pasta)
  {
  detalhar( nlinha);
  } // endif
  if (ntipo == tipo_eof) break;  
 dbSync();
 nlinha = nlinha + 20;
 } // endfor
} // endfunction scan_dir()

// ----------------------------------------------------------------------------
void detalhar(int nlinha) {
// Esta fun��es obt�m e mostra detalhes do arquivo

long nsize = 0;
int ntipo = 0;
char *cArquivo, *cDtCriacao, *cDtModificacao;
char sinfo[255];

// Obt�m detalhes do arquivo
cArquivo = dbGetFileName();
ntipo = dbGetFileType();
nsize = dbFileSize(cArquivo);
cDtCriacao = dbGetFileCreation();
cDtModificacao = dbGetFileDate();

// Mostra o nome da pasta ou arquivo
dbInk( 0, nBranco);
if (ntipo == tipo_pasta){ 
sprintf(sinfo,"[%s%]",cArquivo);
dbText (10, nlinha, sinfo);
} // endif
else {
dbText (10, nlinha, cArquivo);
} // end else

// Mostra tamanho
dbInk( nVermelho, nBranco);
sprintf(sinfo, "[%li]", nsize);
dbText (180, nlinha, sinfo);

// Mostra data de cria��o
dbInk( nAzul, nBranco);
dbText(300, nlinha, cDtCriacao);

// Mostra data de modifica��o
dbInk( nVermelho, nBranco);
dbText(540, nlinha, cDtModificacao);
} // endfunction detalhar()