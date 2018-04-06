
// -----------------------------------------------------------------------------  
// Projeto: prj_DirectShow - arquivo: motor.cpp
// Esta aplicação mostra como tocar vídeo e música
// com o DirectShow. By www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>
#include <time.h>
#include <dshow.h>
#include "motor.h"
#include "gpmediaplayer.cpp"

// Variáveis globais
// Representa o dispositivo Direct3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;

// Representa o buffer de vértices
IDirect3DVertexBuffer9* g_vbVertices = NULL;
// [---
// <b>
GPMediaPlayer g_Tocador;
int bVideoAcionado = 1;
// </b>
// ---]
// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

// Tamanho da janela 
extern int g_xtela;
extern int g_ytela;
extern HWND hJanela;
extern int mediaModo;

// Constante para cores
const DWORD vermelho	= 0xFFFF0000;
const DWORD branco		= 0xFFFFFFFF;
const DWORD amarelo		= 0xFFFFFF00;

UINT g_nVerticesQtd = 60;

// Matrizes de configuração da câmera
D3DXMATRIX g_mtxMundo; 
D3DXMATRIX g_mtxVisao; 
D3DXMATRIX g_mtxProj; 

// Controla a mudança periodica da primitiva
UINT temporizador = 0;

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
	
	
	// inicializa o vertexbuffer 
	inicializar_Buffers();
	
	// configura o posicionamento dos vértices
	montar_Geometria();

	// configura câmera da aplicação
	inicializar_Camera();

  // Habilita iluminação default
  g_device->SetRenderState (D3DRS_LIGHTING, false );  
	

	return S_OK;
} // initGfx().fim

void inicializar_Buffers(void) 
{	
	// Tamanho do vertexbuffer em bytes
	UINT		vbTamanho	= sizeof(CustomVertex_PositionColored) * g_nVerticesQtd;	

	// Criação efetiva do buffer de vértices (vertexbuffer)
	g_hr = g_device->CreateVertexBuffer ( vbTamanho, D3DUSAGE_WRITEONLY, 
		CustomVertex_PositionColored_Format, D3DPOOL_MANAGED, &g_vbVertices, NULL);
	
  // Verifica falha na criação
	if(FAILED (g_hr) ) {
    MessageBox (NULL, 
      "Falha na criação do buffer de vértices",
			"inicializar_Buffers()", MB_OK);    
    return; 
  } // endif


} // inicializar_Buffers().fim

void montar_Geometria(void)
{
	// Posicionamento de profundidade
	float xcol = 0.0f;
	float ylin = 0.0f;
	float zpos = 0.0f;

	// Utilizado para controlar o índice do vértice
	UINT ndx = 0;

	// Distribuição circular dos vértices no espaço 
   UINT passo = 360 / g_nVerticesQtd;

	// Ponteiro de acesso aos dados do buffer de vértices
	CustomVertex_PositionColored* pVerts;	

	// Aqui a aplicação ganha acesso à memória do buffer de vértices
	g_vbVertices->Lock( 0, 0, (void**)&pVerts, 0 );	
	
	// Vamos posicionar os vértices em círculo 
for (float ncx = 0.0f; ncx <= 360.0f; ncx += passo)
 {
 // Converte graus para radianos 
 double radianos = ncx * (D3DX_PI / 180.0f);
 
 // Tamanho do círculo
 float nRaio = 2.0f;

 // (x,y) distribuidos de maneira circular 
 xcol = (float) cos(radianos) * nRaio;
 ylin = (float) sin(radianos) * nRaio; 
	
	// Posicionamento do vértice
	pVerts[ndx] = CustomVertex_PositionColored( xcol, ylin, zpos, vermelho);

 // Coloca no centro o terceiro vértice de cada triângulo 
 if (ndx % 3 == 0)
 pVerts[ndx] = CustomVertex_PositionColored( 0, 0, zpos, amarelo);

 // Atualiza índice de controle do vértice 
 ndx++;

 } // endfor 
	
	// Liberação do vertexbuffer
	g_vbVertices->Unlock();
 
} //  montar_Geometria().fim

