//-----------------------------------------------------------------------------
// Projeto: prj_Device - arquivo: criarDispositivo.cpp
// Este programa ilustra como inicializar o Direct3D e limpar a tela
// Produzido por www.gameprog.com.br
//-----------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>

// Inclui as bibliotecas do Direct3D e sua biblioteca auxiliar
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Protótipos
HRESULT inicializarVertexBuffer();


//-----------------------------------------------------------------------------
// Variáveis globais
//-----------------------------------------------------------------------------

// Representa o dispositivo D3DDevice
LPDIRECT3D9             g_Direct3d       = NULL; 

// Representa o dispositivo Renderizador
LPDIRECT3DDEVICE9       g_device = NULL;

// Representa o buffer de vértices
LPDIRECT3DVERTEXBUFFER9 g_vertexBuffer        = NULL; // Buffer to hold vertices

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z, rhw; // The transformed position for the vertex
    DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

int xtela = 640;
int ytela = 480;


//-----------------------------------------------------------------------------
// Nome: initGfx()
// Descrição: inicializa o Direct3D
//-----------------------------------------------------------------------------
HRESULT initGfx( HWND hWnd )
{
	// Cria o objeto D3D que é necessário para criar o D3DDevice (Renderizador)
	if( NULL == ( g_Direct3d = Direct3DCreate9( D3D_SDK_VERSION ) ) )
		return E_FAIL;    

	// Configura os parâmetros de aparesentação
	// Declara  a variável
	D3DPRESENT_PARAMETERS pps; 

	// Limpa a estrutura
	ZeroMemory( &pps, sizeof(pps) );

	// A aplicação vai ter janela
	pps.Windowed = TRUE;

	// Esse método virar rapidamente o backbuffer para a tela imediata
	pps.SwapEffect = D3DSWAPEFFECT_DISCARD;

	// Esse formato vai procurar se encaixar no modo de vídeo corrente
	pps.BackBufferFormat = D3DFMT_UNKNOWN;	


	// Aqui nós criamos o dispositivo Direct3D
	// Adaptador Default ( D3DADAPTER_DEFAULT )
	// Renderização no hardware ( D3DDEVTYPE_HAL )
	// Processamento de vértices no software (  D3DCREATE_SOFTWARE_VERTEXPROCESSING)
	// Usando a janela corrente ( hWnd )
	// Usando os parâmetros de configuração definidos acima ( pps )
	if( FAILED( g_Direct3d->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&pps, &g_device ) ) )
	{
		return E_FAIL;
	} // endif


	return S_OK;
} // initGfx().fim




//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Libera todos os objetos previamente inicializados
//-----------------------------------------------------------------------------
VOID limpar()
{

	// Libera o buffer de vértices
	if( g_vertexBuffer != NULL ) g_vertexBuffer->Release();

	// Libera o dispositivo gráfico  
	if( g_device != NULL) g_device->Release();

	// Libera o motor do Direct3D  
	if( g_Direct3d != NULL) g_Direct3d->Release();

} // limpar().fim




//-----------------------------------------------------------------------------
// Name: renderizar()
// Desc: Desenha a cena
//-----------------------------------------------------------------------------
VOID renderizar()
{

	// Retorne se o dispositivo estiver nulo
	if( g_device == NULL) return;

	// Cor de fundo da janela
	D3DCOLOR branco = D3DCOLOR_XRGB(255,255,255);

	// Limpa o backbuffer com uma cor branca
	g_device->Clear( 0, NULL, D3DCLEAR_TARGET, branco, 1.0f, 0 );

	// Começa a cena
	if( SUCCEEDED( g_device->BeginScene() ) )
	{
		// Todo código de desenhar ocorre aqui dentro
		        // Draw the triangles in the vertex buffer. This is broken into a few
        // steps. We are passing the vertices down a "stream", so first we need
        // to specify the source of that stream, which is our vertex buffer. Then
        // we need to let D3D know what vertex shader to use. Full, custom vertex
        // shaders are an advanced topic, but in most cases the vertex shader is
        // just the FVF, so that D3D knows what type of vertices we are dealing
        // with. Finally, we call DrawPrimitive() which does the actual rendering
        // of our geometry (in this case, just one triangle).
        g_device->SetStreamSource( 0, g_vertexBuffer, 0, sizeof(CUSTOMVERTEX) );
        g_device->SetFVF( D3DFVF_CUSTOMVERTEX );
        g_device->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 1 );


		// Finalizando a cena
		g_device->EndScene();
	}

	// Apresenta o conteúdo do backbuffer na tela
	g_device->Present( NULL, NULL, NULL, NULL );
} // renderizar().fim

