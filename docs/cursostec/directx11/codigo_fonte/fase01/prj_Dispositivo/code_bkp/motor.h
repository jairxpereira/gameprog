#include <windows.h>

#if !defined motor_h
#define motor_h

	// Função de processamento de mensagens da janela
	LRESULT CALLBACK    processaJanela( HWND, UINT, WPARAM, LPARAM );	
	
	// [--- $Aspectos globais: arquivo motor.h
	// <b>
	// Inicializa o motor gráfico
	HRESULT initGfx();
	
	// Função de renderizar a cena
	void	Renderizar( void );
	
	// Função de liberar os objetos utilizados pela aplicação
	void	Limpar( void );
	// </b>
	// ---]

#endif
