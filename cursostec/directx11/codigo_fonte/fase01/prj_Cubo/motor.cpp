﻿// -----------------------------------------------------------------------------
// Projeto: prj_Cubo - Arquivo: motor.cpp
// Exemplo de como renderizar um cubo colorido (directx 11)
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
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

// [--- $Aspectos globais: arquivo motor.cpp#
// <b>

// Matriz mundo para movimentação da lua ( cubo lateral )
XMMATRIX                g_mtxMundo02;

// Estruturas para segurar temporariamente os dados de constantbuffer
// do planeta (cubo central) e da lua (cubo lateral)
ConstantBuffer g_cbPlaneta;
ConstantBuffer g_cbLua;

// Atualização do timer de movimentação dos objetos
float g_deltaTempo   = 0.0f;
DWORD g_tempoInicial = 0;
DWORD g_tempoAtual   = 0;
// </b>
// ---]

// Preparação para renderizar o cubo
// ------------------------------------------------------------------------
// Configuração inicial dos vértices da forma geométrica
CustomVertex_PositionColored	g_Cubo[8];

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

// Interface para o indebuffer
ID3D11Buffer            *g_pIndexBuffer = NULL;

// Interface para o constantbuffer
ID3D11Buffer            *g_pConstantBuffer = NULL;

// Matrizes de configuração da câmera
// Matriz de mundo
XMMATRIX g_mtxMundo; 
// Matriz de visão
XMMATRIX g_mtxVisao; 
// Matriz de projeção
XMMATRIX g_mtxProj; 

// [--- $initGfx() - Inicialização do motor gráfico#
// ------------------------------------------------------------------------
// Cria a corrente de trocas e os dispositivos do motor gráfico
// ------------------------------------------------------------------------
HRESULT initGfx()
{
// Se tudo ocorrer bem initGfx() vai retornar S_OK
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
// <b>

// Instala a textura alvo no dispositivo 
g_pImmediateContext->OMSetRenderTargets( 1, &g_pRenderTargetView, 0 );
// </b>
	

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

// Montagem da forma geométrica
montar_Geometria();

// Declaração do layout de vértice
g_hr = declarar_Vertexlayout();
if( FAILED( g_hr ) ) return g_hr;

// Inicialização do vertexbuffer e indexbuffer
g_hr = inicializar_Vertexbuffer();
g_hr = inicializar_Indexbuffer();

// Inicialização do constantbuffer
g_hr = inicializar_Constantbuffer();
if( FAILED( g_hr ) ) return g_hr;	
inicializar_Camera();


return S_OK;
} // initGfx().fim
// ---]


// [--- $Renderizar() - Renderização da cena#
// -----------------------------------------------------------------------------
// Renderizar() - renderiza a cena
// -----------------------------------------------------------------------------
void Renderizar ( void )
{	

// Configuração da cor de limpeza
float branco[4] = { 1.0f, 1.0f, 1.0f, 1.0f }; 
// <b>
// Atualização do timer para animação dos cubos
atualizar_Temporizador();
// </b>
// Limpeza do backbuffer
g_pImmediateContext->ClearRenderTargetView( g_pRenderTargetView, branco );

// Instala o vertexshader e o pixelshader
g_pImmediateContext->VSSetShader( g_pVertexShader, NULL, 0 );
g_pImmediateContext->PSSetShader( g_pPixelShader, NULL, 0 );

// Instala o atual constantbuffer
g_pImmediateContext->VSSetConstantBuffers( 0, 1, &g_pConstantBuffer );
// <b>
// Renderiza o planeta
renderizar_Planeta();

// Renderiza a lua
renderizar_Lua();
// </b>
// Apresentação do backbuffer
g_pSwapChain->Present( 0, 0 );
} // Renderizar().fim
// ---]

