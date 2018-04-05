// [--- $Especificação da classe CCamera: Camera.h#
// -----------------------------------------------------------------------------
// Projeto: prj_HierarquiaAnimada - Arquivo: Camera.h
// Esta aplicação mostra como renderizar uma hierarquia animada
// By Keith Ditchburn - Adaptação www.gameprog.com.br
// -----------------------------------------------------------------------------
#pragma once
#include <d3dx9.h>

// Camera.h: Implementação de uma câmera em primeira pessoa
class CCamera
{
private:

	// Posição da câmera
	D3DXVECTOR3 m_position; 
	
	// Rotação ao redor do eixo y
	float m_yaw;	
	
	// Rotação ao redor do eixo x
	float m_pitch;	
	
	// Rotação ao redor do eixo z
	float m_roll;	
	
	// Eixos da câmera
	D3DXVECTOR3 m_up, m_look, m_right; 

	// Restrição para manter ângulo na faixa 0 - 360 graus
	float RestrictAngleTo360Range(float angle) const;

public:
	CCamera();
	CCamera(D3DXVECTOR3 startPos);
	~CCamera(void){};

	// Calcular a matriz de visualização
	void CalculateViewMatrix(D3DXMATRIX *viewMatrix);

	// Sets ( Configurações )
	// Configurar posição
	void SetPosition( const D3DXVECTOR3 &pos ) { m_position = pos; }
	
	// Configurar rotação
	void SetYawPitchRoll( float yaw, float pitch, float roll );	

	// Gets ( Obter )
	// Obter rotação do eixo y
	float GetYaw() const { return m_yaw; }
	
	// Obter rotação do eixo x
	float GetPitch() const { return m_pitch; }
	
	// Obter rotação do eixo z
	float GetRoll() const { return m_roll; }
	
	// Obter posição da câmera
	D3DXVECTOR3 GetPosition() const { return m_position; }	

	// Operações de mover
	// Mover para a frente
	void MoveForward( float amount ) { m_position += m_look * amount; }
	
	// Mover para a direita
	void MoveRight( float amount ) { m_position += m_right * amount; }
	
	// Mover para cima
	void MoveUp( float amount)  { m_position += m_up * amount; }
	
	// Rotações	
	// Rotação ao redor do eixo y
	void Yaw( float amount ); 
	
	// Rotação ao redor do eixo x
	void Pitch( float amount ); 

	// Rotação ao redor do eixo z
	void Roll( float amount ); 
};
// fim da classe CCamera
// fim do arquivo Camera.h
// ---]