void renderizar_Geometria()
{	
	
	// Produz a cada dois segundos um valor de 0 a 5.
	temporizador = ( clock() / 500 ) % 3;
	
	// Declara o formato de vértice utilizado pela aplicação
	g_device->SetFVF( CustomVertex_PositionColored_Format );	

	// Informação do buffer de vértices utilizado
	g_device->SetStreamSource( 0, g_vbVertices, 0, sizeof(CustomVertex_PositionColored));	

	if (temporizador == 0)		
	g_device->DrawPrimitive( D3DPT_LINELIST, 0, g_nVerticesQtd / 2);  	

	if (temporizador == 1)		
	g_device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, g_nVerticesQtd / 3);  
		

} // renderizar_Geometria().fim

// [---
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

	case WM_P_GRAPHNOTIFY:
  tratarMediaEvento();
  break;

	case WM_KEYDOWN:
		if (wParam == 'T') g_Tocador.play();
		if (wParam == 'S') g_Tocador.stop();
		if (wParam == 'P') g_Tocador.pause();
		
		// Aborte o vídeo na tecla espaço
		if (wParam == VK_SPACE ) 	{
		if (mediaModo == modo_video) g_Tocador.abortarVideo(2000);		
		if (mediaModo == modo_musica) g_Tocador.stop();
		bVideoAcionado = -1; } // endif


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
// ---]

// Limpar() -  Libera todos os objetos previamente inicializados
// -----------------------------------------------------------------------------
VOID Limpar()
{	
	// Libera o buffer de vértices
	if( g_vbVertices != NULL) g_vbVertices->Release();

	// Limpa o DirectShow e seus objetos utilizados
	g_Tocador.limpar();
	
	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

	// Anula os ponteiros
	g_vbVertices	= NULL;
	g_device			= NULL;
	g_Direct3d		= NULL;

} // Limpar().fim


// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
// [---
VOID Renderizar()
{
	if ( bVideoAcionado == 1) return;	
	
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;	

	// Limpa o backbuffer com uma cor preta
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET, 0, 1.0f, 0);

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
		
		// Vamos renderizar a geometria
		renderizar_Geometria();
	
		// Finalizando a cena
		g_device->EndScene();
	} // endif

	// Apresenta o conteúdo do backbuffer na tela
	g_device->Present( NULL, NULL, NULL, NULL );

} // Renderizar().fim
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

// [---
void tocar_media()
{		
	// Inicializa o tocador
	g_Tocador = GPMediaPlayer();

	// Inicializa os objetos do DirectShow para tocar mídia
	g_Tocador.inicializar();	

	if (mediaModo == modo_video)
	{
		g_Tocador.carregarVideo ( L"\\gameprog\\gdkmedia\\Video\\youwin.avi");

	// Configura a janela da aplicação como a janela de vídeo
	g_Tocador.setOwner (hJanela);
	bVideoAcionado = 1;
	} // endif

	if (mediaModo == modo_musica)
	{
		g_Tocador.carregarMusica (L"C:\\gameprog\\gdkmedia\\musica\\megaman3Intro.mp3");
	bVideoAcionado = -1;
	}


	// Toca o arquivo de mídia
	g_Tocador.play();

} // tocar_media().fim
// ---]
// [---
void tratarMediaEvento()
{ 
	
	// Coleta dos resultados das operações do directx
	HRESULT hr;	
	
	// Variáveis para coleta do evento e informações complementares
	long cdgEvento;
	long param1, param2;	
  
	// Verifica a ocorrência de eventos
	hr = g_Tocador.mdEventos->GetEvent(&cdgEvento, &param1, &param2, 0);	
	
	// Trata a ocorrência de eventos
	while ( SUCCEEDED(hr) )
  {
		// Tira o evento da fila de eventos  
		hr = g_Tocador.mdEventos->FreeEventParams(cdgEvento, param1, param2);

    
		// Verifica se o evento que o playback da mídia completou-se ou
		// foi abortada ocorreu
		if (( cdgEvento == EC_COMPLETE ) || ( cdgEvento == EC_USERABORT ))
    {
      
			// Aborta o playback da mídia
			g_Tocador.abortarVideo(2000);
			bVideoAcionado = -1;

      break;
    } // endif

		// Verifica a ocorrência de eventos para alimentar o while{}
		hr = g_Tocador.mdEventos->GetEvent(&cdgEvento, &param1, &param2, 0);
  } // endwhile

} // tratarMediaEvento()
// ---]