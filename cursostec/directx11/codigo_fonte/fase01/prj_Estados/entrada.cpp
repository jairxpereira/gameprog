﻿// -----------------------------------------------------------------------------
// Projeto: prj_Estados - Arquivo: entrada.cpp
// Exemplo de renderização de um quadrado em modo wireframe
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include "motor.h"

//-----------------------------------------------------------------------------
// Variáveis globais de criação e manutenção da janela
//-----------------------------------------------------------------------------
HINSTANCE   g_hInst			= NULL;
HWND        g_hJanela		= NULL;

// Variável global da classe da janela; necessária em initWindow()
// e no encerramento de wWinMain()
WCHAR		sclasseJanela[]	= L"cls_directx";

// Recebimento do retorno das funções do directx
HRESULT		g_hr			= 0;
    
// Dimensões da janela
int			g_xtela		= 640;
int			g_ytela		= 480;

// Título da janela
WCHAR		janelaTitulo[]	= L"prj_Estados - Teclado: (S)ólido - (W)ireframe";

//-----------------------------------------------------------------------------
// Protótipo da função de criação da janela
//-----------------------------------------------------------------------------
HRESULT				initWindow( HINSTANCE hInstance, int nCmdShow );

//-----------------------------------------------------------------------------
// Esta função é o ponto de entrada da aplicação. Ela inicializa a janela, 
// entra no laço de mensagens e renderiza a cena no tempo ocioso.
//-----------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					LPWSTR lpCmdLine, int nCmdShow )
{
UNREFERENCED_PARAMETER( hPrevInstance );
UNREFERENCED_PARAMETER( lpCmdLine );

// Inicializa a janela
g_hr = initWindow( hInstance, nCmdShow );
if (FAILED( g_hr ) ) return 0;


// Inicialização do motor gráfico
g_hr = initGfx();

// Verificação de erro
if (FAILED( g_hr ) ) 
{
	
	Limpar();
	MessageBoxW (0, L"Falha na inicialização do motor gráfico", 
		L"prj_Estados", MB_OK);
	return 0;
}

// Main message loop
MSG msg = {0};
while( msg.message != WM_QUIT )
{
    if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
    {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    } // endif
    else
    {
        Renderizar();  
    } // end else
} // endwhile

// Libera os objetos utilizados
Limpar();

// Limpa o registro da classe da janela
UnregisterClass( sclasseJanela, g_hInst);  

// Retorna ao sistema operacional
return ( int )msg.wParam;
}


//-----------------------------------------------------------------------------
// Essa função cria e registra a janela
//-----------------------------------------------------------------------------
HRESULT initWindow( HINSTANCE hInstance, int nCmdShow )
{
    
// Estrutura de descrição da janela
WNDCLASSEX wcls;

// Tornando global o handle da aplicação
g_hInst = hInstance;	

// Estrutura que descreve a janela
wcls.hInstance		= hInstance;
wcls.lpszClassName	= sclasseJanela;
wcls.lpfnWndProc	= processaJanela;      
wcls.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;    
wcls.cbSize			= sizeof (WNDCLASSEX);

// O cursor e os ícones da aplicação são default
wcls.hIcon			= LoadIcon (NULL, IDI_APPLICATION);
wcls.hIconSm		= LoadIcon (NULL, IDI_APPLICATION);
wcls.hCursor		= LoadCursor (NULL, IDC_ARROW);

// Aplicação sem menu
wcls.lpszMenuName	= NULL;              

// Nada de espaço extra atrelado a classe da janela (wcls)
wcls.cbClsExtra		= 0;                      

// Nada de espaço extra atrelado a janela
wcls.cbWndExtra		= 0;                      

 // Cor default da janela
wcls.hbrBackground	= (HBRUSH) GetStockObject ( WHITE_BRUSH );

// Registra a janela e retorna se esta operação falhar
int status = RegisterClassEx (&wcls);
if ( status == 0)	{
MessageBoxW (NULL, L"Registro falhou!", janelaTitulo, MB_OK);
return  E_FAIL;
} // endif
		

// Atributos de configuração da janela
DWORD estiloExtra = 0;
DWORD dwEstilo = WS_OVERLAPPEDWINDOW - WS_MAXIMIZEBOX;
int xpos = 160;
int ypos = 120;
HWND hjanelaPai = HWND_DESKTOP;
HMENU sem_menu = NULL;
LPVOID dadoExtra = NULL;
	
// Criação da janela
g_hJanela = CreateWindowEx ( estiloExtra, sclasseJanela, janelaTitulo, 
	dwEstilo, xpos, ypos,  g_xtela, g_ytela, hjanelaPai, sem_menu,                
	hInstance, dadoExtra );

// Verificação da janela
if ( g_hJanela == NULL)	
{
	MessageBoxW (NULL, L"Criação da janela falhou!", janelaTitulo, MB_OK);
	return E_FAIL;
} // endif  

// Mostra e atualiza a janela
ShowWindow( g_hJanela, nCmdShow );
UpdateWindow ( g_hJanela );

return S_OK;
} // initWindow().fim
// endfile: entrada.cpp


