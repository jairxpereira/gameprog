// Esta aplicação estabelece um ambiente para testar as
// matrizes de transformações. By www.gameprog.com.br
// Baseado em Win32 Tutorial (Dialog Box as main window)
// De Alan Baylis 2004
#include <windows.h>
#include "resource.h"
#include "motor.h"

// Handle global da janela
HWND hJanela;

INT WINAPI WinMain( HINSTANCE  hInstance, HINSTANCE  hPrevInstance,
									 LPSTR      lpCmdLine, INT        nCmdShow )
{
	
	// Estrutura para mensagens
	MSG msg;

	// Criação da janela
	hJanela = CreateDialog( hInstance, (LPCTSTR)"DIALOG_NAME",
		NULL, (DLGPROC)processaJanela );

	// Laço de mensagens
	while(GetMessage(&msg, NULL,0,0) == TRUE)
	{
		if(!IsDialogMessage(hJanela,&msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		} // endif
	} // endwhile

	return msg.wParam;
} // WinMain().fim