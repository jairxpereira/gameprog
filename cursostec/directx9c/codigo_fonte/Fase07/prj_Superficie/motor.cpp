// -----------------------------------------------------------------------------
// Projeto: prj_Superficie - arquivo: motor.cpp
// Esta aplicação mostra como renderizar a cena na textura
// By www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string.h>
#include "motor.h"

// Variáveis globais
// Representa o dispositivo Direct3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;

// Recipientes de materiais e texturas do mesh
D3DMATERIAL9			*g_meshMtl = NULL; 
IDirect3DTexture9	*g_meshTex = NULL; 
// [---
// Objetos para o contexto de renderizar na textura
IDirect3DTexture9			*g_texturaAlvo			= NULL;
ID3DXRenderToSurface	*g_texRenderizador	= NULL;
IDirect3DSurface9			*g_superficieAlvo		= NULL;
ID3DXSprite						*g_radar						= NULL;

// Tamanho da textura desejada 256x256
UINT g_texTam = 256;
// ---]

// Quantidade de materiais do modelo 3d
DWORD g_mtlQtd = 0;

// Interface do objeto 3d
ID3DXMesh *g_objeto3d = NULL;

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
const DWORD azul			= 0xFF0000FF;

// Matrizes de configuração da câmera
D3DXMATRIX g_mtxMundo; 
D3DXMATRIX g_mtxVisao; 
D3DXMATRIX g_mtxProj; 

// [---
void inicializar_texRenderizador(void) 
{
	// Inicializa o Renderizador
	D3DFORMAT texFormato	= D3DFMT_X8R8G8B8;
	g_hr = D3DXCreateRenderToSurface(g_device, g_texTam, g_texTam, 
		texFormato, true, D3DFMT_D16, &g_texRenderizador );

	if ( FAILED(g_hr) ) 
	{
		MessageBox ( NULL, "falha: g_texRenderizador", 
			"inicializar_texRenderizador()", MB_OK);
	} // endif

	// Cria uma textura alvo da renderização
	g_hr = D3DXCreateTexture(g_device, g_texTam, g_texTam, 1, 
		D3DUSAGE_RENDERTARGET, texFormato, D3DPOOL_DEFAULT , &g_texturaAlvo);

	if (FAILED(g_hr) )
	{
		MessageBox (NULL, "falha: g_texturaAlvo", 
			"inicializar_texRenderizador()", MB_OK);
		return;
	} // endif

	// Acessa a superficie de dados da textura
	g_hr = g_texturaAlvo->GetSurfaceLevel (0, &g_superficieAlvo);
	if (FAILED(g_hr) )
	{
		MessageBox (NULL, "falha: g_superficieAlvo", 
			"inicializar_texRenderizador()", MB_OK);
		return;
	} // endif
	
	// Pinta a superficie da textura de vermelho
	g_device->ColorFill (g_superficieAlvo, NULL, 0xFFFF0000);


	// Cria uma sprite para a textura
	g_hr = D3DXCreateSprite(g_device, &g_radar);
	if (FAILED(g_hr) )
	{
		MessageBox (NULL, "falha: D3DXCreateSprite()", 
			"inicializar_texRenderizador()", MB_OK);
		return;
	} // endif
} // inicializar_texRenderizador().fim
// ---]
// [---
void renderizar_naTextura(void)
{
	// Prepara a configuração da janela de visualização	
	D3DVIEWPORT9 visao;  
	visao.MaxZ = 1.0f;
	visao.MinZ = 0.0f;
	visao.X = 10;
	visao.Y = 10; 
	visao.Width =  g_texTam - 20; 
	visao.Height =  g_texTam - 20; 

	// Inicia a renderização da cena
	g_hr = g_texRenderizador->BeginScene(g_superficieAlvo, &visao);  

	if (FAILED(g_hr)) 
	{
		MessageBox (NULL, 
		"Falha: g_texRenderizador->BeginScene()", "renderizar_naTextura", MB_OK);
		return;
	}	// endif

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER , branco, 1.0f, 0);
	g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_POINT); 
	
	// Vamos renderizar a geometria
	g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);	
	g_props.pos = D3DXVECTOR3 (0.0f, 0.2f, -50.0f);		
	desenharObjeto( g_objeto3d, &g_props);

	// Finaliza a cena no Renderizador
	g_texRenderizador->EndScene(D3DX_FILTER_NONE);  	

} // renderizar_naTextura(void);
// ---]
// [---
void renderizarSprite() 
{
	// Cor difusa da sprite
	DWORD cor_difusa = branco;   
	
	// Inicia a renderização considerando efeito de transparência
	g_radar->Begin (D3DXSPRITE_ALPHABLEND);  	

	// Configura posição da sprite na tela
	D3DXMatrixTranslation(&g_mtxMundo, 10.0f, 10.0f, 1.0f);
	g_radar->SetTransform (&g_mtxMundo);

	// Renderiza sprite conforme configuração previamente definida
  g_radar->Draw(g_texturaAlvo, 0, 0, 0 , cor_difusa); 

	// Finaliza processo de renderização de sprites
	g_radar->End();  

} // renderizarSprite().fim
// ---]
// [---
void salvarImagem(void) 
{
	// Cria uma superfície para receber o backbuffer
	IDirect3DSurface9 *backbuffer;

	// Obtém os dados de cor do backbuffer
	g_device->GetBackBuffer (0, 0, D3DBACKBUFFER_TYPE_MONO , &backbuffer);

	// Salva o backbuffer como imagem jpg no disco
	D3DXSaveSurfaceToFile("foto_tela.jpg", D3DXIFF_JPG, backbuffer, 0, 0);

	// Libera a superfície criada
	backbuffer->Release();

	// Notifica o salvamente na barra de títulos
	SetWindowText(hJanela, "prj_Superficie: Ok. Imagem salva no disco");

	// Aguarda um segundo para alertar melhor usuário
	Sleep(1000);

} // void salvarImagem().fim
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

	// Monta a câmera da aplicação
	inicializar_Camera();

	// Configura alguns estados da cena
	configurar_cenaEstados();	
  
	// Carrega o modelo tiny.x
	CarregarModeloTiny();

	// Inicializa os objetos envolvidos na renderização 
	// da cena na textura
	inicializar_texRenderizador();

	return S_OK;
} // initGfx().fim
// ---]

