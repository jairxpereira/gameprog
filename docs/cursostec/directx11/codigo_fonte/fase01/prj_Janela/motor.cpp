// -----------------------------------------------------------------------------
// Projeto: prj_Janela - Arquivo: motor.cpp
// Esta aplicação mostra como produzir uma janela - Curso Directx 10\11
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
// [--- $Aspectos globais - Arquivo: motor.cpp#
#include "motor.h"

// Variáveis definidas em entrada.cpp
extern	HWND		g_hJanela;
extern	HRESULT		g_hr;
// ---]
// [--- $processaJanela() - Tratamento de mensagens da janela#
// -----------------------------------------------------------------------------
// processaJanela() - Tratamento de mensagens da janela
// -----------------------------------------------------------------------------
LRESULT CALLBACK processaJanela( HWND hWnd, UINT message, 
								WPARAM wParam, LPARAM lParam )
{
	PAINTSTRUCT ps;
	HDC hdc;
	
	switch( message )
	{

	// Tratamento do evento onPaint
	case WM_PAINT:
		hdc = BeginPaint( hWnd, &ps );
		EndPaint( hWnd, &ps );
	break;

	// Tratamento do evento onClose ou fechamento da janela
	case WM_CLOSE:			
		Limpar();
		PostQuitMessage (0);
	break;

	// Tratamento do teclado ou evento onKeyDown
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)  
		{
			Limpar();
			PostQuitMessage(0);
		} // endif
	break; 

	// Tratamento onDestroy  ou destruição sem volta da janela
	case WM_DESTROY:
		PostQuitMessage( 0 );
	break;

	// Outras mensagens são passadas para o Windows
	default:
	return DefWindowProc( hWnd, message, wParam, lParam );
	} // endswitch

    // O padrão dessa função é retornar zero (0) para uma mensagem processada
	return 0;
} // processaJanela().fim
// ---]

// [--- $Renderizar() - Renderiza a cena#
// -----------------------------------------------------------------------------
// Renderizar() - renderiza a cena
// -----------------------------------------------------------------------------
void Renderizar ( void )
{	
	// Mensagem para exibir na janela
	WCHAR mensagem[] = L"Pressione ESC para sair";

	// Cor para o texto a ser exibido
	COLORREF azul = RGB(0,0,255);	
	
	// Acesso ao dispositivo gráfico da janela
	HDC hdc;
	hdc = GetDC( g_hJanela );	

	// Configura a cor do texto
	SetTextColor (hdc, azul );

	// Mostra a mensagem
	TextOutW (hdc, 10, 10, mensagem, wcslen (mensagem) );

	// Libera o dispositivo gráfico
	ReleaseDC (g_hJanela, hdc);


} // Renderizar().fim
// ---]

// [--- $Limpar() - libera os objetos utilizados pela cena#
// -----------------------------------------------------------------------------
// Limpar() - libera os objetos utilizados pela cena
// -----------------------------------------------------------------------------
void Limpar( void )
{

		MessageBoxW (0, 
				L"Ok. O ambiente foi limpo adequadamente!",
				L"prj_Janela", MB_OK);

} // Limpar().fim
// endfile: motor.cpp
// ---]