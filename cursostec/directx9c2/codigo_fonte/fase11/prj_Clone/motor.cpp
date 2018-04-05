// -----------------------------------------------------------------------------
// Projeto: prj_Clone - arquivo: motor.cpp
// Esta aplicação mostra como clonar objetos 3d
// By www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>
#include "motor.h"


// Funções de produção e clonagem do cubo
void montarCubo(void);
void clonarCubo(void);
void segundaClonagem(void);

// Interface para os cubos clonados
ID3DXMesh*         g_cuboClonado = NULL;   
ID3DXMesh*         g_segundoClone = NULL; 

// Ponteiro para uma fonte do directx
ID3DXFont* gdxFonte = NULL; 

// Variáveis globais
// Representa o dispositivo Direct3D
LPDIRECT3D9             g_Direct3d = NULL; 

// Representa o dispositivo Renderizador
IDirect3DDevice9*       g_device = NULL;
// [---
// Material para o objeto 3d
D3DMATERIAL9 g_material;

// Interface do objeto 3d
ID3DXMesh *g_objeto3d = NULL;

// Recipiente de cor, rotação e posição do objeto
Propriedades3d g_props;

// Controla o ângulo de rotação do objeto 3d
float g_angulo = 0.0f;

// ---]
// Essa variável recebe informação de erro do Directx
HRESULT g_hr = 0; 	

// Tamanho da janela 
extern int g_xtela;
extern int g_ytela;

// Handle (alça) da janela
extern HWND hJanela;

// Constante para cores
const DWORD branco		= 0xFFFFFFFF;

// Constante para cores com rgba expressado como float's
const D3DCOLORVALUE cvBranco   = { 1.0f, 1.0f, 1.0f, 1.0f }; 
const D3DCOLORVALUE cvVermelho = { 1.0f, 0.0f, 0.0f, 1.0f }; 
const D3DCOLORVALUE cvAmarelo  = { 1.0f, 1.0f, 0.0f, 1.0f }; 
const D3DCOLORVALUE cvVerde    = { 0.0f, 1.0f, 0.0f, 1.0f }; 
const D3DCOLORVALUE cvAzul     = {  0.0f, 0.0f, 1.0f, 1.0f }; 
const D3DCOLORVALUE cvRoxo     = {  0.5f, 0.0f, 0.5f, 1.0f }; 

// Matrizes de configuração da câmera
D3DXMATRIX g_mtxMundo; 
D3DXMATRIX g_mtxVisao; 
D3DXMATRIX g_mtxProj; 

// Controla a mudança periódica da primitiva 3d
UINT temporizador = 0;
// [---
// initGfx() - Inicializa o Direct3D
HRESULT initGfx( HWND hJanela )
{
	// Cria o objeto Direct3D 
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
	
	// Faz a configuração inicial da câmera
	inicializar_Camera();

	// Configura alguns estados da cena
	configurar_cenaEstados();	

	// Configura e coloca uma luz direcional na cena
  D3DXVECTOR3 direcao(0.0f, -1.0f, -1.0f);   
  colocar_DirectionalLight (direcao, cvBranco);  

  montarCubo();
  clonarCubo(); 
  segundaClonagem();
  
  inicializarTexto();

  return S_OK;
} // initGfx().fim
// ---]
// [---
void renderizar_Geometria()
{	
	// Cria e renderiza uma caixa				
	g_props.cor = cvVermelho;
	g_props.pos = D3DXVECTOR3 (0.0f, 2.0f, -7.0f);
	g_props.rot = D3DXVECTOR3 (0.0f, 0.0f, 0.0f);	
	desenharObjeto( g_objeto3d, &g_props);	 

	// Cubo clonado
	g_props.cor = cvVerde;
	g_props.pos = D3DXVECTOR3 (-2.0f, -2.0f, -7.0f);
	g_props.rot = D3DXVECTOR3 (-10.0f, 10.0f, 0.0f);	
	desenharObjeto( g_cuboClonado, &g_props);	 

	// Cubo clonado com normals
	g_props.cor = cvVermelho;
	g_props.pos = D3DXVECTOR3 (2.0f, -2.0f, -7.0f);
	g_props.rot = D3DXVECTOR3 (-10.0f, 10.0f, 0.0f);	
	desenharObjeto( g_segundoClone, &g_props);

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
	if ( g_objeto3d != NULL) g_objeto3d->Release();
	if ( g_cuboClonado != NULL ) g_cuboClonado->Release();
	if ( g_segundoClone != NULL ) g_segundoClone->Release();
	
	// Libera o dispositivo gráfico  
	if ( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if ( g_Direct3d != NULL) g_Direct3d->Release();

	// Limpeza dos ponteiros
	g_objeto3d		= NULL;
	g_cuboClonado	= NULL;
	g_segundoClone	= NULL;
	g_device		= NULL;
	g_Direct3d		= NULL;

} // Limpar().fim


// -----------------------------------------------------------------------------
// Renderizar() - Desenha a cena
// -----------------------------------------------------------------------------
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
		// Vamos renderizar a geometria
		renderizar_Geometria();
		// </b>
		// Finalizando a cena
		g_device->EndScene();
	} // endif

	// Apresenta o conteúdo do backbuffer na tela
	g_device->Present( NULL, NULL, NULL, NULL );

} // Renderizar().fim

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

