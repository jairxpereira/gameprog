// [--- $Aspectos globais: Arquivo entrada.cpp# tpc++
// -----------------------------------------------------------------------------
// Projeto: prj_HierarquiaAnimada - Arquivo: entrada.cpp
// Esta aplicação mostra como renderizar uma hierarquia animada
// By Keith Ditchburn - Adaptação www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include "Motor.h"
#include "Camera.h"
#include "Tools.h"

// Intância global do motor da aplicação
CMotor *g_motor = 0;

// Protótipo da função de processamento da janela
LRESULT CALLBACK processaJanela (HWND hWnd, UINT message, 
						 WPARAM wParam, LPARAM lParam);

// Constantes de tamanho da tela
const int kViewPortWidth = 800;
const int kViewPortHeight = 600;

// Constantes de controle de câmera
const float kCameraMovementSpeed = 0.05f;
const float kCameraRotationSpeed = 0.01f;
// ---]

// [--- $WinMain() - Ponto de entrada da aplicação#
// Ponto de entrada do programa: cria a janela, inicializa o 
// motor gráfico e entra no laço de mensagens
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
					 LPSTR lpCmdLine, int nCmdShow)
{
	// Criação e registro da janela
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 
	wcex.style = 0; 
	wcex.lpfnWndProc = (WNDPROC) processaJanela;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor( NULL, IDC_ARROW );
	wcex.hbrBackground = ( HBRUSH )( COLOR_WINDOW + 1);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = "clsDirectx";
	wcex.hIconSm = 0;		
	RegisterClassEx(&wcex);
    
	// Ajuste de tamanho da janela
	RECT rc;
	SetRect( &rc, 0, 0, kViewPortWidth, kViewPortHeight );  
	AdjustWindowRectEx( &rc, WS_OVERLAPPEDWINDOW, false, 0);  

	// Criação da janela
	HWND hWnd = CreateWindow("clsDirectx", "prj_HierarquiaAnimada", 
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, 
		NULL, NULL, hInstance, NULL);
	if (hWnd==0)
		return 0;

	// Inicialização do motor gráfico
	g_motor= new CMotor();
	if ( !g_motor->initGfx(hWnd) )
	{
		delete g_motor;
		return 0;
	}

	// Carrega um modelo (x) nativo do directx
	g_motor->loadxfile( Tools::GetTheCurrentDirectory() + 
		"/data/bones_all.x", 1);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// Laço de mensagens da aplicação
	MSG msg;
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message != WM_QUIT )
	{
	   if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
	   {
		  TranslateMessage( &msg );
		  DispatchMessage( &msg );
	   }
	   else
	   {
		   g_motor->Renderizar();
	   }  
	} // endwhile

	// Limpeza e finalização
	delete g_motor;
	return (int)msg.wParam;
} // WinMain().fim
// ---]


// [--- $processaJanela() - Processamento de mensagens da janela#
// Função de processamento das mensagens da janela
LRESULT CALLBACK processaJanela(HWND hWnd, UINT message, 
						 WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_KEYDOWN:
		switch(wParam)
		{			
			// Controle de câmera
			case 'W':
			case VK_UP:
				g_motor->GetCamera()->MoveForward(kCameraMovementSpeed);
			break;
			case 'S':
			case VK_DOWN:
				g_motor->GetCamera()->MoveForward(-kCameraMovementSpeed);
			break;
			case 'D':
			case VK_RIGHT:
				g_motor->GetCamera()->MoveRight(kCameraMovementSpeed);				
			break;
			case 'A':
			case VK_LEFT:
				g_motor->GetCamera()->MoveRight(-kCameraMovementSpeed);				
			break;
			case VK_HOME:
				g_motor->GetCamera()->MoveUp(kCameraMovementSpeed);
			break;
			case VK_END:
				g_motor->GetCamera()->MoveUp(-kCameraMovementSpeed);
			break;

			// Controle do modelo
			case VK_NUMPAD4: 
				g_motor->YawModelo(-kCameraRotationSpeed);
			break;
			case VK_NUMPAD6:				
				g_motor->YawModelo(kCameraRotationSpeed);
			break;
			case VK_NUMPAD8:
				g_motor->PitchModelo(-kCameraRotationSpeed);
			break;
			case VK_NUMPAD2:
				g_motor->PitchModelo(kCameraRotationSpeed);
			break;
			case VK_NUMPAD7:
				g_motor->RollModelo(-kCameraRotationSpeed);
			break;
			case VK_NUMPAD9:
				g_motor->RollModelo(kCameraRotationSpeed);
			break;

			// Controle de animação
			case VK_SPACE:
				g_motor->NextAnimation();
			break;
			case VK_ADD:
				g_motor->AnimateFaster();
			break;
			case VK_SUBTRACT:
				g_motor->AnimateSlower();
			break;

			case VK_F1:
			g_motor->ToggleControlsDisplay();
			break;

			default:
				break;
		}
		break;
        case WM_DESTROY:
             PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
} // processaJanela().fim
// ---]
// fim do arquivo entrada.cpp


