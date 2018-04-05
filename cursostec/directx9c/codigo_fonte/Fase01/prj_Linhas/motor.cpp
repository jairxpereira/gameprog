// [---
// -----------------------------------------------------------------------------
// Projeto: prj_Linhas - arquivo: motor.cpp
// Esta aplicação ilustra como desenhar linhas
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
// Representa o dispositivo D3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;

// Ponteiro para uma fonte do directx
ID3DXFont*							gdxFonte = NULL;

// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

extern int g_xtela;
extern int g_ytela;
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

	inicializarTexto();

	return S_OK;
} // initGfx().fim
// ---]
// [---
void quadrado( float x, float y, float largura, float altura)
{	
	// Criação do objeto linha
	ID3DXLine* linhas = NULL;
  D3DXCreateLine(g_device, &linhas);
	
	// Quantidade de pontos
	const int nQtd = 5;

	// Array de coordenadas dos pontos
	D3DXVECTOR2 pontos[nQtd];
	
	// Preenchimento dos pontos do quadrado
	// (esquerda, cima)
	pontos[0] = D3DXVECTOR2 ( x, y ); 	
	// (direita, cima)
	pontos[1] = D3DXVECTOR2 ( x + largura, y );
	// (direita, baixo)
	pontos[2] = D3DXVECTOR2 ( x + largura, y + altura );
	// (esquerda, baixo)
	pontos[3] = D3DXVECTOR2 ( x,  y + altura);
	// (esquerda, cima)
	pontos[4] = D3DXVECTOR2 ( x, y) ;	

	// Cor da linha
	const DWORD vermelho = 0xFFFF0000; 

   // Configura espessura da linha e antiAlias
	linhas->SetWidth (3.0f);	
	linhas->SetAntialias(true);

	// Prepara o ambiente
	linhas->Begin();

	// Desenha a linha
	linhas->Draw ( pontos, nQtd, vermelho );

  // Finaliza restaurando estados internos
	linhas->End();
	
	// Libera o objeto linhas
	linhas->Release();

} // quadrado().fim
// ---]
// [---
//  Esta função é chamada por DispatchMessage()  
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam)
{
	
	// Variáveis para coletar informação do mouse
	int xmouse = 0;
	int ymouse = 0;
	char info[25];
	
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

	case WM_MOUSEMOVE:
		xmouse = LOWORD (lParam);
		ymouse = HIWORD (lParam);		
		sprintf (info, "prj_Linhas (%i, %i)", xmouse, ymouse);
		SetWindowText (hJanela, info);
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
// ---]
// [---
void inicializarTexto()
{

	// Altura
	int  nAltura = 24;

	// Largura
	UINT nLargura = 0;

	// Peso ( weight )
	UINT nPeso = FW_BOLD;

	// Nível de mipmap - 0: mipmap automático
	UINT nMipmap = 0;

	// Efeito itálico
	bool bItalico = false;

	// Conjunto de caracteres (charset)
	DWORD nCharset = DEFAULT_CHARSET; 

	// Precisão (OutputPrecision)
	DWORD nPrecisao = OUT_DEFAULT_PRECIS;
	
	// Qualidade
	DWORD nQualidade = DEFAULT_QUALITY;

	// Pitch e família
	DWORD nFamilia = DEFAULT_PITCH | FF_DONTCARE;

	// Nome da fonte
	char* sFonte = "Arial";	

	g_hr = D3DXCreateFont( g_device, nAltura, nLargura, nPeso, nMipmap, bItalico, 
		nCharset, nPrecisao, nQualidade, nFamilia, sFonte, &gdxFonte );

	if ( FAILED (g_hr) ) 
		MessageBox ( NULL, "Texto: falha na inicialização", "inicializarTexto()", MB_OK);

} // inicializarTexto()
// ---]
// [---
void mostrarTexto(int x, int y, char* texto)
{  
	// Retorne se não houver fonte inicializada
	if ( gdxFonte == NULL ) return;

	// Cor de fundo da janela
	D3DCOLOR azul = D3DCOLOR_XRGB(0, 0, 255);

	RECT area_limite;		

	SetRect( &area_limite, x, y, g_xtela, g_ytela );	

	gdxFonte->DrawText( NULL, texto, -1, &area_limite, 0,  azul );   
	
} // mostrarTexto();
// ---]
// [---
// Limpar() -  Libera todos os objetos previamente inicializados
// -----------------------------------------------------------------------------
VOID Limpar()
{

	// Libera objeto de mostrar texto
	if( gdxFonte != NULL) gdxFonte->Release();	

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
		mostrarTexto (120, 160, "Produzido na escola Gameprog");
		mostrarTexto (200, 200, "Programar é legal!");
		
		// Desenha dois quadrados
		quadrado (90.0f, 130.0f, 420.0f, 120.0f);
		quadrado (100.0f, 140.0f, 400.0f, 100.0f);		

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