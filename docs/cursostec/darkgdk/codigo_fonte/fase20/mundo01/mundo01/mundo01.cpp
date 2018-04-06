// mundo01.cpp
// Esse programa ilustra como carregar um mapa do Quake
#include "DarkGDK.h"
#include "windows.h"

// Prot�tipo das fun��es
void initsys();				// inicializa o sistema
void teclado();				// Interpreta o teclado
void setup_skyBox();		// Configura skyBox
void setup_camera();		// Configura c�mera
void setup_quakemap();		// Carrega mapa do jogo quake
int terminar = 0;

// Dados para posi��o da c�mera
float xcam = 0.0f;
float ycam = 0.5f;
float zcam = 0.0f;

// Dados para movimenta��o da c�mera via teclado
float velocidade = 0.1f;
float curva = 0.03f;

// Dados para girar a c�mera usando o mouse
float old_ycam_angle = 0;
float old_xcam_angle = 0;
float ycam_angle = 0;
float xcam_angle = 0;

// ----------------------------------------------------------------------------
void DarkGDK ( void ) {
//  Come�o da aplica��o DarkGdk 

// Inicializa o sistema
initsys();

// Coloca um c�u ao redor do mapa
setup_skyBox();

// Configura a c�mera
setup_camera();

// Carrega mapa do Quake e configura colis�o de c�mera
setup_quakemap();

// Configura mouse e posi��o da camera
dbPositionMouse (400,300);
dbPositionCamera ( xcam, ycam, zcam);
dbSetWindowTitle("mundo01.cpp");

// Looping principal
while ( LoopGDK ( ) ) { 

	if (terminar == 0) teclado();

	dbSync ( );

	if (terminar == 1)
	{
		
		return;
	} // endif
 } // fim do while
return;
} // fim da fun��o: DarkGDK

// ----------------------------------------------------------------------------
void initsys() {    
// Esta fun��o inicializa o sistema
dbSyncOff( );
dbSyncRate       ( 60 );
dbSetWindowTitle("Carregando mundo do Quake. Aguarde... "); 
dbDisableEscapeKey();
dbSetDisplayMode (800, 600, 32);
} // initsys().fim



// ----------------------------------------------------------------------------
// teclado() - L� o teclado e executa comandos do usu�rio
void teclado() {

    // Utilize as setas para movimentar a camera
    dbControlCameraUsingArrowKeys ( 0, velocidade, curva );

    old_ycam_angle = ycam_angle;
    old_xcam_angle = xcam_angle;

    // O mouse modifica o �ngulo da camera
    ycam_angle = dbWrapValue ( ycam_angle + dbMouseMoveX ( ) * 0.4f );
    xcam_angle = dbWrapValue ( xcam_angle + dbMouseMoveY ( ) * 0.4f );

    // Rotaciona a camera
    dbYRotateCamera ( dbCurveAngle ( ycam_angle, old_ycam_angle, 24 ) );
    dbXRotateCamera ( dbCurveAngle ( xcam_angle, old_xcam_angle, 24 ) );

    if (dbEscapeKey()) terminar = 1;
    if (dbMouseClick() == 2) terminar = 1;

    dbSync();
    
} // teclado().fim

void setup_skyBox()
{
dbBackdropOff();
dbLoadObject ( "c:\\gameprog\\gdkmedia\\sky\\skybox2.x", 200 );
dbSetObjectLight ( 200, 0 );
dbSetObjectTexture ( 200, 3, 1 );
dbPositionObject ( 200, 1000, 2000, 4000 );
dbScaleObject ( 200, 30000, 30000, 30000 );
} // setup_skyBox()

void setup_camera()
{
dbAutoCamOff( );
dbSetCameraRange ( 0.05f, 30000 );
} // setup_Camera().end

void setup_quakemap()
{

// Identifica��o da camera
int cam_default = 0;

// Configura��o de colis�o do mundo BSP com a c�mera
int nresposta_colisao = 0;
float raio_colisao = 0.75f;

// Vamos carregar um mapa do jogo Quake
dbSetDir ("c:\\gameprog\\gdkmedia\\mundo");
dbLoadBSP ("ikzdm1.pk3", "ikzdm1.bsp");

// Destaca a camera zero(0) como a camera do mundo BSP
dbSetBSPCamera (cam_default);

// Habilita colis�o do mundo com a camera
dbSetBSPCameraCollision (  1 , cam_default, raio_colisao, 
						 nresposta_colisao );

} // setup_Quakemap()