// [--- $Aspectos globais - Arquivo Motor.cpp#
// -----------------------------------------------------------------------------
// Projeto: prj_HierarquiaAnimada - Arquivo: Motor.cpp
// Esta aplicação mostra como renderizar uma hierarquia animada
// By Keith Ditchburn - Adaptação www.gameprog.com.br
// -----------------------------------------------------------------------------

#include "Motor.h"
#include "Tools.h"
#include "Modelo3d.h"
#include "Camera.h"

// Tamanho da fonte
const int kFontSize = 16;
// ---]


// [--- $Métodos especiais: construtor\destrutor#
// Construtor
CMotor::CMotor(void) : m_d3dObject(0), m_d3dDevice(0), m_modelo(0),
m_displayControls(true), m_modeloPosition(0,0,0), m_modeloYaw(0), 
m_modeloPitch(0), m_modeloRoll(0), m_font(0)
{
	m_camera = new CCamera();
} // CMotor().fim

// Destrutor 
CMotor::~CMotor(void)
{
 if ( m_modelo )
 {
	delete m_modelo;
	m_modelo = 0;
 } // endif

 if (m_camera)
 {
	delete m_camera;
	m_camera = 0;
 } // endif

 if (m_font)
 {
	m_font->Release();
	m_font=0;
 } // endif

 if ( m_d3dDevice )
 {
	m_d3dDevice->Release();
	m_d3dDevice=0;
 } // endif

 if ( m_d3dObject )
 {
	m_d3dObject->Release();
	m_d3dObject = 0;
 } // endif
} // ~CMotor().fim
// ---]

// [--- $initGfx() - Inicialização do motor gráfico#
// Inicializa o motor gráfico
bool CMotor::initGfx(HWND hWnd)
{
	
	// Criação do objeto Direct3D
	m_d3dObject = Direct3DCreate9( D3D_SDK_VERSION );
	if ( !m_d3dObject )
	{
		MessageBoxA (0, "Falha na criação do objeto Direct3D",
			"CMotor::initGfx()", MB_OK);
		return false;
	} // endif

	
	// Configuração dos parâmetros de apresentação
	D3DPRESENT_PARAMETERS pps;
	memset(&pps,0,sizeof(pps));
	
	pps.Windowed				= TRUE;
	pps.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	pps.BackBufferFormat		= D3DFMT_UNKNOWN;
	pps.BackBufferCount			= 1;
	pps.PresentationInterval	= D3DPRESENT_INTERVAL_IMMEDIATE;
	pps.EnableAutoDepthStencil	= TRUE;
	pps.AutoDepthStencilFormat	= D3DFMT_D16;

	
	// Criação do dispositivo renderizador
	HRESULT hr = m_d3dObject->CreateDevice( D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, 
		&pps, &m_d3dDevice);

	if ( Tools::FailedHr(hr) )
	{
		// Talvez a máquina não suporte processamento de vértices no hardware
		// então vamos tentar no software!		
		hr = m_d3dObject->CreateDevice( D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pps, &m_d3dDevice);
		if ( Tools::FailedHr(hr) )
		{		
			
			MessageBoxA (0, "renderizador não foi criado",
				"CMotor::initGfx()", MB_OK);

			return false;
		} // endif 
	} // endif

	// Configuração básica de estados
	m_d3dDevice->SetRenderState( D3DRS_LIGHTING,         TRUE );
	m_d3dDevice->SetRenderState( D3DRS_DITHERENABLE,     TRUE );
	m_d3dDevice->SetRenderState( D3DRS_SPECULARENABLE,	 FALSE );
	m_d3dDevice->SetRenderState( D3DRS_ZENABLE,          TRUE );
	m_d3dDevice->SetRenderState( D3DRS_CULLMODE,         D3DCULL_CCW );
	m_d3dDevice->SetRenderState( D3DRS_NORMALIZENORMALS, TRUE );

	// Configuração de texturização
	m_d3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,   D3DTOP_MODULATE );
	m_d3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG1, D3DTA_TEXTURE );
	m_d3dDevice->SetTextureStageState( 0, D3DTSS_COLORARG2, D3DTA_CURRENT );
	m_d3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_MODULATE );
	m_d3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	m_d3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE );
	m_d3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	m_d3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );

	// configuração da matriz de projeção
	D3DXMATRIX matProj;	
	D3DXMatrixPerspectiveFovLH( &matProj, D3DX_PI/4, 800.0f/600.0f, 
		1.0f, 5000.0f );
	m_d3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );

	// Criação de uma luz direcional
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof( D3DLIGHT9 ) );
	light.Type       = D3DLIGHT_DIRECTIONAL;
	light.Diffuse.r  = 1.0f;
	light.Diffuse.g  = 1.0f;
	light.Diffuse.b  = 1.0f;
	light.Diffuse.a  = 1.0f;
	light.Range      = 1000.0f;
	
	// Direção da luz: ela deve estar normalizada - apontando pra baixo
	// ao longo do eixo z
	D3DXVECTOR3 vecDir;
	vecDir = D3DXVECTOR3(0.0f, -0.3f, 0.5f);
	D3DXVec3Normalize( (D3DXVECTOR3*) &light.Direction, &vecDir );
	m_d3dDevice->SetLight( 0, &light );
	m_d3dDevice->LightEnable( 0, TRUE );
	
	// Iluminação extra: luz ambiente
	m_d3dDevice->SetRenderState( D3DRS_AMBIENT, D3DCOLOR_XRGB(80, 80, 80) );	
	
	// Criação da fonte para mostrar texto na tela
	D3DXCreateFont( m_d3dDevice, kFontSize, 0, FW_BOLD, 0, FALSE, 
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, 
		DEFAULT_PITCH | FF_DONTCARE, TEXT("Arial"), &m_font );

	return true;
} // initGfx()
// ---]