//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: Manipula as mensagens da janela
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{

		// Limpa o contexto quando o usuário fechar a janela
	case WM_DESTROY:
		limpar();
		PostQuitMessage( 0 );
		return 0;


		// Essa mensagem vai ocorrer a todo momento    
	case WM_PAINT:

		// Renderiza a cena      
		renderizar();

		// Invalida a tela para chamar WM_PAINT novamente      
		ValidateRect( hWnd, NULL );

		// Retorna
		return 0;
	}

	// Deixe o Windows realizar o processamento default!
	return DefWindowProc( hWnd, msg, wParam, lParam );
}




//-----------------------------------------------------------------------------
// Name: wWinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{ 
	// Tamanho da janela
	xtela = 320;
	ytela = 320;	

	// Declara e registra a classe da janela
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		"cls_directx", NULL };
	RegisterClassEx( &wc );   


	// Cria a janela da aplicação
	HWND hWnd = CreateWindow( "cls_directx", "vertexBuffer.cpp - fixed", 
		WS_OVERLAPPEDWINDOW, 0, 0, xtela, ytela,
		NULL, NULL, wc.hInstance, NULL );

	// Initialize Direct3D
	if( SUCCEEDED( initGfx( hWnd ) ) )
	{ 
		
	 inicializarVertexBuffer(); 

		ShowWindow( hWnd, SW_SHOWDEFAULT );
		UpdateWindow( hWnd );

		// Enter the message loop
		MSG msg; 
		while( GetMessage( &msg, NULL, 0, 0 ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		} // endwhile
	} // endif

	// Finaliza a aplicação
	UnregisterClass( "cls_directx", wc.hInstance );
	return 0;

} // wWinMain().fim



//-----------------------------------------------------------------------------
// Name: inicializarVertexBuffer()
// Desc: Creates a vertex buffer and fills it with our vertices. The vertex
//       buffer is basically just a chuck of memory that holds vertices. After
//       creating it, we must Lock()/Unlock() it to fill it. For indices, D3D
//       also uses index buffers. The special thing about vertex and index
//       buffers is that they can be created in device memory, allowing some
//       cards to process them in hardware, resulting in a dramatic
//       performance gain.
//-----------------------------------------------------------------------------
HRESULT inicializarVertexBuffer()
{
    // Inicializa 3 vértices para renderizar o triângulo
    const DWORD vermelho	= 0xffff0000;
		const DWORD verde			= 0xff00ff00;
		const DWORD azul			= 0xff00ffff;


    CUSTOMVERTEX vertices[] =
    {
        { 150.0f,  50.0f, 0.5f, 1.0f, vermelho, }, // x, y, z, rhw, cor
        { 250.0f, 250.0f, 0.5f, 1.0f, verde, },
        {  50.0f, 250.0f, 0.5f, 1.0f, azul, },
    };

    // Create the vertex buffer. Here we are allocating enough memory
    // (from the default pool) to hold all our 3 custom vertices. We also
    // specify the FVF, so the vertex buffer knows what data it contains.
    if( FAILED( g_device->CreateVertexBuffer( 3*sizeof(CUSTOMVERTEX),
                                                  0, D3DFVF_CUSTOMVERTEX,
                                                  D3DPOOL_DEFAULT, &g_vertexBuffer, NULL ) ) )
    {
        return E_FAIL;
    }

    // Now we fill the vertex buffer. To do this, we need to Lock() the VB to
    // gain access to the vertices. This mechanism is required becuase vertex
    // buffers may be in device memory.
    VOID* pVertices;
    if( FAILED( g_vertexBuffer->Lock( 0, sizeof(vertices), (void**)&pVertices, 0 ) ) )
        return E_FAIL;
    memcpy( pVertices, vertices, sizeof(vertices) );
    g_vertexBuffer->Unlock();

    return S_OK;
}


