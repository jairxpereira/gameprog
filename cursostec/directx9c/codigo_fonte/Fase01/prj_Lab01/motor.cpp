// -----------------------------------------------------------------------------
// Projeto: prj_Lab01 - arquivo: motor.cpp
// Esta aplicação estabelece um ambiente para testar as
// matrizes de transformações. By www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "motor.h"
#include "resource.h"
#include "stdio.h"

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
// [---

// Matrizes de configuração da câmera
// Matriz de mundo
D3DXMATRIX g_mtxMundo;
// Matriz de visão
D3DXMATRIX g_mtxVisao;
// Matriz de projeção
D3DXMATRIX g_mtxProj;

// ***************************************************************************
// Dados para a configuração da matriz de visualização
// Aonde está a câmera? - posição da câmera
D3DXVECTOR3 cam_pos (0, 0, 5.0f); 
// Para aonde a câmera está apontada ou olhando? Alvo da câmera
D3DXVECTOR3 cam_alvo (0, 0.0f, 0); 
// A câmera está de cabeça pra baixo? - orientação da câmera
D3DXVECTOR3 cam_vetorcima (0, 1.0f, 0); 

// ***************************************************************************
// Argumentos de configuração da matriz de projeção
// aspecto dos gráficos
int g_xtela = 320;
int g_ytela = 240;

float aspecto = (float) g_xtela / g_ytela; 
// campo de visão
float campo_visao = D3DX_PI / 4; 
// Trapézio de visualização da câmera ( Frustrum )
float corte_perto = 1.0f;
float corte_longe = 100.0f;

// Posicionamento da câmera para a matriz de visualização
float xcam_pos = 0.0f;
float ycam_pos = 0.0f;
float zcam_pos = 0.0f;

// Controle de checkbox dos eixos x, y, z
bool g_bX = false;
bool g_bY = false;
bool g_bZ = false;

// Controle de checkbox da matriz de mundo
bool g_bmundoPos = false;
bool g_bmundoRot = false;
bool g_bmundoEsc = false;

// Controle da matriz de visualização das câmeras
bool g_bCamPos = false;
bool g_bCamAlvo = false;
bool g_bVetorCima = false;

// Controle da matriz de projeção
bool g_bCmpVisao   = false;
bool g_bAspecto    = false;
bool g_bCortePerto = false;
bool g_bCorteLonge = false;

// Translação, rotação e escala da matriz de mundo
float g_xmundo_pos = 0.0f;
float g_ymundo_pos = 0.0f;
float g_zmundo_pos = 0.0f;
float g_xmundo_rot = 0.0f;
float g_ymundo_rot = 0.0f;
float g_zmundo_rot = 0.0f;
float g_xmundo_esc = 1.0f;
float g_ymundo_esc = 1.0f;
float g_zmundo_esc = 1.0f;

// Incremento
float g_incr = 0.1f;

// Submatrizes para a construção da matriz de mundo
D3DXMATRIX g_mtxRot, g_mtxPos, g_mtxEsc;

// Tamanho da janela ( entrada.cpp )
extern HWND hJanela;

// Texto para informações
char g_info[nFloatBuffer]= "\0";

// Constante para cores
const DWORD vermelho	= 0xFFFF0000;
const DWORD branco		= 0xFFFFFFFF;
const DWORD verde			= 0xFF00FF00;
const DWORD azul			= 0xFF0000FF;

// Definição do formato de vértice utilizado pela aplicação
#define CustomVertex_PositionColored_Format ( D3DFVF_XYZ | D3DFVF_DIFFUSE )

// Definição da estrutura de vértice customizado
struct CustomVertex_PositionColored
{	
	float x, y, z;
	DWORD cor;

	// Construtor default
	CustomVertex_PositionColored() {}

	// Construtor com inicialização
	CustomVertex_PositionColored( float _x, float _y, float _z, DWORD _cor)
	{
		x = _x;
		y = _y;
		z = _z;		
		cor = _cor;
	} // fim do construtor

}; // fim da estrutura CustomVertex_PositionColored

