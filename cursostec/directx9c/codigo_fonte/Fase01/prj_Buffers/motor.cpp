// -----------------------------------------------------------------------------
// Projeto: prj_Buffers - arquivo: motor.cpp
// Esta aplicação ilustra como renderizar um quadrado
// utilizando as interfaces do directx para buffer de
// índices e buffer de vértices. By www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "motor.h"

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Variáveis globais
// Representa o dispositivo Direct3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;
// [---
// <b>
// Representa o buffer de vértices
IDirect3DVertexBuffer9* g_vbVertices = NULL;

// Representa o buffer de índices
IDirect3DIndexBuffer9*	g_ibIndices = NULL;
// </b>
// ---]
// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

// Tamanho da janela 
extern int g_xtela;
extern int g_ytela;

// Constante para cores
const DWORD vermelho	= 0xFFFF0000;
const DWORD branco		= 0xFFFFFFFF;
const DWORD verde			= 0xFF00FF00;
const DWORD azul			= 0xFF0000FF;
const DWORD cinza			= 0xFF101010;

// Definição do formato de vértice utilizado por esta aplicação
#define CustomVertex_TransformedColored_Format ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE )

// Estrutura do vértice customizado
struct CustomVertex_TransformedColored
{
	float x, y, z;
	float rhw;
	DWORD cor;

	// Construtor default
	CustomVertex_TransformedColored() {}

	CustomVertex_TransformedColored( float _x, float _y, float _z,  float _rhw, DWORD _cor)
	{
		x = _x;
		y = _y;
		z = _z;
		rhw = _rhw;
		cor = _cor;
	}
}; // fim da estrutura CustomVertex_TransformedColored
// [---
// initGfx() - Inicializa o Direct3D
HRESULT initGfx( HWND hJanela )
{
	// Cria o objeto Direct3D que é necessário para criar o dispositivo gráfico
	g_Direct3d = Direct3DCreate9( D3D_SDK_VERSION );

	// Verifica se o objeto Direct3D foi criado
	if ( g_Direct3d == NULL)
	{
		MessageBox (NULL, 
			"Falha na inialização do Direct3D", "InitGfx()", MB_OK);		
		return E_FAIL;    
	} // endif

	// Declara  a variável para os parâmetros de apresentação
	D3DPRESENT_PARAMETERS pps; 

	// Limpa a estrutura
	ZeroMemory( &pps, sizeof(pps) );

	// Configura os parâmetros de apresentação
	// A aplicação vai ter janela
	pps.Windowed = TRUE;

	// Esse método transfere rapidamente o backbuffer para a tela imediata
	pps.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// Esse formato vai procurar se encaixar no modo de video corrente
	pps.BackBufferFormat = D3DFMT_UNKNOWN;	

	// Configuração do renderizador a ser criado
	// Adaptador default (0)
	int nAdaptador = D3DADAPTER_DEFAULT;

	// Tipo de dispositivo Hardware ou emulador de referência (software) 
	D3DDEVTYPE dispositivo_tipo = D3DDEVTYPE_HAL;

	// Flags de configuração do dispositivo
	DWORD create_flags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// Criamos aqui o dispositivo renderizador
	g_hr = g_Direct3d->CreateDevice( nAdaptador, dispositivo_tipo, 
		hJanela, create_flags, &pps, &g_device );

	// Verifica se houve falha no processo
	if( FAILED( g_hr ) ) { 
		MessageBox (NULL, "Falha na criação: g_device", "initGfx()", MB_OK);
		return E_FAIL;
	} // endif
	// <b>
	inicializar_Buffers();
	montar_Geometria();
	// </b>

	return S_OK;
} // initGfx().fim
// ---]
// [---
void inicializar_Buffers(void) 
{

	// Segue abaixo os argumentos utilizados na criação do buffer
	// de vértices. Alguns deles aparecem também na criação do
	// buffer de índices.

	// Quantidade de vértices do vertexbuffer
	UINT		nVertices	= 4;

	// Tamanho do vertexbuffer em bytes
	UINT		vbTamanho	= sizeof(CustomVertex_TransformedColored) * nVertices;
	
	// Dica de uso. 
	// É usado usado também na configuração do buffer de índices
	DWORD		uso_flags	= D3DUSAGE_WRITEONLY;

	// Formato do vértice dos vértices do vertexbuffer
	DWORD		vbFormato = CustomVertex_TransformedColored_Format;
	
	// Definição da classe de memória (alojamento)
	// É usado também na configuração do buffer de índices
	D3DPOOL Piscina		= D3DPOOL_MANAGED;

	// Argumento sem uso 
	// Aparece também na criação do buffer de índices
	HANDLE*	hSem_Uso	= NULL;
	
	// Criação efetiva do buffer de vértices (vertexbuffer)
	g_hr = g_device->CreateVertexBuffer ( vbTamanho, uso_flags, 
		vbFormato, Piscina, &g_vbVertices, hSem_Uso);
	
  // Verifica falha na criação
	if(FAILED (g_hr) ) {
    MessageBox (NULL, 
      "Falha na criação do buffer de vértices",
			"inicializar_Buffers()", MB_OK);    
    return; 
  } // endif

  // Quantidade de triângulos
	UINT			nTriangulos = 2;
	
	// Cálculo do tamanho do buffer de índices
	UINT			ibTamanho		= nTriangulos * 3 * 2;
	
	// Formato do tipo de dado do buffer de índices
	D3DFORMAT ibFormato		= D3DFMT_INDEX16;	

	// Criação efetiva do buffer de índices
	g_hr = g_device->CreateIndexBuffer ( ibTamanho, uso_flags, 
		ibFormato, Piscina, &g_ibIndices, hSem_Uso);

	// Verifica falha na criação 
	if(FAILED (g_hr) ) {
    MessageBox (NULL, 
      "Falha na criação do buffer de vértices", 
			"inicializar_Buffers()", MB_OK);    
    return; 
  } // endif

} // inicializar_Buffers().fim
// ---]

