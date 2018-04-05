// [--- $Especificação da classe CModelo: Modelo3d.h#
// -----------------------------------------------------------------------------
// Projeto: prj_HierarquiaAnimada - Arquivo: Modelo3d.h
// Esta aplicação mostra como renderizar uma hierarquia animada
// By Keith Ditchburn - Adaptação www.gameprog.com.br
// -----------------------------------------------------------------------------
#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "Hierarquia.h"

// Esta classe representa o modelo 3d animado (.x)
// Ela carrega o arquivo .x e realiza a atualização da animação e renderização
class CModelo
{
private:

	// ponteiro de cópia do dispositivo 3d (não é uma boa idéia mas está aqui
	// para manter a simplicidade do código )
	IDirect3DDevice9			*m_d3dDevice; 	

	
	// Objetos do Direct3D requeridos para realizar a animação 
	// ---------------------------------------------------------------------------
	// O osso raiz da hierarquia
	D3DXFRAME                   *m_frameRoot;
	
	// O mesh container
	MESHPACK					*m_firstMesh;
    
	// O controlador de animações
	ID3DXAnimationController    *m_animController;
	

	// Dados de ossos
	// ---------------------------------------------------------------------------
	// Ponteiro para a array de matrizes dos ossos
	D3DXMATRIX					*m_boneMatrices;
	
	// Quantidade de ossos presentes no modelo 3d
	int							m_maxBones;
	
	
	// Variáveis de gerenciamento da animação
	// ---------------------------------------------------------------------------
	// animation set corrente
	unsigned int				m_currentAnimationSet;	
	
	// total de animation sets
	unsigned int				m_numAnimationSets;
	
	// Trilha corrente
	unsigned int				m_currentTrack;	

	// Tempo corrente
	float						m_currentTime;	

	// Ajuste de velocidade
	float						m_speedAdjust;
	
	
	// Esfera de borda (bounding sphere) (para colocação da câmera )
	// ---------------------------------------------------------------------------
	// Posição central da esfera
	D3DXVECTOR3					m_sphereCentre;
	
	// Raio da esfera
	float						m_sphereRadius;

	// Nome do arquivo do modelo 3d
	std::string					m_filename;

	
	// Métodos privados da classe CModelo
	// ---------------------------------------------------------------------------
	// Atualiza a posição dos ossos que se 'anima' em função
	// do tempo decorrido
	void UpdateBoneMatrices(const D3DXFRAME *frameBase, 
		const D3DXMATRIX *parentMatrix);
	
	// Renderiza o mesh ligado ao osso
	void DrawBone(D3DXFRAME *frame) const;
	
	// Renderiza o mesh container
	void DrawMeshContainer(D3DXMESHCONTAINER *meshContainerBase, 
		D3DXFRAME *frameBase) const;
	
	// Configura a matriz dos ossos
	void SetupBoneMatrices(OSSO *pFrame, D3DXMATRIX *pParentMatrix);	

public:
	
	
	// Métodos públicos da classe CModelo
	// ---------------------------------------------------------------------------
	// Construtor 
	CModelo( IDirect3DDevice9 *d3dDevice );
	
	// Destrutor
	~CModelo(void);

	// Esse método carrega o arquivo do modelo 3d e inicializa a hierarquia
	// através da utilização de uma instância da classe CMeshHierachy
	bool Load(const std::string &filename);
	
	// Move o osso e o mesh atrelado
	void BoneMove(float elapsedTime, const D3DXMATRIX *matWorld);	
	
	// Essa função desencadeia a renderização do modelo 3d animado
	// chamando DrawBone() para renderizar o osso raiz
	void Render() const;

	// Essa função obtém a posição inicial da câmera
	D3DXVECTOR3 GetInitialCameraPosition() const;

	// Essa função estabelece o animation set corrente
	void SetAnimationSet( unsigned int index );

	// Essa função avança para o próximo animation set
	void NextAnimation();
	
	// Essa função acelera a animação
	void AnimateFaster();
	
	// Essa função desacelera a animação
	void AnimateSlower();
	
	// Esse método retorna o animation set atual
	unsigned int GetCurrentAnimationSet() const 
	{ return m_currentAnimationSet; }
	
	// Esse método retorna o nome do animation set
	std::string GetAnimationSetName( unsigned int index );
	
	// Esse método retorna o nome do arquivo do modelo 3d animado
	std::string GetFilename() const { return m_filename; }
};
// fim da classe CModelo
// fim do arquivo Modelo3d.h
// ---]