// [--- $loadxfile() - Carregando o arquivo x#
// Esta função carrega o modelo 3d informado. Na falha ela retorna 'falso'
// provavelmente porque o arquivo do modelo não foi localizado.
// Adicionalmente ela permite a configuração da primeira animação a ser tocada
bool CMotor::loadxfile(const std::string &filename, int startAnimation)
{	
	// Apenas suportamos um modelo 3d. Então deletamos ele se ele existir!
	if (m_modelo)
	{
		delete m_modelo;
		m_modelo = 0;
	} // endif

	// Cria o modelo 3d
	m_modelo = new CModelo( m_d3dDevice );
	if ( !m_modelo->Load(filename) )
	{
		delete m_modelo;
		m_modelo = 0 ;
		return false;
	} // endif

	// Estabelece a animação inicial
	m_modelo->SetAnimationSet( startAnimation );

	// Configura a câmera para olhar para o modelo 3d
	D3DXVECTOR3 pos = m_modelo->GetInitialCameraPosition();
	m_camera->SetPosition(pos);
	m_camera->SetYawPitchRoll(0,0,0);

	return true;
} // loadxfile().fim
// ---]

// [--- $Renderizar() - Renderização da cena#
// É chamada dentro de WinMain(). Essa função calcula o tempo decorrido
// e anima o modelo 3d. Ela também implementa o laço de renderização
void CMotor::Renderizar()
{
	static DWORD lastTime = timeGetTime();
	
	// Inicialização da matriz de visualização
	D3DXMATRIX matView;
	m_camera->CalculateViewMatrix( &matView );
	m_d3dDevice->SetTransform( D3DTS_VIEW, &matView );		
	
	// Limpa o alvo de renderização e o zbuffer
	HRESULT hr = m_d3dDevice->Clear(0, NULL, 
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255,255,255), 1.0f, 0);
	if ( Tools::FailedHr(hr) ) return;

	// Renderiza cena
	if( SUCCEEDED( m_d3dDevice->BeginScene() ) )
	{
		// Renderiza o modelo 3d
		if (m_modelo)
		{
			// Calcula o tempo decorrido
			float timeElapsed = 0.001f * ( timeGetTime() - lastTime );
			lastTime = timeGetTime();

			// É necessário passar a matriz de alto nível para posicionar e 
			// orientar o modelo. Crie isto a partir da posição  e rotação
			// correntes
			D3DXMATRIX matRotX, matRotY, matRotZ, matTrans;
		
			// Calcula a matriz de rotação
			D3DXMatrixRotationX( &matRotX, m_modeloPitch );
			D3DXMatrixRotationY( &matRotY, m_modeloYaw );  
			D3DXMatrixRotationZ( &matRotZ, m_modeloRoll ); 
			
			// Calcula a matriz de translação
			D3DXMatrixTranslation( &matTrans, m_modeloPosition.x,
				m_modeloPosition.y, m_modeloPosition.z);
			
			// Calcula a matriz de mundo pela multiplicação com as matrizes
			// acima na ordem correta
			D3DXMATRIX matWorld = ( matRotX * matRotY * matRotZ ) * matTrans;			

			// BoneMove() realiza a animação enquanto Render()
			// apenas desenha.
			m_modelo->BoneMove( timeElapsed, &matWorld);
			m_modelo->Render();
		} // endif (m_modelo)

		// Exibição de texto na tela
		mostrarTexto();

		// Finaliza e apresenta a cena
		m_d3dDevice->EndScene();
		m_d3dDevice->Present( NULL, NULL, NULL, NULL ); 
	} // endif ( SUCCEEDED( m_d3dDevice->BeginScene() )
} // Renderizar().fim
// ---]

// [--- $GetCamera() - Obtendo a câmera#
// Retorna a câmera
CCamera *CMotor::GetCamera() const
{
	assert( m_camera );
	return m_camera;
} // GetCamera().fim
// ---]

