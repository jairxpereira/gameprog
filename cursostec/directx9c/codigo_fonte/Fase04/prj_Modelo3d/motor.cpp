// -----------------------------------------------------------------------------
// Projeto: prj_Modelo3d - arquivo: motor.cpp
// Esta aplicação mostra como carregar e renderizar
// um modelo 3d estático. By www.gameprog.com.br
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

// [---
// <b>
// Interface do objeto 3d
ID3DXMesh *g_objeto3d = NULL;

// Array para texturas referenciadas pelo modelo 3d
IDirect3DTexture9   **g_meshTex = NULL;

// Variável para manipulação de materiais
D3DMATERIAL9				*g_meshMtl = NULL;

// Quantidade de materiais do modelo 3d
DWORD g_mtlQtd = 0;
// </b>
// Recipiente de cor, rotação e posição do objeto
Propriedades3d g_props;
// ---]
// Controla o ângulo de rotação do objeto 3d
float g_angulo = 0.0f;

// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

// Tamanho da janela 
extern int g_xtela;
extern int g_ytela;
extern HWND hJanela;

// Constante para cores
const DWORD branco		= 0xFFFFFFFF;

// Matrizes de configuração da câmera
D3DXMATRIX g_mtxMundo; 
D3DXMATRIX g_mtxVisao; 
D3DXMATRIX g_mtxProj; 