//  Esta função é chamada por DispatchMessage()  
LRESULT CALLBACK processaJanela (
	HWND hJanela, UINT mensagem, WPARAM wParam, LPARAM lParam)
{
	switch (mensagem)                 
	{	
	case WM_DESTROY:
		// Coloca uma mensagem WM_QUIT na fila de mensagem
		Limpar();
		PostQuitMessage (0);       
		break;

	case WM_KEYDOWN:
		
		// Salva imagem no pressionamento da tecla espaço
		if (wParam == VK_SPACE) salvarImagem();

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
  if (g_meshTex != NULL)  g_meshTex->Release();  
  if (g_meshMtl != NULL)  delete g_meshMtl; 

	// Libera objetos do processo de renderizar na textura
	if (g_radar != NULL)						g_radar->Release();
	if (g_texturaAlvo != NULL)			g_texturaAlvo->Release();
	if (g_texRenderizador != NULL)	g_texRenderizador->Release();
	if (g_superficieAlvo != NULL)		g_superficieAlvo->Release();

	// Libera o objeto mesh
	if( g_objeto3d != NULL) g_objeto3d->Release();

	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

	// Anula os ponteiros
	g_radar						= NULL;
	g_texturaAlvo			= NULL;
	g_texRenderizador = NULL;
	g_superficieAlvo	= NULL;

	g_objeto3d = NULL; 
  g_device  = NULL; 
  g_Direct3d = NULL; 
  g_meshTex  = NULL; 
  g_meshMtl  = NULL; 

} // Limpar().fim


// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
// [---
VOID Renderizar()
{		
	// Renderiza na textura primeiro
	renderizar_naTextura();

	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;	
	g_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID); 

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, azul, 1.0f, 0);

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
		
		// Renderiza o modelo 3d
		g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);	
		g_props.pos = D3DXVECTOR3 (-150.0f, 40.0f, -20.0f);		
		desenharObjeto( g_objeto3d, &g_props);

		// Mostra a textura preparada anteriormente
		renderizarSprite();
		
		// Finalizando a cena
		g_device->EndScene();
	} // endif

	// Apresenta o conteúdo do backbuffer na tela
	g_device->Present( NULL, NULL, NULL, NULL );
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
	g_angulo += 0.02f;

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

	g_device->SetMaterial ( &g_meshMtl[0] );
	g_device->SetTexture ( 0, g_meshTex );
	obj3d->DrawSubset(0);

} // desenharObjeto().fim


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
  if(FAILED (g_hr) ) 
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

  // Verifica falha no carregamento ou criação das texturas
  if(FAILED (g_hr) ) 
  {
    MessageBox (NULL, 
      "Falha na criação da textura", "CarregarModeloTiny()", MB_OK);   
    mtlPack->Release();  
    return; 
  } // endif 

  // Libera o buffer do pacote de materiais
  mtlPack->Release();  

} // CarregarModeloTiny().fim