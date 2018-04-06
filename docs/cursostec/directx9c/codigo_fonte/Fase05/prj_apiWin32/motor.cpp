// -----------------------------------------------------------------------------
// Projeto: prj_apiWin32 - arquivo: motor.cpp
// Esta aplicação mostra como manipular mouse e teclado
// utilizando a api nativa do Windows. 
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "motor.h"

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Variáveis globais
// Representa o dispositivo D3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9       *g_device = NULL;

// Ponteiro para uma fonte do directx
ID3DXFont							 *gdxFonte = NULL;

// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

extern int g_xtela;
extern int g_ytela;
extern HWND hJanela;

// [--- $Aspectos globais - Arquivo: motor.cpp#
// Representação símbólica do jogador
char* smove_esquerda = "<(-:";
char* smove_direita = ":-)>";
char* sjogador;

// Controle de movimentação
int xcol = 320;
int ylin = 240;
int nVelocidade = 2;
// ---]
// [--- $Inicialização do motor gráfico#
// initGfx() - Inicializa o Direct3D
HRESULT initGfx( HWND hJanela )
{
	// Cria o objeto D3D que é necessário para criar o dispositivo gráfico
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

	// Faz inicialização da interface de texto
	inicializarTexto();
	
	// Define forma do jogador
	sjogador = smove_esquerda;

	// Configura a posição do jogador
	setJogadorPos(320, 240);

	return S_OK;
} // initGfx().fim
// ---]

void inicializarTexto()
{

	// Altura
	int  nAltura = 24;

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

	if ( FAILED (g_hr) ) 
		MessageBox ( NULL, "Texto: falha na inicialização", "inicializarTexto()", MB_OK);

} // inicializarTexto()

void mostrarTexto(int x, int y, char* texto)
{  
	// Retorne se não houver fonte inicializada
	if ( gdxFonte == NULL ) return;

	// Cor de fundo da janela
	D3DCOLOR azul = D3DCOLOR_XRGB(0, 0, 255);

	// Configura a área limite
	RECT area_limite;		
	SetRect( &area_limite, x, y, g_xtela, g_ytela );	

	// Desenha o texto
	gdxFonte->DrawText( NULL, texto, -1, &area_limite, 0,  azul );   

} // mostrarTexto();
// Limpar() -  Libera todos os objetos previamente inicializados
// -----------------------------------------------------------------------------
VOID Limpar()
{

	// Libera objeto de mostrar texto
	if( gdxFonte != NULL) gdxFonte->Release();	

	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

} // Limpar().fim
// [--- $Renderização da cena#
// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
VOID Renderizar()
{
	// verificar teclado
	tratarTeclado();

	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;

	// Cor de fundo da janela
	const D3DCOLOR branco = D3DCOLOR_XRGB( 255, 255, 255 );

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET, branco,	1.0f, 0);

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
		// Desenha o jogador na posição dada por (xcol, ylin)
		mostrarTexto (xcol, ylin, sjogador);
		
		// Desenha mensagens
		mostrarTexto (10, 10, "Setas\\Mouse: movimentação");
		mostrarTexto (10, 50, "R ou Botão direito: Resseta posição");
		
		// Finalizando a cena
		g_device->EndScene();
	} // endif

	g_device->Present( NULL, NULL, NULL, NULL );
} // Renderizar().fim
// ---]
// [--- $Tratamento do teclado#
void tratarTeclado(void)
{
	// Declara uma variável para verificar movimento
	static int movOcorrido = 0;

	// Configura como zero (0)
	movOcorrido = 0;

	// Declara variáveis de estados das setas
	int seta_direita, seta_esquerda, seta_cima, seta_baixo;
	seta_direita  = 0;
	seta_esquerda = 0;
	seta_cima = 0;
	seta_baixo = 0;	
	
	// Verifica as setas pressionadas
	if( GetAsyncKeyState(VK_LEFT) & 0x8000f )seta_esquerda = 1;
	if( GetAsyncKeyState(VK_RIGHT) & 0x8000f )seta_direita = 1;
	if( GetAsyncKeyState(VK_UP) & 0x8000f )seta_cima = 1;
	if( GetAsyncKeyState(VK_DOWN) & 0x8000f )seta_baixo = 1;

	// Tratamento da seta esquerda
	if( seta_esquerda )
	{
		xcol = xcol - nVelocidade;
		sjogador = smove_esquerda;
	} // endif seta_esquerda
	
	// Tratamento da seta direita
		if( seta_direita )
	{
		xcol = xcol + nVelocidade;
		sjogador = smove_direita;
	} // endif seta_direita
	
		// Tratamento da seta cima \ seta baixo
		if( seta_cima)ylin = ylin - nVelocidade;
		if( seta_baixo ) ylin = ylin + nVelocidade;

	// Reseta posição do jogador
	if( GetAsyncKeyState('R') & 0x8000f )
		setJogadorPos(320, 240);

	// Esconde ou Mostra o cursor
	if( GetAsyncKeyState('E') & 0x8000f )	ShowCursor(false);
	if( GetAsyncKeyState('M') & 0x8000f )	ShowCursor(true);		
	
	// Atualiza posição do mouse em caso de movimento ocorrido
	movOcorrido = seta_cima + seta_baixo + seta_esquerda + seta_direita;
	if (movOcorrido)
	{
	POINT pt;
	pt.x = xcol - 20;
	pt.y = ylin - 20;
	ClientToScreen(hJanela, &pt);
	SetCursorPos (pt.x, pt.y);
	} // endif movimento ocorrido

} // tratarTeclado().fim
// ---]
// [--- $Tratamento do mouse#
void tratarMouse (UINT mensagem, WPARAM wParam, LPARAM lParam)
{	
	// Pega coordenada do mouse
	int xmouse = LOWORD (lParam);
	int ymouse = HIWORD (lParam);

	// trata as mensagens de mouse
	switch (mensagem)                 
	{	

		case WM_LBUTTONDOWN:		
		setJogadorPos(10, 100);
		break;
	
		case WM_RBUTTONDOWN:		
		setJogadorPos(320, 240);
		break;

		case WM_MOUSEMOVE:
		xcol = xmouse + 20;
		ylin = ymouse + 20;
		break;	

	} // endswitch
}
// ---]
// [--- $Tratamento das mensagens da janela#
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

	case WM_RBUTTONDOWN:	
	case WM_LBUTTONDOWN:
	case WM_MOUSEMOVE:
		tratarMouse (mensagem, wParam, lParam);
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
// [--- $Configuração da posição do jogador#
void setJogadorPos( int xpos, int ypos)
{
		// Variáveis de apoio: (pt.x, pt.y)
	  POINT pt; 
		
	  // Posiciona o mouse convertendo coordenada de janela
		// para coordenada de tela
		pt.x = xpos;
		pt.y = ypos;
		ClientToScreen (hJanela, &pt);
		SetCursorPos(pt.x, pt.y );

		// Recupera a posição do mouse
		GetCursorPos (&pt);

		// Converte coordenada de tela para coordenada de janela
		ScreenToClient (hJanela, &pt);

		// Configura posição do jogador
		xcol = pt.x + 20;
		ylin = pt.y + 20;

} // setJogadorPos().fim
// ---]