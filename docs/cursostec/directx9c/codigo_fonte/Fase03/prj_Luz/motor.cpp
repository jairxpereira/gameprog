// -----------------------------------------------------------------------------
// Projeto: prj_Luz - arquivo: motor.cpp
// Esta aplicação ilustra como iluminar um triângulo
// By www.gameprog.com.br
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

// Variáveis para controlar a rotação do triângulo
float g_Angulo = 0.0f;
float nVelocidade = 0.1f;

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
// <b>
// [---
// Constante para cores 
const DWORD azul			= 0xFF0000FF;

// Constante para cores com rgba expressado como float's
const D3DCOLORVALUE cvBranco		= { 1.0f, 1.0f, 1.0f, 1.0f };
const D3DCOLORVALUE cvVermelho	= { 1.0f, 0.0f, 0.0f, 1.0f };
const D3DCOLORVALUE cvAmarelo		= { 1.0f, 1.0f, 0.0f, 1.0f };
const D3DCOLORVALUE cvVerde			= { 0.0f, 1.0f, 0.0f, 1.0f };

// Variável para o material
D3DMATERIAL9 g_mtlVermelho;

// Indicação de entrada de luz
D3DXVECTOR3 g_normal;

// Definição do formato de vértice utilizado pela aplicação
#define CustomVertex_PositionNormal_Format ( D3DFVF_XYZ | D3DFVF_NORMAL )
// </b>

// Definição da estrutura de vértice customizado
struct CustomVertex_PositionNormal
{	
	float x, y, z;
	float nx, ny, nz;

	// Construtor default
	CustomVertex_PositionNormal() {}

	// Construtor com inicialização
	CustomVertex_PositionNormal( float _x, float _y, float _z, 
		float _nx, float _ny, float _nz)
	{
		// entrada da posição
		x = _x;
		y = _y;
		z = _z;

		// entrada da Normal
		nx = _nx;
		ny = _ny;
		nz = _nz;				
	
	} // fim do construtor

}; // fim da estrutura CustomVertex_PositionNormal

// Declaração dos vértices para o triângulo
CustomVertex_PositionNormal g_Vertices[3];
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

	// Monta as formas geométricas
	montar_Geometria();
	
	// Faz a configuração inicial da câmera
	inicializar_Camera();	
	// <b>	
	// Cria um material vermelho para o triângulo
	criarMaterial(&g_mtlVermelho, cvVermelho);

	// Configura e coloca uma luz na cena
	D3DXVECTOR3 pos(2.0f, 1.0f, -4.0f); 
	colocar_PointLight (pos, cvBranco);
	// </b>
	return S_OK;
} // initGfx().fim
// ---]
// [---
void colocar_PointLight(D3DXVECTOR3 pos, D3DCOLORVALUE cvCor)
{
  // Declara a estrutura
  D3DLIGHT9 luz;

	// Limpa a estrutura
	ZeroMemory( &luz, sizeof(D3DLIGHT9) );
  
	// Configura tipo
	luz.Type = D3DLIGHT_POINT;
  
	// Configura cor
	luz.Diffuse = cvCor;
	    
  // Configura posição
  luz.Position = pos;
  
	// Configura fator de atenuação
	luz.Attenuation0 = 0.2f;
  
	// Configura faixa de alcance
	luz.Range = 100.0f;

  // Instalação e acionamento da luz no dispositivo renderizador
  g_device->SetLight( 0, &luz );
  g_device->LightEnable( 0, TRUE ); 

} // colocar_PointLight().fim
// ---]
// [---
void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor )
{
	// Limpa a estrutura
	ZeroMemory( mtl, sizeof(D3DMATERIAL9) );

	// Configura cor ambiente e difusa
	mtl->Ambient =  cvCor;
	mtl->Diffuse =  cvCor;

} // criarMaterial().fim
// ---]

