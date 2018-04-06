﻿// [--- $Aspecto globais - Arquivo: motor.h#
//-----------------------------------------------------------------------------
// Projeto: prj_Texto3d - arquivo: motor.h
// Esta aplicação mostra como renderizar texto 3d
// By www.gameprog.com.br
//-----------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>

#ifndef motor_h
	#define motor_h

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Estrutura para auxiliar no posicionamento, rotação e cor do objeto 3d
struct Propriedades3d
{
	// Posição, rotação e cor
	D3DXVECTOR3		pos;
	D3DXVECTOR3		rot;
	D3DCOLORVALUE	cor;

};

	// Esta função inicializa o Direct3D
	HRESULT initGfx (HWND hJanela);

	// Essa função libera os objetos utilizados
	void Limpar();

	// Essa função desenha a cena
	void Renderizar();  	
	
	// Faz a configuração inicial da câmera
	void inicializar_Camera(void);

	// Renderiza um objeto 3d do tipo ID3DXMesh
	void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props);

	// Prepara o material do objeto 3d
	void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor );

	// Coloca uma luz direcional na cena
	void colocar_DirectionalLight(D3DXVECTOR3 direcao, D3DCOLORVALUE cvCor);

	// Configura alguns estados da cena
	void configurar_cenaEstados(void);

	// Faz a criação do texto 3d em forma de um mesh 3d
	HRESULT CriarTexto3d( ID3DXMesh **ppMesh, 
                            TCHAR *p_nomeFonte, DWORD nTamanho,
                            BOOL bBold, BOOL bItalic );

	//  Declaração da função que atende as mensagens da janela
	LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
		WPARAM wParam, LPARAM lParam);

#endif
// ---]
﻿// -----------------------------------------------------------------------------
// Projeto: prj_Texto3d - arquivo: motor.cpp
// Esta aplicação mostra como renderizar texto 3d
// By www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include "motor.h"

// Variáveis globais
// Representa o dispositivo Direct3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;

// Material para o objeto 3d
D3DMATERIAL9 g_material;

// Recipiente de cor, rotação e posição do objeto
Propriedades3d g_props;

// Controla o ângulo de rotação do objeto 3d
float g_angulo = 0.0f;

// [--- $Aspectos globais - arquivo: motor.cpp#
// Ponteiro para um mesh de texto 3d
ID3DXMesh *g_pMesh3DText = NULL;
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

// Matrizes de configuração da câmera
D3DXMATRIX g_mtxMundo; 
D3DXMATRIX g_mtxVisao; 
D3DXMATRIX g_mtxProj; 


// [--- $CriarTexto3d() - Criação do texto 3d#
//-----------------------------------------------------------------------------
// Baseado em CreateD3DXTextMesh() do SDK do directx 9
//-----------------------------------------------------------------------------
HRESULT CriarTexto3d( ID3DXMesh **ppMesh, 
                            TCHAR *p_nomeFonte, DWORD nTamanho,
                            BOOL bBold, BOOL bItalic )
{   
	
	// Valor inicial de g_hr
	g_hr = S_OK;
	
	// Objeto mesh para o texto 3d
	ID3DXMesh *pMeshNew = NULL;
	
	// Taxa de extrusão e desvio para o texto 3d
	float extrusao = 0.4f;
	float desvio = 0.001f;		

    // Cria um 'device context' para a elaboração da fonte de texto
	HDC hdc = CreateCompatibleDC( NULL );
    if( hdc == NULL ) return E_OUTOFMEMORY;

    // Variáveis de trabalho da fonte
	HFONT hFont;
    HFONT hFontOld;
	int nHeight = -MulDiv( nTamanho, GetDeviceCaps(hdc, LOGPIXELSY), 72 );
 

    // Criação da fonte
	hFont = CreateFont(nHeight, 0, 0, 0, 
		bBold ? FW_BOLD : FW_NORMAL, bItalic, 
		FALSE, FALSE, DEFAULT_CHARSET, 
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_DONTCARE, p_nomeFonte);
    
    // Selecionando a fonte do 'device context'
	hFontOld = (HFONT) SelectObject(hdc, hFont); 

    
	// Criação do mesh de texto 3d
	g_hr = D3DXCreateText( g_device, hdc, TEXT("GAMEPROG"), 
                         desvio, extrusao, &pMeshNew, NULL, NULL);

    
	// Deletando a fonte de texto criada
	SelectObject(hdc, hFontOld);
    DeleteObject( hFont );
    DeleteDC( hdc );

    // Retornando o mesh de texto 3d pelo argumento interno
	if( SUCCEEDED( g_hr ) ) *ppMesh = pMeshNew;
    return g_hr;

} // CriarTexto3d().fim
// ---]
// [--- $initGfx() - Inicialização do motor gráfico#
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
	
	// Configura as propriedades de cor, posição e rotação
	// para uso na renderização do texto 3d
	g_props.cor = cvVermelho;
	g_props.pos = D3DXVECTOR3 (3.0f, 0.0f, -2.0f);
	g_props.rot = D3DXVECTOR3 (3.0f, 0.0f, -3.0f);
	
	// <b>
    // Vamos criar o texto 3d 
	g_hr = CriarTexto3d( &g_pMesh3DText, TEXT("arial"), 24, false, false );	
    if FAILED ( g_hr ) return E_FAIL;
	// </b>

	return S_OK;
} // initGfx().fim
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
	// if( g_objeto3d != NULL) g_objeto3d->Release();

	if ( g_pMesh3DText != NULL ) g_pMesh3DText->Release();
	
	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

	// Limpeza dos ponteiros
	g_device		= NULL;
	g_Direct3d		= NULL;
	g_pMesh3DText	= NULL;

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
		desenharObjeto( g_pMesh3DText, &g_props);
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
						    props->rot.y, 
							props->rot.x + ( -g_angulo ),
							props->rot.z );


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


