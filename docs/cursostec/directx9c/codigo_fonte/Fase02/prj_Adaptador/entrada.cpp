// [---
// Projeto: prj_Adaptador - Arquivo: entrada.cpp
// Essa aplicação exemplifica como investigar as capacidades
// do adaptador gráfico. By www.gameprog.com.br
#include <windows.h>
#include <wincon.h>
#include <stdio.h>
#include <stdlib.h>
#include "d3d9.h"
#include "d3dx9.h"

// Bibliotecas do directx
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")

// Exibe informações gerais do adaptador gráfico
void adaptador_exibirInfoGeral(void);

// Exibe modo de vídeo corrente
void adaptador_exibirVideoCorrente(void);

// Exibe a lista de modos de vídeo disponíveis para o formato 
// apresentado
void adaptador_exibirListaVideoOk(void);

// Exibe algumas capacidades do dispositivo gráfico
void mostrarcaps(void);

// Verifica a possibilidade de uma configuração específica do dispositivo
void verificar_dispositivo(void);

// Faz a configuração inicial da janela
void config_Janela(void);

// Pausa para leitura da tela
void esperar(void);

// Variáveis globais
// Representa o dispositivo D3D
LPDIRECT3D9             g_Direct3d = NULL; 


// Variáveis para coletar o tamanho da resolução corrente
UINT g_xtela, g_ytela;

// Formato de vídeo
D3DFORMAT g_formato;

// Adaptador default(0)
UINT adaptador_default = D3DADAPTER_DEFAULT;

