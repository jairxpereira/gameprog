//-----------------------------------------------------------------------------
// Projeto: prj_Triangulo - Arquivo: motor.cpp
// Exemplo de renderização de um triângulo com HLSL (directx 11)
// Produzido por www.gameprog.com.br
//-----------------------------------------------------------------------------
#include "motor.h"
#include <d3d11.h>
#include <d3dx11.h>

// Funções matemáticas e compilação de HLSL
#include <d3dcompiler.h>
#include <xnamath.h>

// Bibliotecas do directx 11
#pragma comment(lib, "d3d11.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment (lib, "d3dcompiler.lib")

// ------------------------------------------------------------------------
// Variáveis globais
// ------------------------------------------------------------------------
// Variáveis definidas em entrada.cpp
extern	HWND		g_hJanela;
extern	HRESULT		g_hr;

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
// [--- $Variáveis globais - Arquivo: motor.cpp#

// Preparação para renderizar o triângulo
// ------------------------------------------------------------------------
// Configuração inicial dos vértices da forma geométrica
CustomVertex_Position	g_Triangulo[3];

// Descrição de formato dos vértices para a GPU
ID3D11InputLayout       *g_pVertexLayout = NULL;

// Dados compilados do vertexshader
ID3DBlob				*g_vsBlocoCompilado = NULL;

// Interface para o vertexshader
ID3D11VertexShader      *g_pVertexShader = NULL;

// Interface para o buffer de vértices, buffer de índices e buffer de
// constantes
ID3D11Buffer            *g_pVertexBuffer = NULL;

// Interface para o pixelshader
ID3D11PixelShader       *g_pPixelShader = NULL;
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
    // <b>
	// Inicialização do vertexshader e o pixelshader
	g_hr = inicializar_Efeito();
    if( FAILED( g_hr ) ) return g_hr;

	// Montagem do triângulo
	montar_Geometria();

	// Declaração do layout de vértice
	declarar_Vertexlayout();
	if( FAILED( g_hr ) ) return g_hr;

	// Inicialização do vertexbuffer
	g_hr = inicializar_Vertexbuffer();
	if( FAILED( g_hr ) ) return g_hr;
	// </b>
    return S_OK;
} // initGfx().fim
// ---]

// [--- $compilarEfeito() - Compilação do programa em HLSL#
//-----------------------------------------------------------------------------
// compilarEfeito() - Esta função compila um programa hlsl produzindo o 
// vertexshader ou o pixelshader
//-----------------------------------------------------------------------------
HRESULT compilarEfeito( WCHAR* sArquivo, LPCSTR sEntradaFn, LPCSTR sShaderMdl, 
					   ID3DBlob** hlslCompilado )
{
    // Se tudo ocorrer bem esta função retorn S_OK
	g_hr = S_OK;

    // Flags de compilação de hlsl
	DWORD nConfig = D3DCOMPILE_ENABLE_STRICTNESS |  D3DCOMPILE_DEBUG ;

    // Buffer para a mensagem de erro
	ID3DBlob *bufferMensagem;
    
	// Compilação do shader pixelshader ou vertexshader
	g_hr = D3DX11CompileFromFile( sArquivo, NULL, NULL, sEntradaFn, sShaderMdl, 
        nConfig, 0, NULL, hlslCompilado, &bufferMensagem, NULL );
    
	// Tratamento de erro
	if( FAILED(g_hr) )
    {
        if( bufferMensagem != NULL )		
			MessageBoxA (0, (char*) bufferMensagem->GetBufferPointer(), 
			"compilarEfeito()", MB_OK);
        if( bufferMensagem ) bufferMensagem->Release();
        
		return g_hr;
    } // endif

    if( bufferMensagem ) bufferMensagem->Release();

    return S_OK;
} // compilarEfeito()
// ---]


