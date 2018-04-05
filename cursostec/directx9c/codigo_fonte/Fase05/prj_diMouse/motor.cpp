//------------------------------------------------------
// Projeto: prj_diMouse - arquivo: motor.cpp
// Esta aplicação mostra como utilizar o mouse via 
// DirectInput. Produzido por www.gameprog.com.br
//------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "motor.h"
#include <dinput.h>

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// [--- $Aspectos globais: arquivo: motor.cpp#
// Bibliotecas do DirectInput
#pragma comment ( lib, "dinput8.lib")
#pragma comment ( lib, "dxguid.lib" )

// Ponteiro para o objeto DirectInput
IDirectInput8 *g_DirectInput = NULL; 

// Ponteiro para o dispositivo de teclado
IDirectInputDevice8  *g_mouse = NULL; 

// Texto para coletar e mostrar informação sobre o mouse
char g_text[128] = "\0"; 

// Alça e dimensões da janela
extern HWND hJanela;
extern int g_xtela;
extern int g_ytela;

// Represeñtação simbólica do jogador
char* smove_esquerda = "<(-:";
char* smove_direita = ":-)>";
char* sjogador;

// Controle de movimento
int xcol = 320;
int ylin = 240;
int nVelocidade = 2;
// ---]
// Variáveis globais
// Representa o dispositivo D3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9       *g_device = NULL;

// Ponteiro para uma fonte do directx
ID3DXFont							 *gdxFonte = NULL;

// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

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
// <b>
	// Define forma do jogador
	sjogador = smove_esquerda;

	// Reset posição do jogador
	setJogadorPos(320, 240);
	
	// Inicializa DirectInput e o dispositivo de mouse depois
	inicializar_DirectInput();
	inicializar_Mouse();
