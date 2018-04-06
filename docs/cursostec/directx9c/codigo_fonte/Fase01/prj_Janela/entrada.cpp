// Projeto prj_Janela arquivo: entrada.cpp
// Este programa ilustra como criar uma janela
// Produzido por www.gameprog.com.br
// [---
#include <windows.h>
//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);

// Dimensões da janela
int g_xtela = 320;
int g_ytela = 240;
// ---]

// [---
int WINAPI WinMain (HINSTANCE app_instancia, HINSTANCE app_anterior,
										LPSTR sComando,int nExibir) {
	// alça da janela  
	HWND hJanela = NULL;               

	// Estrutura de recepção das mensagens
	MSG mensagem;            

	// Estrutura de descrição da janela
	WNDCLASSEX wcls;
		
	// Nome da classe da janela
  char sclasseJanela[ ] = "cls_directx";

	// Estrutura que descreve a janela
	wcls.hInstance = app_instancia;
	wcls.lpszClassName = sclasseJanela;
	wcls.lpfnWndProc = processaJanela;      
	wcls.style = CS_HREDRAW | CS_VREDRAW;    
	wcls.cbSize = sizeof (WNDCLASSEX);

	// O cursor e os ícones da aplicação são default
	wcls.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wcls.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	wcls.hCursor = LoadCursor (NULL, IDC_ARROW);

	// Aplicação sem menu
	wcls.lpszMenuName = NULL;              
	
	// Nada de espaço extra atrelado a classe da janela (wcls)
	wcls.cbClsExtra = 0;                      
	
	// Nada de espaço extra atrelado a janela
	wcls.cbWndExtra = 0;                     

  // Cor default da janela
	wcls.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

	// Registra a janela e retorna se esta operação falhar
	int status = RegisterClassEx (&wcls);
	if ( status == 0)	{
	MessageBox (NULL, "Registro falhou!", "prj_Janela", MB_OK);
	return 0;
	} // endif
		

	// Depois da classe criada cria-se a janela
	DWORD estiloExtra = 0;
	const char janelaTitulo[] = "prj_Janela";
	DWORD controleEstilo = WS_OVERLAPPED | WS_SYSMENU ;
	int xpos = 160;
	int ypos = 120;
	HWND hjanelaPai = HWND_DESKTOP;
	HMENU sem_menu = NULL;
	LPVOID dadoExtra = NULL;

	hJanela = CreateWindowEx ( estiloExtra, sclasseJanela, janelaTitulo, 
		controleEstilo, xpos, xpos,  g_xtela, g_ytela, hjanelaPai, sem_menu,                
		app_instancia, dadoExtra );

		if ( hJanela == NULL)	{
			MessageBox (NULL, "Criação da janela falhou!", "prj_Janela", MB_OK);
	return 0;
	} // endif



	// Mostra a janela
	ShowWindow (hJanela, SW_NORMAL);
	UpdateWindow (hJanela);

	// Rode o bombeamento de mensagens até GetMessage() retornar 0
	while (GetMessage (&mensagem, NULL, 0, 0))
	{
		// Traduz mensagem de tecla virtual em mensagem de caracteres
		TranslateMessage(&mensagem);

		// Despacha a mensagem para a função  processaJanela */
		DispatchMessage(&mensagem);
	} // endwhile

	// O valor de retorno é zero(0) passado por PostQuitMessage()
	UnregisterClass ( sclasseJanela, app_instancia );
	return mensagem.wParam;
} // WinMain().fim
// ---]


// [---
//  Esta função é chamada por DispatchMessage()  
LRESULT CALLBACK processaJanela ( HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam )
{
	switch (mensagem)                 
	{	
	case WM_DESTROY:
		// Coloca uma mensagem WM_QUIT na fila de mensagem
		PostQuitMessage (0);       
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) PostQuitMessage( 0 );
		return 0;
		break;

	// Processamento default de mensagens não tratada pela aplicação
	default:                      
		return DefWindowProc (hJanela, mensagem, wParam, lParam);
	} // endswitch

	return 0;
} // processaJanela().fim
// ---]