// [--- $inicializar_Efeito() - Inicialização do vertexshader e do pixelshader#
// ----------------------------------------------------------------------------
// inicialzar_Efeito() - Essa função chama compilarEfeito() para inicializar o 
// pixelshader e o vertexshader
// ----------------------------------------------------------------------------
HRESULT inicializar_Efeito(void)
{
    // Compilação do vertexshader
	g_hr = compilarEfeito( L"prj_Triangulo.fx", "gpVertexShader", "vs_4_0", 
		&g_vsBlocoCompilado );
    if( FAILED( g_hr ) )
    {
        MessageBoxW( NULL,
                    L"Falha na compilação do arquivo prj_Triangulo.fx", 
					L"inicializar_Efeito()", MB_OK );
        return g_hr;
    } // endif

	// Criação do vertexshader
	//----------------------------------------------------------------------------
	g_hr = g_pd3dDevice->CreateVertexShader( g_vsBlocoCompilado->GetBufferPointer(), 
		g_vsBlocoCompilado->GetBufferSize(), NULL, &g_pVertexShader );
	
	// Verificação de erro
	if( FAILED( g_hr ) )
	{	
		g_vsBlocoCompilado->Release();
        return g_hr;
	} // endif


	// Compilação do pixelshader
	ID3DBlob *psBlocoCompilado = NULL;
    g_hr = compilarEfeito( L"prj_Triangulo.fx", "gpPixelShader", "ps_4_0", &psBlocoCompilado );
    
	// Verificação de erro
	if( FAILED( g_hr ) )
    {
         MessageBoxW( NULL,
                    L"Falha na compilação do arquivo prj_Triangulo.fx", 
					L"inicializar_Efeito()", MB_OK );
        return g_hr;
    } // endif

	// Criação do pixelshader
	//----------------------------------------------------------------------------
	g_hr = g_pd3dDevice->CreatePixelShader( psBlocoCompilado->GetBufferPointer(), 
		psBlocoCompilado->GetBufferSize(), NULL, 
		&g_pPixelShader );

	// Liberação do bloco compilado
	psBlocoCompilado->Release();
    
	// Encerramento da função
	if( FAILED( g_hr ) ) return g_hr;
	return S_OK;


} // inicializar_Efeito().fim
// ---]

// [--- $montar_Geometria() - Montagem da forma geométrica#
//-----------------------------------------------------------------------------
// montar_Geometria() - Essa função preenche uma array de vértices montando um 
// triângulo.
//-----------------------------------------------------------------------------
void montar_Geometria(void)
{
	// Configuração dos vértices do triângulo
	g_Triangulo[0] = XMFLOAT3( 0.0f, 0.5f, 0.5f );
	g_Triangulo[1] = XMFLOAT3( 0.5f, -0.5f, 0.5f );
	g_Triangulo[2] = XMFLOAT3( -0.5f, -0.5f, 0.5f );

} // montar_Geometria().fim
// ---]

// [--- $declarar_Vertexlayout() - Declaração do layout de vértice#
//-----------------------------------------------------------------------------
// declarar_Vertexlayout() - Essa função declara o formato de vértice 
// presente no vertexbuffer a ser utilizado.
//-----------------------------------------------------------------------------
HRESULT declarar_Vertexlayout(void)
{
	// Se tudo ocorrer bem esta função vai retornar S_OK
	g_hr = S_OK;

	// Descrição do layout do formato de vértice CustomVertex_Position
	LPCSTR sSemantica = "POSITION";
	UINT ndxSemantica = 0;
	DXGI_FORMAT formato = DXGI_FORMAT_R32G32B32_FLOAT;
	UINT nCanal = 0;
	UINT nAlinhamento = 0;
	D3D11_INPUT_CLASSIFICATION  clsEntrada = D3D11_INPUT_PER_VERTEX_DATA;
	UINT taxaInstanciamento = 0;	
		
	// Produção do primeiro elemento da declaração de vértices
	D3D11_INPUT_ELEMENT_DESC atributo_pos =
	{
		sSemantica, 
		ndxSemantica, 
		formato, 
		nCanal, 
		nAlinhamento, 
		clsEntrada, 
		taxaInstanciamento
	};


	// Definição do layout de entrada
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		atributo_pos
	};
	UINT numElements = ARRAYSIZE( layout );

	// Criação do objeto layout de entrada
	g_hr = g_pd3dDevice->CreateInputLayout( layout, numElements, 
		g_vsBlocoCompilado->GetBufferPointer(),
		g_vsBlocoCompilado->GetBufferSize(), &g_pVertexLayout );

	g_vsBlocoCompilado->Release();
	if( FAILED( g_hr ) ) return g_hr;

	// Instalação do layout de entrada
	g_pImmediateContext->IASetInputLayout( g_pVertexLayout );

	return S_OK;

} // declarar_Vertexlayout().fim
// ---]