// [---
void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props)
{

// Matrizes para controlar posição e rotação do objeto 3d
static D3DXMATRIX obj_rot;
static D3DXMATRIX obj_pos;

// Matriz para combinar todas as transformações do objeto 3d
static D3DXMATRIX mtxCombinada;

// Vamos inicializar as matrizes para um valor neutro
D3DXMatrixIdentity( &obj_rot ); 
D3DXMatrixIdentity( &obj_pos );
D3DXMatrixIdentity( &mtxCombinada );

// Verifica situação do formato de vértice do modelo 3d
if ( ( obj3d->GetFVF() & D3DFVF_NORMAL ) != D3DFVF_NORMAL )
mostrarTexto ( 20, 20, "Cubo não tem informação de normal");  
else
mostrarTexto ( 140, 400, "Cubo tem informação de normal");  

// Atualiza ângulo de rotação
g_angulo += 0.01f;

// Configura rotação do objeto 3d
D3DXMatrixRotationYawPitchRoll(&obj_rot, 
							props->rot.y + g_angulo, 
							props->rot.x + g_angulo,
							props->rot.z);


// Ajusta posição do objeto 3d;
D3DXMatrixTranslation ( &obj_pos, 
						props->pos.x, props->pos.y, props->pos.z);

// Tranfere posição e rotação para o mundo
D3DXMatrixMultiply (&mtxCombinada, &obj_rot, &obj_pos);

// Configura matriz mundo para o dispositivo renderizador
g_device->SetTransform( D3DTS_WORLD, &mtxCombinada );  

// Prepara e aplica uma material no objeto 3d
criarMaterial( &g_material, props->cor);
g_device->SetMaterial (&g_material);

// Renderiza o mesh 
obj3d->DrawSubset(0);

} // desenharObjeto().fim
// ---]

void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor ) 
{
  // Limpa a estrutura
  ZeroMemory( mtl, sizeof(D3DMATERIAL9)  );  

  // Configura cor ambiente e difusa
  mtl->Ambient =  cvCor; 
  mtl->Diffuse =  cvCor; 	

} // criarMaterial().fim
// [---
void colocar_DirectionalLight(D3DXVECTOR3 direcao, D3DCOLORVALUE cvCor) 
{
	// Declara a estrutura
	D3DLIGHT9 luz; 

	// Limpa a estrutura
	ZeroMemory( &luz, sizeof(D3DLIGHT9)  );  

	// Configura tipo
	luz.Type = D3DLIGHT_DIRECTIONAL; 

	// Configura cor
	luz.Diffuse = cvCor; 

	// Configura direção da luz
	luz.Direction = direcao;

	// Instalação e acionamento da luz no dispositivo renderizador
	g_device->SetRenderState (D3DRS_LIGHTING, true );  
	g_device->SetLight( 0, &luz );  
	g_device->LightEnable( 0, TRUE); 


} // colocar_DirectionalLight().fim
// ---]
// [---
void configurar_cenaEstados(void) 
{
	// Configura luz ambiente
	g_device->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(0xEE, 0xEE, 0xEE) );

	// Configura shading
	g_device->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );

	// Habilita uso de buffer de profundidade
	g_device->SetRenderState( D3DRS_ZENABLE, D3DZB_TRUE );	

  // Desliga o culling
	g_device->SetRenderState (D3DRS_CULLMODE, D3DCULL_NONE);  

} // configurar_cenaEstados().fim
// ---]


