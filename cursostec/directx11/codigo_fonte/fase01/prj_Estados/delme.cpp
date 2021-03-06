﻿//-----------------------------------------------------------------------------
// Projeto: prj_Estados - Arquivo: motor.h
// Exemplo de renderização de um quadrado em modo wireframe
// Produzido por www.gameprog.com.br
//-----------------------------------------------------------------------------
#include <windows.h>
#include <xnamath.h>
#include <d3d11.h>

#if !defined motor_h
#define motor_h

// [--- $Aspectos globais: arquivo motor.h#
// Formato de vértice com posição e cor
//--------------------------------------------------------------------------------------
struct CustomVertex_PositionColored
{
	// Posição do vértice (Pos.x, Pos.y, Pos.z)
	XMFLOAT3 Pos;	
	
	// Cor dos vértices (Color.r, Color.g, Color.b, Color.a)
	XMFLOAT4 Color;

	// Construtor padrão
	CustomVertex_PositionColored() {}

	// Construtor alternativo e mais usado
	CustomVertex_PositionColored(XMFLOAT3 _Pos, XMFLOAT4 _Color)
	{
		Pos   = _Pos;
		Color = _Color;

	} // fim do construtor	

}; // fim da estrutura CustomVertex_PositionColoredColored
	
	// Essa função preenche uma array de vértices montando um triângulo
	void montar_Geometria(void);

	// Essa função declara o layout de vértice utilizado
	HRESULT declarar_Vertexlayout(void);

	// Essa função inicializa o vertexbuffer. O vertexshader e a geometria devem
	// ser inicializados antes dele.
	HRESULT inicializar_Vertexbuffer(void);
	
	// Função de processamento de mensagens da janela
	LRESULT CALLBACK    processaJanela( HWND, UINT, WPARAM, LPARAM );	
	// <b>	
	// Trtat pressionamento das teclas 'S' e 'W'
    void tratarTeclado (WPARAM wParam);
	
	// Configura o rasterizado em modo sólido ou wireframe
	HRESULT configurar_Rasterizador(void);
	
		// Inicializa o motor gráfico
	HRESULT initGfx();
	
	// Função de renderizar a cena
	void	Renderizar( void );
	// </b>
	// ---]

	// Esta função compila um programa hlsl produzindo o vertexshader
	// ou o pixelshader
	HRESULT compilarEfeito( WCHAR* sArquivo, LPCSTR sEntradaFn, 
		LPCSTR sShaderMdl, ID3DBlob** hlslCompilado );

	// Essa função chama compilarEfeito() para inicializar o pixelshader e
	// o vertexshader
	HRESULT inicializar_Efeito(void);
	
	// Função de liberar os objetos utilizados pela aplicação
	void	Limpar( void );	

#endif
// endfile: motor.h﻿//-----------------------------------------------------------------------------
// Projeto: prj_Estados - Arquivo: motor.cpp
// Exemplo de renderização de um quadrado em modo wireframe
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

// Preparação para renderizar o triângulo
// ------------------------------------------------------------------------
// Dados compilados do vertexshader
ID3DBlob				*g_vsBlocoCompilado = NULL;

// Interface para o vertexshader
ID3D11VertexShader      *g_pVertexShader = NULL;

// Interface para o pixelshader
ID3D11PixelShader       *g_pPixelShader = NULL;
// [--- $Variáveis globais - Arquivo: motor.cpp#
// <b>
// Interface para o buffer de vértices, buffer de índices e buffer de
// constantes
ID3D11Buffer            *g_pVertexBuffer = NULL;

// Descrição de formato dos vértices para a GPU
ID3D11InputLayout       *g_pVertexLayout = NULL;

// Configuração inicial dos vértices da forma geométrica
CustomVertex_PositionColored	g_Triangulo[6];

// Interface do rasterizador
ID3D11RasterizerState	*g_rasterState;

// Configuração de visualização do rasterizador
D3D11_FILL_MODE g_nFillMode = D3D11_FILL_SOLID;
// </b>
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

// Inicialização do vertexshader e o pixelshader
g_hr = inicializar_Efeito();
if( FAILED( g_hr ) ) return g_hr;

