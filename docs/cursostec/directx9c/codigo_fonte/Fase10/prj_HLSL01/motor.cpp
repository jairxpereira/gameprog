// -----------------------------------------------------------------------------
// Projeto: prj_HLSL01 - arquivo: motor.cpp
// Esta aplicação mostra como renderizar um 
// quadrado  colorido  com  HLSL. 
// By www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>
#include "motor.h"

// Variáveis globais
// Representa o dispositivo Direct3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9       *g_device = NULL;

// [---
// Representa o buffer de vértices
IDirect3DVertexBuffer9 *g_vbVertices = NULL;

// Representa o objeto efeito
ID3DXEffect						*g_efeito = NULL;

// Interface para a declaração de vértices
IDirect3DVertexDeclaration9 *g_VertexDeclaration;

// Variáveis para provocar mudanças de cor e movimento
float angulo = 0.01f;
float nMovimento = 0.0f;
float nVelocidade = 0.01f;
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
void DeclararVertices_Auto(void)
{		
	// Declaração coletiva dos elementos
	D3DVERTEXELEMENT9 Elementos[ sizeof(D3DVERTEXELEMENT9) * 2 ]; 

	// Preenche a array dos elementos
	D3DXDeclaratorFromFVF(CustomVertex_PositionOnly_Format, Elementos );

	// Criação da declaração de vértices
	g_hr = g_device->CreateVertexDeclaration(Elementos, 
		&g_VertexDeclaration);

} // DeclararVertices(void);
// ---]

// [---
void DeclararVertices_Manual(void)
{	
	// Argumentos para preenchimento da array D3DVERTEXELEMENT9
	WORD nStream				= 0;
	WORD nDeslocamento	= 0;
	BYTE nTipo					= D3DDECLTYPE_FLOAT3;
	BYTE nMetodo				= D3DDECLMETHOD_DEFAULT;
	BYTE nUso						= D3DDECLUSAGE_POSITION;
	BYTE nIndiceUso			= 0;

	// Declaração do primeiro elemento
	D3DVERTEXELEMENT9 position = {nStream, nDeslocamento, 
	nTipo, nMetodo, nUso, nIndiceUso };

	// Declaração do elemento final
	D3DVERTEXELEMENT9 finalizador = D3DDECL_END();

	// Declaração coletiva dos elementos
	D3DVERTEXELEMENT9 Elementos[] = { position, finalizador };
	
	// Criação da declaração de vértices
	g_hr = g_device->CreateVertexDeclaration(Elementos, 
		&g_VertexDeclaration);

} // DeclararVertices(void);
// ---]
// [---
void inicializarEfeito() 
{
	// Nome do arquivo de efeito
	char fx_arquivo[] = "\\gameprog\\gdkmedia\\shader\\simples.fx";

	// Flag de configuração
	DWORD create_flags = D3DXSHADER_DEBUG;

	// Buffer para receber informação em caso de erro
	ID3DXBuffer *txtErro = NULL;

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
// [---
void atualizarCamera(void)
{
	// Atualiza movimento\cor através da variação de nMovimento
	nMovimento += nVelocidade; 
	if (nMovimento >= 1.0f)  nVelocidade *= -1;
	if (nMovimento <= 0.0f)  nVelocidade *= -1;

	// Atualiza a câmera
	angulo += 0.05f;  
	D3DXMatrixRotationZ (&g_mtxMundo, angulo);
	D3DXMATRIX camera = g_mtxMundo * g_mtxVisao * g_mtxProj;

	// Handle para a variável do shader 'nMovimento'
	D3DXHANDLE hMov = NULL;

	// Handle para a variável do shader 'camera'
	D3DXHANDLE hCam = NULL;

	// Obtém acesso às variáveis do shader
	hMov = g_efeito->GetParameterByName (0, "nMovimento");
	hCam = g_efeito->GetParameterByName (0, "Camera");

	// Atualiza variáveis no shader
	g_efeito->SetValue (hMov, &nMovimento, sizeof(nMovimento) );
	g_efeito->SetValue (hCam, &camera, sizeof(camera) );

} // 	atualizarCamera(void);
// ---]
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

	// Configuração do renderizador a ser criado
	// Adaptador default (0)
	int nAdaptador = D3DADAPTER_DEFAULT;

	// Tipo de dispositivo Hardware ou emulador de referência (software) 
	D3DDEVTYPE dispositivo_tipo = D3DDEVTYPE_HAL;
	// <b>
	// Flags de configuração do dispositivo
	DWORD create_flags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	// </b>
	// Criamos aqui o dispositivo renderizador
	g_hr = g_Direct3d->CreateDevice( nAdaptador, dispositivo_tipo, 
		hJanela, create_flags, &pps, &g_device );

	// Verifica se houve falha no processo
	if( FAILED( g_hr ) ) { 
		MessageBox (NULL, "Falha na criação: g_device", "initGfx()", MB_OK);
		return E_FAIL;
	} // endif
	// <b>
	// Inicializa o vertexbuffer e configura os vértices
	inicializar_Buffers();
	montar_Geometria();

	// Elabora a declaração dos vértices
	DeclararVertices_Manual();

	// Inicializa um objeto efeito
	inicializarEfeito();

	// Inicializa e atualiza a configuração de câmera
	inicializar_Camera();
	atualizarCamera();
	// </b>

	return S_OK;
} // initGfx().fim
// ---]
// [---
void inicializar_Buffers(void) 
{
	// Quantidade de vértices do vertexbuffer
	UINT		nVertices	= 6;

	// Tamanho do vertexbuffer em bytes
	UINT		vbTamanho	= sizeof(CustomVertex_PositionOnly) * nVertices;		

	// Criação efetiva do buffer de vértices (vertexbuffer)
	g_hr = g_device->CreateVertexBuffer ( vbTamanho, D3DUSAGE_WRITEONLY, 
		CustomVertex_PositionOnly_Format, D3DPOOL_MANAGED, &g_vbVertices,
		NULL);

	// Verifica falha na criação
	if(FAILED (g_hr) ) {
		MessageBox (NULL, 
			"Falha na criação do buffer de vértices",
			"inicializar_Buffers()", MB_OK);    
		return; 
	} // endif  

} // inicializar_Buffers().fim
// ---]