// [--- $atualizar_Temporizador() - Atualiza o timer#
// ------------------------------------------------------------------------
// Atualizar o timer de movimentação dos objetos
// ------------------------------------------------------------------------
void atualizar_Temporizador(void)
{
// Verificação do tempo atual
DWORD tempoAtual = GetTickCount();

// Configuração inicial da variável g_tempoInicial
if( g_tempoInicial == 0 )	g_tempoInicial = tempoAtual;

// Diferença de tempo entre os frames em termos de segundos
g_deltaTempo = ( tempoAtual - g_tempoInicial ) / 1000.0f;

} // atualizar_Temporizador
// ---]

// [--- $renderizar_Planeta() - Renderização do cubo central#
// -----------------------------------------------------------------------------
// renderizar_Planeta() - renderiza o planeta (cubo central)
// -----------------------------------------------------------------------------
void renderizar_Planeta(void)
{

// Atualização da matriz mundo que anima o cubo
XMMATRIX  rot = XMMatrixRotationY( g_deltaTempo );
XMMATRIX  pos = XMMatrixTranslation(0.0f, 1.0f, 3.0f);  
XMMATRIX  sc  = XMMatrixScaling(0.5f, 1.0f, 1.0f);
g_mtxMundo = rot * pos * sc;

// Atualização das variáveis do shader
g_cbPlaneta.mWorld		= XMMatrixTranspose( g_mtxMundo );
g_cbPlaneta.mView	    = XMMatrixTranspose( g_mtxVisao  );
g_cbPlaneta.mProjection	= XMMatrixTranspose( g_mtxProj );

// Atualização das variáveis na placa de vídeo
g_pImmediateContext->UpdateSubresource( g_pConstantBuffer, 0, 
									   NULL, &g_cbPlaneta, 0, 0 );

// Desenha a forma geométrica
g_pImmediateContext->DrawIndexed( 36, 0, 0 );  


} // renderizar_Planeta()
// ---]

// [--- $renderizar_Lua() - Renderização do cubo lateral#
// ------------------------------------------------------------------------
// Renderiza o cubo lateral que representa uma lua orbitando
// em torno de um planeta ( o cubo central )
// ------------------------------------------------------------------------
void renderizar_Lua(void)
{

// Monta a rotação da lua ao redor do planeta
XMMATRIX zrot  = XMMatrixRotationZ( -g_deltaTempo );
XMMATRIX yrot  = XMMatrixRotationY( -g_deltaTempo * 1.1f );
XMMATRIX pos   = XMMatrixTranslation( -4.0f, 1.0f, 2.0f );
XMMATRIX sc    = XMMatrixScaling( 0.3f, 0.3f, 0.3f );

// Ordem de transformações para orbitar ao redor da origem
// O movimento orbital é causado por yrot no final
g_mtxMundo02   = sc * zrot * pos * yrot;

// Prepara os dados para o shader
g_cbLua.mWorld      = XMMatrixTranspose( g_mtxMundo02 );
g_cbLua.mView       = XMMatrixTranspose( g_mtxVisao );  
g_cbLua.mProjection = XMMatrixTranspose( g_mtxProj );

// Atualiza o constantbuffer no shader
g_pImmediateContext->UpdateSubresource( g_pConstantBuffer, 0, 
							   NULL, &g_cbLua, 0, 0 );

// Desenha a forma geométrica
g_pImmediateContext->DrawIndexed( 36, 0, 0 );

}  // renderizar_Lua().fim
// ---]