// Declaração dos vértices para o triângulo
CustomVertex_PositionColored g_Vertices[3];
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
	// <b>
	// Monta as formas geométricas
	montar_Geometria();

	// Faz a configuração inicial da câmera
	inicializar_Camera();	
	// </b>
	return S_OK;
} // initGfx().fim
// ---]
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

	// Configura a matriz de visão
	D3DXMatrixLookAtLH( 
		&g_mtxVisao, 
		&cam_pos, 
		&cam_alvo, 
		&cam_vetorcima );

	// Configura a matriz de visão no dispositivo renderizador
	g_device->SetTransform( D3DTS_VIEW, &g_mtxVisao ); 	

	// Configura a matriz de projeção	
	D3DXMatrixPerspectiveFovLH( &g_mtxProj, campo_visao, aspecto, 
		corte_perto, corte_longe);

	// Configura a matriz de projeção no dispositivo renderizador
	g_device->SetTransform( D3DTS_PROJECTION, &g_mtxProj );

} // inicializar_Camera().fim
// ---]
// [---
void atualizar_Camera(void)
{  	
	
		// Configura a matriz de visão
	D3DXMatrixLookAtLH( &g_mtxVisao, &cam_pos, &cam_alvo, &cam_vetorcima );
		// Configura a matriz de visão no dispositivo renderizador
	g_device->SetTransform( D3DTS_VIEW, &g_mtxVisao );
	
	// Configura rotação, escala e translação para a matriz de mundo
	D3DXMatrixRotationYawPitchRoll ( &g_mtxRot, g_ymundo_rot, g_xmundo_rot, g_zmundo_rot);
	D3DXMatrixScaling (&g_mtxEsc, g_xmundo_esc, g_ymundo_esc, g_zmundo_esc);
	D3DXMatrixTranslation (&g_mtxPos, g_xmundo_pos, g_ymundo_pos, g_zmundo_pos);

	// Combina rotação, escala e translação
	g_mtxMundo = g_mtxRot * g_mtxEsc * g_mtxPos;

	// Atualiza a matriz de mundo no dispositivo
	g_device->SetTransform( D3DTS_WORLD, &g_mtxMundo ); 

		// Configura a matriz de projeção	
	D3DXMatrixPerspectiveFovLH( &g_mtxProj, campo_visao, aspecto, 
		corte_perto, corte_longe);
		// Configura a matriz de projeção no dispositivo renderizador
	g_device->SetTransform( D3DTS_PROJECTION, &g_mtxProj );

} // atualizar_Camera().fim
// ---]
// [---
// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
VOID Renderizar()
{
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;	

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET, branco, 1.0f, 0);

	// Mostra a parte interna do polígono
	// Experimente desativar essa linha com a instrução de comentário      
	g_device->SetRenderState (D3DRS_CULLMODE, D3DCULL_NONE); 

	// Utiliza iluminação default
	// Experimente desativar essa linha com a instrução de comentário
	g_device->SetRenderState (D3DRS_LIGHTING, false );

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
// [---
void montar_Geometria(void)
{
	// Posicionamento de profundidade
	float zpos = 0.0f;

	// p0 - primeiro vértice
	g_Vertices[0] = CustomVertex_PositionColored( 0.0f,  1.0f, zpos, vermelho);

	// p1 - segundo vértice
	g_Vertices[1] = CustomVertex_PositionColored( -1.0f, -1.0f, zpos, verde);

	// p2 - terceiro vértice
	g_Vertices[2] = CustomVertex_PositionColored( 1.0f, -1.0f, zpos, azul); 

} //  montar_Geometria().fim
// ---]
// [---
void renderizar_Geometria()
{
	// Configura formato de vértice no dispositivo
	g_device->SetFVF( CustomVertex_PositionColored_Format );

	// Quantidade de primitivas possíveis de acordo com o uso de vértices
	UINT nContagem = 1;		 

	// Tamanho do passo para achar o próximo vértice
	UINT nPasso =  sizeof(CustomVertex_PositionColored);		 

	// Desenha forma geométrica
	g_device->DrawPrimitiveUP( D3DPT_TRIANGLELIST, nContagem, &g_Vertices, nPasso);

} // renderizar_Geometria().fim
// ---]


// Limpar() -  Libera todos os objetos previamente inicializados
// -----------------------------------------------------------------------------
VOID Limpar()
{		
	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

	// Coloca NULL nos ponteiros
	g_device = NULL;
	g_Direct3d = NULL;

} // Limpar().fim


