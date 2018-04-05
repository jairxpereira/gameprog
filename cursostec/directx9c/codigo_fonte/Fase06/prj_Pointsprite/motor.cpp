// -----------------------------------------------------------------------------
// Projeto: prj_PointSprite - arquivo: motor.cpp
// Esta aplicação mostra como renderizar partículas com pontosprites
// By www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>
#include "motor.h"

// Desliga aviso de 'função insegura' devido ao uso das
// funções de string antigas( strcat etc... )
#pragma warning( disable:4996 )

// Variáveis globais
// Representa o dispositivo Direct3D
IDirect3D9             *g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9       *g_device = NULL;

// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

// Tamanho da janela 
extern int g_xtela;
extern int g_ytela;
extern HWND hJanela;

// Constante para cores
const DWORD branco		= 0xFFFFFFFF;
const DWORD vermelho		= 0xFFFF0000;
const DWORD verde		    = 0xFF00FF00;
const DWORD azul		    = 0xFF0000FF;
const DWORD amarelo		    = 0xFFFFFF00;

// Matrizes de configuração da câmera
D3DXMATRIX g_mtxMundo; 
D3DXMATRIX g_mtxVisao; 
D3DXMATRIX g_mtxProj; 

// [--- $Aspectos globais: arquivo motor.cpp#
// <b>
// Preparação para pointsprites
// ----------------------------------------------------------------------------
// Vertexbuffer
IDirect3DVertexBuffer9	*g_pVertexbuffer = NULL;

// Textura
IDirect3DTexture9		*g_pTex = NULL;

// matriz de posição e orientação do pontosprite
D3DXMATRIX g_mtxPos, g_mtxRot;

// Tamanho de cada sprite
const float nTamanho = 6.0f;

// Posição, tamanho e cor de cada pontosprite
CustomVertex_PointSprite g_Pontos[] =
{
	{ -100.0f,  100.0f,  5.0f, nTamanho, amarelo  },
	{ 100.0f,  -100.0f,  5.0f, nTamanho, azul     },
	{ -100.0f, -100.0f,  5.0f, nTamanho, verde    },
	{ 100.0f,  100.0f,   5.0f, nTamanho, vermelho }
};

// Controla o ângulo de rotação do objeto 3d
float g_angulo = 0.0f;

// Ponteiro de acesso aos dados do vertexbuffer
void *g_pDados;
// </b>
// ---]

// [--- $initGfx() -  Inicialização do motor gráfico (Direct3D)#
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

	// Vamos ativar o buffer de profundidade
	pps.EnableAutoDepthStencil = true;
	pps.AutoDepthStencilFormat = D3DFMT_D16;	

	// Configura os parâmetros de apresentação
	// A aplicação vai ter janela
	pps.Windowed = TRUE;

	// Esse método transfere rapidamente o backbuffer para a tela imediata
	pps.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// Esse formato vai permitir o uso de alpha blending
	pps.BackBufferFormat = D3DFMT_A8R8G8B8; 

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
	
	// Configura a câmera
	inicializar_Camera();	
	// <b>
	// Inicializa o ambiente e objetos pertinentes da produção
	// de pointsprites.
	inicializar_Pointsprite();
	// </b>
	return S_OK;
} // initGfx().fim
// ---]

// [--- $inicializar_Pointsprite()- Inicialização das partículas#
void inicializar_Pointsprite(void)
{

// Configuração dos estados pertinentes a sprites
g_device->SetRenderState(D3DRS_POINTSPRITEENABLE, true);
g_device->SetRenderState(D3DRS_POINTSCALEENABLE, true);

// Configuração de tamanho de ponto
float nPointSize = 1.0f;
g_device->SetRenderState(D3DRS_POINTSIZE, *((DWORD*) &nPointSize));

// Configuração do tamanho mínimo
float nMinPointSize = 1.0f;
g_device->SetRenderState(D3DRS_POINTSIZE_MIN, *((DWORD*) &nMinPointSize));

// Configuração do fator de escala
float nPointScaleB = 1.0f;
g_device->SetRenderState(D3DRS_POINTSCALE_B, *((DWORD*) &nPointScaleB));

// Aciona iluminação automática
g_device->SetRenderState(D3DRS_LIGHTING, false);

// Desliga uso do z buffer
g_device->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);

