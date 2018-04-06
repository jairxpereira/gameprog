// -----------------------------------------------------------------------------
// Projeto: prj_Textura - arquivo: motor.cpp
// Esse projeto ilustra como renderizar um quadrado com textura
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "motor.h"

// Vamos usar a função clock() para produzir um temporizador
#include <time.h>

// Variáveis globais
// Representa o dispositivo Direct3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;

// Matrizes de configuração da câmera
// Matriz de mundo
D3DXMATRIX g_mtxMundo; 
// Matriz de visão
D3DXMATRIX g_mtxVisao; 
// Matriz de projeção
D3DXMATRIX g_mtxProj; 

// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

// Tamanho da janela 
extern int g_xtela;
extern int g_ytela;

// Constante para cores
const DWORD branco		= 0xFFFFFFFF;

// Buffer de índices - indica a ordem de conexão dos vértices
WORD g_Indices[6] = {  0,1,2,   2,3,0 }; 

// [---
// <b>
// Interface de textura
IDirect3DTexture9*			g_Textura = NULL;

// Controla a mudança periódica do quadrado texturizado
// com diferentes coordenadas de textura
UINT temporizador = 0;
// </b>

// Memória para os vértices
CustomVertex_PositionTextured g_Verts1[4]; 
CustomVertex_PositionTextured g_Verts2[4];
CustomVertex_PositionTextured g_Verts3[4]; 
CustomVertex_PositionTextured g_Verts4[4];
CustomVertex_PositionTextured g_Verts5[4]; 

// Um ponteiro para cada conjunto de vértices
CustomVertex_PositionTextured *g_pVerts[5];