// [---
void montar_Geometria(void)
{
	// Posicionamento de profundidade
	float zpos = 1.0f;

	// Ponteiro de acesso aos dados do buffer de vértices
	CustomVertex_PositionOnly *pVerts;

	// Aqui a aplicação ganha acesso à memória do buffer de vértices
	g_vbVertices->Lock( 0, 0, (void**) &pVerts, 0 );

	// Primeiro triângulo
	pVerts[0] = CustomVertex_PositionOnly( -1.0f,  1.0f, zpos ); 
	pVerts[1] = CustomVertex_PositionOnly( -1.0f, -1.0f, zpos ); 
	pVerts[2] = CustomVertex_PositionOnly( 1.0f,  -1.0f, zpos ); 	

	// Segundo triângulo
	pVerts[3] = CustomVertex_PositionOnly( -1.0f, 1.0f, zpos ); 
	pVerts[4] = CustomVertex_PositionOnly( 1.0f, -1.0f, zpos ); 	
	pVerts[5] = CustomVertex_PositionOnly( 1.0f,  1.0f, zpos ); 	

	// Liberação do vertexbuffer	
	g_vbVertices->Unlock();

} //  montar_Geometria().fim
// ---]
// [---
void renderizar_Geometria()
{

	// O VertexShader é informado da estruturação dos vértices
	g_device->SetVertexDeclaration( g_VertexDeclaration);

	// Informação do buffer de vértices utilizado
	g_device->SetStreamSource( 0, g_vbVertices, 0, 
		sizeof(CustomVertex_PositionOnly));

	// Atualiza a câmera
	atualizarCamera();

	// Número de passos do efeito
	UINT nPassosQtd = 0;

	// Renderiza o quadrado usando o efeito
	g_efeito->Begin( &nPassosQtd, 0 );  

	for ( UINT nPasso = 0; nPasso < nPassosQtd; nPasso++) 
	{
		// Renderiza uma etapa no VertexShader
		g_efeito->BeginPass (nPasso);  

		// Renderização efetiva dos vértices
		g_device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2);  

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
	if( g_vbVertices				!= NULL) g_vbVertices->Release();

	if (g_efeito						!= NULL) g_efeito->Release();

	if (g_VertexDeclaration != NULL) g_VertexDeclaration->Release();

	// Libera o dispositivo gráfico  
	if( g_device						!= NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d					!= NULL) g_Direct3d->Release();

	// Anulação dos ponteiros
	g_device						= NULL;
	g_Direct3d					= NULL;
	g_vbVertices				= NULL;
	g_efeito						= NULL;
	g_VertexDeclaration = NULL;

} // Limpar().fim


// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
// [---
VOID Renderizar()
{
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;	

	// Limpa o backbuffer com uma cor verde
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET, verde, 1.0f, 0);

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
		// Vamos renderizar a geometria
		renderizar_Geometria();

		// Finalizando a cena
		g_device->EndScene();
	} // endif

	// Apresenta o conteúdo do backbuffer na tela
	g_device->Present( NULL, NULL, NULL, NULL );

} // Renderizar().fim
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
	// Dados para a configuração da matriz de visualização
	// Aonde está a câmera? - posição da câmera
	D3DXVECTOR3 cam_pos (0.0f, 0.0f, 5.0f);   
	// Para aonde a câmera está apontada ou olhando? Alvo da câmera
	D3DXVECTOR3 cam_alvo (0.0f, 0.0f, 0.0f);   
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
	g_ytela = area_cliente.bottom;	

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

} // inicializar_Camera().fim
// ---]