// Configuração de alpha blending
g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
g_device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
g_device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ZERO);

// Configura o formato de vértice
g_device->SetFVF( CustomVertex_PointSprite_Format );

// Elaboração do vertexbuffer
g_device->CreateVertexBuffer(sizeof( g_Pontos),
							 D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
							 CustomVertex_PointSprite_Format,
							 D3DPOOL_MANAGED, 
							 &g_pVertexbuffer, NULL);

// Tranca o vertexbuffer para inicializar o ponteiro de dados
g_pVertexbuffer->Lock(0, 0, &g_pDados, 0);

// Transfere os dados para o vertexbuffer
memcpy(g_pDados, g_Pontos, sizeof(g_Pontos) );

// Destranca o vertexbuffer
g_pVertexbuffer->Unlock();

// Carrega a textura
D3DXCreateTextureFromFile(g_device, "particula.png", &g_pTex);

} // inicializar_Pointsprite()
// ---]

// [--- $renderizar_Pointsprite() - Renderização das partículas#
void renderizar_Pointsprite()
{

// Configura transformação do objeto Pointsprite
D3DXMatrixRotationZ(&g_mtxRot, g_angulo );
D3DXMatrixTranslation(&g_mtxPos, 0.0f, 0.0f, 0.0f);
g_device->SetTransform(D3DTS_WORLD, &( g_mtxRot * g_mtxPos ) );

// Declara a textura e o vertexbuffer
g_device->SetTexture(0, g_pTex);
g_device->SetStreamSource(0, g_pVertexbuffer, 0, sizeof( CustomVertex_PointSprite ) );

// Desenha o objeto pointsprite
g_device->DrawPrimitive(D3DPT_POINTLIST, 0, 4);

// Atualiza ângulo para a próxima renderização
g_angulo  += 0.10f;

} // renderizar_Pointsprite().fim
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
  D3DXVECTOR3 cam_pos (0.0f, 0.0f, 700.0f);   
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
	// <b> 	
	// Pega o tamanho da área cliente
	RECT area_cliente;
	GetWindowRect (hJanela, &area_cliente);
	g_xtela = area_cliente.right;
  g_ytela = area_cliente.bottom ;	

  // aspecto dos gráficos 
	float aspecto = (float)  g_xtela / g_ytela; 
	// </b>
	// campo de visão
  float campo_visao =  0.785398f; 
  // Trapézio de visualização da câmera ( Frustrum )
  float corte_perto = 1.0f; 
  float corte_longe = 1000.0f; 

  // Configura a matriz de projeção
  D3DXMatrixPerspectiveFovLH( &g_mtxProj, campo_visao, aspecto, 
    corte_perto, corte_longe);  

  // Configura a matriz de projeção no dispositivo renderizador
  g_device->SetTransform( D3DTS_PROJECTION, &g_mtxProj );  

} // inicializar_Camera().fim

// [--- $Renderizar() - Renderização da cena#
VOID Renderizar()
{
	// Fundo preto para combinar com o fundo da textura do pontosprite
	const DWORD dwPreto = 0;

	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;	

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 
		dwPreto, 1.0f, 0);

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
	// <b>
	renderizar_Pointsprite();
	// </b>
	// Finalizando a cena
	g_device->EndScene();
	} // endif

	// Apresenta o conteúdo do backbuffer na tela
	g_device->Present( NULL, NULL, NULL, NULL );
	

} // Renderizar().fim
// ---]

VOID Limpar() 
{	
		
	// Libera o dispositivo gráfico  
	if( g_device != NULL       ) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL     ) g_Direct3d->Release();
	
	// Libera a textura
	if(g_pTex != NULL          ) g_pTex->Release();
	
	// Libera o vertexbuffer
	if(g_pVertexbuffer != NULL ) g_pVertexbuffer->Release();
	
	// Limpeza dos ponteiros
	g_device	    = NULL;
	g_Direct3d	    = NULL;
	g_pTex          = NULL;
	g_pVertexbuffer = NULL;

} // Limpar().fim



//  Esta função é chamada por DispatchMessage()  
LRESULT CALLBACK processaJanela (
	HWND hJanela, UINT mensagem, WPARAM wParam, LPARAM lParam)
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
// fim do arquivo: motor.cpp