// <b>
// Montagem do triângulo
montar_Geometria();

// Declaração do layout de vértice
declarar_Vertexlayout();
if( FAILED( g_hr ) ) return g_hr;

// Inicialização do vertexbuffer
g_hr = inicializar_Vertexbuffer();
if( FAILED( g_hr ) ) return g_hr;

// Configuração do rasterizador
// A visualização inicial da cena é sólida (D3D11_FILL_SOLID)
configurar_Rasterizador();

// </b>
return S_OK;
} // initGfx().fim
// ---]
// [--- $tratarTeclado() - Tramento do teclado#
//-----------------------------------------------------------------------------
// tratarTeclado() - Faz tratamento do teclado
//-----------------------------------------------------------------------------
void tratarTeclado (WPARAM wParam) 
{
 // Modo de preenchimento sólido na tecla S
 if (wParam == 'S')  
 {
	 g_nFillMode = D3D11_FILL_SOLID;
	 configurar_Rasterizador();

 }

 // Modo de preenchimento wireframe na tecla S
 if (wParam == 'W')  
 {
	 g_nFillMode = D3D11_FILL_WIREFRAME;
	configurar_Rasterizador();
 }
 
} // tratarTeclado().fim
// ---]

// [--- $configurar_Rasterizador() - Configuração do rasterizador#
//-----------------------------------------------------------------------------
// configurar_Rasterizador() - Configura o rasterizador
//-----------------------------------------------------------------------------
HRESULT configurar_Rasterizador(void)
{

// Se tudo ocorrer bem, essa função retorna S_OK
g_hr = S_OK;


// Liberação do rasterizador com configuração anterior
if (g_rasterState)	
{
	g_rasterState->Release();
	g_rasterState = NULL;
}

// Preparação inicial da estrutura de descrição do rasterizador
D3D11_RASTERIZER_DESC rasterDesc;
ZeroMemory ( &rasterDesc, sizeof (D3D11_RASTERIZER_DESC) );

// Descrição do rasterizar que determina quais e como os polígonos
// serão renderizados.
rasterDesc.AntialiasedLineEnable = false;
rasterDesc.CullMode = D3D11_CULL_BACK;
rasterDesc.DepthBias = 0;
rasterDesc.DepthBiasClamp = 0.0f;
rasterDesc.DepthClipEnable = true;
rasterDesc.FillMode = g_nFillMode; 
rasterDesc.FrontCounterClockwise = false;
rasterDesc.MultisampleEnable = false;
rasterDesc.ScissorEnable = false;
rasterDesc.SlopeScaledDepthBias = 0.0f;

// Criação efetiva do rasterizador
g_hr = g_pd3dDevice->CreateRasterizerState(&rasterDesc, &g_rasterState);

// Verificação de erro
if(FAILED(g_hr ))
{
	return g_hr ;
}

// Instalação dos estados do rasterizador
g_pImmediateContext->RSSetState(g_rasterState);

// Saindo da função
return S_OK;

} // configurar_Rasterizador().fim
// ---]

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

