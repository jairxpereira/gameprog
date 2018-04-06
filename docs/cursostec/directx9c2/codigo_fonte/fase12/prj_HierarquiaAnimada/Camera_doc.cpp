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
	
	// Obter rotação da câmera
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
// ---]﻿

// [--- $Aspectos globais: arquivo Camera.cpp#
// -----------------------------------------------------------------------------
// Projeto: prj_HierarquiaAnimada - Arquivo: Camera.cpp
// Esta aplicação mostra como renderizar uma hierarquia animada
// By Keith Ditchburn - Adaptação www.gameprog.com.br
// -----------------------------------------------------------------------------
#include "Camera.h"
// ---]

// [--- $CCamera::CCamera() - Construtor default#
CCamera::CCamera() : m_position(0,0,0), m_yaw(0), m_pitch(0), m_roll(0)
{
	
	// Comece com um eixo de camera ortogonal olhando para baixo-z
	m_up    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );	
	m_look  = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	m_right = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
} // construtor default fim
// ---]

// [--- $CCamera::CCamera(D3DXVECTOR3 startPos) - Construtor alternativo#
CCamera::CCamera(D3DXVECTOR3 startPos) : m_position(startPos), m_yaw(0), m_pitch(0), m_roll(0)
{		
	// Comece com um eixo de camera ortogonal olhando para baixo-z
	m_up    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	m_look  = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	m_right = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
} // construtor alternativo
// ---]



// [--- $CCamera::SetYawPitchRoll() - Configuração da orientação da câmera#
void CCamera::SetYawPitchRoll(float _yawy, float _pitchx, float _rollz)
{
	m_yaw   = _yawy;
	m_pitch = _pitchx;
	m_roll  = _rollz;
} // CCamera::SetYawPitchRoll().fim
// ---]

// [--- $CCamera::CalculateViewMatrix() - Cálculo da matriz de visualização#
// Calcula a matriz de visualização pela rotação dos nossos eixos a partir da
// orientação default (olhando para baixo-z) via variáveis membro yaw, pitch e roll. 
// Também adicione qualquer translação
void CCamera::CalculateViewMatrix( D3DXMATRIX *viewMatrix)
{	
	// Comece com o eixo da nossa camera apontado baixo-z
	m_up    = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	m_look  = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	m_right = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );

	
	// Yaw é a rotação ao redor do eixo y ( m_up)
	// Elabore a matriz que pode realizar esta rotação
	D3DXMATRIX yawMatrix;
	D3DXMatrixRotationAxis(&yawMatrix, &m_up, m_yaw);
		
	// Para aplicar 'yaw' nós rodamos os vetores m_look e m_right ao redor do vetor
	// m_up ( usando nossa matriz-yaw )
	D3DXVec3TransformCoord( &m_look, &m_look, &yawMatrix  ); 
	D3DXVec3TransformCoord( &m_right, &m_right, &yawMatrix ); 
	
	
	// Pitch é a rotação ao redor do eixo x ( m_right)
	// Elabora a matriz que pode realizar essa rotação
	D3DXMATRIX pitchMatrix;
	D3DXMatrixRotationAxis( &pitchMatrix, &m_right, m_pitch );
		
	// Para aplicar 'pitch' nós rodamos os vetores m_look e m_up ao redor do vetor
	// m_right ( usando nossa matriz-pitch )
	D3DXVec3TransformCoord( &m_look, &m_look, &pitchMatrix ); 
	D3DXVec3TransformCoord( &m_up, &m_up, &pitchMatrix ); 
		
	
	// Roll é a rotação ao redor do eixo z ( m_look)
	// Elabore a matriz que pode realizar essa rotação
	D3DXMATRIX rollMatrix;
	D3DXMatrixRotationAxis( &rollMatrix, &m_look, m_roll );	
	
	// Para aplicar esta rotação nós rodamos para cima e para a direta ao redor do
	// vetor olhar ( usando nossa matriz-roll)
	D3DXVec3TransformCoord( &m_right, &m_right, &rollMatrix ); 
	D3DXVec3TransformCoord( &m_up, &m_up, &rollMatrix ); 
		
	// Elabore a matriz de visualização a partir dos eixos da camera transformados
	D3DXMatrixIdentity(viewMatrix);

	viewMatrix->_11 = m_right.x; viewMatrix->_12 = m_up.x; viewMatrix->_13 = m_look.x;
	viewMatrix->_21 = m_right.y; viewMatrix->_22 = m_up.y; viewMatrix->_23 = m_look.y;
	viewMatrix->_31 = m_right.z; viewMatrix->_32 = m_up.z; viewMatrix->_33 = m_look.z;
	
	viewMatrix->_41 = - D3DXVec3Dot( &m_position, &m_right ); 
	viewMatrix->_42 = - D3DXVec3Dot( &m_position, &m_up );
	viewMatrix->_43 = - D3DXVec3Dot( &m_position, &m_look );
} // CCamera::CalculateViewMatrix().fim
// ---]



// [--- $CCamera::Yaw() - Rotação ao redor do eixo y#
void CCamera::Yaw(float amount) 
{
	m_yaw += amount;
	m_yaw = RestrictAngleTo360Range( m_yaw );
} // CCamera::Yaw().fim
// ---]



// [--- $CCamera::Pitch() - Rotação ao redor do eixo x#
void CCamera::Pitch( float amount )
{
	m_pitch += amount;
	m_pitch = RestrictAngleTo360Range( m_pitch );
} // CCamera::Pitch()
// ---]


// [--- $CCamera::Roll() - Rotação ao redor do eixo z#
// Nota: normalmente apenas usado para cameras de aeronaves - não é usado 
// normalmente para veículos terrestres
void CCamera::Roll( float amount ) 
{
	m_roll += amount;
	m_roll = RestrictAngleTo360Range( m_roll );
} // CCamera::Roll().fim
// ---]


// [--- $CCamera::RestrictAngleTo360Range() - Restrição de valores#
// Mantenha o ângulo na faixa 0 à 360 graus ( 2*PI radianos)
float CCamera::RestrictAngleTo360Range( float angle ) const
{
	while( angle > 2 * D3DX_PI )
		angle -= 2 * D3DX_PI;

	while( angle < 0 )
		angle += 2 * D3DX_PI;

	return angle;
} // CCamera::RestrictAngleTo360Range().fim
// ---]
// fim do arquivo Camera.cpp