BOOL CALLBACK processaJanela( HWND hDlgWnd, UINT Message, WPARAM wParam, LPARAM lParam )
{
	// Torna global o handle da janela
	hJanela = hDlgWnd;

	switch(Message)	{

// Inicialização da janela de diálogo
case WM_INITDIALOG:
	{
		on_wmInitDialog ( wParam, lParam );
		return TRUE;
	} // wm_initdialog
	break;

// Refresca a janela em caso de reposicioanmento
case WM_WINDOWPOSCHANGED:
	{
		UpdateWindow (hJanela);
		return true;
	}
	break;

// O coração desta aplicação: a renderização via wm_paint
case WM_PAINT:
	{
		Renderizar();
		InvalidateRect (hJanela, NULL, false);
		Sleep(0);
		return true;
	}
	break;

// Encerramento da aplicação
case WM_CLOSE:
	{
		Limpar();
		ExitProcess(0);
		return true;
	}
	break;			

// Execução dos comandos via botões
case WM_COMMAND:
	{
		on_wmCommand ( wParam, lParam );
		return true;			
	} // wm_command.fim		
	break;

	} // endswitch

	// Retorna falso
	return FALSE;

} // endfunction


void config_inicial_controles()
{	
	
	// Ligue manutenção no eixo z
	SendDlgItemMessage (hJanela, chk_z, BM_SETCHECK, 1, 0);

	// Ligue manutenção na posição da câmera
	SendDlgItemMessage (hJanela, chk_cam_pos, BM_SETCHECK, 1, 0);	
	
} // config_inicial_controles().fim


void incrementar_Variaveis(void)
{

	// Configuração da matriz de mundo
	if (g_bmundoPos == true)
	{
		if (g_bX == true) g_xmundo_pos += g_incr;
		if (g_bY == true) g_ymundo_pos += g_incr;
		if (g_bZ == true) g_zmundo_pos += g_incr;
	} // g_bMundoPos

	if (g_bmundoRot == true)
	{
		if (g_bX == true) g_xmundo_rot += g_incr;
		if (g_bY == true) g_ymundo_rot += g_incr;
		if (g_bZ == true) g_zmundo_rot += g_incr;
	} // g_bMundoRot

	if (g_bmundoEsc == true)
	{
		if (g_bX == true) g_xmundo_esc += g_incr;
		if (g_bY == true) g_ymundo_esc += g_incr;
		if (g_bZ == true) g_zmundo_esc += g_incr;
	} // g_bMundoEsc

	
	
	// ***************************************************************************
	// Configuração da matriz de visualização
		if (g_bCamPos == true)
	{
		if (g_bX == true) cam_pos.x  += g_incr;
		if (g_bY == true) cam_pos.y  += g_incr;
		if (g_bZ == true) cam_pos.z  += g_incr;
	} // g_bCamPos

	if (g_bCamAlvo == true)
	{
		if (g_bX == true)  cam_alvo.x += g_incr;
		if (g_bY == true)  cam_alvo.y += g_incr;
		if (g_bZ == true)  cam_alvo.z  += g_incr;
	} // g_bCamAlvo

	if (g_bVetorCima == true)
	{
		if (g_bX == true) cam_vetorcima.x  += g_incr;
		if (g_bY == true) cam_vetorcima.y  += g_incr;
		if (g_bZ == true) cam_vetorcima.z  += g_incr;
	} // g_bVetorCima


		// ***************************************************************************
	// Configuração da matriz de projeção
	if ( g_bCmpVisao == true )  campo_visao += g_incr;
  if ( g_bAspecto == true ) aspecto += g_incr;
  if ( g_bCortePerto == true ) corte_perto += g_incr;
  if ( g_bCorteLonge == true ) corte_longe += g_incr;


	mostrar_Variaveis();

} // incrementar_Variaveis().fim


