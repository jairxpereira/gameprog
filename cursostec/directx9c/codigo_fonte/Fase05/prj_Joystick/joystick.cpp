// [--- $Aspectos globais: arquivo: joystick.cpp#
//-------------------------------------------------------------------
// Projeto: prj_Joystick - arquivo: joystick.cpp
// Esta aplicação mostra como utilizar o Joystick
// via DirectInput. Produzido por www.gameprog.com.br
//-------------------------------------------------------------------
#include <dinput.h>
#include "joystick.h"
#include "motor.h"

// Handle da janela da aplicação
extern HWND hJanela;

extern Relatorio g_relatorio;

// Ponteiro uma instância do DirectInput
extern IDirectInput8 *g_DirectInput; 

// Ponteiro para o dispositivo de entrada joystick
extern IDirectInputDevice8  *g_joystick; 

// Estrutura de dados
DIJOYSTATE2 g_jsStatus; 
// ---]

// [--- $Inicialização do joystick#
HRESULT inicializar_Joystick( void )
{

	HRESULT     hr;

	// Procura por um joystick que possa ser usado
	if( FAILED( hr = g_DirectInput->EnumDevices( DI8DEVCLASS_GAMECTRL, 
		alistarJoysticks,
		NULL, DIEDFL_ATTACHEDONLY ) ) )
		return hr;

	// Verificação de falha
	if( NULL == g_joystick )
	{
		MessageBox( NULL, "Joystick não encontrado.",  
			"inicializar_Joystick()", 
			MB_ICONERROR | MB_OK );        
		return S_OK;
	}

	// Configuração do formato de dados para um formato pré-definido
	// O formato de dados especifica quais os controles em um dispositivo
	// estamos interessado e como eles deverão ser reportados. O formato
	// aqui indicado avisa ao directInput que vamos o utilizar a estrutura
	// de dados DIJOYSTATE2
	if( FAILED( hr = g_joystick->SetDataFormat( &c_dfDIJoystick2 ) ) )
		return hr;

	// Configuração do modo de cooperação
	if( FAILED( hr = g_joystick->SetCooperativeLevel( hJanela, 
		DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
		return hr;

	// Alistamento dos objetos do joystick. A função callback habilita a
	// aplicação fazer uso dos objetos que são encontrados e configura
	// os valores mínimos e máximos dos eixos descobertos.
	if( FAILED( hr = g_joystick->EnumObjects( alistarControleComponentes, 
		(void*) hJanela, DIDFT_ALL ) ) )
		return hr;

	return S_OK;

} // inicializar_Joystick( ).fim
// ---]
// [--- $Alistamento dos controles espetados no sistema#
//-----------------------------------------------------------------------------
// alistarJoysticks()
// Essa função é chamada para cada joystick localizado. Quando um
// joystick é encontrado é criado uma interface para que ele possa
// ser utilizado.
//-----------------------------------------------------------------------------
BOOL CALLBACK alistarJoysticks( const DIDEVICEINSTANCE *diControle,
															 void* pContext )
{
	// Coleta de resultado das operações  
	HRESULT hr;

	// Obtém uma interface para o joystick localizado
	hr = g_DirectInput->CreateDevice( diControle->guidInstance, &g_joystick, NULL );

	// Se ocorreu falha não podemos utilizar o joystick. Talvez o usuário
	// tenha desconectado ele no meio do alistamento.
	if( FAILED(hr) ) return DIENUM_CONTINUE;

	// Pare o alistamento! Nota: estamos pegando apenas o primeiro joystick
	// encontrado. Você poderia alistar todos os joysticks encontrados e
	// deixar para o usuário a escolha final do controle a ser usado. 
	return DIENUM_STOP;
} // alistarJoysticks().fim
// ---]
// [--- $Alistamento dos componentes espetados no joystick#
//-----------------------------------------------------------------------------
// alistarControleComponentes()
// Esta função alista ou enumera os componentes de um joystick tais
// como eixos, botões, pov's etc. . ., Esta função configura a faixa de    
// valor dos eixos encontrados. Os componentes também são chamados de
// 'objetos do dispositivo'.
//-----------------------------------------------------------------------------
BOOL CALLBACK alistarControleComponentes( const DIDEVICEOBJECTINSTANCE *joycomp,
																				 VOID* pContext )
{  
	// Quantidade de sliders
	static int nSliderCount = 0; 

	// Quantidade de POV's
	static int nPOVCount = 0;  

	// A faixa de alcance é configurada no caso dos eixos encontrados
	if( joycomp->dwType & DIDFT_AXIS )
	{
		DIPROPRANGE diprg; 
		diprg.diph.dwSize       = sizeof(DIPROPRANGE); 
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		diprg.diph.dwHow        = DIPH_BYID; 

		// Indica o eixo alistado!
		diprg.diph.dwObj        = joycomp->dwType; 

		// Define o valor da faixa de valor dos eixos
		diprg.lMin              = -1000; 
		diprg.lMax              = +1000; 

		// Configura a faixa de valor dos eixos
		if( FAILED( g_joystick->SetProperty( DIPROP_RANGE, &diprg.diph ) ) ) 
			return DIENUM_STOP;

	} // endif(configuração da faixa dos eixos)

	// Grave um relatório para refletir quais objetos ou
	// componentes o joystick suporta
	if (joycomp->guidType == GUID_XAxis)   
		g_relatorio.Gravar ("GUID_XAxis presente");   

	if (joycomp->guidType == GUID_YAxis)   
		g_relatorio.Gravar("GUID_YAxis presente");   

	if (joycomp->guidType == GUID_ZAxis)    
		g_relatorio.Gravar("GUID_ZAxis presente\n");   

	if (joycomp->guidType == GUID_RxAxis)
		g_relatorio.Gravar("GUID_RxAxis presente"); 

	if (joycomp->guidType == GUID_RyAxis)
		g_relatorio.Gravar("GUID_RyAxis presente");   

	if (joycomp->guidType == GUID_RzAxis)
		g_relatorio.Gravar("GUID_RzAxis presente\n");

	// Verifica a presença de sliders
	if (joycomp->guidType == GUID_Slider)
	{
		switch( nSliderCount++ )
		{
		case 0 :
			g_relatorio.Gravar("Slider[0] presente");
			break;
			g_relatorio.Gravar("Slider[1] presente\n");
		case 1 :

			break;
		} // endswitch
	} // endif

	// Verifica a presença de POVs
	if (joycomp->guidType == GUID_POV)
	{
		switch( nPOVCount++ )
		{
		case 0 :
			g_relatorio.Gravar("POV[0] presente");
			break;

		case 1 :
			g_relatorio.Gravar("POV[1] presente");
			break;

		case 2 :
			g_relatorio.Gravar("POV[2] presente");

		case 3 :
			g_relatorio.Gravar("POV[3] presente\n");
			break;
		} // endswitch 
	} // endif

	return DIENUM_CONTINUE;
} // alistarControleComponentes().fim
// ---]