// [---
void CarregarModelo( char *diretorioBase, char *arquivo)
{
	// Composição do nome final do arquivo do modelo 3d
	// caminhoFinal = diretorioBase + arquivo
	char caminhoFinal[255] = "\0";	
	strcat (caminhoFinal, diretorioBase);
	strcat (caminhoFinal, arquivo);

	// Buffer para o pacote de materiais e texturas do modelo 3d 
	ID3DXBuffer *mtlPack;

	// Recebe nome do arquivo de textura sendo carregado 
	char *arquivo_tex = NULL;

	// Carrega modelo 3d com suas texturas e materiais 
	g_hr = D3DXLoadMeshFromX(caminhoFinal, D3DXMESH_SYSTEMMEM, 
		g_device, NULL, &mtlPack, NULL, &g_mtlQtd, &g_objeto3d );
	
	// Verifica falha no carregamento do modelo 3d
	if ( FAILED (g_hr) )
	{
		MessageBox (NULL, 
			"Falha no carregamento do modelo", "CarregarModelo()", MB_OK);		
		return;    
	} // endif

	// Pacote de materiais da biblioteca auxiliar d3dx
	D3DXMATERIAL  *xMtl = (D3DXMATERIAL*) mtlPack->GetBufferPointer();

	// Inicializa as variáveis arrays de materiais e texturas 
	g_meshMtl  = new D3DMATERIAL9[g_mtlQtd];
	g_meshTex  = new IDirect3DTexture9*[g_mtlQtd];

	// Carrega texturas e materiais
	for (DWORD ncx = 0;  ncx < g_mtlQtd; ncx++)
	{
		// Copia o material
		g_meshMtl[ncx] = xMtl[ncx].MatD3D;

		// Configura a cor ambiente do material
		g_meshMtl[ncx].Ambient = g_meshMtl[ncx].Diffuse;

		// Cria a textura se ela existir
		g_meshTex[ncx] = NULL;
		ZeroMemory ( caminhoFinal, sizeof(caminhoFinal));
		strcat(caminhoFinal, diretorioBase);
		arquivo_tex = strcat(caminhoFinal, xMtl[ncx].pTextureFilename);	

		// Carrega a textura do arquivo 
		if (arquivo_tex != NULL) 
			g_hr = D3DXCreateTextureFromFile(g_device, 
			arquivo_tex, &g_meshTex[ncx]);

		// Verifica falha no carregamento da textura
		if ( FAILED (g_hr) )
		{
			MessageBox (NULL, 
				"Falha no carregamento da textura", "CarregarModelo()", MB_OK);	
			mtlPack->Release();
			return;    
		} // endif

	} // endfor

	// Libera o buffer do pacote de materiais
	mtlPack->Release();

} // CarregarModelo().fim
// ---]
// [---
void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props)
{

// Matrizes para controlar posição e rotação do objeto 3d
D3DXMATRIX obj_rot;
D3DXMATRIX obj_pos;

// Matriz para combinar todas as transformações do objeto 3d
D3DXMATRIX mtxCombinada;

// Vamos inicializar as matrizes para um valor neutro
D3DXMatrixIdentity( &obj_rot ); 
D3DXMatrixIdentity( &obj_pos );
D3DXMatrixIdentity( &mtxCombinada );

// Atualiza ângulo de rotação
g_angulo += 0.02f;

// Configura rotação do objeto 3d
D3DXMatrixRotationYawPitchRoll( &obj_rot, 
	props->rot.y, props->rot.x + g_angulo, props->rot.z);

// Ajusta posição do objeto 3d;
D3DXMatrixTranslation ( &obj_pos, 
	props->pos.x, props->pos.y, props->pos.z);

// Tranfere posição e rotação para o mundo
D3DXMatrixMultiply (&mtxCombinada, &obj_rot, &obj_pos);

// Configura matriz mundo para o dispositivo renderizador
g_device->SetTransform( D3DTS_WORLD, &mtxCombinada );  
// <b>
// Renderiza o mesh 
if (g_mtlQtd > 0)
	
	for (DWORD ncx=0; ncx < g_mtlQtd; ncx++)
	{
		g_device->SetMaterial ( &g_meshMtl[ncx] );
		g_device->SetTexture ( 0, g_meshTex[ncx] );
		obj3d->DrawSubset(ncx);
	} // endfor 
// </b>
} // desenharObjeto().fim
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

	// Vamos ativar o buffer de profundidade
	pps.EnableAutoDepthStencil = true;
	pps.AutoDepthStencilFormat = D3DFMT_D16;

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
	
	// Configura a câmera
	inicializar_Camera();

	// Configura alguns estados da cena
	configurar_cenaEstados();	
		
	// Carrega um modelo 3d com suas texturas e materiais
	CarregarModelo("\\gameprog\\gdkmedia\\Modelos\\Tiny\\", "tiny.x");

	return S_OK;
} // initGfx().fim
// ---]
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
// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
// [---
VOID Renderizar()
{
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;	

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, branco, 1.0f, 0);

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
		// <b>
		// Vamos renderizar a geometria
		g_props.pos = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
		g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);	
    desenharObjeto( g_objeto3d, &g_props);
		// </b>
		// Finalizando a cena
		g_device->EndScene();
	} // endif

	// Apresenta o conteúdo do backbuffer na tela
	g_device->Present( NULL, NULL, NULL, NULL );

} // Renderizar().fim
// ---]
void configurar_cenaEstados(void) 
{
	// Configuração de iluminação
	 g_device->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(220,220,220) );
	
	 // Corrige visualização blocada da textura - quando textura for
  // menor do que a superfície
  g_device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);   

  // Corrige visualização blocada da textura - quando textura for
  // maior do que a superfície
  g_device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);   
} // configurar_cenaEstados().fim
// [---
// Limpar() -  Libera todos os objetos previamente inicializados
// -----------------------------------------------------------------------------
VOID Limpar() 
{	
	
	// Limpeza das texturas do modelo 3d
	if (g_mtlQtd > 0)
	{		
		for (DWORD ncx=0; ncx < g_mtlQtd; ncx++)
		{
			if (g_meshTex[ncx] != NULL) 
			{
				g_meshTex[ncx]->Release();
				g_meshTex[ncx] = NULL;
			} // endif		
		} // endfor

		// Libera a memória alocada com a instrução 'new'
		if (g_meshTex != NULL) delete g_meshTex;
		if (g_meshMtl != NULL) delete g_meshMtl;
		
		// Limpa os ponteiros
		g_meshTex = NULL;
		g_meshMtl = NULL;

	} // endif	
	
	// Libera o objeto 3d
	if( g_objeto3d != NULL) g_objeto3d->Release();
	
	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

	// Limpeza dos ponteiros
	g_objeto3d	= NULL;
	g_device		= NULL;
	g_Direct3d	= NULL;

} // Limpar().fim
// ---]