// -----------------------------------------------------------------------------
// inicializar_Constantbuffer() - Essa função inicializa o constantbuffer. 
// -----------------------------------------------------------------------------
HRESULT inicializar_Constantbuffer(void)
{    
 
// Se tudo ocorrer bem, essa função retorna S_OK
g_hr = S_OK;

// Declaração e preparação inicial do constantbuffer
D3D11_BUFFER_DESC bd;
ZeroMemory( &bd, sizeof(bd) );

// Declaração de uso
bd.Usage = D3D11_USAGE_DEFAULT;    

// Tamanho em bytes do constantbuffer
bd.ByteWidth = sizeof(ConstantBuffer);

// Indicação de constantbuffer
bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

// Flags de configuração de acesso
bd.CPUAccessFlags = 0;

// Criação efetiva do constantbuffer
g_hr  = g_pd3dDevice->CreateBuffer( &bd, NULL, &g_pConstantBuffer );

// Verificação de erro
if( FAILED( g_hr ) )
{
    MessageBoxW( NULL,
                L"Falha na inicialização do constantbuffer", 
				L"inicializar_Constantbuffer()", MB_OK );
    return g_hr;
} // endif

return S_OK;

} // inicializar_Constantbuffer().fim

// -----------------------------------------------------------------------------
// inicializar_Camera() - Essa função inicializa a câmera. 
// -----------------------------------------------------------------------------
void inicializar_Camera(void)
{

// Inicializa a matriz de mundo - Essa matriz é utilizada para transformar
// posição, rotação e escala do objeto 3d; será usada em atualizar_Camera()
// ----------------------------------------------------------------------------
g_mtxMundo = XMMatrixIdentity();


// Inicializa a matriz de visualização
// ----------------------------------------------------------------------------
// Dados para a configuração da matriz de visualização
// Aonde está a câmera? - posição da câmera
XMVECTOR cam_pos = XMVectorSet(0.0f, 1.0f, -8.0f, 0.0f); 

// Para aonde a câmera está apontada ou olhando? Alvo da câmera
XMVECTOR cam_alvo = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);   

// A câmera está de cabeça pra baixo? - orientação da câmera
XMVECTOR cam_vetorcima = XMVectorSet(0.0f, 1.0f, 0.0f,0.0f);   

// Configura matriz de visualização
g_mtxVisao = XMMatrixLookAtLH( cam_pos, cam_alvo, cam_vetorcima );

// Inicializa a matriz de projeção
// ----------------------------------------------------------------------------
// Vamos obter o tamanho da área cliente da janela
RECT areaCliente;
GetClientRect( g_hJanela, &areaCliente );
UINT largura = areaCliente.right - areaCliente.left;
UINT altura  = areaCliente.bottom - areaCliente.top;

// Vamos identificar outros argumentos da matriz de projeção
float aspecto		= (float) largura / altura;
float corte_perto	= 0.1f; 
float corte_longe	= 1000.0f; 
float campo_visao	= XM_PIDIV4;

// Configura matriz de projeção
g_mtxProj = XMMatrixPerspectiveFovLH( campo_visao, aspecto, 
								       corte_perto, corte_longe );
} // inicializar_Camera().fim