// [---
void montar_Geometria(void)
{
	// Posicionamento de profundidade
	float zpos = 1.0f;

	// Segue abaixo os argumentos utilizados no acesso ao buffer
	// de vértices. Alguns deles aparecem também no acesso ao
	// buffer de índices.

	// Ponteiro de acesso aos dados do buffer de vértices
	CustomVertex_TransformedColored* pVerts;

	// nPosInicial e nQtd permite acesso parcial ao buffer de vértices
	// Ambos configurados como zero (0) indica acesso ao conteúdo total
	UINT nPosInicial	= 0;
	UINT nQtd					= 0;

	// Estabelece o modo de acesso ao buffer 
	DWORD tranca_flags  = 0;

	// nPosInicial, nQtd, tranca_flags também são utilizados no
	// acesso ao buffer de índices com os mesmos significados.

	// Aqui a aplicação ganha acesso à memória do buffer de vértices
	g_vbVertices->Lock( nPosInicial, nQtd, (void**)&pVerts, tranca_flags );

	// Configuração normal dos vértices agora
	pVerts[0] = CustomVertex_TransformedColored( 128.0f, 50.0f, zpos, 
		0.7f, vermelho);

	pVerts[1] = CustomVertex_TransformedColored( 512.0f, 384.0f,zpos, 
		0.8f, verde);

	pVerts[2] = CustomVertex_TransformedColored( 128.0f, 384.0f,zpos, 
		1.0f, azul);

	pVerts[3] = CustomVertex_TransformedColored( 512.0f, 50.0f, zpos, 
		1.0f, cinza); 

	// Buffer de índices local temporário
	WORD Indices[6] = {0,1,2,0,3,1};
	
	// Ponteiro de acesso aos dados do buffer de índices
	WORD *pIndices = NULL;

  // Aqui a aplicação ganha acesso à memória do buffer de índices
	g_ibIndices->Lock( nPosInicial, nQtd, (void**)&pIndices, tranca_flags );

	// Configuração normal do buffer de índices
	// Copiando dados do buffer local para o indexbuffer definitivo
	for (int ncx=0; ncx <6; ncx++) pIndices[ncx] = Indices[ncx];	
	
	// Liberação dos buffers (vertexbuffer, indexbuffer) ao directx 
	// que pode mandá-los ou não para a memória de vídeo da placa
	g_vbVertices->Unlock();
  g_ibIndices->Unlock();

} //  montar_Geometria().fim
// ---]
// [---
void renderizar_Geometria()
{
	// Declara o formato de vértice utilizado pela aplicação
	g_device->SetFVF( CustomVertex_TransformedColored_Format );	 
	// <b>
	// Argumentos da função DrawIndexedPrimitive()	
	// A finalidade destes 5 argumentos é permitir a renderização
	// parcial ou uma região localizada do vertexbuffer.
	// A configuração deste contexto é para renderizar totalmente
	// o buffer de vértices.
	UINT			nVerticeBase = 0;
	UINT			nIndiceInicial = 0;
	UINT			nMinVertexIndice = 0;
	UINT			nVerticeQtd			= 4;
	UINT			nContagemPrim		= 2;		

	// O passo (stride) permite ao directx navegar com segurança pelos
	// vértices apresentados.
	UINT			nPasso					=  sizeof(CustomVertex_TransformedColored);	

	// Indicação do stream fonte dos dados
	UINT idStream = 0;

	// Informação do buffer de vértices utilizado
	g_device->SetStreamSource( idStream, g_vbVertices, nVerticeBase, nPasso);
	
	// Informação do buffer de índices utilizado
	g_device->SetIndices( g_ibIndices);
	
	// Renderização efetiva dos vértices
	g_device->DrawIndexedPrimitive( D3DPT_TRIANGLELIST, nVerticeBase,
		nMinVertexIndice,	nVerticeQtd, nIndiceInicial, nContagemPrim);  
	// </b>

} // renderizar_Geometria().fim
// ---]

//  Esta função é chamada por DispatchMessage()  
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam)
{
	switch (mensagem)                 
	{	
	case WM_DESTROY:
		// Coloca uma mensagem WM_QUIT na fila de mensagem
		Limpar();
		PostQuitMessage (0);       
		break;

	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) 
		{
			Limpar();
			PostQuitMessage( 0 );
		} // endif
		break;

		// Essa mensagem vai ocorrer a todo momento    
	case WM_PAINT:
		// Renderiza a cena      
		Renderizar();
		// Invalida a tela para chamar WM_PAINT novamente      
		InvalidateRect( hJanela, NULL, false );
		break;

		// Processamento default de mensagens não tratada pela aplicação
	default:                      
		return DefWindowProc (hJanela, mensagem, wParam, lParam);
	} // endswitch

	return 0;
} // processaJanela().fim

// Limpar() -  Libera todos os objetos previamente inicializados
// -----------------------------------------------------------------------------
VOID Limpar()
{	
	// Libera o buffer de vértices
	if( g_vbVertices != NULL) g_vbVertices->Release();

	// Libera o buffer de índices
	if( g_ibIndices != NULL) g_ibIndices->Release();
	
	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

} // Limpar().fim


// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
VOID Renderizar()
{
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;	

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET, branco, 1.0f, 0);

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
		// <b>
		// Vamos renderizar a geometria
		renderizar_Geometria();
		// </b>
		// Finalizando a cena
		g_device->EndScene();
	} // endif

	// Apresenta o conteúdo do backbuffer na tela
	g_device->Present( NULL, NULL, NULL, NULL );

} // Renderizar().fim

