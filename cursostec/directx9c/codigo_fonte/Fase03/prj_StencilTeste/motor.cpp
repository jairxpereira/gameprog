// -------------------------------------------------------------------
// Projeto: prj_StencilTeste - Arquivo: motor.cpp
// Esta aplicação mostra um exemplo simples de uso do stencil
// Produzido por www.gameprog.com.br
// -------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include "motor.h"
#include <stdio.h>

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Variáveis globais
// Representa o dispositivo Direct3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;

// Textura do quad
IDirect3DTexture9*		g_Textura = NULL;

// Matrizes de configuração da câmera
D3DXMATRIX g_mtxMundo; 
D3DXMATRIX g_mtxVisao; 
D3DXMATRIX g_mtxProj; 

// Material para o objeto 3d
D3DMATERIAL9 g_material;

// Recipiente de cor, rotação e posição do objeto
Propriedades3d g_props;

// Constante para cores com rgba expressado como float's
D3DCOLORVALUE cvBranco   = { 1.0f, 1.0f, 1.0f, 1.0f }; 

// Constante para cores com rgba expresso como dword
const DWORD dwBranco = 0xFFFFFFFF;

// Ponteiro para uma fonte do directx
ID3DXFont* gdxFonte = NULL; 

// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

// Tamanho da janela 
extern int g_xtela;
extern int g_ytela;

// handle de acesso à janela
extern HWND hJanela;

// Definição do formato de vértice utilizado por esta aplicação
#define CustomVertex_PositionTextured_Format ( D3DFVF_XYZ | D3DFVF_TEX1 )


// Estrutura do vértice customizado
struct CustomVertex_PositionTextured
{
	// Posição do vértice
	float x, y, z;

	// Coordenada da textura
	float tu, tv;	

	// Construtor default
	CustomVertex_PositionTextured() {}

	CustomVertex_PositionTextured( float _x, float _y, float _z, TexCoord texcoord)
	{		
		// Configura posição
		x = _x;
		y = _y;
		z = _z;

		// Configura textura
		tu = texcoord.tu;
		tv = texcoord.tv;
	}

}; // fim da estrutura CustomVertex_PositionTextured

// Memória pas os vértices
CustomVertex_PositionTextured g_Vertices01[4]; 

// Buffer de índices - indica a ordem de conexão dos vértices
WORD g_Indices[6] = {  0,1,2,   2,3,0 }; 

// [--- $initGfx() - Inicialização do motor gráfico#
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
	pps.AutoDepthStencilFormat = D3DFMT_D24S8;

	pps.MultiSampleType            = D3DMULTISAMPLE_NONE;
	pps.MultiSampleQuality         = 0;

	// Esse método transfere rapidamente o backbuffer para a tela imediata
	pps.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// Esse formato vai permitir o uso de alpha blending
	pps.BackBufferFormat = D3DFMT_A8R8G8B8;	
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

	// Monta o quad
	montar_Geometria();	

	// Inicializa a textura
	inicializar_Textura();

	// Inicializa a câmera
	inicializar_Camera();	  

	// Configura estados da cena
	configurar_cenaEstados();	

	// Inicialização do texto
	inicializarTexto();

    // Configuração inicial de cor e rotação do quad
	g_props.cor = cvBranco;	
	g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);

	return S_OK;
} // initGfx().fim
// ---]


void mostrarTexto(int x, int y, char* texto) 
{
  // Retorne se não houver fonte inicializada
  if(gdxFonte == NULL) return; 

  // Cor de fundo da janela
  D3DCOLOR azul = D3DCOLOR_XRGB(0, 0, 255);  

  RECT area_limite; 

  SetRect( &area_limite, x, y, g_xtela, g_ytela );  

  gdxFonte->DrawText( NULL, texto, -1, &area_limite, 0,  azul );  
} // mostrarTexto(); 


// [--- $desligar_backbuffer() - Desligando a renderização no backbuffer#
void desligar_backbuffer(void)
{

// Desliga a renderização no backbuffer
g_device->SetRenderState(D3DRS_ZWRITEENABLE, false);
g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
g_device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
g_device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

} // desligar_backbuffer().fim
// ---]

// [--- $ligar_backbuffer() - Ligando a renderização no backbuffer#
void ligar_backbuffer(void)
{
// Habilita a renderização no backbuffer
g_device->SetRenderState(D3DRS_ZWRITEENABLE, true);
g_device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
} // ligar_backbuffer().fim
// ---]


// [--- $configurar_stencil() - configuração do stencil#
void configurar_stencil(void)
{

// Habilita o stencil	
g_device->SetRenderState(D3DRS_STENCILENABLE, true);

// Garante que tudo vai ser sempre renderizado
g_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);

// Configuração das mascaras para um valor neutro
g_device->SetRenderState(D3DRS_STENCILMASK, 0xffffffff);
g_device->SetRenderState(D3DRS_STENCILWRITEMASK, 0xffffffff);

// O valor de referência é configurado como 'um' que vai indicar
// que o pixel deve ser renderizado
g_device->SetRenderState(D3DRS_STENCILREF, 0x1);

// Se o teste de profundidade falhar o valor no stencil permanece
g_device->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);

// Se o teste de stencil falhar o valor no stencil permanece
g_device->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);

