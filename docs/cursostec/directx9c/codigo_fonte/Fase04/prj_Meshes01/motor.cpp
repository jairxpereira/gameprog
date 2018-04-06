// -----------------------------------------------------------------------------
// Projeto: prj_Meshes01 - arquivo: motor.cpp
// Esta aplicação mostra como renderizar as formas primitivas 3d
// By www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <string.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <time.h>
#include "motor.h"

// Variáveis globais
// Representa o dispositivo Direct3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;
// [---
// Material para o objeto 3d
D3DMATERIAL9 g_material;

// Interface do objeto 3d
ID3DXMesh *g_objeto3d = NULL;

// Recipiente de cor, rotação e posição do objeto
Propriedades3d g_props;

// Controla o ângulo de rotação do objeto 3d
float g_angulo = 0.0f;

// ---]
// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

// Tamanho da janela 
extern int g_xtela;
extern int g_ytela;

// Handle (alça) da janela
extern HWND hJanela;

// Constante para cores
const DWORD branco		= 0xFFFFFFFF;

// Constante para cores com rgba expressado como float's
const D3DCOLORVALUE cvBranco   = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const D3DCOLORVALUE cvVermelho = { 1.0f, 0.0f, 0.0f, 1.0f }; 
const D3DCOLORVALUE cvAmarelo  = { 1.0f, 1.0f, 0.0f, 1.0f }; 
const D3DCOLORVALUE cvVerde    = { 0.0f, 1.0f, 0.0f, 1.0f }; 
const D3DCOLORVALUE cvAzul     = {  0.0f, 0.0f, 1.0f, 1.0f }; 
const D3DCOLORVALUE cvRoxo     = {  0.5f, 0.0f, 0.5f, 1.0f }; 

// Matrizes de configuração da câmera
D3DXMATRIX g_mtxMundo; 
D3DXMATRIX g_mtxVisao; 
D3DXMATRIX g_mtxProj; 

// Controla a mudança periódica da primitiva 3d
UINT temporizador = 0;
// [---
// initGfx() - Inicializa o Direct3D
HRESULT initGfx( HWND hJanela )
{
	// Cria o objeto Direct3D 
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
	
	// Faz a configuração inicial da câmera
	inicializar_Camera();

	// Configura alguns estados da cena
	configurar_cenaEstados();	

	// Configura e coloca uma luz direcional na cena
  D3DXVECTOR3 direcao(0.0f, -1.0f, -1.0f);   
  colocar_DirectionalLight (direcao, cvBranco);  

	return S_OK;
} // initGfx().fim
// ---]
// [---
void renderizar_Geometria()
{	

	// Mensagens para a barra de títulos da janela
	char *mensagem[] = 
		{ 
		"prj_Meshes01: D3DXCreateBox ( )",
		"prj_Meshes01: D3DXCreatePolygon ( )",
		"prj_Meshes01: D3DXCreateTeapot ( )", 
		"prj_Meshes01: D3DXCreateSphere ( )", 
		"prj_Meshes01: D3DXCreateTorus ( )",
		"prj_Meshes01: D3DXCreateCylinder ( )"
		};

	// Produz a cada dois segundos um valor de 0 a 5.
	temporizador = ( clock() / 2000 ) % 6;	
	
	// Configura o texto da janela
	config_janelaTexto( mensagem[temporizador]);		
	
	// Renderiza a primitiva 3d selecionada pelo tempo decorrido
		switch( temporizador )
	{

		case 0:
		// Cria e renderiza uma caixa				
		D3DXCreateBox (g_device, 1.0f, 1.0f, 1.0f, &g_objeto3d, NULL);
    g_props.cor = cvVermelho;
		g_props.pos = D3DXVECTOR3 (0.0f, 0.0f, 2.0f);
		g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);	
    desenharObjeto( g_objeto3d, &g_props);
		break;	

		case 1:
		// Cria e renderiza um polígono		
		D3DXCreatePolygon (g_device, 2.0f, 8, &g_objeto3d, NULL);
    g_props.cor = cvVerde;
		g_props.pos = D3DXVECTOR3 (0.0f, 0.0f, -5.0f);
		g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
    desenharObjeto( g_objeto3d, &g_props);
		break;

	  case 2:
		// Cria e renderiza um teapot		
		D3DXCreateTeapot (g_device, &g_objeto3d, NULL);
    g_props.cor = cvAmarelo;
		g_props.pos = D3DXVECTOR3 (0.0f, 0.0f, -1.0f);
		g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
    desenharObjeto( g_objeto3d, &g_props);
		break;

		case 3:
		// Cria e renderiza uma esfera		
		D3DXCreateSphere (g_device, 2.0f, 8, 8, &g_objeto3d, NULL);
    g_props.cor = cvAzul;
		g_props.pos = D3DXVECTOR3 (0.0f, 0.0f, -5.0f);
		g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
		g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME); 
    desenharObjeto( g_objeto3d, &g_props);
		g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID); 
		break;
		
		case 4:
		// Cria e renderiza um torus		
		D3DXCreateTorus (g_device, 0.1f, 2.0f, 32, 32, &g_objeto3d, NULL);
    g_props.cor = cvRoxo;
		g_props.pos = D3DXVECTOR3 (0.0f, 0.0f, -2.0f);
		g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
    desenharObjeto( g_objeto3d, &g_props);
		break;

		case 5:
		// Cria e renderiza um cilindro		
		D3DXCreateCylinder (g_device, 0.5f, 1.0f, 5.0f, 32, 32, &g_objeto3d, NULL);
    g_props.cor = cvAzul;
		g_props.pos = D3DXVECTOR3 (0.0f, 0.0f, -5.0f);
		g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
    desenharObjeto( g_objeto3d, &g_props);
		break;

		// Libera o objeto criado
		g_objeto3d->Release();
		g_objeto3d = NULL;

	} // fim do switch

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
	// Libera o buffer de vértices
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


// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
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
		renderizar_Geometria();
		// </b>
		// Finalizando a cena
		g_device->EndScene();
	} // endif

	// Apresenta o conteúdo do backbuffer na tela
	g_device->Present( NULL, NULL, NULL, NULL );

} // Renderizar().fim

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
D3DXMatrixRotationYawPitchRoll(&obj_rot, 
															 props->rot.y + g_angulo, 
															 props->rot.x + g_angulo,
															 props->rot.z);


// Ajusta posição do objeto 3d;
D3DXMatrixTranslation ( &obj_pos, 
											 props->pos.x, props->pos.y, props->pos.z);

// Tranfere posição e rotação para o mundo
D3DXMatrixMultiply (&mtxCombinada, &obj_rot, &obj_pos);

// Configura matriz mundo para o dispositivo renderizador
g_device->SetTransform( D3DTS_WORLD, &mtxCombinada );  

// Prepara e aplica uma material no objeto 3d
criarMaterial( &g_material, props->cor);
g_device->SetMaterial (&g_material);

// Renderiza o mesh 
obj3d->DrawSubset(0);

} // desenharObjeto().fim
// ---]

void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor ) 
{
  // Limpa a estrutura
  ZeroMemory( mtl, sizeof(D3DMATERIAL9)  );  

  // Configura cor ambiente e difusa
  mtl->Ambient =  cvCor; 
  mtl->Diffuse =  cvCor; 	

} // criarMaterial().fim
// [---
void colocar_DirectionalLight(D3DXVECTOR3 direcao, D3DCOLORVALUE cvCor) 
{
	// Declara a estrutura
	D3DLIGHT9 luz; 

	// Limpa a estrutura
	ZeroMemory( &luz, sizeof(D3DLIGHT9)  );  

	// Configura tipo
	luz.Type = D3DLIGHT_DIRECTIONAL; 

	// Configura cor
	luz.Diffuse = cvCor; 

	// Configura direção da luz
	luz.Direction = direcao;

	// Instalação e acionamento da luz no dispositivo renderizador
  g_device->SetRenderState (D3DRS_LIGHTING, true );  
	g_device->SetLight( 0, &luz );  
	g_device->LightEnable( 0, TRUE); 

} // colocar_DirectionalLight().fim
// ---]
// [---
void configurar_cenaEstados(void) 
{
	// Configura luz ambiente
	g_device->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(80,80,80) );

	// Configura shading
	g_device->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );

	// Habilita uso de buffer de profundidade
	g_device->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );	

  // Desliga o culling
	g_device->SetRenderState (D3DRS_CULLMODE, D3DCULL_NONE);  

} // configurar_cenaEstados().fim
// ---]