void montarCubo(void)
{
 
    // We are going to fill the empty mesh with the geometry of a box,   
    // so we need 12 triangles and 24 vetices.   
    g_hr = D3DXCreateMeshFVF(   
        12,   
        24,   
        D3DXMESH_MANAGED,   
        CustomVertex_PositionOnly_Format,   
        g_device,   
        &g_objeto3d);   
   
    if(FAILED(g_hr))
	{   
        MessageBoxA(0, "D3DXCreateMeshFVF() - FAILED", 0, 0);   
        return ;
    }   
   
    // Fill in vertices of a box       
    CustomVertex_PositionOnly *v = 0;   
    g_objeto3d->LockVertexBuffer(0, (void**) &v);   
   
    // fill in the front face vertex data   
    v[0] = CustomVertex_PositionOnly(-1.0f, -1.0f, -1.0f ); 
    v[1] = CustomVertex_PositionOnly(-1.0f,  1.0f, -1.0f );  
    v[2] = CustomVertex_PositionOnly( 1.0f,  1.0f, -1.0f );    
    v[3] = CustomVertex_PositionOnly( 1.0f, -1.0f, -1.0f );  
   
    // fill in the back face vertex data   
    v[4] = CustomVertex_PositionOnly(-1.0f, -1.0f, 1.0f );   
    v[5] = CustomVertex_PositionOnly( 1.0f, -1.0f, 1.0f );    
    v[6] = CustomVertex_PositionOnly( 1.0f,  1.0f, 1.0f );    
    v[7] = CustomVertex_PositionOnly(-1.0f,  1.0f, 1.0f );    
   
    // fill in the top face vertex data   
    v[8]  = CustomVertex_PositionOnly(-1.0f, 1.0f, -1.0f );   
    v[9]  = CustomVertex_PositionOnly(-1.0f, 1.0f,  1.0f );  
    v[10] = CustomVertex_PositionOnly( 1.0f, 1.0f,  1.0f );    
    v[11] = CustomVertex_PositionOnly( 1.0f, 1.0f, -1.0f );    
   
    // fill in the bottom face vertex data   
    v[12] = CustomVertex_PositionOnly(-1.0f, -1.0f, -1.0f );    
    v[13] = CustomVertex_PositionOnly( 1.0f, -1.0f, -1.0f );   
    v[14] = CustomVertex_PositionOnly( 1.0f, -1.0f,  1.0f );   
    v[15] = CustomVertex_PositionOnly(-1.0f, -1.0f,  1.0f );   
   
    // fill in the left face vertex data   
    v[16] = CustomVertex_PositionOnly(-1.0f, -1.0f,  1.0f );   
    v[17] = CustomVertex_PositionOnly(-1.0f,  1.0f,  1.0f );   
    v[18] = CustomVertex_PositionOnly(-1.0f,  1.0f, -1.0f );    
    v[19] = CustomVertex_PositionOnly(-1.0f, -1.0f, -1.0f );   
   
    // fill in the right face vertex data   
    v[20] = CustomVertex_PositionOnly( 1.0f, -1.0f, -1.0f ); 
    v[21] = CustomVertex_PositionOnly( 1.0f,  1.0f, -1.0f );   
    v[22] = CustomVertex_PositionOnly( 1.0f,  1.0f,  1.0f ); 
    v[23] = CustomVertex_PositionOnly( 1.0f, -1.0f,  1.0f ); 
   
    g_objeto3d->UnlockVertexBuffer();   
   
       
    // Define the triangles of the box      
    WORD* i = 0;   
    g_objeto3d->LockIndexBuffer(0, (void**)&i);   
   
    // fill in the front face index data   
    i[0] = 0; i[1] = 1; i[2] = 2;   
    i[3] = 0; i[4] = 2; i[5] = 3;   
   
    // fill in the back face index data   
    i[6] = 4; i[7]  = 5; i[8]  = 6;   
    i[9] = 4; i[10] = 6; i[11] = 7;   
   
    // fill in the top face index data   
    i[12] = 8; i[13] =  9; i[14] = 10;   
    i[15] = 8; i[16] = 10; i[17] = 11;   
   
    // fill in the bottom face index data   
    i[18] = 12; i[19] = 13; i[20] = 14;   
    i[21] = 12; i[22] = 14; i[23] = 15;   
   
    // fill in the left face index data   
    i[24] = 16; i[25] = 17; i[26] = 18;   
    i[27] = 16; i[28] = 18; i[29] = 19;   
   
    // fill in the right face index data   
    i[30] = 20; i[31] = 21; i[32] = 22;   
    i[33] = 20; i[34] = 22; i[35] = 23;   
   
    g_objeto3d->UnlockIndexBuffer();   
   
    //   
    // Specify the subset each triangle belongs to, in this example   
    // we will use three subsets, the first two faces of the cube specified   
    // will be in subset 0, the next two faces will be in subset 1 and   
    // the the last two faces will be in subset 2.   
    //   
    DWORD* attributeBuffer = 0;   
    g_objeto3d->LockAttributeBuffer(0, &attributeBuffer);   
   
    for(int a = 0; a < 4; a++)   
        attributeBuffer[a] = 0;   
   
    for(int b = 4; b < 8; b++)   
        attributeBuffer[b] = 0;   
   
    for(int c = 8; c < 12; c++)   
        attributeBuffer[c] = 0;   
   
    g_objeto3d->UnlockAttributeBuffer();   
   
    
    // Optimize the mesh to generate an attribute table.        
    std::vector<DWORD> adjacencyBuffer(g_objeto3d->GetNumFaces() * 3);   

	
    g_objeto3d->GenerateAdjacency(0.0f, &adjacencyBuffer[0]);   
   
    g_hr = g_objeto3d->OptimizeInplace(         
        D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,   
        &adjacencyBuffer[0],   
        0, 0, 0);      

} // montarCubo()


