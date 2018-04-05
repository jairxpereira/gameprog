//-----------------------------------------------------------------------------
// Projeto: prj_Dispositivo - Arquivo: motor.h
// Exemplo de inicialização do motor gráfico (Directx 11)
// Produzido por www.gameprog.com.br
//-----------------------------------------------------------------------------
#include <windows.h>

#if !defined motor_h
#define motor_h

	// Função de processamento de mensagens da janela
	LRESULT CALLBACK    processaJanela( HWND, UINT, WPARAM, LPARAM );	
	
	// [--- $Aspectos globais: arquivo motor.h#
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

//-----------------------------------------------------------------------------
// Projeto: prj_Dispositivo - Arquivo: motor.cpp
// Exemplo de inicialização do motor gráfico (Directx 11)
// Produzido por www.gameprog.com.br
//-----------------------------------------------------------------------------
#include "motor.h"
#include <d3d11.h>
#include <d3dx11.h>


// [--- $Variáveis globais#
// ------------------------------------------------------------------------
// Variáveis globais
// ------------------------------------------------------------------------

// Corrente de trocas
IDXGISwapChain         *g_pSwapChain = NULL;


// Tipo de driver
D3D_DRIVER_TYPE         g_driverType = D3D_DRIVER_TYPE_HARDWARE;
// nível desejado de capacidades do dispositivo
D3D_FEATURE_LEVEL       g_featureLevel = D3D_FEATURE_LEVEL_11_0;

// Dispositivo gerenciador de recursos
ID3D11Device           *g_pd3dDevice = NULL;
// Disposisitivo renderizador
ID3D11DeviceContext    *g_pImmediateContext = NULL;


// Interface de gestão da textura alvo de visualização
ID3D11RenderTargetView *g_pRenderTargetView = NULL;


// Variáveis definidas em entrada.cpp
extern	HWND		g_hJanela;
extern	HRESULT		g_hr;
// ---]

// [--- $initGfx() - Inicialização do motor gráfico#
// ------------------------------------------------------------------------
// Cria a corrente de trocas e os dispositivos do motor gráfico
// ------------------------------------------------------------------------
HRESULT initGfx()
{
    // Se tudo ocorrer bem initGfx() vair retornar S_OK
	g_hr = S_OK;
    
	// Vamos obter o tamanho da área cliente da janela
	RECT areaCliente;
    GetClientRect( g_hJanela, &areaCliente );
    UINT largura = areaCliente.right - areaCliente.left;
    UINT altura  = areaCliente.bottom - areaCliente.top;
    


    // Configuração da corrente de trocas
	// Inicialização básica da estrutura
	DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof( sd ) );

    // Quantidade de backbuffers
	sd.BufferCount			= 1;
    
	// Configuração da largura e tamanho
	sd.BufferDesc.Width		= largura;
    sd.BufferDesc.Height	= altura;
    
	// Configuração da taxa de refrescamento de vídeo 60Hz
	sd.BufferDesc.RefreshRate.Numerator		= 60;
    sd.BufferDesc.RefreshRate.Denominator	= 1;
    
	// Configuração do formato e declaração de uso do backbuffer
	sd.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage			= DXGI_USAGE_RENDER_TARGET_OUTPUT;
    
	// Configuração do nível de qualidade da imagem final
	sd.SampleDesc.Count		= 1;
    sd.SampleDesc.Quality	= 0;
    
	// Configuração do modo janela e indicação da janela de saída
	sd.OutputWindow			= g_hJanela;
    sd.Windowed				= TRUE;

	// Mode de descarte do backbuffer
	sd.SwapEffect			= DXGI_SWAP_EFFECT_DISCARD;
	
	
	// Criação do dispositivo gráfico e da corrente de trocas	
	// ------------------------------------------------------------------------
	// Indicação do display default
	IDXGIAdapter *pAdapterDefault = NULL;

	// Nenhum software de renderização de terceiros será usado.
	HMODULE NoRasterSoftware = NULL;

		// Configuração dos flags de criação
	UINT createDeviceFlags = 0;
    
	// Níveis desejados de capacidades do dispositivo
	D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
	UINT numFeatureLevels = ARRAYSIZE( featureLevels );

	
	// Criação efetiva da corrente de trocas e dos dispositivos do
	// motor gráfico do directx 11.
	g_hr = D3D11CreateDeviceAndSwapChain( pAdapterDefault, g_driverType,
		NoRasterSoftware, createDeviceFlags, featureLevels, 
		numFeatureLevels, D3D11_SDK_VERSION, &sd, &g_pSwapChain, 
		&g_pd3dDevice, &g_featureLevel, &g_pImmediateContext );

    if( FAILED( g_hr ) ) return g_hr;
   
	
	
	// Criação da textura alvo de renderização (render target view)
    // ------------------------------------------------------------------------
	ID3D11Texture2D *pBackBuffer = NULL;
    
	g_hr = g_pSwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), 
		( LPVOID* )&pBackBuffer );    
	if( FAILED( g_hr ) ) return g_hr;

    g_hr = g_pd3dDevice->CreateRenderTargetView( pBackBuffer, NULL, 
		&g_pRenderTargetView );
    pBackBuffer->Release();
    if( FAILED( g_hr ) )  return g_hr;

    // Configuração da textura alvo no dispositivo
	g_pImmediateContext->OMSetRenderTargets( 1, &g_pRenderTargetView, NULL );

    
	
	// Configuração da janela de visualização (viewport)
    // ------------------------------------------------------------------------
	D3D11_VIEWPORT vp;
    vp.Width =  (float) largura;
    vp.Height = (float) altura;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_pImmediateContext->RSSetViewports( 1, &vp );

    return S_OK;
} // initGfx().fim
// ---]

