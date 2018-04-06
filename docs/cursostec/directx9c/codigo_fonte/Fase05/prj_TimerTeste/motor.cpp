// -----------------------------------------------------------------------------
// Projeto: prj_TimerTeste - Arquivo: motor.cpp
// Esta aplicação mostra como utilizar o timer de alta precisão
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "motor.h"
#include <stdio.h>
#include <mmsystem.h>

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Localização do código do timer de alta precisão
// mmsystem.h - winmm.lib
#pragma comment ( lib, "winmm.lib")

// Desliga aviso de função de string antiquada
#pragma warning (disable: 4996)

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
// Preparação para o timer
// ----------------------------------------------------------------------------
// Taxa de microticks entre dois frames
float	g_deltaTempo	    = 0.0f;

// Taxa de contagens por segundo
__int64 g_cntsPerSec		= 0ULL;

// Fator de conversão segundo por contagens
float	g_secsPerCnt		= 0.0f;

// Flag de mudança de timer
bool bHardwareTimer = true;

// Representação símbólica do jogador
char* smove_esquerda = "<(-:";
char* smove_direita = ":-)>";
char* sjogador;

// Controle de movimentação
int xcol = 0;
int ylin = 240;
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
	sjogador = smove_direita;
	
	// Verifica a frequência do contador do relógio do hardware
	QueryPerformanceFrequency( (LARGE_INTEGER*) &g_cntsPerSec );
    
	// Obtém-se aqui um fator para traduzir a marca do relógio para 
	// uma expressão em segundos. 
	g_secsPerCnt = 1.0f / (float) g_cntsPerSec;

	return S_OK;
} // initGfx().fim
// ---]

// [--- $mostrarTempo() - Indicadores de performance da aplicação#
// Mostra os indicadores de performance da aplicação
void mostrarTempo(void)
{
	
	// Buffers para preparar exibição de informações
	static char  info[128];	
	static char deltainfo[128] = "g_deltaTempo: 0.10000 microtick";
		
	// Taxa de milessegundos por frame
	static float msFrame = 0.0f;

	// Taxa de frames por segundo
	static float fps = 0.0f;

	// Contador de frames
	static float nFrames = 0.0f;

	// Tempo decorrido
	static float tempoDecorrido = 0.0f;

	// Marca atual do relógio do hardware
	static __int64 tempoAtual = 0;

	// Marca anterior do relógio do hardware
	static __int64 tempoAnterior = 0;		
	
	// Verifica a marca atual do relógio do hardware
	QueryPerformanceCounter(( LARGE_INTEGER* )  &tempoAtual ) ;	
	
	// Verifica a diferença entre o tempo atual e o anterior
	// e transforma o valor em termos de segundos 
	if ( tempoAnterior == 0ULL ) tempoAnterior = tempoAtual;
	g_deltaTempo = (tempoAtual - tempoAnterior) * g_secsPerCnt;	
	
	// Depois de calculado g_deltaTempo seria conveniente aqui
	// chamar as funções que atualizam e desenham a cena utilizando
	// esta marca de tempo como referência para avançar seus processos.
	
	// Incrementa o contador de frames
	nFrames += 1.0f;

	// Acumula o tempo decorrido
	tempoDecorrido += g_deltaTempo;

	// Passou-se um segundo? Calculamos a taxa de frames uma vez
	// a cada segundo. Perceba que o tempo entre frames pode variar
	// então essa taxa é uma média por segundo
	if( tempoDecorrido >= 1.0f )
	{
		
		// Frames por segundo (fps) = nFrames / tempoDecorrido
		// fps = nFrames (nFrames contados no segundo)
		fps = nFrames;
		
		// Tempo médio em milesegundos que o frame levou para ser renderizado
		msFrame = 1000.0f / fps;
		
		// Resseta a variável do tempo decorrido para preparar para o cálculo
		// das taxas para o próximo segundo.
		tempoDecorrido = 0.0f;
		nFrames   = 0.0f;		
	}
	
	// Preparação para a próximo frame
	// O tempoAtual se torna o tempoAnterior para o próximo frame
	tempoAnterior = tempoAtual;

	// Exibe as informações
	sprintf(info, "Milessegundos por frame: %f ( ms )", msFrame);	
	mostrarTexto (10, 10, info);

	sprintf(info, "Frames por segundo: %f ( fps ) ", fps);
	mostrarTexto (10, 40, info);	

	if (tempoDecorrido == 0.0f)
	sprintf(deltainfo, "g_deltaTempo: %f microtick", g_deltaTempo);
	mostrarTexto (10, 70, deltainfo);

} // mostrarTempo().fim
// ---]