void reduzir_Variaveis(void)
{


	// Posicionamento na matriz mundo
	if (g_bmundoPos == true)
	{
		if (g_bX == true) g_xmundo_pos -= g_incr;
		if (g_bY == true) g_ymundo_pos -= g_incr;
		if (g_bZ == true) g_zmundo_pos -= g_incr;
	} // g_bMundoPos

	// Rotação na matriz mundo	
	if (g_bmundoRot == true)
	{
		if (g_bX == true) g_xmundo_rot -= g_incr;
		if (g_bY == true) g_ymundo_rot -= g_incr;
		if (g_bZ == true) g_zmundo_rot -= g_incr;
	} // g_bMundoRot


	// Escala na matriz mundo	
	if (g_bmundoEsc == true)
	{
		if (g_bX == true) g_xmundo_esc -= g_incr;
		if (g_bY == true) g_ymundo_esc -= g_incr;
		if (g_bZ == true) g_zmundo_esc -= g_incr;
	} // g_bMundoEsc


		// ***************************************************************************
	// Configuração da matriz de visualização
		if (g_bCamPos == true)
	{
		if (g_bX == true) cam_pos.x  -= g_incr;
		if (g_bY == true) cam_pos.y  -= g_incr;
		if (g_bZ == true) cam_pos.z  -= g_incr;
	} // g_bCamPos

	if (g_bCamAlvo == true)
	{
		if (g_bX == true)  cam_alvo.x -= g_incr;
		if (g_bY == true)  cam_alvo.y -= g_incr;
		if (g_bZ == true)  cam_alvo.z  -= g_incr;
	} // g_bCamAlvo

	if (g_bVetorCima == true)
	{
		if (g_bX == true) cam_vetorcima.x  -= g_incr;
		if (g_bY == true) cam_vetorcima.y  -= g_incr;
		if (g_bZ == true) cam_vetorcima.z  -= g_incr;
	} // g_bVetorCima

			// ***************************************************************************
	// Configuração da matriz de projeção
	if ( g_bCmpVisao == true )  campo_visao -= g_incr;
  if ( g_bAspecto == true ) aspecto -= g_incr;
  if ( g_bCortePerto == true ) corte_perto -= g_incr;
  if ( g_bCorteLonge == true ) corte_longe -= g_incr;

	mostrar_Variaveis();

} // incrementar_Variaveis().fim

void mostrar_Variaveis(void)
{
	// Mostra a valor das variáveis em seus respectivos
	// textboxes
	setFloatText (txt_xmundopos, g_xmundo_pos);
	setFloatText (txt_ymundopos, g_ymundo_pos);
	setFloatText (txt_zmundopos, g_zmundo_pos);

	setFloatText (txt_xmundorot, g_xmundo_rot);
	setFloatText (txt_ymundorot, g_ymundo_rot);
	setFloatText (txt_zmundorot, g_zmundo_rot);

	setFloatText (txt_xmundoesc, g_xmundo_esc);
	setFloatText (txt_ymundoesc, g_ymundo_esc);
	setFloatText (txt_zmundoesc, g_zmundo_esc);

  setFloatText (txt_xcampos, cam_pos.x );
	setFloatText (txt_ycampos, cam_pos.y );
	setFloatText (txt_zcampos, cam_pos.z );

  setFloatText (txt_xcamalvo, cam_alvo.x );
	setFloatText (txt_ycamalvo, cam_alvo.y );
	setFloatText (txt_zcamalvo, cam_alvo.z );

	setFloatText (txt_xvetorcima, cam_vetorcima.x );
	setFloatText (txt_yvetorcima, cam_vetorcima.y );
	setFloatText (txt_zvetorcima, cam_vetorcima.z );

	setFloatText (txt_cmpvisao, campo_visao );
	setFloatText (txt_corteperto, corte_perto );
	setFloatText (txt_cortelonge, corte_longe );
	setFloatText (txt_aspecto, aspecto );

	UpdateWindow (hJanela);

} // atualizar_Variaveis().fim

void setFloatText (int controle, float nVal)
{
	// Configura o texto da textbox com um float
	sprintf_s(g_info, nFloatBuffer, "%f", nVal);
	char *pInfo = g_info;
	SetDlgItemText (hJanela, controle, pInfo);

} // setFloatText().fim

void verificar_Checkboxes(void)
{
	// Obtém o estado das checkboxes
	g_bX = getCheckboxState (chk_x);
	g_bY = getCheckboxState (chk_y);
	g_bZ = getCheckboxState (chk_z);

	g_bmundoPos = getCheckboxState (chk_mundo_pos);
	g_bmundoRot = getCheckboxState (chk_mundo_rot);
	g_bmundoEsc = getCheckboxState (chk_mundo_esc);

	g_bCamPos = getCheckboxState (chk_cam_pos);
	g_bCamAlvo = getCheckboxState (chk_cam_alvo);
	g_bVetorCima = getCheckboxState (chk_vetorcima);

	g_bCmpVisao    = getCheckboxState (chk_visao);
	g_bCortePerto  = getCheckboxState (chk_corteperto );
	g_bCorteLonge  = getCheckboxState (chk_cortelonge );
	g_bAspecto  = getCheckboxState (chk_aspecto );

} // verificar_Checkbox().fim

