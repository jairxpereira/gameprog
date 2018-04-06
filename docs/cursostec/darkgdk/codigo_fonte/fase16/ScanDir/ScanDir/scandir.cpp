// scandir.cpp
// Este programa testa funções de sistema de arquivos da linha dbPerform...
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void avisar(char *cText);   // Exibe um aviso 
void scan_dir();			// Testa funções de sistema de arquivos

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys(); 
scan_dir();

// Looping principal
while ( LoopGDK ( ) ) { 
 dbSync ( );	
 } // fim do while
return;
} // endfunction DarkGDK()

// ----------------------------------------------------------------------------
void initsys() {    
// Esta função inicializa o sistema
dbSyncOn( );
dbSetDisplayMode (800,600,32);
dbSetWindowSize(800,600);
dbCLS ( dbRGB(0,0,255));
dbInk( dbRGB(255,255,255), dbRGB(0,0,255) );
dbSetWindowTitle("scandir.cpp"); dbSetTextOpaque();
} // initsys().fim

// ----------------------------------------------------------------------------

void avisar(char * cText) {
dbPrint(" ");
dbPrint(cText);
dbPrint("-------------------------------------------------------------------");
} // endfunction avisar()

void scan_dir() {
int ntam, ncx;
char *cArquivo;	
char *cDrive;
char sinfo[255];

// Vamos mostrar a lista de drives do sistema
avisar("        dbPerformCheckListForDrives()");
dbPerformCheckListForDrives();
ntam = dbChecklistQuantity();
for (ncx=1; ncx <= ntam; ncx++)
 {
 cDrive = dbChecklistString (ncx);
 sprintf(sinfo, "        Drive: %s", cDrive);
 dbPrint ( sinfo);
 } // endfor

// Vamos mostrar os arquivos da pasta c:\Gameprog
avisar("        dbPerformCheckListForFiles()");
dbCD("c:\\Gameprog");
dbPerformCheckListForFiles();
ntam = dbChecklistQuantity();
for (ncx=1; ncx <= ntam; ncx++)
 {
 cArquivo =  dbChecklistString (ncx);
 sprintf(sinfo, "        %d %s", ncx, cArquivo);
 dbPrint( sinfo);
 } // endfor

} // endfunction scan_dir()