// [---
void ajuda_visual(D3DXVECTOR3 pos, D3DCOLORVALUE cvCor)
{

	// Variável de controle do objeto 3d
	ID3DXMesh* obj3d;

	// Matriz mundo para posicionamento do objeto 3d
	D3DXMATRIX  mtxMundo;
	D3DXMatrixIdentity( &mtxMundo );

	// Configuração do material do objeto 3d
	D3DMATERIAL9 mtl;
	criarMaterial(&mtl, cvCor);

	// Cria o objeto 3d
	float nRaio = 0.2f;
	UINT nSegs = 16;
	D3DXCreateSphere(g_device, nRaio, nSegs, nSegs, &obj3d, 0);
	
	// Configura posição do objeto no mundo 3d
	D3DXMatrixTranslation(&mtxMundo,  pos.x, pos.y, pos.z);
	g_device->SetTransform(D3DTS_WORLD, &mtxMundo);
	
	// Configura material
	g_device->SetMaterial (&mtl);
	
	// Renderiza o objeto
	obj3d->DrawSubset(0);

	// Libera o objeto utilizado
	obj3d->Release();

} // void ajuda_visual().fim
// ---]
// [--- 
void calcularNormal(D3DXVECTOR3* p0, D3DXVECTOR3* p1,
D3DXVECTOR3* p2, D3DXVECTOR3* pSaida)
{
D3DXVECTOR3 u = *p1 - *p0;
D3DXVECTOR3 v = *p2 - *p0;
D3DXVec3Cross(pSaida, &u, &v);
D3DXVec3Normalize(pSaida, pSaida);
} // calcularNormal().fim
// ---]
// [---
void configurar_cenaEstados(void)
{
 	// Mostra a parte interna do polígono   
	g_device->SetRenderState (D3DRS_CULLMODE, D3DCULL_NONE); 

	// Habilita iluminação
	g_device->SetRenderState (D3DRS_LIGHTING, true );

	// Aplica o material no dispositivo renderizador
	g_device->SetMaterial ( &g_mtlVermelho);

	// Corrige as normais
	g_device->SetRenderState(D3DRS_NORMALIZENORMALS, true);

	// Desabilita cálculo de luz especular
	g_device->SetRenderState(D3DRS_SPECULARENABLE, false);
} // configurar_cenaEstados().fim
// ---]

// [---
void montar_Geometria(void)
{
	// Posicionamento de profundidade
	float zpos = 0.0f;

	// Faz o cálculo da normal para configurar os vértices
	calcularNormal (&D3DXVECTOR3(0.0f, 1.0f, zpos), 
		&D3DXVECTOR3(-1.0f, -1.0f, zpos), 
		&D3DXVECTOR3(1.0f, -1.0f, zpos), &g_normal);		

	// p0 - primeiro vértice
	g_Vertices[0] = CustomVertex_PositionNormal( 0.0f,  1.0f, zpos, 
		g_normal.x , g_normal.y, g_normal.z);

	// p1 - segundo vértice
	g_Vertices[1] = CustomVertex_PositionNormal( -1.0f, -1.0f, zpos,
			g_normal.x , g_normal.y, g_normal.z);

	// p2 - terceiro vértice
	g_Vertices[2] = CustomVertex_PositionNormal( 1.0f, -1.0f, zpos, 
			g_normal.x , g_normal.y, g_normal.z); 		

} //  montar_Geometria().fim
// ---]
// [---
void renderizar_Geometria()
{
	// Configura formato de vértice no dispositivo
	g_device->SetFVF( CustomVertex_PositionNormal_Format );

	// Quantidade de primitivas possíveis de acordo com o uso de vértices
	UINT nContagem = 1;		 

	// Tamanho do passo para achar o próximo vértice
	UINT nPasso =  sizeof(CustomVertex_PositionNormal);		 

	// Desenha forma geométrica
	g_device->DrawPrimitiveUP( D3DPT_TRIANGLELIST, nContagem, &g_Vertices, nPasso);

	// Mostra localização aproximada da luz
	ajuda_visual( D3DXVECTOR3(1.5f, 0.5f, -3.5f), cvAmarelo);
	
	// Mostra posição da normal
	ajuda_visual( g_normal, cvVerde);	

} // renderizar_Geometria().fim
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


void atualizar_Camera(void)
{
	// Variável para receber o ângulo final
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

// [---
VOID Renderizar()
{
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;	

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET, azul, 1.0f, 0);
	// <b>
	// Configure estados de renderização
	configurar_cenaEstados();	
	// </b>
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