// ---]
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
	// Monta vários quads (quadrados) com diferentes coordenadas 
	// de textura
	montar_Geometria();	

	// Carrega a textura do disco e configura alguns estados referentes.
	inicializar_Textura();

	// Configura a câmera
	inicializar_Camera();	

	// Habilita a iluminação default
	g_device->SetRenderState (D3DRS_LIGHTING, false);
	// </b>

	return S_OK;
} // initGfx().fim
// ---]
// [---
void montar_Geometria(void)
{
	// *** Coordenadas de texturas ***
	// cima-esquerda
	TexCoord cimaEsq( 0.0f, 0.0f);
	// cima-meio
	TexCoord cimaMeio( 0.5f, 0.0f);
	// cima-direita
	TexCoord cimaDir( 1.0f, 0.0f );
	// meio-direita
	TexCoord meioDir( 0.0f, 0.5f );
	// meio-meio
	TexCoord meioMeio( 0.5f, 0.5f );
  // meio-esquerda
	TexCoord meioEsq( 1.0f, 0.5f );
	// baixo-esquerda
	TexCoord baixoEsq ( 0.0f, 1.0f );	
	// baixo-meio
	TexCoord baixoMeio ( 0.5f, 1.0f );	
	// baixo-direita
	TexCoord baixoDir ( 1.0f, 1.0f );	
	
	// Posicionamento de profundidade
	float zpos = 1.0f;

	// Configuração normal dos vértices com coordenadas de textura
	g_Verts1[0] = CustomVertex_PositionTextured( 1.0f,  1.0f, zpos, cimaEsq);
	g_Verts1[1] = CustomVertex_PositionTextured(-1.0f,  1.0f, zpos, cimaDir);
	g_Verts1[2] = CustomVertex_PositionTextured(-1.0f, -1.0f, zpos, baixoDir);
	g_Verts1[3] = CustomVertex_PositionTextured( 1.0f, -1.0f, zpos, baixoEsq);

	// Configuração normal dos vértices com coordenadas de textura
	g_Verts2[0] = CustomVertex_PositionTextured( 1.0f,  1.0f, zpos, cimaEsq);
	g_Verts2[1] = CustomVertex_PositionTextured(-1.0f,  1.0f, zpos, cimaMeio);
	g_Verts2[2] = CustomVertex_PositionTextured(-1.0f, -1.0f, zpos, meioMeio);
	g_Verts2[3] = CustomVertex_PositionTextured( 1.0f, -1.0f, zpos, meioDir);

	// Configuração normal dos vértices com coordenadas de textura
	g_Verts3[0] = CustomVertex_PositionTextured( 1.0f,  1.0f, zpos, cimaMeio);
	g_Verts3[1] = CustomVertex_PositionTextured(-1.0f,  1.0f, zpos, cimaDir);
	g_Verts3[2] = CustomVertex_PositionTextured(-1.0f, -1.0f, zpos, meioEsq);
	g_Verts3[3] = CustomVertex_PositionTextured( 1.0f, -1.0f, zpos, meioMeio);

	// Configuração normal dos vértices com coordenadas de textura
	g_Verts4[0] = CustomVertex_PositionTextured( 1.0f,  1.0f, zpos, meioDir);
	g_Verts4[1] = CustomVertex_PositionTextured(-1.0f,  1.0f, zpos, meioMeio);
	g_Verts4[2] = CustomVertex_PositionTextured(-1.0f, -1.0f, zpos, baixoMeio);
	g_Verts4[3] = CustomVertex_PositionTextured( 1.0f, -1.0f, zpos, baixoEsq);

	// Configuração normal dos vértices com coordenadas de textura
	g_Verts5[0] = CustomVertex_PositionTextured( 1.0f,  1.0f, zpos, meioMeio);
	g_Verts5[1] = CustomVertex_PositionTextured(-1.0f,  1.0f, zpos, meioEsq);
	g_Verts5[2] = CustomVertex_PositionTextured(-1.0f, -1.0f, zpos, baixoDir);
	g_Verts5[3] = CustomVertex_PositionTextured( 1.0f, -1.0f, zpos, baixoMeio);

	// Um ponteiro para cada conjunto de vértices
	g_pVerts[0] = &g_Verts1[0];
	g_pVerts[1] = &g_Verts2[0];
	g_pVerts[2] = &g_Verts3[0];
	g_pVerts[3] = &g_Verts4[0];
	g_pVerts[4] = &g_Verts5[0];

} //  montar_Geometria().fim
// ---]
// [---
void renderizar_Geometria()
{
		// Produz a cada segundo um valor de 0 a 4.
	temporizador = ( clock() / 1000 ) % 5;	

	// Argumentos da função DrawIndexedPrimitiveUP()
  UINT   nVerticeInicial = 0; 
  UINT   nVerticeQtd   = 4; 
  UINT   nContagemPrim  = 2; 
  UINT   nPasso     =  sizeof(CustomVertex_PositionTextured);   

	// Declara o formato de vértice utilizado pela aplicação
	g_device->SetFVF( CustomVertex_PositionTextured_Format );	 
	
  g_device->DrawIndexedPrimitiveUP( D3DPT_TRIANGLELIST, 
    nVerticeInicial, nVerticeQtd, nContagemPrim, &g_Indices, 
		D3DFMT_INDEX16, g_pVerts[temporizador], nPasso);


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
	// Libera a textura
	if (g_Textura != NULL) g_Textura->Release();

	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

	// Limpando os ponteiros
	g_Direct3d	= NULL;
	g_device		= NULL;
	g_Textura		= NULL;

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
// [---
void inicializar_Textura(void)
{
	g_hr = D3DXCreateTextureFromFile (g_device, 
		"\\gameprog\\gdkmedia\\bitmap\\textura2x2.png", 
		&g_Textura);

	if (FAILED (g_hr))
	{
		MessageBox(NULL, "Falha: D3DXCreateTextureFromFile()", 
			"inicializar_Textura()", MB_OK);
	} // endif

	// Configura a textura no dispositivo
	g_device->SetTexture (0, g_Textura);

	// Corrige visualização blocada da textura - quando textura for
	// menor do que a superfície ( atuante nesta aplicação )
	g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	// Corrige visualização blocada da textura - quando textura for
	// maior do que a superfície	( não atuante nesta aplicação )
	g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);

} // inicializar_Textura(void).fim
// ---]
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
	D3DXVECTOR3 cam_pos (0.0f, 0.0f, 5.0f);   
	// Para aonde a câmera está apontada ou olhando? Alvo da câmera
	D3DXVECTOR3 cam_alvo (0.0f, 0.0f, 0);   
	// A câmera está de cabeça pra baixo? - orientação da câmera
	D3DXVECTOR3 cam_vetorcima (0.0f, 1.0f, 0.0f);   

	// Configura a matriz de visão
	D3DXMatrixLookAtLH( &g_mtxVisao, &cam_pos, &cam_alvo, &cam_vetorcima );  

	// Configura a matriz de visão no dispositivo renderizador
	g_device->SetTransform( D3DTS_VIEW, &g_mtxVisao );  

	// ***************************************************************************
	// Argumentos de configuração da matriz de projeção
	// aspecto dos gráficos
	float aspecto = (float)  g_xtela / g_ytela; 
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