bool getCheckboxState (int chk )
{
	// Obtém a configuração da checkbox
	bool sts = false;

	if ( SendDlgItemMessage (hJanela, chk, BM_GETCHECK, 0, 0))
	{
		sts = true;
	}

	else
	{
		sts = false;
	}

	return sts;

} // getCheckboxState().fim

void on_wmInitDialog(  WPARAM wParam, LPARAM lParam )
{
	// Configura os ícones da aplicação
	SendMessage(hJanela, WM_SETICON, ICON_SMALL, (LPARAM)LoadIcon(NULL, IDI_APPLICATION) );
	SendMessage(hJanela, WM_SETICON, ICON_BIG, (LPARAM)LoadIcon(NULL, IDI_APPLICATION ));

	// Configuração inicial dos controles
	config_inicial_controles();

	// Inicializa o motor gráfico
	initGfx(GetDlgItem (hJanela, pic_tela));

	// Exibe as variáveis
	mostrar_Variaveis();

} // on_wmInitDialog().fim

void on_wmCommand (  WPARAM wParam, LPARAM lParam  )
{

	// Obtém os estados das checkboxes
	verificar_Checkboxes();

	// Verifical qual é o comando em wParam
	WORD comando = LOWORD(wParam);	

	// Aumenta ou reduz a variável conforme o botão pressionado
	if  ( comando ==  btn_mais ) incrementar_Variaveis();		
	if  ( comando ==  btn_menos ) reduzir_Variaveis();	
	
	// Resseta as variáveis para valores iniciais
	if  ( comando ==  btn_reset ) reset_Variaveis();

	// Encerramento do programa
	if  (comando ==  btn_sair)	{
		Limpar();
		ExitProcess(0);
	} // endif

} // on_wmCommand().fim

void reset_Variaveis(void)
{
	
	// Configuração da matriz de mundo
	if (g_bmundoPos == true)
	{
		if (g_bX == true) g_xmundo_pos = 0.0f;
		if (g_bY == true) g_ymundo_pos = 0.0f;
		if (g_bZ == true) g_zmundo_pos = 0.0f;
	} // g_bMundoPos

	if (g_bmundoRot == true)
	{
		if (g_bX == true) g_xmundo_rot = 0.0f;
		if (g_bY == true) g_ymundo_rot = 0.0f;
		if (g_bZ == true) g_zmundo_rot = 0.0f;
	} // g_bMundoRot

	if (g_bmundoEsc == true)
	{
		if (g_bX == true) g_xmundo_esc = 1.0f;
		if (g_bY == true) g_ymundo_esc = 1.0f;
		if (g_bZ == true) g_zmundo_esc = 1.0f;
	} // g_bMundoEsc

	
	
	// ***************************************************************************
	// Configuração da matriz de visualização
		if (g_bCamPos == true)
	{
		if (g_bX == true) cam_pos.x  = 0.0f;
		if (g_bY == true) cam_pos.y  = 0.0f;
		if (g_bZ == true) cam_pos.z  = 5.0f;
	} // g_bCamPos

	if (g_bCamAlvo == true)
	{
		if (g_bX == true)  cam_alvo.x = 0.0f;
		if (g_bY == true)  cam_alvo.y = 0.0f;
		if (g_bZ == true)  cam_alvo.z  = 0.0f;
	} // g_bCamAlvo

	if (g_bVetorCima == true)
	{
		if (g_bX == true) cam_vetorcima.x  = 0.0f;
		if (g_bY == true) cam_vetorcima.y  = 1.0f;
		if (g_bZ == true) cam_vetorcima.z  = 0.0f;
	} // g_bVetorCima


		// ***************************************************************************
	// Configuração da matriz de projeção
	if ( g_bCmpVisao == true )  campo_visao  = D3DX_PI / 4; 
  if ( g_bAspecto == true ) aspecto = (float) g_xtela / g_ytela; 
  if ( g_bCortePerto == true ) corte_perto = 1.0f;
  if ( g_bCorteLonge == true ) corte_longe = 100.0f;

	mostrar_Variaveis();

} // reset_Variaveis().fim




