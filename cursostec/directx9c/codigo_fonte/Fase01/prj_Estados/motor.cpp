// [---
// -----------------------------------------------------------------------------
// Projeto: prj_Estados - arquivo: motor.cpp
// Esta aplicação ilustra como renderizar um quadrado
// em modo de preenchimento sólido ou wireframe
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

// Controla o modo de preenchimento da forma geométrica
DWORD g_nFillMode = 0;

// Constante para cores
const DWORD vermelho	= 0xFFFF0000;
const DWORD branco		= 0xFFFFFFFF;
const DWORD verde			= 0xFF00FF00;
const DWORD azul			= 0xFF0000FF;
const DWORD cinza			= 0xFF808080;

// Definição do formato de vértice utilizado por estado aplicação
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

// Declara 6 vértices para produzir o quadrado
CustomVertex_TransformedColored g_Vertices[6];
// ---]
// [---
// initGfx() - Inicializa o Direct3D
HRESULT initGfx( HWND hJanela )
{
	// Cria o objeto D3D que é necessário para criar o dispositivo gráfico
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
	montar_Geometria();
	// </b>

	return S_OK;
} // initGfx().fim
// ---]
// [---
void montar_Geometria(void)
{
  // Posicionamento de profundidade
  float zpos = 1.0f;
	
	// Primeiro triângulo
	g_Vertices[0] = CustomVertex_TransformedColored( 128.0f, 50.0f, zpos, 0.7f, vermelho);
	g_Vertices[1] = CustomVertex_TransformedColored( 512.0f, 384.0f,zpos, 0.8f, verde);
	g_Vertices[2] = CustomVertex_TransformedColored( 128.0f, 384.0f,zpos, 1.0f, azul);

	// Segundo triângulo
	g_Vertices[3] = CustomVertex_TransformedColored( 128.0f, 50.0f, zpos, 0.7f, vermelho);
	g_Vertices[4] = CustomVertex_TransformedColored( 512.0f, 50.0f, zpos, 1.0f, cinza); 
	g_Vertices[5] = CustomVertex_TransformedColored( 512.0f, 384.0f,zpos, 0.8f, verde);	
	
} //  montar_Geometria().fim
// ---]
// [---
void tratarTeclado (WPARAM wParam) 
{
  // Modo de preenchimento sólido na tecla S
	if (wParam == 'S')  g_nFillMode = D3DFILL_SOLID; 

	// Modo de preenchimento wireframe na tecla S
	if (wParam == 'W')  g_nFillMode = D3DFILL_WIREFRAME; 

} // tratarTeclado().fim
// ---]
// [---
void renderizar_Geometria()
{
		 // Declara o formato de vértice utilizado pela aplicação
	   g_device->SetFVF( CustomVertex_TransformedColored_Format );
		 
		 // Configura modo de preenchimento da renderização
		 g_device->SetRenderState ( D3DRS_FILLMODE, g_nFillMode);		 
		 
		 // Quantidade de primitivas possíveis de acordo com o uso dos vértices
		 UINT nContagem = 2;		 
		 
		 // Tamanho do passo para achar o próximo vértice
		 UINT nPasso =  sizeof(CustomVertex_TransformedColored);		 
     
		 // Desenha forma geométrica
		 g_device->DrawPrimitiveUP( D3DPT_TRIANGLELIST, nContagem, &g_Vertices, nPasso);
		  
		 // Configura modo de visualização em ponto
		 g_device->SetRenderState ( D3DRS_FILLMODE, D3DFILL_POINT);
		 
		 // Configura tamanho do ponto
		 float nTamanho = 30.0f;
		 g_device->SetRenderState ( D3DRS_POINTSIZE, *(( DWORD* ) &nTamanho ));

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
		tratarTeclado (wParam);

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

