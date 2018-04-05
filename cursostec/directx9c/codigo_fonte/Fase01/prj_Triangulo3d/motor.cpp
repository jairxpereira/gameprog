// -----------------------------------------------------------------------------
// Projeto: prj_Triangulo3d - arquivo: motor.cpp
// Esta aplicação ilustra como configurar uma câmera e 
// renderizar um triângulo 3d. By www.gameprog.com.br
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
// [---
// Variáveis para controlar a rotação do triângulo
float g_Angulo = 0.0f;
const float nVelocidade = 0.2f;

// Matrizes de configuração da câmera
// Matriz de mundo
D3DXMATRIX g_mtxMundo;
// Matriz de visão
D3DXMATRIX g_mtxVisao;
// Matriz de projeção
D3DXMATRIX g_mtxProj;

// Tamanho da janela
extern int g_xtela;
extern int g_ytela;

// Constante para cores
const DWORD vermelho	= 0xFFFF0000;
const DWORD branco		= 0xFFFFFFFF;
const DWORD verde			= 0xFF00FF00;
const DWORD azul			= 0xFF0000FF;

// Definição do formato de vértice utilizado pela aplicação
#define CustomVertex_PositionColored_Format ( D3DFVF_XYZ | D3DFVF_DIFFUSE )

// Definição da estrutura de vértice customizado
struct CustomVertex_PositionColored
{	
	float x, y, z;
	DWORD cor;

	// Construtor default
	CustomVertex_PositionColored() {}

	// Construtor com inicialização
	CustomVertex_PositionColored( float _x, float _y, float _z, DWORD _cor)
	{
		x = _x;
		y = _y;
		z = _z;		
		cor = _cor;
	} // fim do construtor

}; // fim da estrutura CustomVertex_PositionColored

// Declaração dos vértices para o triângulo
CustomVertex_PositionColored g_Vertices[3];
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
	
	// Faz a configuração inicial da câmera
	inicializar_Camera();	
	// </b>
	return S_OK;
} // initGfx().fim
// ---]
// [---
void inicializar_Camera(void)
{
	// ***************************************************************************
	// Inicializa todas as matrizes para elemento neutro
	D3DXMatrixIdentity( &g_mtxMundo );
	D3DXMatrixIdentity( &g_mtxVisao );
	D3DXMatrixIdentity( &g_mtxProj );

	// ***************************************************************************
		// Configura a matriz de mundo no dispositivo renderizador
	g_device->SetTransform( D3DTS_WORLD, &g_mtxMundo ); 

	// ***************************************************************************
	// Dados para a configuração da matriz de visualização
	// Aonde está a câmera? - posição da câmera
	D3DXVECTOR3 cam_pos (0, 0, 5.0f); 
	// Para aonde a câmera está apontada ou olhando? Alvo da câmera
	D3DXVECTOR3 cam_alvo (0, 0.0f, 0); 
	// A câmera está de cabeça pra baixo? - orientação da câmera
	D3DXVECTOR3 cam_vetorcima (0, 1.0f, 0); 

	// Configura a matriz de visão
	D3DXMatrixLookAtLH( &g_mtxVisao, &cam_pos, &cam_alvo, &cam_vetorcima );

	// Configura a matriz de visão no dispositivo renderizador
	g_device->SetTransform( D3DTS_VIEW, &g_mtxVisao ); 

	// ***************************************************************************
	// Argumentos de configuração da matriz de projeção
	// aspecto dos gráficos
	float aspecto = (float) g_xtela / g_ytela; 
	// campo de visão
	float campo_visao = D3DX_PI / 4; 
	// Trapézio de visualização da câmera ( Frustrum )
	float corte_perto = 1.0f;
	float corte_longe = 1000.0f;

	// Configura a matriz de projeção	
	D3DXMatrixPerspectiveFovLH( &g_mtxProj, campo_visao, aspecto, 
		corte_perto, corte_longe);

	// Configura a matriz de projeção no dispositivo renderizador
	g_device->SetTransform( D3DTS_PROJECTION, &g_mtxProj );

} // inicializar_Camera().fim
// ---]
// [---
void atualizar_Camera(void)
{
	float angulo_final = 0.0f;
	
	// Atualiza ângulo para dar movivento
	g_Angulo = g_Angulo + nVelocidade;
	angulo_final = g_Angulo / D3DX_PI;

	// Rotaciona o triângulo indiretamente através da rotação 
	// dos eixos da matriz de espaço mundial.
	D3DXMatrixRotationY( &g_mtxMundo, angulo_final );      

	// Configura a matriz de mundo no dispositivo renderizador
	g_device->SetTransform( D3DTS_WORLD, &g_mtxMundo ); 

} // atualizar_Camera().fim
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

	// Mostra a parte interna do polígono
	// Experimente desativar essa linha com a instrução de comentário      
	g_device->SetRenderState (D3DRS_CULLMODE, D3DCULL_NONE); 

	// Utiliza iluminação default
	// Experimente desativar essa linha com a instrução de comentário
	g_device->SetRenderState (D3DRS_LIGHTING, false );

	// Atualize a câmera
	atualizar_Camera();
	
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
	float zpos = 0.0f;

	// p0 - primeiro vértice
	g_Vertices[0] = CustomVertex_PositionColored( 0.0f,  1.0f, zpos, vermelho);

	// p1 - segundo vértice
	g_Vertices[1] = CustomVertex_PositionColored( -1.0f, -1.0f, zpos, verde);

	// p2 - terceiro vértice
	g_Vertices[2] = CustomVertex_PositionColored( 1.0f, -1.0f, zpos, azul); 

} //  montar_Geometria().fim
// ---]
// [---
void renderizar_Geometria()
{
	// Configura formato de vértice no dispositivo
	g_device->SetFVF( CustomVertex_PositionColored_Format );

	// Quantidade de primitivas possíveis de acordo com o uso de vértices
	UINT nContagem = 1;		 

	// Tamanho do passo para achar o próximo vértice
	UINT nPasso =  sizeof(CustomVertex_PositionColored);		 

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



