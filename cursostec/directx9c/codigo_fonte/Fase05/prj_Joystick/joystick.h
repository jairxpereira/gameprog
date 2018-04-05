
// [--- $Aspectos globais: arquivo: joystick.h# tpc++
//-------------------------------------------------------------------
// Projeto: prj_Joystick - arquivo: joystick.h
// Esta aplicação mostra como utilizar o Joystick
// via DirectInput. Produzido por www.gameprog.com.br
//-------------------------------------------------------------------
#ifndef joystick_h
 #define joystick_h

#include <dinput.h>

// Alista ou enumera os joysticks disponíveis
BOOL CALLBACK alistarJoysticks( 
															 const DIDEVICEINSTANCE *diControle, 
															 void* pContext );

// Inicializa o joystick
HRESULT inicializar_Joystick( void );


// Alista ou enumera os objetos componentes do joystick localizado
BOOL CALLBACK alistarControleComponentes(
	const DIDEVICEOBJECTINSTANCE *joycomp, void* pContext );

#endif
// ---]

