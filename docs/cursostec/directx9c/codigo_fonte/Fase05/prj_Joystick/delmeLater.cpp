// [--- $Aspectos globais: arquivo: motor.h#
//-------------------------------------------------------------------
// Projeto: prj_Joystick - Arquivo: motor.h
// Esta aplicação mostra como utilizar o Joystick
// via DirectInput. Produzido por www.gameprog.com.br
//-------------------------------------------------------------------
#ifndef motor_h
 #define motor_h

#include <stdio.h>

// Desativa aviso de função string insegura
#pragma warning ( disable:4996 )

// ********** Classe para gravar um relatório ***********************
class Relatorio
{
public:
	FILE *m_arquivo;

// Construtor	
Relatorio() 
	{ 
		m_arquivo = NULL; 
	} // fim do construtor

~Relatorio() 
	{ 
	if (m_arquivo != NULL) fclose (m_arquivo); 	
	} // fim do construtor

	void Inicializar()
	{
	  if (m_arquivo == NULL)
		m_arquivo = fopen("joystick.txt", "wt");	
	} // abrirArquivo().fim

	void Gravar(char *info)
	{
	if (m_arquivo != NULL)
	fprintf(m_arquivo, "%s\n", info);
	} // gravarDados().fim

	void Fechar()
	{ 
		if (m_arquivo != NULL) fclose (m_arquivo); 
		m_arquivo = NULL;
	} // fecharArquivo().fim
}; // fim da classe Relatorio
// ********** Classe para gravar um relatório ***********************

// Esta função inicializa o Direct3D
HRESULT initGfx (HWND hJanela);

// Essa função libera os objetos utilizados
void Limpar();

// Essa função desenha a cena
void Renderizar();

// Esta função inicializa o objeto para mostrar texto
void inicializarTexto(); 

// Configura posição do jogador
void setJogadorPos( int xpos, int ypos);

// Esta função mostra um texto na coordenada (x, y) da janela
void mostrarTexto( int x, int y, char* texto); 

// Essa função inicializa o objeto DirectInput
bool inicializar_DirectInput();

// Mostra informações de estados do joystick
void mostrar_joyinfo();

// Essa função trata a entrada via joystick
HRESULT tratar_Joystick(void);

// Libera os objetos do DirectInput
void limpar_DirectInput();

//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
			WPARAM wParam, LPARAM lParam);
#endif
// ---]

﻿//-------------------------------------------------------------------
// Projeto: prj_Joystick - arquivo: motor.cpp
// Esta aplicação mostra como utilizar o Joystick
// via DirectInput. Produzido por www.gameprog.com.br
//-------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "motor.h"
#include <dinput.h>
#include "joystick.h"

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Bibliotecas do DirectInput
#pragma comment ( lib, "dinput8.lib")
#pragma comment ( lib, "dxguid.lib" )
// [--- $Aspectos globais: arquivo: motor.cpp#
// Ponteiro para o objeto DirectInput
IDirectInput8 *g_DirectInput = NULL; 

// Ponteiro para o dispositivo de entrada joystick
IDirectInputDevice8  *g_joystick = NULL; 

// Objeto para gravar informações em arquivo texto
Relatorio g_relatorio;

// Estrutura para coletar os estados do joystick
extern DIJOYSTATE2 g_jsStatus; 
// ---]

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
	
	// Define forma do jogador
	sjogador = smove_esquerda;

	// Reset posição do jogador
	setJogadorPos(320, 240);
