// [--- $Aspectos globais: arquivo Hierarquia.h#
// -----------------------------------------------------------------------------
// Projeto: prj_HierarquiaAnimada - Arquivo: Hierarquia.h
// Esta aplicação mostra como renderizar uma hierarquia animada
// By Keith Ditchburn - Adaptação www.gameprog.com.br
// -----------------------------------------------------------------------------
#pragma once

#include <d3d9.h>
#include <d3dx9.h>
// ---]

// [--- $A estrutura MESHPACK : D3DXMESHCONTAINER#
// MESHPACK - Essa estrutura é derivada da estrutura base D3DXMESHCONTAINER e
// foi estendida com dados específicos para a aplicação que vão ser estocados 
// com cada mesh. Para ajudar na distinção de qual dado é  estendido  e  qual
// é da base cada membro estendido vai começar com o prefixo ex.
struct MESHPACK: public D3DXMESHCONTAINER
{
  // A base D3DXMESHCONTAINER tem um ponteiro pMaterials que  é  uma  estrutura 
  // D3DXMATERIAL que contém um nome de textura e dados de material.    É fácil
  // ignorar isso e no lugar estocar os dados em arrays de texturas e materiais
  // nesta estrutura estendida:

  // Array de ponteiros para as texturas
  IDirect3DTexture9  **exTextures;	

  // Array de ponteiros para os materiais
  D3DMATERIAL9		 *exMaterials;	
                            

  // Variáveis de skinning
  //O skin mesh
  ID3DXMesh           *exSkinMesh;			

  // As matrizes offset de ossos, uma por osso
  D3DXMATRIX		 *exBoneOffsets;			

  // Array dos ponteiros das matrizes dos frames
  D3DXMATRIX		 **exFrameCombinedMatrixPointer;
};
// fim da estrutura MESHPACK : D3DXMESHCONTAINER
// ---]

// [--- $A estrutura OSSO : D3DXFRAME#
// A estrutura OSSO é derivada da estrutura base D3DXFRAME e foi estendida com
// dados específicos para a aplicação que vão ser  estocados  com  cada  frame. 
// Para ajudar na distinção do membro estendido das variáveis da base o membro
// estendido vai ser prefixado com ex
struct OSSO: public D3DXFRAME
{
    D3DXMATRIX exCombinedTransformationMatrix;
};
// fim da estrutura OSSO : D3DXFRAME
// ---]

// [--- $A estrutura da classe CMeshHierarchy#
// Classe CMeshHierarchy
// Esta classe define as funções callback obrigatórias requeridas pela função
// D3DXLoadMeshHierarchyFromX(). Estas funções estão definidas como abstratas
// pela interface ID3DXAllocateHierarchy()
class CMeshHierarchy : public ID3DXAllocateHierarchy
{
public:	
    
	// função para criar e inicializar o objeto D3DXFRAME estendido
    STDMETHOD( CreateFrame )(LPCSTR _nome, D3DXFRAME **_outNovoOsso);

		// função para liberar o objeto D3DXFRAME estendido
    STDMETHOD( DestroyFrame )(D3DXFRAME *frameToFree );

	// função para criar e inicializar o objeto D3DXMESHCONTAINER estendido
    STDMETHOD( CreateMeshContainer )(
		LPCSTR						_nome,
		CONST D3DXMESHDATA			*_meshData,
		CONST D3DXMATERIAL			*_materials,
		CONST D3DXEFFECTINSTANCE	*_effectInstances,
		DWORD						_numMaterials,
		CONST DWORD					*_adjacency,
		ID3DXSkinInfo				*_pSkinInfo,
		D3DXMESHCONTAINER		    **_outNewMeshPack		
		);


	// função para liberar o objeto D3DXMESHCONTAINER estendido
    STDMETHOD( DestroyMeshContainer )( D3DXMESHCONTAINER *meshContainerToFree );

};
// fim da classe CMeshHierarchy
// ---]
// fim do arquivo Hierarquia.h