// [--- $mostrarTexto() - Exibição de informações na tela#
// Mostra as informações na tela
void CMotor::mostrarTexto() const
{

 // Variáveis para controle do tempo e performance	
 static DWORD lastTime = timeGetTime();
 static int numFrames = 0;
 static float fps = 0;

 // Calcula a taxa de frames a cada segundo
 numFrames++;
 DWORD timePassed = timeGetTime() - lastTime;
 if ( timePassed > 1000 )
 {
	fps = 0.001f * timePassed * numFrames;
	numFrames = 0;
	lastTime = timeGetTime();
 } // endif

 D3DCOLOR fontColor = D3DCOLOR_XRGB( 0, 0, 128 );    
 RECT rct;
 rct.left = kFontSize;
 rct.right = 800;
 rct.top = kFontSize;
 rct.bottom = rct.top + kFontSize;

 // Exibe a taxa de frames
 std::string fpsString = "FPS: " + ToString(fps);
 m_font->DrawText( NULL, fpsString.c_str(), -1, &rct, 0, fontColor );
 rct.top += kFontSize; rct.bottom = rct.top + kFontSize;

 if ( m_modelo )
 {
	// Pega o nome do arquivo do modelo 3d
	std::string fnameString = "Arquivo: " + m_modelo->GetFilename();
	m_font->DrawText( NULL, fnameString.c_str(), -1, &rct, 0, fontColor );
	
	// Pega o nome do animation set corrente
	rct.top += kFontSize; rct.bottom = rct.top + kFontSize;		
	std::string animString = "AnimationSet: (" + 
		ToString( m_modelo->GetCurrentAnimationSet() ) + ") " +	
		m_modelo->GetAnimationSetName( m_modelo->GetCurrentAnimationSet() );	
	m_font->DrawText(NULL,animString.c_str(), -1, &rct, 0, fontColor ); 
 } // endif ( m_modelo )
 
 else
 {
	m_font->DrawText(NULL,"Falha no carregamento do modelo", -1, 
		&rct, 0, fontColor );
 } // end else

 if ( m_displayControls )
 {
	rct.top += kFontSize; rct.bottom = rct.top + kFontSize;
	rct.top += kFontSize; rct.bottom = rct.top + kFontSize;
	m_font->DrawText(NULL, "CONTROLES", -1, &rct, 0, fontColor );
	
	rct.top += kFontSize; rct.bottom = rct.top + kFontSize;
	m_font->DrawText(NULL, "Espaço: próximo animationSet", -1, 
		&rct, 0, fontColor );
	
	rct.top += kFontSize; rct.bottom = rct.top + kFontSize;
	m_font->DrawText(NULL, "+/-: Muda velocidade da animação", -1, 
		&rct, 0, fontColor );
	
	rct.top += kFontSize; rct.bottom=rct.top + kFontSize;
	m_font->DrawText(NULL, 
		"Seta esquerda \\ Direita: movimenta a câmera lateralmente",
		-1, &rct, 0, fontColor );
	
	rct.top += kFontSize; rct.bottom = rct.top + kFontSize;
	m_font->DrawText(NULL, 
		"Seta cima \\ baixo: movimenta a câmera frente\\fundo", -1, 
		&rct, 0, fontColor );
	rct.top += kFontSize; rct.bottom = rct.top + kFontSize;

	m_font->DrawText(NULL, 
		"Teclas Home e End: movimenta a câmera cima\\baixo", -1, 
		&rct, 0, fontColor );

	rct.top += kFontSize; rct.bottom = rct.top + kFontSize;
	m_font->DrawText(NULL, 
		"Teclas 4 e 6: gira o modelo no eixo y (yaw)", -1, 
		&rct, 0, fontColor );

	rct.top += kFontSize; rct.bottom = rct.top + kFontSize;
	m_font->DrawText(NULL, 
		"Teclas 8 e 2: gira o modelo no eixo x (pitch)", -1, 
		&rct, 0, fontColor );
	
	rct.top += kFontSize; rct.bottom = rct.top + kFontSize;
	m_font->DrawText(NULL, 
		"Teclas 7 e 9: gira o modelo no eixo z (roll)", -1, 
		&rct, 0, fontColor );
	
	rct.top += kFontSize; rct.bottom = rct.top + kFontSize;
	m_font->DrawText(NULL, 
		"F1: Liga \\ desliga lengenda dos controles", -1, 
		&rct, 0, fontColor );
 
 } // endif (m_displayControls)
} // mostrarTexto().fim
// ---]

// [--- $Interface para controle de animação#
// Seleciona o próximo animationSet
void CMotor::NextAnimation()
{
	if ( m_modelo ) m_modelo->NextAnimation();
} // NextAnimation()


// Acelera a animação
void CMotor::AnimateFaster()
{
	if ( m_modelo )
		m_modelo->AnimateFaster();
} // AnimateFaster().fim

// Desacelera a animação
void CMotor::AnimateSlower()
{
	if ( m_modelo ) m_modelo->AnimateSlower();
} // AnimateSlower().fim
// ---]
// fim do arquivo Motor.cpp