// <b>
	// Inicia o objeto para salvar informações no disco
	g_relatorio = Relatorio();
	g_relatorio.Inicializar();

	// Inicializa DirectInput e o dispositivo de joystick depois
		inicializar_DirectInput();
	inicializar_Joystick();
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
// [--- $Tratamento do joystick via DirectInput#
HRESULT tratar_Joystick( void )
{

	// Resultado das operações
	HRESULT       hr;

	// Retorne se não houver um joystick ok
	if( NULL == g_joystick )  return S_OK;

	// Limpe a estrutura e colete o estado do joystick 
	ZeroMemory( &g_jsStatus, sizeof(g_jsStatus) );	

	// Verifique o estado atual do dispositivo
	hr = g_joystick->Poll();

	if( FAILED(hr) ) 
	{
		// o directInput poderia estar informando de que o fluxo de
		// entrada foi interrompido. Não estamos rastreando qualquer
		// estado entre as pesquisas (polls), então nós não temos
		// nenhum procedimento especial de reconfiguração que precisa
		// ser feito. Simplesmente re-adquirimos e tentamos de novo.

		// Se o dispositivo de entrada foi perdido então
		// continue tentando a reaquisição.
		hr = g_joystick->Acquire();
		while( hr == DIERR_INPUTLOST ) hr = g_joystick->Acquire();

		// Retorne se houver algum erro
		// hr pode ser DIERR_OTHERAPPHASPRIO e outros erros que podem
		// ocorrer quando a aplicação está minimizada ou em processo de 
		// transição. Então, tente mais tarde... 
		if( hr == DIERR_OTHERAPPHASPRIO || hr == DIERR_NOTACQUIRED ) 
			return S_OK; 

	} // endif 

	// Obtém os estados do joystick
	hr = g_joystick->GetDeviceState( sizeof(DIJOYSTATE2), &g_jsStatus );

	// Retorne imediamente em caso de falha
	if ( FAILED (hr) ) return hr;	

	// Testa botão 01
	if (g_jsStatus.rgbButtons[0] & 0x80)	setJogadorPos(10, 100);

	// Testa botão 02
	if (g_jsStatus.rgbButtons[1] & 0x80)	setJogadorPos(320, 240);	

	// Declara variáveis de estados das setas
	int seta_direita, seta_esquerda, seta_cima, seta_baixo;
	seta_direita  = 0;
	seta_esquerda = 0;
	seta_cima			= 0;
	seta_baixo		= 0;	

	// Verifica a movimentação dos eixos e atualiza os flags de movimento
	if( g_jsStatus.lX == -1000) seta_esquerda = 1;
	if( g_jsStatus.lX ==  1000) seta_direita  = 1;
	if( g_jsStatus.lY == -1000) seta_cima     = 1;
	if( g_jsStatus.lY ==  1000) seta_baixo    = 1;

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
} // tratar_Joystick().fim
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

	// Feche o arquivo de relatório
	g_relatorio.Fechar();

} // Limpar().fim
// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
// [--- $Renderização da cena#
VOID Renderizar()
{

	// Verifica e trata joystick
	tratar_Joystick();

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
		// Mostra o jogador
		mostrarTexto (xcol, ylin, sjogador);

		// Mostra as mensagens
		mostrarTexto (10, 10, "Joystick: movimentação");
		mostrarTexto (10, 50, "Botão 1 ou 2: Resseta posição");

		// Mostra informações sobre o joystick
		mostrar_joyinfo();

// </b>

		// Finalizando a cena
		g_device->EndScene();
	} // endif

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

