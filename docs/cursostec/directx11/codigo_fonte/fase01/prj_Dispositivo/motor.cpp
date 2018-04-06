//-----------------------------------------------------------------------------
// Projeto: prj_Dispositivo - Arquivo: motor.cpp
// Exemplo de inicialização do motor gráfico (Directx 11)
// Produzido por www.gameprog.com.br
//-----------------------------------------------------------------------------
#include "motor.h"
#include <d3d11.h>
#include <d3dx11.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")


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

	// Modo de descarte do backbuffer
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




