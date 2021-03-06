﻿// -----------------------------------------------------------------------------
// Projeto: prj_TeclaCheia - arquivo: motor.cpp
// Esta aplicação ilustra como renderizar uma sprite em tela cheia
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

// Ponteiro para uma fonte do directx
ID3DXFont*							gdxFonte = NULL;

// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

extern int g_xtela;
extern int g_ytela;

// Interfaces necessárias para a criação da sprite 
// A textura vai compor a imagem da sprite
IDirect3DTexture9*	g_textura = NULL;
ID3DXSprite*				g_sprite = NULL;

// Argumentos necessários na criação da sprite
// Posicionamento e recorte da sprite
RECT						    g_recorte;
// Posicionamento 3d da sprite
D3DXVECTOR3*				g_posicao = NULL;
// Centro de apoio para rotações da sprite
D3DXVECTOR3*				g_centro = NULL;

// Controle de movimentação da sprite
int                 movimento_direcao = 1;
int		              xpos = -240;
int                 ypos = -160;

// Constante para cores
const DWORD vermelho	= 0xFFFF0000;
const DWORD branco		= 0xFFFFFFFF;

// Constante para cores com transparência
const DWORD verde_transparente	= 0x8000FF00;
const DWORD vermelho_transp			= 0x80FF0000;

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

	// Esse método transfere rapidamente o backbuffer para a tela imediata
	pps.SwapEffect = D3DSWAPEFFECT_DISCARD;
// <b>
	// Vamos configurar a aplicação para tela cheia
	// Inicialmente vamos descobrir a configuração de video corrente
	D3DDISPLAYMODE monitor;
	g_Direct3d->GetAdapterDisplayMode (0, &monitor);
	g_xtela = monitor.Width;
	g_ytela = monitor.Height;
	
	// Esconde o ponteiro do mouse
	ShowCursor (false);

	// Configura para modo tela cheia dentro da configuração obtida
	pps.Windowed = false;
	
	// Pega formato atual. D3DFMT_A2R10G10B10 poderia ser especificado
	pps.BackBufferFormat = monitor.Format;	

	// (largura, altura) do backbuffer
	pps.BackBufferWidth  = g_xtela;
	pps.BackBufferHeight = g_ytela;
	
// </b>
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

	// Inicializa texto
	inicializarTexto();

	// Inicializa sprite
	inicializarSprite();

	return S_OK;
} // initGfx().fim
// ---]

void inicializarSprite()
{

	// Carrega e prepara textura 256 x 256
	const char* stextura = "C:\\gameprog\\gdkmedia\\bitmap\\teste-transp.png";
	g_hr = D3DXCreateTextureFromFile(g_device, stextura, &g_textura);

	if (FAILED ( g_hr )) 
	{ 
		MessageBox (NULL, "Textura: falha no carregamento", "inicializarSprite()", MB_OK);
		return;
	} // endif


	g_hr = D3DXCreateSprite (g_device, &g_sprite);
	if (FAILED ( g_hr )) 
	{ 
		MessageBox (NULL, "Sprite: falha na criação", "inicializarSprite()", MB_OK);
	} // endif

	// Posicionamento 3d não utilizado extensamente
	g_posicao = &D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_centro = &D3DXVECTOR3(0.0f, 0.0f, 0.0f);

} // inicializarSprite().fim


void renderizarSprite()
{ 
	// Cor difusa da sprite
	DWORD cor_difusa = branco;

	// Muda cor difusa conforme direção assumida
	if (movimento_direcao == 1)	cor_difusa = branco;
	if (movimento_direcao == -1) cor_difusa = vermelho;
	if (movimento_direcao == 2)	cor_difusa = verde_transparente;
	if (movimento_direcao == -2) cor_difusa = vermelho_transp;

	// Indica o ponto de corte da sprite
	int direita = 128;
	int fundo = 120;

	// Configuração posição de colocação da sprite na tela
	// o ponto de corte da textura
	SetRect ( &g_recorte, xpos, ypos, direita, fundo);

	// Inicia a renderização considerando efeito de transparência
	g_sprite->Begin (D3DXSPRITE_ALPHABLEND );

	// Renderiza sprite conforme configuração previamente definida
	g_sprite->Draw(g_textura, &g_recorte, g_centro, g_posicao, cor_difusa);

	// Finaliza processo de renderização de sprites
	g_sprite->End();

} // renderizarSprite().fim


void tratarTeclado (WPARAM wParam)
{
	// Controle de movimento da sprite para colocação
	// da sprite sobre a tela
	if (wParam == VK_UP) ypos = ypos + 5;
	if (wParam == VK_DOWN) ypos = ypos - 5;
	if (wParam == VK_LEFT) xpos = xpos + 5;
	if (wParam == VK_RIGHT) xpos = xpos - 5;

	// Controle de movimento da sprite utilizado para
	// mudar a cor difusa da sprite conforme direção assumida
	if (wParam == VK_UP) movimento_direcao = 1;
	if (wParam == VK_DOWN) movimento_direcao = -1;
	if (wParam == VK_LEFT) movimento_direcao = 2;
	if (wParam == VK_RIGHT) movimento_direcao = -2 ;
} // tratarTeclado().fim


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
		tratarTeclado ( wParam );

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

// Limpar() -  Libera todos os objetos previamente inicializados
// -----------------------------------------------------------------------------
VOID Limpar()
{
	// Libera o objeto textura
	if( g_textura != NULL) g_textura->Release();

	// Libera o objeto sprite
	if( g_sprite != NULL)  g_sprite->Release();

	// Libera objeto de mostrar texto
	if( gdxFonte != NULL) gdxFonte->Release();	

	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

} // Limpar().fim

// [---
// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
VOID Renderizar()
{
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;

	// String para mostrar posição da sprite
	char info[40];	

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET, branco, 1.0f, 0);

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
		// Todo código de desenhar ocorre aqui dentro
		mostrarTexto (220, 160, "www.gameprog.com.br");
		mostrarTexto (170,400, "Movimente a sprite com as setas.");	

		// Mostra posicionamento da sprite
		sprintf (info, "( %i, %i )", xpos, ypos);
		mostrarTexto (10, 10, info);

		// Desenha sprite
		renderizarSprite();		

		// Finalizando a cena
		g_device->EndScene();
	} // endif

	// Apresenta o conteúdo do backbuffer na tela
	g_device->Present( NULL, NULL, NULL, NULL );

} // Renderizar().fim