// ----------------------------------------------------------------------------
// inicialzar_Efeito() - Essa função chama compilarEfeito() para inicializar o 
// pixelshader e o vertexshader
// ----------------------------------------------------------------------------
HRESULT inicializar_Efeito(void)
{
// Compilação do vertexshader
g_hr = compilarEfeito( L"prj_Estados.fx", "gpVertexShader", "vs_4_0", 
	&g_vsBlocoCompilado );
if( FAILED( g_hr ) )
{
    MessageBoxW( NULL,
                L"Falha na compilação do arquivo prj_Estados.fx", 
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
g_hr = compilarEfeito( L"prj_Estados.fx", "gpPixelShader", "ps_4_0", &psBlocoCompilado );

// Verificação de erro
if( FAILED( g_hr ) )
{
     MessageBoxW( NULL,
                L"Falha na compilação do arquivo prj_Estados.fx", 
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



// [--- $montar_Geometria() - Montagem da forma geométrica#
//-----------------------------------------------------------------------------
// montar_Geometria() - Essa função preenche uma array de vértices montando  
// uma forma geométrica.
//-----------------------------------------------------------------------------
void montar_Geometria(void)
{

// Definição de cores
XMFLOAT4 vermelho =  XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f);
XMFLOAT4 verde	  =  XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f);
XMFLOAT4 azul	  =  XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f);
XMFLOAT4 cinza	  =  XMFLOAT4( 0.3f, 0.3f, 0.3f, 1.0f);

// Posicionamento dos vértices do primeiro triângulo
XMFLOAT3 p0 = XMFLOAT3(  -0.5f,  0.5f,  0.5f  );
XMFLOAT3 p1 = XMFLOAT3(  0.5f,  -0.5f,  0.5f  );
XMFLOAT3 p2 = XMFLOAT3( -0.5f,  -0.5f,  0.5f  );

// Posicionamento dos vértices do segundo triângulo
XMFLOAT3 p3 = XMFLOAT3( -0.5f,  0.5f,  0.5f  );
XMFLOAT3 p4 = XMFLOAT3(  0.5f,  0.5f,  0.5f  );
XMFLOAT3 p5 = XMFLOAT3(  0.5f, -0.5f,  0.5f  );

// Configuração dos vértices do primeiro triângulo
g_Triangulo[0] = CustomVertex_PositionColored (p0, vermelho );
g_Triangulo[1] = CustomVertex_PositionColored (p1, verde    );
g_Triangulo[2] = CustomVertex_PositionColored (p2, azul     );

// Configuração dos vértices do segundo triângulo
g_Triangulo[3] = CustomVertex_PositionColored (p3, vermelho );
g_Triangulo[4] = CustomVertex_PositionColored (p4, cinza    );
g_Triangulo[5] = CustomVertex_PositionColored (p5, verde    );
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

// Descrição do layout do formato de vértice CustomVertex_PositionColored
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

// Produção do segundo elemento da declaração de vértices
D3D11_INPUT_ELEMENT_DESC atributo_cor = 
{ 
	"COLOR", 
	0, 
	DXGI_FORMAT_R32G32B32A32_FLOAT, 
	0, 
	12, 		
	D3D11_INPUT_PER_VERTEX_DATA, 0 
};


// Definição do layout de entrada
D3D11_INPUT_ELEMENT_DESC layout[] =
{
	atributo_pos, atributo_cor
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
bd.ByteWidth = sizeof( CustomVertex_PositionColored ) * 6;

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
UINT stride = sizeof( CustomVertex_PositionColored );
UINT offset = 0;
g_pImmediateContext->IASetVertexBuffers( 0, 1, &g_pVertexBuffer, &stride, &offset );

// Definição da topologia primitiva relativa ao vertexbuffer
g_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

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
g_pImmediateContext->Draw( 6, 0 );

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

// Limpa o dispositivo renderizador
if( g_pImmediateContext )	g_pImmediateContext->ClearState();

// Liberação do rasterizador
if( g_rasterState )	g_rasterState->Release();	 

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

// Limpeza responsável
g_rasterState 		= NULL;
g_pVertexBuffer		= NULL;
g_pVertexLayout 	= NULL;
g_pVertexShader		= NULL;
g_pPixelShader 		= NULL;
g_pRenderTargetView = NULL;
g_pSwapChain 		= NULL;
g_pImmediateContext	= NULL;
g_pd3dDevice 		= NULL;

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
// [--- $processaJanela() - Tratamento da mensagem WM_KEYDOWN#
	case WM_KEYDOWN:

		if (wParam == VK_ESCAPE)  
		{
		    Limpar();
			PostQuitMessage( 0);  
		} // endif
// <b>
		tratarTeclado (wParam);
// </b>
		break; 
// ---]

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;

    default:
        return DefWindowProc( hWnd, message, wParam, lParam );
} // endswitch

return 0;
} // processaJanela().fim
// endfile: motor.cpp

﻿//-----------------------------------------------------------------------------
// Projeto: prj_Estados - Arquivo: entrada.cpp
// Exemplo de renderização de um quadrado em modo wireframe
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