// -----------------------------------------------------------------------------
// compilarEfeito() - Esta função compila um programa hlsl produzindo o 
// vertexshader ou o pixelshader
// -----------------------------------------------------------------------------
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
// inicializar_Efeito() - Essa função chama compilarEfeito() para inicializar o 
// pixelshader e o vertexshader
// ----------------------------------------------------------------------------
HRESULT inicializar_Efeito(void)
{
// Compilação do vertexshader
g_hr = compilarEfeito( L"prj_Camera.fx", "gpVertexShader", "vs_4_0", 
	&g_vsBlocoCompilado );
if( FAILED( g_hr ) )
{
    MessageBoxW( NULL,
                L"Falha na compilação do arquivo prj_Camera.fx", 
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
g_hr = compilarEfeito( L"prj_Camera.fx", "gpPixelShader", "ps_4_0", &psBlocoCompilado );

// Verificação de erro
if( FAILED( g_hr ) )
{
     MessageBoxW( NULL,
                L"Falha na compilação do arquivo prj_Camera.fx", 
				L"inicializar_Efeito()", MB_OK );
    return g_hr;
} // endif

// Criação do pixelshader
// ----------------------------------------------------------------------------
g_hr = g_pd3dDevice->CreatePixelShader( psBlocoCompilado->GetBufferPointer(), 
	psBlocoCompilado->GetBufferSize(), NULL, 
	&g_pPixelShader );

// Liberação do bloco compilado
psBlocoCompilado->Release();

// Encerramento da função
if( FAILED( g_hr ) ) return g_hr;
return S_OK;


} // inicializar_Efeito().fim

// -----------------------------------------------------------------------------
// [--- $montar_Geometria() - Listagem da montagem do cubo# 
// -----------------------------------------------------------------------------
void montar_Geometria(void)
{

// Definição de cores
XMFLOAT4 vermelho =  XMFLOAT4( 1.0f, 0.0f, 0.0f, 1.0f);   
XMFLOAT4 verde    =  XMFLOAT4( 0.0f, 1.0f, 0.0f, 1.0f);   
XMFLOAT4 azul     =  XMFLOAT4( 0.0f, 0.0f, 1.0f, 1.0f);   
XMFLOAT4 cinza    =  XMFLOAT4( 0.3f, 0.3f, 0.3f, 1.0f);   

// Posicionamento dos vértices
XMFLOAT3 p0 = XMFLOAT3(  -1.0f, 1.0f, -1.0f );  
XMFLOAT3 p1 = XMFLOAT3(   1.0f, 1.0f, -1.0f );  
XMFLOAT3 p2 = XMFLOAT3(   1.0f, 1.0f,  1.0f );  
XMFLOAT3 p3 = XMFLOAT3(  -1.0f, 1.0f,  1.0f );  

XMFLOAT3 p4 = XMFLOAT3(  -1.0f, -1.0f, -1.0f );  
XMFLOAT3 p5 = XMFLOAT3(   1.0f, -1.0f, -1.0f );  
XMFLOAT3 p6 = XMFLOAT3(   1.0f, -1.0f,  1.0f );  
XMFLOAT3 p7 = XMFLOAT3(  -1.0f, -1.0f,  1.0f ); 

// Posicionamento dos vértices na array pré-vertexbuffer
g_Cubo[0] = CustomVertex_PositionColored (p0, vermelho );  
g_Cubo[1] = CustomVertex_PositionColored (p1, verde    );  
g_Cubo[2] = CustomVertex_PositionColored (p2, azul     );  
g_Cubo[3] = CustomVertex_PositionColored (p3, cinza    );

g_Cubo[4] = CustomVertex_PositionColored (p4, vermelho );  
g_Cubo[5] = CustomVertex_PositionColored (p5, verde    );  
g_Cubo[6] = CustomVertex_PositionColored (p6, azul     );  
g_Cubo[7] = CustomVertex_PositionColored (p7, cinza    );

} // montar_Geometria().fim
// ---]

// -----------------------------------------------------------------------------
// declarar_Vertexlayout() - Essa função declara o formato de vértice 
// presente no vertexbuffer a ser utilizado.
// -----------------------------------------------------------------------------
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


// Definição do segundo do formato\layout de vértice
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

// -----------------------------------------------------------------------------
// inicializar_Vertexbuffer() - Essa função inicializa o vertexbuffer. 
// O vertexshader e a geometria devem ser inicializados antes dele.
// -----------------------------------------------------------------------------
HRESULT inicializar_Vertexbuffer(void)
{     

// Descrição do vertexbuffer sendo montado
// Declaração e preparação inicial da estrutura
D3D11_BUFFER_DESC bd;
ZeroMemory( &bd, sizeof(bd) );

// Declaração de uso
bd.Usage = D3D11_USAGE_DEFAULT;    

// Tamanho em bytes do vertexbuffer
bd.ByteWidth = sizeof( CustomVertex_PositionColored ) * 8;

// Indicação de vertexbuffer
bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	

// Flags de configuração de acesso
bd.CPUAccessFlags = 0;    

// Declaração dos dados do vertexbuffer
D3D11_SUBRESOURCE_DATA vbDados;
ZeroMemory( &vbDados, sizeof(vbDados) );
vbDados.pSysMem = g_Cubo;
g_hr = g_pd3dDevice->CreateBuffer( &bd, &vbDados, &g_pVertexBuffer );

// Verificação de erro
if( FAILED( g_hr ) )
{
    MessageBoxW( NULL,
                L"Falha na inicialização do Vertexbuffer", 
				L"inicializar_Vertexbuffer()", MB_OK );
    return g_hr;
} // endif

// Instalação do vertexbuffer
UINT stride = sizeof( CustomVertex_PositionColored );
UINT offset = 0;
g_pImmediateContext->IASetVertexBuffers( 0, 1, &g_pVertexBuffer, &stride, &offset );

// Definição da topologia primitiva relativa ao vertexbuffer
g_pImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST  );

return S_OK;

} // inicializar_Vertexbuffer().fim

// -----------------------------------------------------------------------------
// [--- $inicializar_Indexbuffer() - indexbuffer para montagem do cubo.# 
// -----------------------------------------------------------------------------
HRESULT inicializar_Indexbuffer(void)
{    

// Se tudo ocorrer bem, essa função retorna S_OK
g_hr = S_OK;

// Elementos do indexbuffer para montar o cubo
WORD indices[] =
{
    3,1,0,
    2,1,3,

    0,5,4,
    1,5,0,

    3,4,7,
    0,4,3,

    1,6,5,
    2,6,1,

    2,7,6,
    3,7,2,

    6,4,5,
    7,4,6,
};


// Declaração e preparação inicial do indexbuffer
D3D11_BUFFER_DESC bd;
ZeroMemory( &bd, sizeof(bd) );

// Declaração de uso
bd.Usage = D3D11_USAGE_DEFAULT;    

// Tamanho em bytes do vertexbuffer
bd.ByteWidth = sizeof( WORD ) * 36;

// Indicação de indexbuffer
bd.BindFlags = D3D11_BIND_INDEX_BUFFER;	

// Flags de configuração de acesso
bd.CPUAccessFlags = 0;    

// Declaração dos dados do vertexbuffer
D3D11_SUBRESOURCE_DATA ibDados;
ZeroMemory( &ibDados, sizeof(ibDados) );
ibDados.pSysMem = indices;

// Criação efetiva do indexbuffer
g_hr  = g_pd3dDevice->CreateBuffer( &bd, &ibDados, &g_pIndexBuffer );

// Verificação de erro
if( FAILED( g_hr ) )
{
    MessageBoxW( NULL,
                L"Falha na inicialização do indexbuffer", 
				L"inicializar_Indexbuffer()", MB_OK );
    return g_hr;
} // endif

// Instalação do indexbuffer
g_pImmediateContext->IASetIndexBuffer( g_pIndexBuffer, 
									  DXGI_FORMAT_R16_UINT, 0 );

return S_OK;

} // inicializar_Indexbuffer().fim
// ---]


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


// -----------------------------------------------------------------------------
// Limpar() - libera os objetos utilizados pela cena
//  -----------------------------------------------------------------------------
void Limpar( void )
{
static bool bLimpo = false;

// Retorne se já estiver limpo
if (bLimpo == true) return;	

if( g_pImmediateContext )	g_pImmediateContext->ClearState();

// Libera o vertexbuffer
if( g_pVertexBuffer ) g_pVertexBuffer->Release();

if( g_pConstantBuffer ) g_pConstantBuffer->Release();
if( g_pIndexBuffer ) g_pIndexBuffer->Release();

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
g_pVertexBuffer		= NULL; 
g_pIndexBuffer		= NULL; 
g_pConstantBuffer	= NULL;
g_pVertexLayout		= NULL; 
g_pVertexShader		= NULL; 
g_pPixelShader		= NULL; 
g_pRenderTargetView = NULL; 
g_pSwapChain		= NULL; 
g_pImmediateContext = NULL; 
g_pd3dDevice		= NULL;

} // Limpar().fim
// endfile: motor.cpp