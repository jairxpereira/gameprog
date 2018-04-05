// [--- $Aspectos globais - Arquivo: entrada.cpp#
// -----------------------------------------------------------------------------
// Projeto: prj_Janela - Arquivo: entrada.cpp
// Esta aplicação mostra como produzir uma janela - Curso Directx 10\11
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include "motor.h"
#include <tchar.h>

// -----------------------------------------------------------------------------
// Variáveis globais de criação e manutenção da janela
// -----------------------------------------------------------------------------
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
WCHAR		janelaTitulo[]	= L"prj_Janela";

// -----------------------------------------------------------------------------
// Protótipo da função de criação da janela
// -----------------------------------------------------------------------------
HRESULT				initWindow( HINSTANCE hInstance, int nCmdShow );
// ---]


// [--- $wWinMain() - Ponto de entrada da aplicação#
// -----------------------------------------------------------------------------
// Esta função é o ponto de entrada da aplicação. Ela inicializa a janela, 
// entra no laço de mensagens e renderiza a cena no tempo ocioso desse laço.
// -----------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					LPWSTR lpCmdLine, int nCmdShow )
{
    // Estes argumentos não serão usados, por isso estão assinalados
	// desta forma para evitar a mensagem relativa na compilação
	UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );
    
	// Inicializa e mostra a janela
	g_hr = initWindow( hInstance, nCmdShow );
	if (FAILED( g_hr ) ) return 0;

    // Laço de bombeamento de mensagens
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

    // Des-registre a classe e encerre a aplicação
	UnregisterClass( sclasseJanela, g_hInst); 
	return ( int )msg.wParam;
} // wWinMain().fim
// ---]


// [--- $initWindow() - Criação da janela da aplicação#
// -----------------------------------------------------------------------------
// Essa função cria e registra a janela
// -----------------------------------------------------------------------------
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
	MessageBox (NULL, L"Registro falhou!", janelaTitulo, MB_OK);
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

	// Verificação de erro
	if ( g_hJanela == NULL)	
	{
		MessageBox (NULL, L"Criação da janela falhou!", janelaTitulo, MB_OK);
		return E_FAIL;
	} // endif  

    // Mostra a janela
	ShowWindow( g_hJanela, nCmdShow );
	
	// Atualiza a 'tela' da janela
	UpdateWindow ( g_hJanela );

    return S_OK;
} // initWindow().fim
// endfile: entrada.cpp
// ---]

