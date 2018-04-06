// string01.cpp
// Esse programa ilustra o uso de fun��es de texto
#include "DarkGDK.h"
void initsys();
void tst_texto_03();
void mostreFonteConfig();

int nPreto = 0;
int nAzul = 0x0000FF;
int nBranco = 0xFFFFFF;

//  Come�o da aplica��o DarkGdk
void DarkGDK ( void ) {

initsys();	
tst_texto_03();		

while ( LoopGDK ( ) ) {		
dbSync ( );
} // fim do while

return;
} // fim da fun��o: DarkGDK

void initsys() {	
// Esta fun��o inicializa o sistema
	dbCLS(nBranco);
	dbInk(nPreto, nBranco);
	dbSetWindowTitle ("string03.cpp");	
	// Configurando o video para a m�xima performance a 60 fps
	dbSyncOn   ( );
	dbSyncRate ( 60 );
} // fim da fun��o: initsys()


void tst_texto_03() {
// Ilustra obten��o de dados de configura��o de fonte
// Configura��o inicial
dbInk(nPreto, nBranco); dbSetTextTransparent(); dbPrint();	
mostreFonteConfig();

// Separe as diferentes configura��es para melhor leitura dos resultados
dbPrint(); // Pule uma linha
dbPrint("----------------------------------------------------------------------");
dbPrint(); // Pule uma linha

// Vamos reconfigurar alguns aspectos da fonte e na sequ�ncia exibimos a config
dbSetTextFont("Courier New"); dbSetTextSize(20); dbSetTextToBold(); 
dbInk(nBranco, nAzul); dbSetTextOpaque();
mostreFonteConfig();

} // fim de tst_texto_03()

void mostreFonteConfig() {
// Esta fun��o obt�m e mostra a configura��o padr�o dos aspectos da fonte

// Vari�veis de trabalho
char site[] = "Gameprog";
char txt[255];
char* sfontnome;
int nLargura, nAltura, nEstilo, nTipoFundo, nFonteTam;

// Vamos pegar os dados da configura��o de fonte
sfontnome = dbTextFont();				// Pega o nome da fonte corrente
nLargura = dbTextWidth(site);			// Pega a largura da string em px
nAltura = dbTextHeight(site);			// Pega a altura da string em px			
nEstilo = dbTextStyle();				// Pega o estilo de impress�o da fonte
nTipoFundo = dbTextBackgroundType();    // Tipo de fundo da fonte
nFonteTam = dbTextSize();				// Pega o tamanho da fonte em px

sprintf(txt, " String site: %s", site); dbPrint (txt);
sprintf(txt, " Fonte corrente: %s <-- dbTextFont()", sfontnome); dbPrint (txt);

sprintf(txt, " Largura('Gameprog'): %dpx <-- dbTextWidth(site)", nLargura);
dbPrint (txt);

sprintf(txt, " Altura('Gameprog'): %dpx <-- dbTextHeigth(site)", nAltura);
dbPrint (txt);

sprintf(txt, " Estilo da fonte: %d <-- dbTextStyle()", nEstilo); dbPrint (txt);

sprintf(txt, " nTipoFundoFonte: %d  <-- dbTextBackgroundType()", nTipoFundo);
dbPrint (txt);

sprintf(txt, " Tamanho da fonte: %dpx <-- dbTextSize()", nFonteTam); dbPrint (txt);
} // fim de mostreFontConfig()