// [--- $Renderizar() - Renderização da cena#
//-----------------------------------------------------------------------------
// Renderizar() - renderiza a cena
//-----------------------------------------------------------------------------
void Renderizar ( void )
{
    
	// Configuração da cor de limpeza
    float fundoRGBA[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; 

    // Limpeza do backbuffer
	g_pImmediateContext->ClearRenderTargetView( g_pRenderTargetView, fundoRGBA );

    // Apresentação do backbuffer
	g_pSwapChain->Present( 0, 0 );


} // Renderizar().fim
// ---]


// [--- $Limpar() - Limpeza adequada do ambiente#
//-----------------------------------------------------------------------------
// Limpar() - libera os objetos utilizados pela cena
//-----------------------------------------------------------------------------
void Limpar( void )
{
	static bool bLimpo = false;
	
	// Retorne se já estiver limpo
	if (bLimpo == true) return;	

    if( g_pImmediateContext )	g_pImmediateContext->ClearState();

    if( g_pRenderTargetView )	g_pRenderTargetView->Release();

	if( g_pSwapChain )			g_pSwapChain->Release();

	if( g_pImmediateContext )	g_pImmediateContext->Release();
   
	if( g_pd3dDevice )			g_pd3dDevice->Release();

	bLimpo = true;


} // Limpar().fim
// ---]

//-----------------------------------------------------------------------------
// processaJanela() - Tratamento de mensagens da janela
//-----------------------------------------------------------------------------
LRESULT CALLBACK processaJanela( HWND hWnd, UINT message, 
								WPARAM wParam, LPARAM lParam )
{
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;

		    case WM_CLOSE:			
		        Limpar();
				PostQuitMessage (0);
            break;

		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)  
			{
			    Limpar();
				PostQuitMessage( 0);  
			} // endif
		break; 

        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    } // endswitch

    return 0;
} // processaJanela().fim




//-----------------------------------------------------------------------------
// Projeto: prj_Dispositivo - Arquivo: entrada.cpp
// Exemplo de inicialização do motor gráfico (Directx 11)
// Produzido por www.gameprog.com.br
//-----------------------------------------------------------------------------
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
WCHAR		janelaTitulo[]	= L"prj_Janela";



//-----------------------------------------------------------------------------
// Protótipo da função de criação da janela
//-----------------------------------------------------------------------------
HRESULT				initWindow( HINSTANCE hInstance, int nCmdShow );


//-----------------------------------------------------------------------------
// Esta função é o ponto de entrada da aplicação. Ela inicializa a janela e 
// entra no laço de mensagens. O tempo ocioso é utilizado para renderizar a cena.
//-----------------------------------------------------------------------------
int WINAPI wWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					LPWSTR lpCmdLine, int nCmdShow )
{
    UNREFERENCED_PARAMETER( hPrevInstance );
    UNREFERENCED_PARAMETER( lpCmdLine );
    
	// Inicializa a janela
	g_hr = initWindow( hInstance, nCmdShow );
	if (FAILED( g_hr ) ) return 0;

	g_hr = initGfx();
	if (FAILED( g_hr ) ) 
	{
		
		Limpar();
		MessageBoxW (0, L"Falha na inicialização do motor gráfico", 
			L"prj_Dispositivo", MB_OK);
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

	Limpar();
    UnregisterClass( sclasseJanela, g_hInst);  
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

	if ( g_hJanela == NULL)	
	{
		MessageBoxW (NULL, L"Criação da janela falhou!", janelaTitulo, MB_OK);
		return E_FAIL;
	} // endif  

    ShowWindow( g_hJanela, nCmdShow );
	UpdateWindow ( g_hJanela );

    return S_OK;
}

