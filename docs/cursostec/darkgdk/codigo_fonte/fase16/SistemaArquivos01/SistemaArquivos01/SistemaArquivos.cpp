// SistemaArquivos.cpp
// Este programa testa funções de sistema de arquivos
#include "DarkGDK.h"

// Protótipo das funções
void initsys();				// inicializa o sistema
void avisar(char *cText);   // Exibe um aviso 
void testar_dir();			// Testa funções de sistema de arquivos

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk
initsys(); 
testar_dir();


// Looping principal
while ( LoopGDK ( ) ) { 
 dbSync ( );

 if (dbMouseClick()==2) {
  dbSync();
  MessageBox(0,"Rodando notepad.exe", "dbExecuteFile()", MB_OK);
  dbExecuteFile("notepad.exe","c:\\windows\\win.ini","");
  } // endif
	
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
dbSetWindowTitle("SistemaArquivos.cpp"); dbSetTextOpaque();
} // initsys().fim

// ----------------------------------------------------------------------------

void avisar(char * cText) {
dbPrint(" ");
dbPrint(cText);
dbPrint("-------------------------------------------------------------------");
} // endfunction avisar()

void testar_dir() {

avisar(" dbCD()  dbSetDir()  dbGetDir()  dbDir():");
dbCD("c:\\Gameprog"); 
dbPrint( dbGetDir() ); dbSetDir("..\\BCC55");
dbDir();

avisar(" dbDriveList():"); dbDriveList();

avisar("  dbWindir()  dbAppname()");
dbPrint ( dbWindir() );
dbPrint ( dbAppname() );


avisar(" dbFileExist()  dbPathExist()");
if ( dbFileExist("c:\\windows\\notepad.exe") == 1) 
dbPrint("O arquivo c:\\windows\\notepad.exe existe!");

if ( dbPathExist("c:\\windows\\media") == 1) 
dbPrint("A pasta c:\\windows\\media existe!");

avisar("...botao direito do mouse para testar dbExecuteFile()");
} // endfunction testar_dir()



