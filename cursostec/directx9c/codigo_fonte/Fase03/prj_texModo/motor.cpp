// -----------------------------------------------------------------------------
// Projeto: prj_texModo - arquivo: motor.cpp
// Esta aplicação mostra os modos de endereçamento de textura
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include "motor.h"

// Variáveis globais
// Representa o dispositivo Direct3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;

// Interface para uso de textura
IDirect3DTexture9*			g_Textura = NULL;

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

// Handle da janela usado na função config_janelaTexto()
extern HWND hJanela;

// Constante para cores
const DWORD dwBranco		= 0xFFFFFFFF;
const DWORD dwAzul			= 0xFF0000FF;

// Controla a mudança periódica do modo de endereçamento de textura
UINT temporizador = 0;

// Memória para os vértices
CustomVertex_PositionTextured g_Verts[4]; 

// Buffer de índices - indica a ordem de conexão dos vértices
WORD g_Indices[6] = {  0,1,2,   2,3,0 }; 


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

	// Monta o quadrado texturizado
	montar_Geometria();	

	// Carrega a textura do disco e inicializa contexto de texturização
	inicializar_Textura();
	
	// Faz a configuração inicial da câmera
	inicializar_Camera();	

	// Habilita iluminação default
	g_device->SetRenderState (D3DRS_LIGHTING, false);

	return S_OK;
} // initGfx().fim

void montar_Geometria(void)
{
	// *** Coordenadas de textura ***
	// cima-esquerda
	TexCoord cimaEsq( 0.0f, 0.0f);
	// cima-direita
	TexCoord cimaDir( 3.0f, 0.0f );
	// baixo-esquerda
	TexCoord baixoEsq ( 0.0f, 3.0f );	
	// baixo-direita
	TexCoord baixoDir ( 3.0f, 3.0f );	
	
	// Posicionamento de profundidade
	float zpos = 0.9f;

	// Configuração normal dos vértices com coordenadas de textura
	g_Verts[0] = CustomVertex_PositionTextured(  2.20f,  1.50f, zpos, cimaEsq);
	g_Verts[1] = CustomVertex_PositionTextured( -2.20f,  1.50f, zpos, cimaDir);
	g_Verts[2] = CustomVertex_PositionTextured( -2.20f, -1.50f, zpos, baixoDir);
	g_Verts[3] = CustomVertex_PositionTextured(  2.20f, -1.50f, zpos, baixoEsq);

} //  montar_Geometria().fim
// [---
void renderizar_Geometria()
{
	// <b>
	// Mensagens para a barra de títulos da janela
	char mensagem[6][80] = 
	{ 
	"prj_texModo: 0. By Gameprog           ",
	"prj_texModo: 1. D3DTADDRESS_WRAP      ",
  "prj_texModo: 2. D3DTADDRESS_MIRROR    ",
  "prj_texModo: 3. D3DTADDRESS_CLAMP     ",
  "prj_texModo: 4. D3DTADDRESS_BORDER    ",
	"prj_texModo: 5. D3DTADDRESS_MIRRORONCE"
	};
	
	// Produz a cada dois segundos um valor de 1 a 5 com temporizador++.
	temporizador = ( clock() / 2000 ) % 5;
	temporizador++;
	// </b>
	// Argumentos da função DrawIndexedPrimitiveUP()
  UINT   nVerticeInicial = 0; 
  UINT   nVerticeQtd   = 4; 
  UINT   nContagemPrim  = 2; 
  UINT   nPasso     =  sizeof(CustomVertex_PositionTextured);   

	// Declara o formato de vértice utilizado pela aplicação
	g_device->SetFVF( CustomVertex_PositionTextured_Format );	 
	// <b>
	// Configura o texto da barra de títulos
	config_janelaTexto( mensagem[temporizador] );

	// Configura o modo de endereçamento da textura
	g_device->SetSamplerState(0, D3DSAMP_ADDRESSU, temporizador);
	g_device->SetSamplerState(0, D3DSAMP_ADDRESSV, temporizador);

	// Define a cor azul para o modo de endereçamento D3DSAMP_BORDERCOLOR
	if (temporizador == D3DSAMP_BORDERCOLOR)
	g_device->SetSamplerState(0,  D3DSAMP_BORDERCOLOR, dwAzul);
	// </b>
  // Renderiza o quadrado
	g_device->DrawIndexedPrimitiveUP( D3DPT_TRIANGLELIST, 
    nVerticeInicial, nVerticeQtd, nContagemPrim, &g_Indices, 
		D3DFMT_INDEX16, &g_Verts, nPasso);

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

	// Reconfiguração dos ponteiros para NULL
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
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET, dwBranco, 1.0f, 0);

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

// [---
void config_janelaTexto( char *texto)
{	
	// Pega o texto atual da janela
	char temp_txt[80];
	GetWindowText (hJanela, temp_txt, 80);

	// Configura apenas se o texto de entrada for diferente
	// do texto que está na janela
	// Isto é para evitar um efeito visual desagradável na barra
	// de título da janela.
	if (strcmp (temp_txt, texto))
		SetWindowText (hJanela, texto);

} // config_janelaTexto().fim
// ---]
