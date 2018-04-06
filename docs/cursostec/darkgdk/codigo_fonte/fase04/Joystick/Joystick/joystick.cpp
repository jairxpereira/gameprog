// Joystick01.cpp
// Esse programa ilustra o tratamento do Joystick
#include "DarkGDK.h"

void initsys();				// Inicializa o sistema
void getJoyStatus(void);	// Pega status do JoyStick
void showJoyStatus(void);	// Mostra status do JoyStick
void tst_joystick(void);	// Testa Joystick

// Cores
#define nPreto		0
#define nAzul		0x0000FF
#define nBranco		0xFFFFFF

// Lista para guardar dados do Joystick
int joySts[20];	

// Nomes para clarificar as posições da lista
#define joy_up		0
#define joy_down	1
#define joy_left	2
#define joy_right	3

#define joy_btn_a	4
#define joy_btn_b	5
#define joy_btn_c	6
#define joy_btn_d	7

#define joy_analog_x	8
#define joy_analog_y	9
#define joy_analog_z	10

#define joy_btn_04	11
#define joy_btn_05	12
#define joy_btn_06	13
#define joy_btn_07	14
#define joy_btn_08	15
#define joy_btn_09	16
#define joy_btn_10	17
#define joy_btn_11	18


void DarkGDK ( void ) {
//  Começo da aplicação DarkGdk

initsys();   

while ( LoopGDK ( ) ) {    
 tst_joystick();
 dbSync ( );
 } // fim do while

return;
} // fim da função: DarkGDK

// Esta função inicializa o sistema
void initsys() {    

dbSyncOn( ); dbSyncRate (60);

// Estabelecendo a configuração de vídeo
dbSetWindowOn();dbSetDisplayMode(640,480,32);   
dbCLS(nBranco); dbInk(nPreto, nBranco);
dbSetTextOpaque();

// Configurando a janela
dbSetWindowTitle("joystick01.cpp"); 
dbSetWindowSize (640,480); 
dbSetWindowPosition (320,20);
} // fim da função: initsys()

//---------- Esta função obtém o status dos recursos do Joystick
void getJoyStatus(void) {

	// Direcional
	joySts[joy_up] = dbJoystickUp();
	joySts[joy_down] = dbJoystickDown();
	joySts[joy_left] = dbJoystickLeft();
	joySts[joy_right] = dbJoystickRight();

	// Botões principais
	joySts[joy_btn_a] = dbJoystickFireA();
	joySts[joy_btn_b] = dbJoystickFireB();
	joySts[joy_btn_c] = dbJoystickFireC();
	joySts[joy_btn_d] = dbJoystickFireD();

	// Direcional analógico
	joySts[joy_analog_x] = dbJoystickX();
	joySts[joy_analog_y] = dbJoystickY();
	joySts[joy_analog_z] = dbJoystickZ();

	// Outros botões
	joySts[joy_btn_04] = dbJoystickFireX(4);
	joySts[joy_btn_05] = dbJoystickFireX(5);
	joySts[joy_btn_06] = dbJoystickFireX(6);
	joySts[joy_btn_07] = dbJoystickFireX(7);
	joySts[joy_btn_08] = dbJoystickFireX(8);
	joySts[joy_btn_09] = dbJoystickFireX(9);
	joySts[joy_btn_10] = dbJoystickFireX(10);	
	joySts[joy_btn_11] = dbJoystickFireX(11);

}// endfunction


//---------- Esta função exibe o status dos recursos do Joystick
void showJoyStatus(void) {
	char *joyMsg[] = {"dbJoystickUp", "dbJoystickDown", "dbJoystickLeft", 
	"dbJoystickRight", "dbJoystickFireA","dbJoystickFireB","dbJoystickFireC",
	"dbJoystickFireD", "dbJoystickX", "dbJoystickY", "dbJoystickZ", 
	"joy_btn_04","joy_btn_05","joy_btn_06","joy_btn_07","joy_btn_08", 
	"joy_btn_09","joy_btn_10","joy_btn_11"};

	int npalavras = 18;
	char texto[255];

	int nlinha = 20;
	int ncoluna = 10;
	int entrelinha = 20;
	int ncx = 0;
	
	// Mostra na tela os status obtidos
	for (ncx=0; ncx < npalavras; ncx++)
	{
		if (ncx == 0) dbInk(nPreto, nBranco);
		sprintf(texto, "%s: %d", joyMsg[ncx], joySts[ncx]);	
		dbText (ncoluna, nlinha, dbSpaces(20));		

		// Imprime o texto e avança a linha
		dbText (ncoluna, nlinha, texto);
		nlinha = ((ncx+1) * entrelinha) + entrelinha;

		// Colore o texto pra facilitar a leitura
		if (ncx == 3) dbInk(nAzul, nBranco);
		if (ncx == 7) dbInk(nPreto, nBranco);
		if (ncx == 10) dbInk(nAzul, nBranco);
	} // endfor

} // endfunction

// Esta função testa o Joystick
void tst_joystick(void) {
	getJoyStatus();
	showJoyStatus();
} // endfunction