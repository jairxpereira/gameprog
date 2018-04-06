// -----------------------------------------------------------------------------
// Projeto: prj_ModificarTextura - arquivo: motor.cpp
// Esta aplicação mostra como modificar uma textura em tempo de execução
// By www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "motor.h"

// Variáveis globais
// Representa o dispositivo Direct3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;
// [---
// Recipientes de materiais e texturas do mesh  
D3DMATERIAL9				*g_meshMtl = NULL;
IDirect3DTexture9   *g_meshTex = NULL;
IDirect3DTexture9		*g_texturaAlternativa = NULL;

// Controle de seleção da textura
int g_texturaFlag = 1;

// Interface do objeto 3d
ID3DXMesh *g_objeto3d = NULL;
// ---]
// Quantidade de materiais no objeto 3d
DWORD g_mtlQtd = 0;

// Recipiente de cor, rotação e posição do objeto
Propriedades3d g_props;

// Controla o ângulo de rotação do objeto 3d
float g_angulo = 0.0f;

// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

// Tamanho da janela 
extern int g_xtela;
extern int g_ytela;
extern HWND hJanela;

// Constante para cores
const DWORD branco		= 0xFFFFFFFF;

// Matrizes de configuração da câmera
D3DXMATRIX g_mtxMundo; 
D3DXMATRIX g_mtxVisao; 
D3DXMATRIX g_mtxProj; 

// [---
void CarregarModeloTiny()
{
	// Nome final do arquivo do modelo 3d
	char arquivo_x[] = "\\gameprog\\gdkmedia\\Modelos\\Tiny\\tiny.x";

	// Buffer para o pacote de materiais e texturas do modelo 3d 
	ID3DXBuffer *mtlPack;	

	// Carrega modelo 3d com suas texturas e materiais 
	g_hr = D3DXLoadMeshFromX(arquivo_x, D3DXMESH_SYSTEMMEM, 
		g_device, NULL, &mtlPack, NULL, &g_mtlQtd, &g_objeto3d );

	// Verifica falha no carregamento do modelo 3d
	if ( FAILED (g_hr) )
	{
		MessageBox (NULL, 
			"Falha no carregamento do modelo", "CarregarModeloTiny()", MB_OK);		
		return;    
	} // endif

	// Pacote de materiais da biblioteca auxiliar d3dx
	D3DXMATERIAL *xMtl = (D3DXMATERIAL *) mtlPack->GetBufferPointer();	

	// Inicializa a array de materiais
  g_meshMtl  = new D3DMATERIAL9[1];  

	// Copia o ponteiro do material
	g_meshMtl[0] = xMtl[0].MatD3D;

	// Configura a cor ambiente do material
	g_meshMtl[0].Ambient = g_meshMtl[0].Diffuse;

	// Nome completo da textura do modelo 3d 
	char *arquivo_textura = "\\gameprog\\gdkmedia\\Modelos\\Tiny\\Tiny_skin.bmp";		
	
	// Carrega a textura do disco
	g_hr = D3DXCreateTextureFromFile(g_device, arquivo_textura, &g_meshTex);

		// Criação da textura alternativa 
	g_hr = D3DXCreateTexture(g_device, 256, 256, 0, 
		D3DUSAGE_DYNAMIC, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT, 
		&g_texturaAlternativa);

	// Verifica falha no carregamento ou criação das texturas
	if ( FAILED (g_hr) )
	{
		MessageBox (NULL, 
			"Falha na criação da textura", "CarregarModeloTiny()", MB_OK);	
		mtlPack->Release();
		return;    
	} // endif

	// Modifica a textura original 
	modificar_Textura (g_meshTex);

	// Libera o buffer do pacote de materiais
	mtlPack->Release();

} // CarregarModeloTiny().fim
// ---]
// [---
void modificar_Textura (IDirect3DTexture9 *textura)
{
	// Componentes rgb para montar depois a cor final
	unsigned char r, g, b;

	// Cor temporária
	ARGBCOR tempcor;

	// Obtém a área de dados da textura
	D3DLOCKED_RECT texData;

	// Acessa os dados da textura
	textura->LockRect(0, &texData, 0, 0);

	// Acessa dados de cor
	ARGBCOR *cores = (ARGBCOR *) texData.pBits;

	// Escreve a média dos canais de cor na metade da textura
	for (UINT linha = 0; linha < 32768 ; linha++) 
	{
		// Leitura dos componentes rgb
		r = cores->r;
		g = cores->g;
		b = cores->b;

		// Média para deixar em preto e branco
		unsigned char media = ( r + g + b ) / 3;

		// Configura cor
		tempcor.a = media;
		tempcor.r = media;
		tempcor.g = media;
		tempcor.b = media;

		// Escreve a cor na área de dados da textura
		*cores  = tempcor;

		// Avança o ponteiro
		cores++;		

	} // endfor linha

	// Libera a textura para o sistema\placa de vídeo
	textura->UnlockRect (0);

} // ModificarTextura().fim
// ---]
// [---
void modificar_TexturaEx (IDirect3DTexture9 *textura)
{
	// Obtém a descrição da textura
	D3DSURFACE_DESC desc;
	g_hr = textura->GetLevelDesc (0, &desc);

	// Retângulo para receber os dados de cor da textura
	D3DLOCKED_RECT texData;

	// Seleção da região a ser modificada da textura (toda a textura)
	RECT texSelecao = { 0, 0, 0, 0 };
	texSelecao.right = desc.Width ;
	texSelecao.bottom  = desc.Height ;

	// Nível de mipmap
	UINT mipNivel = 0;

	// Flags de modo de acesso
	DWORD tranca_flags = 0;

	// Obtém os dados da textura
	textura->LockRect(mipNivel, &texData, &texSelecao, tranca_flags);

	// Faz o cast dos dados obtidos para o formato de cor argb
	ARGBCOR *cores = (ARGBCOR *) texData.pBits;

	// Cálcula o total de pontos de cor da textura
	UINT nTotal = desc.Width  * desc.Height;

	// Escreve uma cor aleatória em cada ponto da textura
	for (UINT ncx = 0; ncx < nTotal ; ncx++) 
	{
		// Seleciona um valor aleatório
		unsigned char nval = (unsigned char )  rand() % 255;	

		// Configura o valor nos canais de uma cor temporária
		ARGBCOR tempcor;
		tempcor.a = nval;		
		tempcor.r = nval;		
		tempcor.g = nval;
		tempcor.b = nval;

		// Escreve a cor na área de dados da textura
		*cores  = tempcor;

		// Avança o ponteiro pra frente
		cores++;	

	} // endfor linha

	// Libera a textura para o sistema\placa de vídeo
	textura->UnlockRect (0);

} // ModificarTexturaEx().fim
// ---]

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

	// Vamos ativar o buffer de profundidade
	pps.EnableAutoDepthStencil = true;
	pps.AutoDepthStencilFormat = D3DFMT_D16;

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

	// Inicializa o gerador de números aleatórios
	srand( clock() );

	// Configura uma câmera para a aplicação
	inicializar_Camera();

	// Configura alguns estados da cena
	configurar_cenaEstados();	

	// Carrega o modelo tiny.x
	CarregarModeloTiny();

	return S_OK;
} // initGfx().fim

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
		// Inverte a textura aplicada 
		if (wParam == VK_SPACE) g_texturaFlag *= -1; 
		
		// Encerra a aplicação
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
	// Libera a memória de materiais e textura
	if (g_meshTex != NULL) g_meshTex->Release();
	if (g_meshMtl != NULL) delete g_meshMtl;
	if (g_texturaAlternativa != NULL) g_texturaAlternativa->Release();
	
	// Libera o objeto 3d, o renderizador e o Direct3d
	if( g_objeto3d != NULL) g_objeto3d->Release();
	if( g_device != NULL) g_device->Release();
	if( g_Direct3d != NULL) g_Direct3d->Release();

	// Anula os ponteiros
	g_objeto3d	= NULL;
	g_device		= NULL;
	g_Direct3d	= NULL;
	g_meshTex		= NULL;
	g_meshMtl		= NULL;
	g_texturaAlternativa = NULL;

} // Limpar().fim


// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
// [---
VOID Renderizar()
{
	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;	

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, branco, 1.0f, 0);

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
		// <b>
		// Vamos renderizar o modelo da esquerda sem filtros de textura
		g_device->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_NONE );
		g_device->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_NONE );
		g_device->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );

		// Configura posição e renderiza
		g_props.pos = D3DXVECTOR3 (100.0f, 0.2f, -20.0f);
		g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);	
		desenharObjeto( g_objeto3d, &g_props);

		// Filtros para suavizar a textura do modelo da direita
		g_device->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		g_device->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

		// Salienta mais a visão das faces
		g_device->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

		// Configura posição e renderiza
		g_props.pos = D3DXVECTOR3 (-150.0f, 40.0f, -20.0f);		
		desenharObjeto( g_objeto3d, &g_props);
		// </b>
		// Finalizando a cena
		g_device->EndScene();
	} // endif

	// Apresenta o conteúdo do backbuffer na tela
	g_device->Present( NULL, NULL, NULL, NULL );
	
	// Isso melhora a performance do sistema Windows
	Sleep(0);

} // Renderizar().fim
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
	D3DXVECTOR3 cam_pos (0.0f, 0.0f, 700.0f);   
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
	// Pega o tamanho da área cliente
	RECT area_cliente;
	GetWindowRect (hJanela, &area_cliente);
	g_xtela = area_cliente.right;
	g_ytela = area_cliente.bottom ;	

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

// [---
void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props)
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

	// Atualiza ângulo de rotação
	g_angulo += 0.01f;

	// Configura rotação do objeto 3d
	D3DXMatrixRotationYawPitchRoll(&obj_rot, 
		props->rot.y, 
		props->rot.x + g_angulo,
		props->rot.z);

	// Ajusta posição do objeto 3d;
	D3DXMatrixTranslation ( &obj_pos, 
		props->pos.x, props->pos.y, props->pos.z);

	// Tranfere posição e rotação para o mundo
	D3DXMatrixMultiply (&mtxCombinada, &obj_rot, &obj_pos);

	// Configura matriz mundo para o dispositivo renderizador
	g_device->SetTransform( D3DTS_WORLD, &mtxCombinada );  

	// Renderiza o mesh 
	g_device->SetMaterial ( &g_meshMtl[0] );

	// Seleciona a textura de acordo com o flag g_texturaFlag
	// Renderiza com textura original modificada
	if (g_texturaFlag == 1) g_device->SetTexture ( 0, g_meshTex);
	
	// Renderiza com textura alternativa
	else
	{
		modificar_TexturaEx ( g_texturaAlternativa );		
		g_device->SetTexture ( 0, g_texturaAlternativa );		
	} // endif

	// Renderiza o mesh
	obj3d->DrawSubset(0);

} // desenharObjeto().fim
// ---]

void configurar_cenaEstados(void) 
{
	// Configuração de iluminação
	g_device->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(255,255,255) );
	g_device->SetRenderState (D3DRS_LIGHTING, true ); 

	// Configura modo de shading
	g_device->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );

	// Habilita uso de buffer de profundidade
	g_device->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );	

	// Desliga o culling
	g_device->SetRenderState (D3DRS_CULLMODE, D3DCULL_NONE);  

} // configurar_cenaEstados().fim