void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor ) 
{
  // Limpa a estrutura
  ZeroMemory( mtl, sizeof(D3DMATERIAL9)  );  

  // Configura cor ambiente e difusa
  mtl->Ambient =  cvCor; 
  mtl->Diffuse =  cvCor; 	

} // criarMaterial().fim

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

// fim do arquivo motor.cpp




﻿//-----------------------------------------------------------------------------
// Projeto: prj_Texto3d - arquivo: entrada.cpp
// Esta aplicação mostra como renderizar texto 3d
// By www.gameprog.com.br
//-----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "motor.h"

// Variável global da classe da janela
char sclasseJanela[ ] = "cls_directx";

// Dimensões da janela
int g_xtela = 640;
int g_ytela = 480;

// Handle (alça) da janela
HWND hJanela; 

int WINAPI WinMain (HINSTANCE app_instancia, HINSTANCE app_anterior,
										LPSTR sComando,int nExibir) {	

	// Estrutura de recepção das mensagens
	MSG mensagem;            

	// Estrutura de descrição da janela
	WNDCLASSEX wcls;        

	// Estrutura que descreve a janela
	wcls.hInstance = app_instancia;
	wcls.lpszClassName = sclasseJanela;
	wcls.lpfnWndProc = processaJanela;      
	wcls.style = CS_HREDRAW | CS_VREDRAW;    
	wcls.cbSize = sizeof (WNDCLASSEX);

	// O cursor e os ícones da aplicação são default
	wcls.hIcon   = LoadIcon (NULL, IDI_APPLICATION);
	wcls.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	wcls.hCursor = LoadCursor (NULL, IDC_ARROW);

	// Aplicação sem menu
	wcls.lpszMenuName = NULL;              
	
	// Nada de espaço extra atrelado a classe da janela (wcls)
	wcls.cbClsExtra = 0;                      
	
	// Nada de espaço extra atrelado a janela
	wcls.cbWndExtra = 0;                     

  // Cor default da janela
	wcls.hbrBackground = ( HBRUSH ) COLOR_BACKGROUND;

	// Registra a janela e retorna se esta operação falhar
	int status = RegisterClassEx (&wcls);
	if ( status == 0)	{
	MessageBox ( NULL, "Registro falhou!", "WinMain()", MB_OK);
	return 0;
	} // endif		

	// Com a classe criada pode-se criar a janela
	DWORD estiloExtra = 0;
	const char janelaTitulo[] = "prj_Texto3d";
	DWORD controleEstilo = WS_OVERLAPPED | WS_SYSMENU | WS_MINIMIZEBOX;
	int xpos = 160;
	int ypos = 120;
	HWND hjanelaPai = HWND_DESKTOP;
	HMENU sem_menu = NULL;
	LPVOID dadoExtra = NULL;

	// Cria a janela
	hJanela = CreateWindowEx ( estiloExtra, sclasseJanela, janelaTitulo, 
		controleEstilo, xpos, xpos,  g_xtela, g_ytela, hjanelaPai, sem_menu,                
		app_instancia, dadoExtra );

	// Verifica se janela foi criada
	if ( hJanela == NULL)	{
	MessageBox ( NULL, "Falha na criação da janela!", "WinMain()", MB_OK);
	return 0;
	} // endif
	
	// Essa variável recebe informação de erro do Directx
	HRESULT hr;
	// Inicia o Direct3D
	hr = initGfx ( hJanela );
	
	// Encerre a aplicação se houve falha
	if ( FAILED (hr) ) {
		MessageBox (hJanela, 
			"Direct3D: falha na inicialização", "WinMain()", MB_OK);
		UnregisterClass( sclasseJanela, wcls.hInstance );
		return E_FAIL;
	} // endif

	// Mostra a janela
	ShowWindow ( hJanela, nExibir);
	UpdateWindow ( hJanela );

	// Rode a bombeamento de mensagens até GetMessage() retornar 0
	while (GetMessage ( &mensagem, NULL, 0, 0 ))
	{
		// Traduz mensagem de tecla virtual em mensagem de caracteres
		TranslateMessage( &mensagem );

		// Despacha a mensagem para a função  processaJanela */
		DispatchMessage( &mensagem );
	} // endwhile

	// O valor de retorno é zero(0) passado por PostQuitMessage()
	UnregisterClass( sclasseJanela, wcls.hInstance );
	return mensagem.wParam;
} // WinMain().fim