// [--- $inicializar_Vertexbuffer() - Inicialização do vertexbuffer#
//-----------------------------------------------------------------------------
// inicializar_Vertexbuffer() - Essa função inicializa o vertexbuffer. 
// O vertexshader e a geometria devem ser inicializados antes dele.
//-----------------------------------------------------------------------------
HRESULT inicializar_Vertexbuffer(void)
{     

   // Descrição do vertexbuffer sendo montado
	// Declaração e preparação inicial da estrutura
	D3D11_BUFFER_DESC bd;
	ZeroMemory( &bd, sizeof(bd) );
    
	// Declaração de uso
	bd.Usage = D3D11_USAGE_DEFAULT;    
	
	// Tamanho em bytes do vertexbuffer
	bd.ByteWidth = sizeof( CustomVertex_Position ) * 3;
    
	// Indicação de vertexbuffer
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	
	
	// Flags de configuração de acesso
	bd.CPUAccessFlags = 0;    
	
	// Declaração dos dados do vertexbuffer
	D3D11_SUBRESOURCE_DATA vbDados;
	ZeroMemory( &vbDados, sizeof(vbDados) );
    vbDados.pSysMem = g_Triangulo;
    g_hr = g_pd3dDevice->CreateBuffer( &bd, &vbDados, &g_pVertexBuffer );
    if( FAILED( g_hr ) ) return g_hr;

    // Instalação do vertexbuffer
    UINT stride = sizeof( CustomVertex_Position );
    UINT offset = 0;
    g_pImmediateContext->IASetVertexBuffers( 0, 1, &g_pVertexBuffer, &stride, &offset );

    // Definição da topologia primitiva relativa ao vertexbuffer
    g_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST  );

    return S_OK;

} // inicializar_Buffers().fim
// ---]

// [--- $Renderizar() - Renderização da cena#
//-----------------------------------------------------------------------------
// Renderizar() - renderiza a cena
//-----------------------------------------------------------------------------
void Renderizar ( void )
{
    
	// Configuração da cor de limpeza
    float fundoRGBA[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; 

    // Limpeza do backbuffer
	g_pImmediateContext->ClearRenderTargetView( g_pRenderTargetView, fundoRGBA );

	// Instala o vertexshader, o pixelshader e desenha o triângulo
	g_pImmediateContext->VSSetShader( g_pVertexShader, NULL, 0 );
	g_pImmediateContext->PSSetShader( g_pPixelShader, NULL, 0 );
    g_pImmediateContext->Draw( 3, 0 );

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


	// Libera o vertexbuffer
	if( g_pVertexBuffer ) g_pVertexBuffer->Release();
    
	// Liberar o vertexlayout
	if( g_pVertexLayout ) g_pVertexLayout->Release();
    
	// Libera o vertexshader
	if( g_pVertexShader ) g_pVertexShader->Release();
    
	// Libera o pixelshader
	if( g_pPixelShader ) g_pPixelShader->Release();


    // Liberação dos demais objetos
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
// endfile: motor.cpp


