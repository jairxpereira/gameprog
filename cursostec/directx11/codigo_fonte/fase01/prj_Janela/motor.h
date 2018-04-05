// [--- $Aspectos globais - Arquivo: motor.h#
// -----------------------------------------------------------------------------
// Projeto: prj_Janela - Arquivo: motor.h
// Esta aplicação mostra como produzir uma janela - Curso Directx 10\11
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>

#if !defined motor_h
#define motor_h

	// Função de processamento de mensagens da janela
	LRESULT CALLBACK    processaJanela( HWND, UINT, WPARAM, LPARAM );
	
	// Função de renderizar a cena
	void				Renderizar( void );
	
	// Função de liberar os objetos utilizados pela aplicação
	void				Limpar( void );

#endif
// endfile: motor.h
// ---]
