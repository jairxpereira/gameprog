// [---
// -----------------------------------------------------------------------------
// Projeto: prj_HLSL02 - Arquivo: motor.h
// Esta  aplicação  ilustra  como renderizar um mesh
// iluminado utilizando hlsl. By www.gameprog.com.br
// -----------------------------------------------------------------------------
#ifndef motor_h
	#define motor_h

// Estrutura para posicionamento e rotação do mesh
struct Propriedades3d 
{ 
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
};

	// Esta função inicializa o Direct3D
	HRESULT initGfx (HWND hJanela);

	// Essa função libera os objetos utilizados
	void Limpar();

	// Essa função desenha a cena
	void Renderizar();	

	// Renderiza o mesh utilizando hlsl
	void renderizar_Geometria (void);

	// Inicializa as matrizes da câmera
	void inicializar_Camera(void); 	

  // Inicializa o objeto efeito
	void inicializarEfeito(void);

	// Desenha o objeto 3d
	void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props);

	// Declaração da função que atende as mensagens da janela
  LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
				WPARAM wParam, LPARAM lParam);

#endif
// ---]
﻿// -----------------------------------------------------------------------------
// Projeto: prj_HLSL02 - arquivo: motor.cpp
// Esta  aplicação  ilustra  como renderizar um mesh
// iluminado utilizando hlsl. By www.gameprog.com.br
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
IDirect3DDevice9       *g_device = NULL;
// [---
// Representa o objeto efeito
ID3DXEffect						 *g_efeito = NULL;

// Variáveis para provocar mudanças de cor e movimento
float nMovimento  = 0.0f;
float nVelocidade = 0.01f;
float g_angulo    = 0.01f;

// Interface do objeto 3d
ID3DXMesh *g_objeto3d = NULL;

// Recipiente de cor, rotação e posição do objeto
Propriedades3d g_props;
// ---]
// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

// Tamanho da janela 
extern int g_xtela;
extern int g_ytela;
extern HWND hJanela;

// Constante para cores
const DWORD branco		= 0xFFFFFFFF;
const DWORD verde			= 0xFF008000;

// Matrizes de configuração da câmera
D3DXMATRIX g_mtxMundo; 
D3DXMATRIX g_mtxVisao; 
D3DXMATRIX g_mtxProj;  
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

	// Adaptador default (0)
	int nAdaptador = D3DADAPTER_DEFAULT;

	// Tipo de dispositivo Hardware ou emulador de referência (software) 
	D3DDEVTYPE dispositivo_tipo = D3DDEVTYPE_HAL;

	// Flags de configuração do dispositivo
	DWORD create_flags = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	// Criamos aqui o dispositivo renderizador
	g_hr = g_Direct3d->CreateDevice( nAdaptador, dispositivo_tipo, 
		hJanela, create_flags, &pps, &g_device );

	// Verifica se houve falha no processo
	if( FAILED( g_hr ) ) { 
		MessageBox (NULL, "Falha na criação: g_device", "initGfx()", MB_OK);
		return E_FAIL;
	} // endif
	// <b>	
	// Monta a geometria
	D3DXCreateCylinder (g_device, 0.5f, 1.0f, 5.0f, 32, 32, &g_objeto3d, NULL);
	g_props.pos = D3DXVECTOR3 (0.0f, 0.0f, -5.0f);
	g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);

	// Inicializa um objeto efeito
	inicializarEfeito();

	// Inicializa e atualiza a configuração de câmera
	inicializar_Camera();
	// </b>

	return S_OK;
} // initGfx().fim
// ---]
// [---
void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props)
{
	// Matrizes para controlar posição e rotação do objeto 3d
	D3DXMATRIX obj_rot;
	D3DXMATRIX obj_pos;
	D3DXMATRIX camera; 

	// Handle para a variáveis do shader
	D3DXHANDLE hMov = NULL;
	D3DXHANDLE hCam = NULL; 

	// Vamos inicializar as matrizes para um valor neutro
	D3DXMatrixIdentity( &obj_rot ); 
	D3DXMatrixIdentity( &obj_pos );
	D3DXMatrixIdentity( &camera );

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

	// Tranfere posição e rotação para o g_mtxMundo
	D3DXMatrixMultiply (&g_mtxMundo, &obj_rot, &obj_pos);

	// Atualiza cor
	nMovimento += nVelocidade; 
	if (nMovimento >= 1.0f)  nVelocidade *= -1;
	if (nMovimento <= 0.0f)  nVelocidade *= -1;

	// Atualiza a câmera
	camera = g_mtxMundo * g_mtxVisao * g_mtxProj; 

	// Obtém acesso às variáveis do shader
	hMov = g_efeito->GetParameterByName (0, "nMovimento");
	hCam = g_efeito->GetParameterByName (0, "Camera");

	// Atualiza variáveis no shader
	g_efeito->SetValue (hMov, &nMovimento, sizeof(nMovimento) );
	g_efeito->SetValue (hCam, &camera, sizeof(camera) );

	// Renderiza o objeto
	obj3d->DrawSubset(0);

} // desenharObjeto().fim
// ---]
// [---
void renderizar_Geometria()
{
	// Número de passos do efeito
	UINT nPassosQtd = 0;

	// Renderiza o mesh usando o efeito
	g_efeito->Begin(&nPassosQtd, 0);  

	for ( UINT ncx = 0; ncx < nPassosQtd; ncx++) 
	{
		// Renderiza a cena passo a passo
		g_efeito->BeginPass (ncx);  

		// Renderização efetiva dos vértices
		desenharObjeto(g_objeto3d, &g_props); 

		// Fim do passo
		g_efeito->EndPass ();

	} // endfor

	// Fim do efeito
	g_efeito->End ();

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

	if (g_efeito != NULL) g_efeito->Release();

	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

} // Limpar().fim


// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
VOID Renderizar()
{
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;	

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET, verde, 1.0f, 0);

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
	// Dados para a configuração da matriz de visualização
	// Aonde está a câmera? - posição da câmera
	D3DXVECTOR3 cam_pos (0.0f, 0.0f, 5.0f);   
	// Para aonde a câmera está apontada ou olhando? Alvo da câmera
	D3DXVECTOR3 cam_alvo (0.0f, 0.0f, 0);   
	// A câmera está de cabeça pra baixo? - orientação da câmera
	D3DXVECTOR3 cam_vetorcima (0.0f, 1.0f, 0.0f);   

	// Configura a matriz de visão
	D3DXMatrixLookAtLH( &g_mtxVisao, &cam_pos, &cam_alvo, &cam_vetorcima ); 	 

	// ***************************************************************************
	// Argumentos de configuração da matriz de projeção

	// Pega o tamanho da área cliente
	RECT area_cliente;
	GetWindowRect (hJanela, &area_cliente);
	g_xtela = area_cliente.right;
	g_ytela = area_cliente.bottom ;	

	// aspecto dos gráficos 
	float aspecto = (float)  g_xtela / g_ytela; 

	// campo de visão
	float campo_g_mtxVisao = D3DX_PI / 4; 
	// Trapézio de visualização da câmera ( Frustrum )
	float corte_perto = 1.0f; 
	float corte_longe = 1000.0f; 

	// Configura a matriz de projeção
	D3DXMatrixPerspectiveFovLH( &g_mtxProj, campo_g_mtxVisao, aspecto, 
		corte_perto, corte_longe);  

} // inicializar_Camera().fim
// [---
void inicializarEfeito() 
{
	// Nome do arquivo de efeito
	char fx_arquivo[] = "\\gameprog\\gdkmedia\\shader\\mesh_simples.fx";

	// Flag de configuração
	DWORD create_flags = D3DXSHADER_DEBUG;

	// Buffer para receber informação em caso de erro
	ID3DXBuffer* txtErro = NULL;

	// Gera o efeito a partir do arquivo carregado
	g_hr = D3DXCreateEffectFromFile( g_device, fx_arquivo, 
		0, 0, create_flags, 0, &g_efeito, &txtErro);

	if (FAILED(g_hr))
	{
		MessageBox(NULL, "falha: D3DXCreateEffectFromFile()", 
			"inicializarEfeito", MB_OK); 
		MessageBox(NULL, (char*) txtErro->GetBufferPointer(), 
			"inicializarEfeito", MB_OK); 			
		txtErro->Release ();
		return;
	} // endif

	// Seleciona a técnica de renderização
	D3DXHANDLE htech_MovimentoCor;
	htech_MovimentoCor = g_efeito->GetTechniqueByName ("MovimentoCor");
	g_efeito->SetTechnique(htech_MovimentoCor);

	// Libera o buffer de erros
	if (txtErro != NULL) txtErro->Release();

} // inicializarEfeito().fim
// ---]
﻿//-----------------------------------------------------------------------------
// Projeto: prj_HLSL02 - arquivo: entrada.cpp
// Esta  aplicação  ilustra  como renderizar um mesh
// iluminado utilizando hlsl. By www.gameprog.com.br
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
              
// alça da janela  
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
	const char janelaTitulo[] = "prj_HLSL02";
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