// </b>

	return S_OK;
} // initGfx().fim
// ---]
// [--- $Inicialização do DirectInput#
// inicializar_DirectInput() - Cria o objeto DirectInput
bool inicializar_DirectInput() 
{ 

	// Criação do objeto DirectInput
	g_hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (void**) &g_DirectInput, NULL); 

	if FAILED(g_hr) 
	{
		MessageBox (NULL, "DirectInput: falha na criação", 
			"inicializar_DirectInput()", MB_OK);		
		return false;     
	} // endif

	return true;

} // inicializar_DirectInput().fim
// ---]
// [--- $Inicialização do mouse#
// inicializar_Mouse() - Essa função inicializa o mouse
bool inicializar_Mouse() 
{    
	// Criação do ponteiro para uma interface IDirectInputDevice8
	g_hr = g_DirectInput->CreateDevice(GUID_SysMouse, &g_mouse, NULL);     

	if FAILED(g_hr) 
	{ 
		MessageBox (NULL, "g_DirectInput->CreateDevice() falhou.", 
			"inicializar_Mouse()", MB_OK);  
		limpar_DirectInput(); 
		return false; 
	} // endif

	// Configuração do formato de dados do dispositivo com uma constante
	// pré-definida de mouse do DirectInput ( c_dfDIMouse2 )
	g_hr = g_mouse->SetDataFormat(&c_dfDIMouse2); 

	if FAILED(g_hr) 
	{ 
		MessageBox (NULL, "g_mouse->SetDataFormat() falhou.", 
			"inicializar_Mouse()", MB_OK);
		limpar_DirectInput(); 
		return false; 
	} // endif

	// Configuração do nível de cooperação 
	DWORD cooperacao_flags = DISCL_BACKGROUND | DISCL_NONEXCLUSIVE;
	g_hr = g_mouse->SetCooperativeLevel( hJanela, cooperacao_flags);		

	if FAILED(g_hr) 
	{ 
		MessageBox (NULL, "g_mouse->SetCooperativeLevel() falhou.", 
			"inicializar_Teclado()", MB_OK);  
		limpar_DirectInput(); 
		return false; 
	} // endif

	// Pega acesso ao dispositivo de entrada. 
	g_hr = g_mouse->Acquire(); 
	if FAILED(g_hr) 
	{ 
		limpar_DirectInput(); 
		return false; 
	} // endif

	return TRUE; 
} // inicializar_Mouse().fim
// ---]
// [--- $Tratamento do mouse via DirectInput#
HRESULT tratarMouse( void )
{
	
	// Resultado das operações
	HRESULT       hr;

	// estrutura para coletar status do mouse
	DIMOUSESTATE2 stsMouse;     

	// Retorne se não houver um mouse ok
	if( NULL == g_mouse )  return S_OK;

	// Limpe a estrutura e colete o estado do mouse
	ZeroMemory( &stsMouse, sizeof(stsMouse) );
	hr = g_mouse->GetDeviceState( sizeof(DIMOUSESTATE2), &stsMouse );
	if( FAILED(hr) ) 
	{
		// o directInput poderia estar informando de que o fluxo de
		// entrada foi interrompido. Não estamos rastreando qualquer
		// estado entre as pesquisas (polls), então nós não temos
		// nenhum procedimento especial de reconfiguração que precisa
		// ser feito. Simplesmente re-adquirimos e tentamos de novo.

		// Se o dispositivo de entrada foi perdido então
		// continue tentando a reaquisição.
		hr = g_mouse->Acquire();
		while( hr == DIERR_INPUTLOST ) hr = g_mouse->Acquire();

		// Retorne se houver algum erro
		// hr pode ser DIERR_OTHERAPPHASPRIO e outros erros que podem
		// ocorrer quando a aplicação está minimizada ou em processo de 
		// transição. Então, tente mais tarde... 
		if( hr == DIERR_OTHERAPPHASPRIO || hr == DIERR_NOTACQUIRED ) 
				return S_OK; 

	} // endif 

	// Prepara a string de informação do estado do mouse
	sprintf( g_text, ("(X=% 3.3d, Y=% 3.3d, Z=% 3.3d) B0=%c B1=%c B2=%c "),
		stsMouse.lX, stsMouse.lY, stsMouse.lZ,
		(stsMouse.rgbButtons[0] & 0x80) ? '1' : '0',
		(stsMouse.rgbButtons[1] & 0x80) ? '1' : '0',
		(stsMouse.rgbButtons[2] & 0x80) ? '1' : '0');

	// Testa botão esquerdo
	if (stsMouse.rgbButtons[0] & 0x80)	setJogadorPos(10, 100);
	
	// Testa botão direito
	if (stsMouse.rgbButtons[1] & 0x80)	setJogadorPos(320, 240);	

	// Declara variáveis de estados das setas
	int seta_direita, seta_esquerda, seta_cima, seta_baixo;
	seta_direita  = 0;
	seta_esquerda = 0;
	seta_cima = 0;
	seta_baixo = 0;	

	// Verifica a movimentação dos eixos e atualiza os flags de movimento
	if( stsMouse.lX < 0) seta_esquerda = 1;
	if( stsMouse.lX > 0) seta_direita  = 1;
	if( stsMouse.lY < 0) seta_cima     = 1;
	if( stsMouse.lY > 0) seta_baixo    = 1;

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
	if( seta_cima  ) ylin = ylin - nVelocidade;
	if( seta_baixo ) ylin = ylin + nVelocidade;	  

	return S_OK;
} // tratarMouse().fim
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

	// Limpe os objetos do DirectInput
	limpar_DirectInput();

} // Limpar().fim
// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
// [--- $Renderização da cena#
VOID Renderizar()
{

	// Verifica e trata teclado
	tratarTeclado();

	// Verifica e trata mouse
	tratarMouse();

	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;

	// Cor de fundo da janela
	const D3DCOLOR branco = D3DCOLOR_XRGB( 255, 255, 255 );

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( NULL, NULL, D3DCLEAR_TARGET, branco, 
		1.0f, 0);

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
// <b>	
		// Desenha jogador
		mostrarTexto (xcol, ylin, sjogador);

		// Desenha mensagens
		mostrarTexto (10, 10, "Mouse: movimentação");
		mostrarTexto (10, 50, "R ou Botão direito: Resseta posição");
		
		// Mostra informações sobre o mouse
		mostrarTexto (10, 90, g_text);
// </b>

		// Finalizando a cena
		g_device->EndScene();
	} // endif

	g_device->Present( NULL, NULL, NULL, NULL );
} // Renderizar().fim
// ---]
void tratarTeclado(void)
{

	// Reseta posição do jogador
	if( GetAsyncKeyState('R') & 0x8000f )
		setJogadorPos(320, 240);

	// Esconde ou Mostra o cursor
	if( GetAsyncKeyState('E') & 0x8000f )	ShowCursor(false);
	if( GetAsyncKeyState('M') & 0x8000f )	ShowCursor(true);			

} // tratarTeclado().fim

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

void setJogadorPos( int xpos, int ypos)
{
	// Variáveis de apoio: ( pt.x, pt.y )
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


// [--- $Limpeza dos objetos do DirectInput#
// limpar_DirectInput() - Libera os objetos do DirectInput
void limpar_DirectInput() 
{ 
	if (g_DirectInput) 
	{ 
		if (g_mouse) 
		{ 
			// Liberação do mouse
			// Chame primeiro unacquire() antes de chamar Release(). 
			g_mouse->Unacquire(); 
			g_mouse->Release();
			g_mouse = NULL; 
		} // endif (g_mouse)

		// Liberação do objeto DirectInput
		g_DirectInput->Release();
		g_DirectInput = NULL; 
	} // endif (g_DirectInput)
} // limpar_DirectInput().fim
// ---]