// Coleta de informação de erro do directx
HRESULT g_hr;
// ---]
// [---
int main(void)
{
	// Cria o objeto Direct3D
	g_Direct3d = Direct3DCreate9( D3D_SDK_VERSION );  

	// Verifica se objeto Direct3D foi criado
	if(g_Direct3d == NULL)  
	{
		MessageBox (NULL, 
			"Falha na inialização do Direct3D", "main()", MB_OK);   
		return E_FAIL; 
	} // endif

	// Configura a janela
	config_Janela();

	// Exibe informações gerais do adaptador
	adaptador_exibirInfoGeral();

	// Exibe o modo de vídeo corrente
	adaptador_exibirVideoCorrente();

	// Exibe uma lista de modos de vídeo disponíveis para o formato
	// apresentado.
	adaptador_exibirListaVideoOk();

	// Mostra algumas capacidades do dispositivo
	mostrarcaps();

	// Testa uma possibilidade de configuração para o dispositivo
	verificar_dispositivo();

	// Finaliza a aplicação
	esperar();
	g_Direct3d->Release();

} // main().fim
// ---]
// [---
void adaptador_exibirInfoGeral(void)
{

	// Estrutura para coletar informações gerais do adaptador gráfico
	D3DADAPTER_IDENTIFIER9 placaVideo;

	// Coleta informações sobre o adaptador
	g_hr = g_Direct3d->GetAdapterIdentifier( adaptador_default, 
		0, &placaVideo);

	// Espaços em branco para manter a boa estética do console
	printf("\n");

	// Mostra descrição e o arquivo de driver de vídeo
	printf(" %s \n", placaVideo.Description);
	printf(" %s \n", placaVideo.Driver);	

	// Verifica a quantidade de adaptadores no sistema
	UINT nAdaptadores = 0;
	nAdaptadores = g_Direct3d->GetAdapterCount();
	printf (" Número de adaptadores de vídeo: %i \n", nAdaptadores);

} // adaptador_exibirInfoGeral().fim
// ---]
// [---
void adaptador_exibirVideoCorrente(void)
{
	// Estrutura para a coleta de informações sobre o modo de vídeo
	// corrente
	D3DDISPLAYMODE video; 

	// Coleta informações sobre o modo de vídeo
	g_Direct3d->GetAdapterDisplayMode (adaptador_default, &video);  

	// Transfere essas informações para as variáveis
	g_xtela = video.Width; 
	g_ytela = video.Height; 
	g_formato = video.Format;

	// Exibe as informações
	printf(" Modo de video corrente: (%i, %i) Formato: %i \n", 
		g_xtela, g_ytela, g_formato);

} //  adaptador_exibirVideoCorrente().fim
// ---]
// [---
void adaptador_exibirListaVideoOk(void)
{
	// Variável para guardar a quantidade de modos de vídeo
	// disponíveis dentro de um formato
	UINT nQtd = 0;

	// Estrutura com informações básica do modo de vídeo
	D3DDISPLAYMODE video; 

	// Obtém a quantidade de modos de vídeo no formato apresentado
	nQtd = g_Direct3d->GetAdapterModeCount( adaptador_default, g_formato);

	// Esta linha exibe o valor numérico do formato apresentado.
	printf(" \n\n Modos de video disponivel no formato %i \n", g_formato);

	// Mostra as informações dos modos de vídeo disponíveis no formato
	for (UINT ncx=0; ncx < nQtd; ncx++)
	{
		// Obtém informação do modo de vídeo apontado por ncx
		g_hr = g_Direct3d->EnumAdapterModes(adaptador_default, g_formato, ncx, &video);

		//Transfere as informações para as variáveis
		g_xtela = video.Width; 
		g_ytela = video.Height; 
		g_formato = video.Format;

		// Exibe a informação
		printf(" %i x %i \n", g_xtela, g_ytela);
	} // endfor	

} // adaptador_exibirListaVideoOk().fim
// ---]
// [---
void verificar_dispositivo(void)
{
	// Resultado da vericação
	bool resultado = false;

	// Argumentos de trabalho do método CheckDeviceType()
	D3DDEVTYPE	tipo_hardware			= D3DDEVTYPE_HAL;
	D3DFORMAT		videoFormato			= D3DFMT_X8R8G8B8;
	D3DFORMAT		backbufferFormato = videoFormato;

	// Vai ter janela? sim (true) ou não(false).
	bool				telaCheia					= false;

	// Verifica se a configuração passada é possível 
	g_hr = g_Direct3d->CheckDeviceType( adaptador_default,  tipo_hardware, 
		videoFormato, backbufferFormato, telaCheia );

	// Verifica o resultado retornado
	if ( SUCCEEDED(g_hr) ) resultado = true;
	if ( FAILED   (g_hr) ) resultado = false;

	// Exibe resultado
	printf("\n");
	if (resultado) 
		printf(" Aplicação em tela cheia Ok para o formato X8R8G8B8 no hardware!");
	if (!resultado) 
		printf(" Configuração impraticável \n");

	return;

} // verificar_dispositivo().fim
// ---]
// [---
void mostrarcaps(void)
{
	printf("\n");

	// Estrutura que alista as capacidades possíveis de um
	// adaptador gráfico.
	D3DCAPS9 caps;

	// Limpa a estrutura
	ZeroMemory ( &caps, sizeof (D3DCAPS9));

	// Obtém as capacidades do adaptador gráfico
	g_hr = g_Direct3d->GetDeviceCaps ( adaptador_default, D3DDEVTYPE_HAL, &caps);

	// Verifica se houve falha no processo...
	if( FAILED(g_hr))  
	{
		MessageBox (NULL, "Falha no processo", "mostrarcaps()", MB_OK);   
		return;
	} // endif

	// Mostra a versão do pixelshader e do vertexshader
	printf (" VertexShaderVersion: %X \n", caps.VertexShaderVersion);
	printf (" PixelShaderVersion : %X \n", caps.PixelShaderVersion);

	// Quantidade máxima de luzes ativas simultaneamente
	printf (" MaxActiveLights    : %i \n", caps.MaxActiveLights);
	printf("\n");

	// Mostra algumas capacidades sobre linhas
	DWORD linecaps = caps.LineCaps;
	printf(" LineCaps    %X: \n", linecaps);
	if ( (linecaps & D3DLINECAPS_ANTIALIAS) > 0 ) printf(" D3DLINECAPS_ANTIALIAS Ok \n");
	if ( (linecaps & D3DLINECAPS_BLEND ) > 0 )    printf(" D3DLINECAPS_BLEND Ok \n");
	if ( (linecaps & D3DLINECAPS_TEXTURE ) > 0 )  printf(" D3DLINECAPS_TEXTURE Ok \n");

} // mostrarcaps().fim
// ---]
// [---
void esperar(void)
{
	// Aguarda o pressionamento da tecla ENTER para continuar
	printf("\n\n");
	printf(" Pressione ENTER para continuar \n");
	getchar();
} // esperar().fim
// ---]
// [---
void config_Janela(void)
{	
	// Configura cor e título da janela
	system("color f1");	
	SetConsoleTitle ("prj_Adaptador");

	// Obtém o handle de escrita do console.
	HANDLE hJanela = GetStdHandle(STD_OUTPUT_HANDLE);	

	// Configura tamanho do buffer do console
	COORD bufferTam = {80, 90};	
	SetConsoleScreenBufferSize( hJanela, bufferTam);

	// Configura tamanho da janela 
	SMALL_RECT janelaTam = {0, 0, 79, 29};	
	SetConsoleWindowInfo(hJanela, TRUE, &janelaTam);

	// Permite a boa acentuação em português.
	SetConsoleOutputCP(1252);
	printf("\n");

} // config_Janela().fim
// ---]