// [---
// -----------------------------------------------------------------------------
// Projeto: prj_Dispositivo - arquivo: motor.cpp
// Este programa ilustra como inicializar o Direct3D e 
// limpar a tela. Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Variáveis globais
// Representa o dispositivo D3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;

// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	
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

	return S_OK;
} // initGfx().fim
// ---]
// [---
// Limpar() -  Libera todos os objetos previamente inicializados
// -----------------------------------------------------------------------------
VOID Limpar()
{
	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

} // Limpar().fim
// ---]
// [---
// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
VOID Renderizar()
{
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;

	// Cor de fundo da janela
	const D3DCOLOR branco = D3DCOLOR_XRGB( 255, 255, 255 );
	const D3DCOLOR cor_fundo = branco;
	
	// Superfícies que serão limpas
	DWORD superficies = D3DCLEAR_TARGET;
	
	// Configuração padrão do buffer de profundidade
	float zBuffer = 1.0f;

	// Configuração padrão do stencil
	DWORD sBuffer = 0;

	// Quantidade de retângulos a serem limpos
	DWORD nPartes = 0;

	// Array de retângulos que serão limpos
	const D3DRECT* pPartes = NULL;

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( nPartes, pPartes, superficies, cor_fundo, 
		zBuffer, sBuffer);

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
		// Todo código de desenhar ocorre aqui dentro

		// Finalizando a cena
		g_device->EndScene();
	} // endif

	// Apresenta o conteúdo do backbuffer na tela
	// Retangulo fonte e destino
	const RECT* rFonte = NULL;	
	const RECT* rDestino = NULL;
	
	// Janela alternativa para apresentar os dados visuais
	HWND hOutraJanela = NULL;

	g_device->Present( rFonte, rDestino, hOutraJanela, NULL );
} // Renderizar().fim
// ---]