// [--- $clonarCubo() - Produz uma cópia do cubo original#
void clonarCubo(void)
{
	g_objeto3d->CloneMeshFVF ( 
	D3DXMESH_MANAGED, 
	CustomVertex_PositionOnly_Format, g_device,
	&g_cuboClonado);

} // clonarCubo().fim
// ---]


// [--- $segundaClonagem() - Clona o cubo com expansão do formato de vértice#
void segundaClonagem(void)
{
	
	// Vamos clonar o cubo original agora expandindo o formato de
	// vértice com espaço para as normais.
	g_objeto3d->CloneMeshFVF ( 
	D3DXMESH_MANAGED, 
	CustomVertex_PositionOnly_Format | D3DFVF_NORMAL, 
	g_device,
	&g_segundoClone);
	        
    // Gera a informação de adjacência
	std::vector<DWORD> adjacencyBuffer(g_segundoClone->GetNumFaces() * 3);  	
    g_objeto3d->GenerateAdjacency(0.0f, &adjacencyBuffer[0]);

	// Gera a informação das normais
	D3DXComputeNormals ( g_segundoClone, &adjacencyBuffer[0] );
	
	
} // segundaClonagem().fim
// ---]
// fim do arquivo motor.cpp

void inicializarTexto( void ) 
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

  if(FAILED (g_hr) ) 
    MessageBox(NULL, "Texto: falha na inicialização", "inicializarTexto()", MB_OK);   

} // inicializarTexto()


void mostrarTexto(int x, int y, char* texto) 
{
  // Retorne se não houver fonte inicializada
  if ( gdxFonte == NULL ) return; 

  // Cor de fundo da janela
  D3DCOLOR azul = D3DCOLOR_XRGB(0, 0, 255);  

  RECT area_limite; 

  SetRect( &area_limite, x, y, g_xtela, g_ytela );  

  gdxFonte->DrawText( NULL, texto, -1, &area_limite, 0,  azul );  
} // mostrarTexto(); 


