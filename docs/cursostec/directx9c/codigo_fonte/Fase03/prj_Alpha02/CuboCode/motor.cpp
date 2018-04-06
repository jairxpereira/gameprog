// -----------------------------------------------------------------------------
// Projeto: prj_Alpha02 - arquivo: motor.cpp
// Esta aplicação mostra os efeitos de alpha blending
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include "motor.h"
#include "cubo.h"
#include "customvertex.h"

// Variáveis globais
// Representa o dispositivo Direct3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;
// [---
// <b>
IDirect3DTexture9*			g_Textura = NULL;
IDirect3DTexture9*			g_texDds  = NULL;

// Matrizes de configuração da câmera
// Matriz de mundo
D3DXMATRIX g_mtxMundo; 
// Matriz de visão
D3DXMATRIX g_mtxVisao; 
// Matriz de projeção
D3DXMATRIX g_mtxProj; 

// Material para o objeto 3d
D3DMATERIAL9 g_material;

// Recipiente de cor, rotação e posição do objeto
Propriedades3d g_props;

// Controla a rotação do cubo
float g_angulo = 0.0f;
float velocidade = 0.02f;

// Constante para cores com rgba expressado como float's
D3DCOLORVALUE cvBranco   = { 1.0f, 1.0f, 1.0f, 1.0f }; 
// Constante para cores
const DWORD dwBranco = 0xFFFFFFFF;

// </b>
// ---]
// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

// Tamanho da janela 
extern int g_xtela;
extern int g_ytela;
extern HWND hJanela;

Cubo                    *g_cubo    = NULL;
IDirect3DTexture9       *tex_cubo  = NULL;

// Controla a mudança periódica da primitiva
UINT temporizador = 0;

// Memória pas os vértices
CustomVertex_PositionTextured g_Verts[4]; 

// Buffer de índices - indica a ordem de conexão dos vértices
WORD g_Indices[6] = {  0,1,2,   2,3,0 }; 

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

	// Habilita o buffer de profundidade
	pps.EnableAutoDepthStencil = true;
	pps.AutoDepthStencilFormat = D3DFMT_D16;

	// Esse método transfere rapidamente o backbuffer para a tela imediata
	pps.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// Esse formato vai procurar se encaixar no modo de video corrente
	pps.BackBufferFormat = D3DFMT_A8R8G8B8; //D3DFMT_UNKNOWN;	
	pps.BackBufferCount = 1;

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

	// Monta o quad
	montar_Geometria();	

	// Inicializa a textura
	inicializar_Textura();
	
	// Inicializa a câmera
	inicializar_Camera();	  
	
  // Configura luz ambiente
	g_device->SetRenderState (D3DRS_LIGHTING, true ); 
	g_device->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(200,200,200) );	

	// </b>

	return S_OK;
} // initGfx().fim
// ---]
// [---
void montar_Geometria(void)
{

	// Cria o cubo
	g_cubo = new Cubo(g_device);
	
	// Posicionamento de profundidade
	float zpos = 0.9f;
	// Configuração normal dos vértices
	g_Verts[0] = CustomVertex_PositionTextured( 2.20f,  1.50f,  zpos, 0.0f, 0.0f);
	g_Verts[1] = CustomVertex_PositionTextured( -2.20f, 1.50f,  zpos, 3.0f, 0.0f);
	g_Verts[2] = CustomVertex_PositionTextured( -2.20f, -1.50f, zpos, 3.0f, 3.0f);
	g_Verts[3] = CustomVertex_PositionTextured( 2.20f, -1.50f,  zpos, 0.0f, 3.0f);	
	

} //  montar_Geometria().fim
// ---]
// [---
void renderizar_Geometria()
{
	// Mensagens para a barra de títulos da janela
	char *mensagem[] = 
	{ 
		"prj_Alpha02: By Gameprog",
		"prj_Alpha02: 1. D3DBLEND_ZERO",
		"prj_Alpha02: 2. D3DBLEND_ONE",
		"prj_Alpha02: 3. D3DBLEND_SRCCOLOR",
		"prj_Alpha02: 4. D3DBLEND_INVSRCCOLOR",
		"prj_Alpha02: 5. D3DBLEND_SRCALPHA",
		"prj_Alpha02: 6. D3DBLEND_INVSRCALPHA",
		"prj_Alpha02: 7. D3DBLEND_DESTALPHA",
		"prj_Alpha02: 8. D3DBLEND_INVDESTALPHA",
		"prj_Alpha02: 9. D3DBLEND_DESTCOLOR",
		"prj_Alpha02: 10. D3DBLEND_INVDESTCOLOR",
		"prj_Alpha02: 11. D3DBLEND_SRCALPHASAT",
		"prj_Alpha02: 12. D3DBLEND_BOTHSRCALPHA",
		"prj_Alpha02: 13. D3DBLEND_BOTHINVSRCALPHA",
		"prj_Alpha02: 14. D3DBLEND_BLENDFACTOR",
		"prj_Alpha02: 15. D3DBLEND_INVBLENDFACTOR",
	};

	// Produz a cada quadro segundos um valor de 2 a 15.
	temporizador = ( clock() / 4000 ) % 14;
	temporizador = temporizador + 2;		

		// Configura o texto da janela
	config_janelaTexto (mensagem[temporizador]);

	// Fator de mistura para os modos 14 e 15
	if (temporizador > 13)
		g_device->SetRenderState(D3DRS_BLENDFACTOR, 0xFFFF0000);		

	// Desenha o quad
	g_props.cor = cvBranco;
	g_props.pos = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
	g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);
	g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	desenhar_Quad(&g_props);	

	// Faz a configuração de alpha blending fonte e destino
	g_device->SetRenderState(D3DRS_SRCBLEND, temporizador);
	g_device->SetRenderState(D3DRS_DESTBLEND,  D3DBLEND_ONE); 	

	// Posição e rotação do cubo
	cvBranco.a = 0.2f;
	g_props.cor = cvBranco;
	g_props.pos = D3DXVECTOR3 (0.0f, 0.0f, 1.0f);
	g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);	
	
	g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	desenhar_Cubo(&g_props);	

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

	if (tex_cubo != NULL) tex_cubo->Release();	

	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

	// Limpa os ponteiros
	g_Direct3d	= NULL;
	g_device		= NULL;
	g_Textura		= NULL;
	tex_cubo		= NULL;

} // Limpar().fim


// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
VOID Renderizar()
{
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;	

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, dwBranco, 1.0f, 0);

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
		 "\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp", 
		&g_Textura); 

	 // cratewalpha.dds	
	 g_hr = D3DXCreateTextureFromFile( g_device, 
		 "\\gameprog\\gdkmedia\\bitmap\\gp-alpha.bmp", 
		 &tex_cubo); 

	 if (FAILED (g_hr))
	{
		MessageBox(NULL, "Falha: D3DXCreateTextureFromFile()", 
			"inicializar_Textura()", MB_OK);
	} // endif
	
	// Habilita o uso do canal alpha da cor difusa do material
	g_device->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	g_device->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);	

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

void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor ) 
{
	// Limpa a estrutura
	ZeroMemory( mtl, sizeof(D3DMATERIAL9)  );  

	// Configura cor ambiente e difusa
	mtl->Ambient =  cvCor; 
	mtl->Diffuse =  cvCor; 

} // criarMaterial().fim

void desenhar_Quad( Propriedades3d *props )
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

	// Configura rotação do objeto 3d
	// Configura rotação do objeto 3d
	D3DXMatrixRotationYawPitchRoll(&obj_rot, 
		props->rot.y, 
		props->rot.x,
		props->rot.z);

	// Ajusta posição do objeto 3d;
	D3DXMatrixTranslation ( &obj_pos, 
		props->pos.x, props->pos.y, props->pos.z );

	// Tranfere posição e rotação para o mundo
	D3DXMatrixMultiply (&mtxCombinada, &obj_rot, &obj_pos);

	// Configura matriz mundo para o dispositivo renderizador
	g_device->SetTransform( D3DTS_WORLD, &mtxCombinada );  

	// Prepara e aplica uma material na caixa
	criarMaterial( &g_material, cvBranco);
	g_device->SetMaterial (&g_material);	
	g_device->SetTexture (0, g_Textura);

	// Argumentos da função DrawIndexedPrimitiveUP()
	UINT   nVerticeInicial = 0; 
	UINT   nVerticeQtd   = 4; 
	UINT   nContagemPrim  = 2; 
	UINT   nPasso     =  sizeof(CustomVertex_PositionTextured);   

	// Declara o formato de vértice utilizado pela  aplicação
	g_device->SetFVF( CustomVertex_PositionTextured_Format );	 

	// Configura modo de textura
	g_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// Renderiza o quad
	g_device->DrawIndexedPrimitiveUP( D3DPT_TRIANGLELIST, 
		nVerticeInicial, nVerticeQtd, nContagemPrim, &g_Indices, 
		D3DFMT_INDEX16, &g_Verts, nPasso);

} // desenhar_Quad()

void desenhar_Cubo(Propriedades3d *props )
{	
	// Matrizes para controlar posição e rotação do objeto 3d
	D3DXMATRIX obj_rot;
	D3DXMATRIX obj_pos;
	D3DXMATRIX obj_esc;
	
	// Atualiza o ângulo
	g_angulo += 0.01f;

	// Matriz para combinar todas as transformações do objeto 3d
	D3DXMATRIX mtxCombinada;

	// Vamos inicializar as matrizes para um valor neutro
	D3DXMatrixIdentity( &obj_rot ); 
	D3DXMatrixIdentity( &obj_pos );
	D3DXMatrixIdentity( &obj_esc );
	D3DXMatrixIdentity( &mtxCombinada );

	// Configura rotação do objeto 3d
	D3DXMatrixRotationYawPitchRoll(&obj_rot, 
		props->rot.y + g_angulo, 
		props->rot.x + g_angulo,
		props->rot.z);

	// Ajusta posição do objeto 3d;
	D3DXMatrixTranslation ( &obj_pos, 
		props->pos.x, props->pos.y, props->pos.z );	

	// Tranfere posição e rotação para o mundo
	D3DXMatrixScaling (&obj_esc, 0.8f, 0.8f, 0.8f);

	// Produz a matriz combina com as matrizes parciais
	mtxCombinada = obj_rot * obj_esc * obj_pos;

	// Configura matriz mundo para o dispositivo renderizador
	g_device->SetTransform( D3DTS_WORLD, &mtxCombinada ); 
	
		// Prepara e aplica uma material na caixa
	criarMaterial( &g_material, props->cor);
	g_device->SetMaterial (&g_material);


	// Desenha o cubo
	g_cubo->desenhar(tex_cubo);
	

} // desenhar_Cubo().fim