// Se o teste de stencil passar, o valor de referência é jogador
// no stencil para marcar o pixel que vai ser desenhado
g_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

} // configurar_stencil().fim
// ---]

// [--- $marcar_stencil()- Marcação do stencil da área renderizável#
void marcar_stencil(void)
{
mostrarTexto (40, 40, "GAMEPROG");	
g_props.pos = D3DXVECTOR3 ( 0.25f, 2.0f, -1.0f);	
desenhar_Quad(&g_props);
} // marcar_stencil()
// ---]

// [--- $gerarDelta()- Geração de valor baseado no tempo decorrido#
float gerarDelta(void)
{
// Temporizador para animação
static float offset = 0.0f;
static float delta_offset = 0.01f;
static UINT temporizador = 0;

temporizador = clock() / 500 ;
if ( temporizador % 1 == 0) offset += delta_offset;	
if ( offset >= 3.2f ) delta_offset = delta_offset * -1.0f;
if ( offset <= -1.2f ) delta_offset = delta_offset * -1.0f;
return offset;
} // gerarDelta().fim
// ---]

void montar_Geometria(void)
{

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

	// Configuração normal dos vértices
	g_Vertices01[0] = CustomVertex_PositionTextured( 2.20f,  1.50f,  zpos, cimaEsq);
	g_Vertices01[1] = CustomVertex_PositionTextured( -2.20f, 1.50f,  zpos, cimaDir);
	g_Vertices01[2] = CustomVertex_PositionTextured( -2.20f, -1.50f, zpos, baixoDir);
	g_Vertices01[3] = CustomVertex_PositionTextured( 2.20f, -1.50f,  zpos, baixoEsq);

} //  montar_Geometria().fim

// [--- $renderizar_Geometria() - Renderização da geometria#
void renderizar_Geometria()
{
	
	// Desliga a renderização no backbuffer
	desligar_backbuffer();

	// Configura o stencil para renderizar tudo e na renderização
	// assinalar 'um' em cada entrada do stencil para cada pixel
	// do próximo objeto a ser renderizado.
	configurar_stencil();	

	// Renderiza no stencil para marcá-lo
	marcar_stencil();
	
	// Liga a renderização no backbuffer
	ligar_backbuffer();

	// --------------- Renderização do quad ------------------------
	// Desenha o quad aonde o quad-stencil foi renderizado
	g_device->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);
    g_device->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);

	// Gera um movimento para o quad
	static float dx = 0.0f;
	dx = gerarDelta();

	// Renderiza o quad na posição determinada
	g_props.pos = D3DXVECTOR3 ( 0.0f, dx, 0.0f);
	desenhar_Quad(&g_props);			

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

	// Limpa os ponteiros
	g_Direct3d	= NULL;
	g_device		= NULL;
	g_Textura		= NULL;

} // Limpar().fim

// [--- $Renderizar() - Renderização da cena#
// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
VOID Renderizar()
{
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;	

	// Limpa o backbuffer com uma cor branca, o buffer de profundidade com
	// o valor 1.0f e o stencil com o valor zero (0).
	g_device->Clear( 0, NULL, 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL, 
		dwBranco, 1.0f, 0);

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
// ---]

void inicializar_Textura(void)
{
	g_hr = D3DXCreateTextureFromFile (g_device, 
		"\\gameprog\\gdkmedia\\bitmap\\textura2x2.bmp", 
		&g_Textura);

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

	// Configura modo de textura
	g_device->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_device->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
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


void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor ) 
{
	// Limpa a estrutura
	ZeroMemory( mtl, sizeof(D3DMATERIAL9)  );  

	// Configura cor ambiente e difusa
	mtl->Ambient =  cvCor; 
	mtl->Diffuse =  cvCor; 

} // criarMaterial().fim


void configurar_cenaEstados(void) 
{

// Configura luz ambiente
g_device->SetRenderState (D3DRS_LIGHTING, true ); 
g_device->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(200,200,200) );

} // configurar_cenaEstados().fim

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
		D3DFMT_INDEX16, &g_Vertices01, nPasso);

} // desenhar_Quad()


void inicializarTexto() 
{

  // Altura
  int  nAltura = 96; 

  // Largura
  UINT nLargura = 0; 

  // Peso ( weight )
  UINT nPeso = FW_BOLD; 

  // Nível de mipmap - 0: mipmap automático
  UINT nMipmap = 0; 

  // Efeito itálico
  bool bItalico = false; 

  // Conjunto de caracteres (charset)
  DWORD nCharset = DEFAULT_CHARSET; 

  // Precisão (OutputPrecision)
  DWORD nPrecisao = OUT_DEFAULT_PRECIS; 

  // Qualidade
  DWORD nQualidade = DEFAULT_QUALITY; 

  // Pitch e família
  DWORD nFamilia = DEFAULT_PITCH | FF_DONTCARE; 

  // Nome da fonte
  char* sFonte = "Arial"; 

  g_hr = D3DXCreateFont( g_device, nAltura, nLargura, nPeso, nMipmap, bItalico, 
    nCharset, nPrecisao, nQualidade, nFamilia, sFonte, &gdxFonte );  

  if(FAILED (g_hr) ) 
    MessageBox(NULL, "Texto: falha na inicialização", "inicializarTexto()", MB_OK);   

} // inicializarTexto()
// fim do arquivo: motor.cpp