void setJogadorPos( int xpos, int ypos)
{
	// Variáveis de apoio: ( pt.x, pt.y )
	POINT pt; 

	// Posiciona o ponteiro do mouse convertendo coordenada 
	// de janela para coordenada de tela
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


// [--- $Limpeza do DirectInput#
// limpar_DirectInput() - Libera os objetos do DirectInput
void limpar_DirectInput() 
{ 
	if (g_DirectInput) 
	{ 
		if (g_joystick) 
		{ 
			// Liberação do joystick
			// Chame primeiro unacquire() antes de chamar Release(). 
			g_joystick->Unacquire(); 
			g_joystick->Release();
			g_joystick = NULL; 
		} // endif (g_joystick)

		// Liberação do objeto DirectInput
		g_DirectInput->Release();
		g_DirectInput = NULL; 
	} // endif (g_DirectInput)
} // limpar_DirectInput().fim
// ---]
// [--- $Informações dos estados do joystick#
void mostrar_joyinfo(void)
{
	// Tamanho do buffer de texto
	#define tam_buffer 64

	// Controle de texto
	// (coluna, linha) e espaço de separação entre linhas
	int linha, coluna, spc_linha;
	linha			= 80;
	coluna		= 10;
	spc_linha = 30;

	// Informação de eixos de posição
	char pos_eixo[tam_buffer]				= "\0"; 
	sprintf( pos_eixo, "xyz position: %ld %ld %d", 
		g_jsStatus.lX, g_jsStatus.lY, g_jsStatus.lZ);
	mostrarTexto(coluna, linha, pos_eixo);
	linha += spc_linha;

	// Informação de eixos de rotação
	char rot_eixo[tam_buffer]				= "\0"; 
	sprintf( rot_eixo, "xyz rotation: %ld %ld %d", 
		g_jsStatus.lRx, g_jsStatus.lRy, g_jsStatus.lRz);
	mostrarTexto(coluna, linha, rot_eixo);
	linha += spc_linha;

	// Informação sobre slider (alavanca que escorrega)
	char info_slider[tam_buffer]		= "\0";
	sprintf( info_slider, "rglSlider: %ld %d", 
		g_jsStatus.rglSlider[0], g_jsStatus.rglSlider[1]);
	mostrarTexto(coluna, linha, info_slider);
	linha += spc_linha;

	// Informação sobre pov's ( point of view ou pontos de vista )
	char info_pov[tam_buffer]				= "\0";
	sprintf( info_pov, "rgdwPOV: %ld %ld %ld %ld", 
		g_jsStatus.rgdwPOV[0], g_jsStatus.rgdwPOV[1], 
		g_jsStatus.rgdwPOV[2], g_jsStatus.rgdwPOV[3]);
	mostrarTexto(coluna, linha, info_pov);
	linha += spc_linha;

	// ******************************************************************
	// Coleta e exibição de informação sobre os botões
	char       btnText[128]; 
	char*      str;

	// Preencha o texto com os botões pressionados
	str = btnText;
	for( int nbtn = 0; nbtn < 128; nbtn++ )
	{
		if ( g_jsStatus.rgbButtons[nbtn] & 0x80 )
			str += sprintf( str, "%02d ", nbtn );
	} // endfor
	
	// Termine a string
	*str = 0;   

	// Mostre a string de botões
	mostrarTexto(coluna, linha, "Botões: ");
	mostrarTexto(coluna + 80, linha, btnText);
	linha += spc_linha;

} // mostrar_joyinfo().fim
// ---]
﻿
// [--- $Aspectos globais: arquivo: joystick.h# tpc++
//-------------------------------------------------------------------
// Projeto: prj_Joystick - arquivo: joystick.h
// Esta aplicação mostra como utilizar o Joystick
// via DirectInput. Produzido por www.gameprog.com.br
//-------------------------------------------------------------------
#ifndef joystick_h
 #define joystick_h

#include <dinput.h>

// Alista ou enumera os joysticks disponíveis
BOOL CALLBACK alistarJoysticks( 
															 const DIDEVICEINSTANCE *diControle, 
															 void* pContext );

// Inicializa o joystick
HRESULT inicializar_Joystick( void );


// Alista ou enumera os objetos componentes do joystick localizado
BOOL CALLBACK alistarControleComponentes(
	const DIDEVICEOBJECTINSTANCE *joycomp, void* pContext );

#endif
// ---]

﻿// [--- $Aspectos globais: arquivo: joystick.cpp#
//-------------------------------------------------------------------
// Projeto: prj_Joystick - arquivo: joystick.cpp
// Esta aplicação mostra como utilizar o Joystick
// via DirectInput. Produzido por www.gameprog.com.br
//-------------------------------------------------------------------
#include <dinput.h>
#include "joystick.h"
#include "motor.h"

// Handle da janela da aplicação
extern HWND hJanela;

extern Relatorio g_relatorio;

// Ponteiro uma instância do DirectInput
extern IDirectInput8 *g_DirectInput; 

// Ponteiro para o dispositivo de entrada joystick
extern IDirectInputDevice8  *g_joystick; 

// Estrutura de dados
DIJOYSTATE2 g_jsStatus; 
// ---]

// [--- $Inicialização do joystick#
HRESULT inicializar_Joystick( void )
{

	HRESULT     hr;

	// Procura por um joystick que possa ser usado
	if( FAILED( hr = g_DirectInput->EnumDevices( DI8DEVCLASS_GAMECTRL, 
		alistarJoysticks,
		NULL, DIEDFL_ATTACHEDONLY ) ) )
		return hr;

	// Verificação de falha
	if( NULL == g_joystick )
	{
		MessageBox( NULL, "Joystick não encontrado.",  
			"inicializar_Joystick()", 
			MB_ICONERROR | MB_OK );        
		return S_OK;
	}

	// Configuração do formato de dados para um formato pré-definido
	// O formato de dados especifica quais os controles em um dispositivo
	// estamos interessado e como eles deverão ser reportados. O formato
	// aqui indicado avisa ao directInput que vamos o utilizar a estrutura
	// de dados DIJOYSTATE2
	if( FAILED( hr = g_joystick->SetDataFormat( &c_dfDIJoystick2 ) ) )
		return hr;

	// Configuração do modo de cooperação
	if( FAILED( hr = g_joystick->SetCooperativeLevel( hJanela, 
		DISCL_EXCLUSIVE | DISCL_FOREGROUND ) ) )
		return hr;

	// Alistamento dos objetos do joytick. A função callback habilita a
	// aplicação fazer uso dos objetos que são encontrados e configura
	// os valores mínimos e máximos dos eixos descobertos.
	if( FAILED( hr = g_joystick->EnumObjects( alistarControleComponentes, 
		(void*) hJanela, DIDFT_ALL ) ) )
		return hr;

	return S_OK;

} // inicializar_Joystick( ).fim
// ---]
// [--- $Alistamento dos controles espetados no sistema#
//-----------------------------------------------------------------------------
// alistarJoysticks()
// Essa função é chamada para cada joystick localizado. Quando um
// joystick é encontrado é criado uma interface para que ele possa
// ser utilizado.
//-----------------------------------------------------------------------------
BOOL CALLBACK alistarJoysticks( const DIDEVICEINSTANCE *diControle,
															 void* pContext )
{
	// Coleta de resultado das operações  
	HRESULT hr;

	// Obtém uma interface para o joystick localizado
	hr = g_DirectInput->CreateDevice( diControle->guidInstance, &g_joystick, NULL );

	// Se ocorreu falha não podemos utilizar o joytick. Talvez o usuário
	// tenha desconectado ele no meio do alistamento.
	if( FAILED(hr) ) return DIENUM_CONTINUE;

	// Pare o alistamento! Nota: estamos pegando apenas o primeiro joytick
	// encontrado. Você poderia alistar todos os joysticks encontrados e
	// deixar para o usuário a escolha final do controle a ser usado. 
	return DIENUM_STOP;
} // alistarJoysticks().fim
// ---]
// [--- $Alistamento dos componentes espetados no joystick#
//-----------------------------------------------------------------------------
// alistarControleComponentes()
// Esta função alista ou enumera os componentes de um joystick tais
// como eixos, botões, pov's etc. . ., Esta função configura a faixa de    
// valor dos eixos encontrados. Os componentes também são chamados de
// 'objetos do dispositivo'.
//-----------------------------------------------------------------------------
BOOL CALLBACK alistarControleComponentes( const DIDEVICEOBJECTINSTANCE *joycomp,
																				 VOID* pContext )
{  
	// Quantidade de sliders
	static int nSliderCount = 0; 

	// Quantidade de POV's
	static int nPOVCount = 0;  

	// A faixa de alcance é configurada no caso dos eixos encontrados
	if( joycomp->dwType & DIDFT_AXIS )
	{
		DIPROPRANGE diprg; 
		diprg.diph.dwSize       = sizeof(DIPROPRANGE); 
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER); 
		diprg.diph.dwHow        = DIPH_BYID; 

		// Indica o eixo alistado!
		diprg.diph.dwObj        = joycomp->dwType; 

		// Define o valor da faixa de valor dos eixos
		diprg.lMin              = -1000; 
		diprg.lMax              = +1000; 

		// Configura a faixa de valor dos eixos
		if( FAILED( g_joystick->SetProperty( DIPROP_RANGE, &diprg.diph ) ) ) 
			return DIENUM_STOP;

	} // endif(configuração da faixa dos eixos)

	// Grave um relatório para refletir quais objetos ou
	// componentes o joystick suporta
	if (joycomp->guidType == GUID_XAxis)   
		g_relatorio.Gravar ("GUID_XAxis presente");   

	if (joycomp->guidType == GUID_YAxis)   
		g_relatorio.Gravar("GUID_YAxis presente");   

	if (joycomp->guidType == GUID_ZAxis)    
		g_relatorio.Gravar("GUID_ZAxis presente\n");   

	if (joycomp->guidType == GUID_RxAxis)
		g_relatorio.Gravar("GUID_RxAxis presente"); 

	if (joycomp->guidType == GUID_RyAxis)
		g_relatorio.Gravar("GUID_RyAxis presente");   

	if (joycomp->guidType == GUID_RzAxis)
		g_relatorio.Gravar("GUID_RzAxis presente\n");

	// Verifica a presença de sliders
	if (joycomp->guidType == GUID_Slider)
	{
		switch( nSliderCount++ )
		{
		case 0 :
			g_relatorio.Gravar("Slider[0] presente");
			break;
			g_relatorio.Gravar("Slider[1] presente\n");
		case 1 :

			break;
		} // endswitch
	} // endif

	// Verifica a presença de POVs
	if (joycomp->guidType == GUID_POV)
	{
		switch( nPOVCount++ )
		{
		case 0 :
			g_relatorio.Gravar("POV[0] presente");
			break;

		case 1 :
			g_relatorio.Gravar("POV[1] presente");
			break;

		case 2 :
			g_relatorio.Gravar("POV[2] presente");

		case 3 :
			g_relatorio.Gravar("POV[3] presente\n");
			break;
		} // endswitch 
	} // endif

	return DIENUM_CONTINUE;
} // alistarControleComponentes().fim
// ---]﻿
//-------------------------------------------------------------------
// Projeto: prj_Joystick - arquivo: entrada.cpp
// Esta aplicação mostra como utilizar o Joystick
// via DirectInput. Produzido por www.gameprog.com.br
//-------------------------------------------------------------------
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
	const char janelaTitulo[] = "prj_Joystick";
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