// [--- $mostrarTempoEx() - Versão alternativa com timeGetTime()#
// Mostra os indicadores de performance da aplicação
void mostrarTempoEx(void)
{
	
	// Buffers para preparar exibição de informações
	static char  info[128];	
	static char deltainfo[128] = "g_deltaTempo: 0.10000 microtick";
		
	// Taxa de milessegundos por frame
	static float msFrame = 0.0f;

	// Taxa de frames por segundo
	static float fps = 0.0f;

	// Contador de frames
	static float nFrames = 0.0f;

	// Tempo decorrido
	static float tempoDecorrido = 0.0f;

	// Marca atual do relógio do hardware
	static DWORD tempoAtual = 0;

	// Marca anterior do relógio do hardware
	static DWORD tempoAnterior = 0;		
	
	// Verifica a marca atual do relógio do hardware
	tempoAtual = timeGetTime();
	
	// Verifica a diferença entre o tempo atual e o anterior
	// e transforma o valor em termos de segundos 
	if (tempoAnterior == 0) tempoAnterior = tempoAtual;
	g_deltaTempo = ((float) tempoAtual - tempoAnterior) / 1000.0f;	
	
	// Depois de calculado g_deltaTempo seria conveniente aqui
	// chamar as funções que atualizam e desenham a cena utilizando
	// esta marca de tempo como referência para avançar seus processos.
	
	// Incrementa o contador de frames
	nFrames += 1.0f;

	// Acumula o tempo decorrido
	tempoDecorrido += g_deltaTempo;

	// Passou-se um segundo? Calculamos a taxa de frames uma vez
	// a cada segundo. Perceba que o tempo entre frames pode variar
	// então essa taxa é uma média por segundo
	if( tempoDecorrido >= 1.0f )
	{
		
		// Frames por segundo (fps) = nFrames / tempoDecorrido
		// fps = nFrames (nFrames contados no segundo)
		fps = nFrames;
		
		// Tempo médio em milesegundos que o frame levou para ser renderizado
		msFrame = 1000.0f / fps;
		
		// Resseta a variável do tempo decorrido para preparar para o cálculo
		// das taxas para o próximo segundo.
		tempoDecorrido = 0.0f;
		nFrames   = 0.0f;		
	}
	
	// Preparação para a próximo frame
	// O tempoAtual se torna o tempoAnterior para o próximo frame
	tempoAnterior = tempoAtual;

	// Exibe as informações de performance da aplicação
	sprintf(info, "Milessegundos por frame: %f (ms) - timeGetTime()", msFrame);	
	mostrarTexto (10, 10, info);

	sprintf(info, "Frames por segundo: %f ( fps ) ", fps);
	mostrarTexto (10, 40, info);	

	if (tempoDecorrido == 0.0f)
	sprintf(deltainfo, "g_deltaTempo: %f microtick", g_deltaTempo);
	mostrarTexto (10, 70, deltainfo);

} // mostrarTempoEx().fim
// ---]

// [--- $mostrarMensagemTemporizada() - Mensagens temporizadas#
void mostrarMensagemTemporizada()
{
	
	// controle local de tempo decorrido
	static float tempoDecorrido = 0.0f;
	
	// Controle de mudança de mensagem no intervalo [0, 3]
	static int dx = 0;	
	
	// Acumulação do tempo decorrido
	tempoDecorrido += g_deltaTempo;

	// Gerando um valor aleatório no intervalo de 0 à 3
	dx = ( (int) tempoDecorrido) % 3;

	// Bloco de mensagens para bHardwareTimer = true
	static char* mensagens[] = {
		"Testando QueryPerformanceCounter()",
		"Produzido por Gameprog",
		"Visite www.gameprog.com.br"};

	// Bloco de mensagens para bHardwareTimer = false
	static char* mensagens_ex[] = {
		"Testando timeGetTime()",
		"Produzido por Gameprog",
		"Visite www.gameprog.com.br"};	

	// Mostra mensagem adequada de acordo com o tipo de timer selecionado
	if (bHardwareTimer)
	mostrarTexto(100,280, mensagens[dx]);
	else
	mostrarTexto(100,280, mensagens_ex[dx]);


} // mostrarMensagemTemporizada().fim
// ---]

// [--- $atualizaMovimento() - Atualização de movimento do 'jogador'#
void atualizaMovimento()
{

	// direção: 1 (direita) -1 (esquerda)
	static int direcao = 1;	
	
	// controle local de tempo decorrido
	static float tempoDecorrido = 0.0f;

	// controle de deslocamento do jogador
	static int dx = 0;

	// controle de velocidade do jogador
	static float velocidade = 100.0f;
	
	// acumulação do tempo decorrido
	tempoDecorrido += g_deltaTempo;

	// cálculo de um valor para dx no intervalo [0, 640]
	dx = ((int) (tempoDecorrido * velocidade)) % 640;
	
	// move jogador para direita se direção = 1
	if (direcao == 1)	
	{	
	xcol = dx;
	sjogador = smove_direita;
	} // endif
	
	// move jogador para a esquerda se direção = -1
	else
	{
	xcol = 640 - dx;
	sjogador = smove_esquerda;
	} // end else

	// Inverte direção no encontro dos limites do intervalo
	if (xcol >= 640 || xcol <= 0) direcao = direcao * -1;	

} // atualizaMovimento().fim
// ---]


// inicializarTexto() - Inicialização da interface de texto
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


// mostrarTexto(x, y, txt) - Exibição de texto na coordenada 2d indicada
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

// [--- $Renderizar() - Renderização da cena#
VOID Renderizar()
{
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;
	
	// Cor de fundo da janela
	const D3DCOLOR branco = D3DCOLOR_XRGB( 255, 255, 255 );

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET, branco,	1.0f, 0);

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
		// <b>
		// Atualiza movimento do jogador
		atualizaMovimento();
		
		// Desenha o jogador na posição dada por (xcol, ylin)
		mostrarTexto (xcol, ylin, sjogador);

		// Mostra uma mensagem temporizada
		mostrarMensagemTemporizada();

		// Mostra as informações sobre o tempo
		if ( bHardwareTimer == true ) mostrarTempo();
		if ( bHardwareTimer == false ) mostrarTempoEx();

		// </b>		
		// Finalizando a cena
		g_device->EndScene();

	} // endif

	g_device->Present( NULL, NULL, NULL, NULL );

} // Renderizar().fim
// ---]

// Tratamento das mensagens da janela
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

		// Inverte o tipo de timer na barra de espaços
		if (wParam == VK_SPACE) 
			bHardwareTimer = !bHardwareTimer;

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
// fim do arquivo: motor.cpp