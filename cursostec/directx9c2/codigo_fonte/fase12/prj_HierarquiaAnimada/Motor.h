// [--- $Especificação da classe CMotor: Motor.h#
// -----------------------------------------------------------------------------
// Projeto: prj_HierarquiaAnimada - Arquivo: motor.h
// Esta aplicação mostra como renderizar uma hierarquia animada
// By Keith Ditchburn - Adaptação www.gameprog.com.br
// -----------------------------------------------------------------------------
#pragma once
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

// Bibliotecas do directx
#pragma comment (lib, "d3d9.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "dxerr.lib")

// Biblioteca para uso de timeGetTime()
#pragma comment (lib, "winmm.lib")

// Classes de apoio que serão utilizadas
class CModelo;
class CCamera;

// A classe CMotor provê toda a funcionalidade gráfica da aplicação;
// ela tem o código para inicializar o Direct3D e carregar o modelo 
// 3d pela classe CModelo
class CMotor
{
private:

	// objetos do Direct3D
	IDirect3D9				*m_d3dObject;
	IDirect3DDevice9		*m_d3dDevice;
	ID3DXFont				*m_font;

	// Objetos internos
	CModelo					*m_modelo;
	CCamera					*m_camera;	

	// Posição e orientação do modelo 3d
	D3DXVECTOR3 m_modeloPosition;
	float m_modeloYaw, m_modeloPitch, m_modeloRoll;

	// Exibição de informações na tela
	bool m_displayControls;		
	void mostrarTexto() const;

public:
	
	// Os métodos especiais: construtor \ destrutor
	CMotor(void);
	~CMotor(void);

	// Inicializa o motor gráfico
	bool initGfx(HWND hWnd);

	// Carrega o arquivo x e define a animação inicial
	bool loadxfile(const std::string &filename, int startAnimation = 0);

	// Renderiza a cena
	void Renderizar();
	
	// Obtém a câmera
	CCamera *GetCamera() const;
	
	// Liga\desliga exibição de texto
	void ToggleControlsDisplay() 
	{ m_displayControls =! m_displayControls; }

	// Controle de orientação do modelo
	void YawModelo( float value)  { m_modeloYaw += value; }
	void PitchModelo( float value){ m_modeloPitch += value; }
	void RollModelo( float value) { m_modeloRoll += value; }

	// Interface para controle de animação
	void NextAnimation();
	void AnimateFaster();
	void AnimateSlower();
};
// fim da classe CMOTOR
// fim do arquivo motor.h
// ---]

