// [---
// -----------------------------------------------------------------------------
// Projeto: prj_Triangulo01 - arquivo: motor.cpp
// Esta aplicação ilustra como renderizar um triângulo
// Produzido por www.gameprog.com.br
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

// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

extern int g_xtela;
extern int g_ytela;

// Constante para cores
const DWORD vermelho	= 0xFFFF0000;
const DWORD branco		= 0xFFFFFFFF;
const DWORD verde			= 0xFF00FF00;
const DWORD azul			= 0xFF0000FF;

// Definição do formato de vértice utilizado pela aplicação
#define CustomVertex_TransformedColored_Format ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE )

// Definição da estrutura de vértice customizado
struct CustomVertex_TransformedColored
{	
	float x, y, z;
	float rhw;
	DWORD cor;

	// Construtor default
	CustomVertex_TransformedColored() {}

	// Construtor com inicialização
	CustomVertex_TransformedColored( float _x, float _y, float _z,  float _rhw, DWORD _cor)
	{
		x = _x;
		y = _y;
		z = _z;
		rhw = _rhw;
		cor = _cor;
	} // fim do construtor

}; // fim da estrutura CustomVertex_TransformedColored

// Declaração dos vértices para o triângulo
CustomVertex_TransformedColored g_Vertices[3];
// ---]
// [---
// initGfx() - Inicializa o Direct3D
HRESULT initGfx( HWND hJanela )
{
	// Cria o objeto Direct3D que é necessário para criar o dispositivo gráfico
	g_Direct3d = Direct3DCreate9( D3D_SDK_VERSION );

	// Verifica se objeto Direct3D foi criado
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

	// Esse método vira rapidamente o backbuffer para a tela imediata
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
	// Monta as formas geométricas
	montar_Geometria();
	// </b>

	return S_OK;
} // initGfx().fim
// ---]
// [---
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

		// Vamos renderizar as formas geométricas
		renderizar_Geometria();

		// Finalizando a cena
		g_device->EndScene();
	} // endif

	// Apresenta o conteúdo do backbuffer na tela
	g_device->Present( NULL, NULL, NULL, NULL );

} // Renderizar().fim
// ---]
// [---
void montar_Geometria(void)
{
	// Posicionamento de profundidade
	float zpos = 1.0f;

	// p0 - primeiro vértice
	g_Vertices[0] = CustomVertex_TransformedColored( 320.0f,  50.0f, zpos, 1.0f, vermelho);

	// p1 - segundo vértice
	g_Vertices[1] = CustomVertex_TransformedColored( 512.0f, 384.0f, zpos, 1.0f, verde);

	// p2 - terceiro vértice
	g_Vertices[2] = CustomVertex_TransformedColored( 128.0f, 384.0f, zpos, 1.0f, azul);

} //  montar_Geometria().fim
// ---]
// [---
void renderizar_Geometria()
{
	// Todo código de desenhar ocorre aqui dentro
	g_device->SetFVF( CustomVertex_TransformedColored_Format );

	// Quantidade de primitivas possíveis de acordo com o uso de vértices
	UINT nContagem = 1;		 

	// Tamanho do passo para achar o próximo vértice
	UINT nPasso =  sizeof(CustomVertex_TransformedColored);		 

	// Desenha forma geométrica
	g_device->DrawPrimitiveUP( D3DPT_TRIANGLELIST, nContagem, &g_Vertices, nPasso);

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
	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

} // Limpar().fim
