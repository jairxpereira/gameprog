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
﻿// [--- $Aspectos globais: arquivo Hierarquia.cpp#
// -----------------------------------------------------------------------------
// Projeto: prj_HierarquiaAnimada - Arquivo: Hierarquia.cpp
// Esta aplicação mostra como renderizar uma hierarquia animada
// By Keith Ditchburn - Adaptação www.gameprog.com.br
// -----------------------------------------------------------------------------

#include "Hierarquia.h"
#include "Tools.h"
// ---]


// [--- $CMeshHierarchy::CreateFrame() - Carregando o osso#
// CMeshHierarchy::CreateFrame() - Esse  método é chamado sempre que 
// um novo frame é encontrado durante o carregamento do modelo 3d (x).
// _nome é o nome do frame
// **_outNovoOsso - é o ponteiro de retorno aonde assinalamos o frame
// recém-criado.
HRESULT CMeshHierarchy::CreateFrame(LPCSTR _nome, D3DXFRAME **_outNovoOsso)
{
	
	// É sempre uma boa idéia inicializar o ponteiro de retorno antes de avançar
	*_outNovoOsso = 0;
	
	// Cria o novo frame utilizando a versão derivada da estrutura
    OSSO *novoOsso = new OSSO;
	ZeroMemory(novoOsso, sizeof(OSSO));	

	// Agora vamos preencher os membros na estrutura de frame
	// Vamos inicializar outros membros para valores default
    D3DXMatrixIdentity( &novoOsso->TransformationMatrix );
    D3DXMatrixIdentity( &novoOsso->exCombinedTransformationMatrix );

	// Zerando os ponteiros
	novoOsso->pMeshContainer	= 0;
    novoOsso->pFrameSibling		= 0;
    novoOsso->pFrameFirstChild	= 0;
	
	// Assinalação do ponteiro de retorno para nosso recém-criado frame
    *_outNovoOsso = novoOsso;	
	
	// Nome do frame (ele pode ser 0 ou ter tamanho zero)
	if (_nome && strlen(_nome))
	{
		novoOsso->Name = Tools::DuplicateCharString(_nome);			
	} // endif
    
	return S_OK;

} // CMeshHierarchy::CreateFrame().fim
// ---]

// [--- $CMeshHierarchy::DestroyFrame() - Destruindo o osso#
// CMeshHierarchy::DestroyFrame() - Esse método desaloca dados de frame
HRESULT CMeshHierarchy::DestroyFrame(D3DXFRAME *frameToFree) 
{	
	// Converte para nosso tipo estendido. OK para fazer isso porque temos
    // certeza de que temos um frame aqui
	OSSO *frame = (OSSO*) frameToFree;

	// Deleta a memória do nome
	if (frame->Name)
		delete[] frame->Name;
	delete frame;

    return S_OK; 
} // CMeshHierarchy::DestroyFrame().fim
// ---]

// [--- $CMeshHierarchy::CreateMeshContainer() - Carregando o mesh container#
// CMeshHierarchy::CreateMeshContainer() Esse método é  chamado  sempre  que um
// 'mesh data' ou dados de mesh  são  encontrados  durante  o  carregamento  do
//  modelo 3d( .x ),
// *_nome - nome  do Mesh (const char*)
// *_meshData - dados do mesh
// *_materials - array de materiais
// *_effectInstances - arquivos e configurações de efeito
// _numMaterials - número de materiais no mesh
// *_adjacency - array de informação de adjacência 
// *_pSkinInfo - informação de skin
// **__outNewMeshPack - ponteiro externo para assinalar o mesh container récem
// criado
HRESULT CMeshHierarchy::CreateMeshContainer(
    LPCSTR						_nome,
    CONST D3DXMESHDATA			*_meshData,
    CONST D3DXMATERIAL			*_materials,
    CONST D3DXEFFECTINSTANCE	*_effectInstances,
    DWORD						_numMaterials,
    CONST DWORD					*_adjacency,
    ID3DXSkinInfo				*_pSkinInfo,
    D3DXMESHCONTAINER		    **_outNewMeshPack)
{    
	// A) Preparação inicial das estruturas
	// ---------------------------------------------------------------------------
	// Criação da estrutura mesh container e inicialização dela para  os  zeros
	// iniciais. Perceba que a estrutura mesh containter é uma versão estendida
	// que foi definida no arquivo Hierarquia.h (MESHPACK)
	MESHPACK *newMeshPack = new MESHPACK;
	ZeroMemory(newMeshPack, sizeof(MESHPACK));
	// Inicialização de segurança do ponteiro de retorno
	*_outNewMeshPack = 0;
	
	
	// B) Copiando o nome do meshcontainer
	// ---------------------------------------------------------------------------
	// Nome do mesh (que pode ser 0) necessita ser copiado
	if ( _nome && strlen(_nome))
	{
		newMeshPack->Name = Tools::DuplicateCharString(_nome);		
	}
	
	
	// C) Preparação dos dados básicos do objeto ID3DMESH
	// ---------------------------------------------------------------------------
	// Tipo de mesh ( D3DXMESHTYPE_MESH, D3DXMESHTYPE_PMESH ou 
	// D3DXMESHTYPE_PATCHMESH )
	if (_meshData->Type != D3DXMESHTYPE_MESH)
	{
		// Esta app apenas manipula mesh padrão. Esta app não manipula outros
		// tipos   de  mesh  como  D3DXMESHTYPE_PMESH ( progressive mesh )  e 
		// D3DXMESHTYPE_PATCHMESH (patch mesh)
		DestroyMeshContainer(newMeshPack);
		return E_FAIL;
	}

	// Estabelece o tipo de mesh como o mesh padrão
	newMeshPack->MeshData.Type = D3DXMESHTYPE_MESH;	

	// Informação de adjacência. É requerida pelo objeto ID3DMESH
	DWORD dwFaces			= _meshData->pMesh->GetNumFaces();
	newMeshPack->pAdjacency = new DWORD[dwFaces*3];
	memcpy(newMeshPack->pAdjacency, _adjacency, sizeof(DWORD) * dwFaces * 3);

	
	// Não precisa clonar. Basta apenas assinalar o ponteiro e adicionar uma
	// referência.
	newMeshPack->MeshData.pMesh = _meshData->pMesh;
	newMeshPack->MeshData.pMesh->AddRef();
	
		
	// D) Carregando texturas e materiais
	// ---------------------------------------------------------------------------
	// Dispositivo renderizador Direct3D. Esse dado é mantido no próprio mesh mas
	// deve ser liberado quando o mesh tiver sido utilizado.
	IDirect3DDevice9 *pd3dDevice = 0;
	_meshData->pMesh->GetDevice(&pd3dDevice);

	
	// Criação da array de texturas e materiais. Perceba que queremos ter ao
	// menos um material
	newMeshPack->NumMaterials	= max(_numMaterials, 1);
	newMeshPack->exMaterials	= new D3DMATERIAL9[newMeshPack->NumMaterials];
	newMeshPack->exTextures		= new IDirect3DTexture9*[newMeshPack->NumMaterials];

	// Limpando a memória para texturas
	ZeroMemory(newMeshPack->exTextures, 
		sizeof(IDirect3DTexture9*) * newMeshPack->NumMaterials);

	
	// Se tiver materiais e texturas vamos carregá-los.
	if (_numMaterials > 0)
	{		
		// Carregamento de todas as texturas e cópia do material por cima
		for(DWORD i = 0; i < _numMaterials; ++i)
		{
			// Copia o material
			newMeshPack->exMaterials[i] = _materials[i].MatD3D;

			// Copia as texturas
			newMeshPack->exTextures[i] = 0;			
			if(_materials[i].pTextureFilename)
			{
				// Pega o nome do arquivo da textura
				std::string texturePath( _materials[i].pTextureFilename );
				
				// Encontre o arquivo e carregue a textura
				if (Tools::FindFile(&texturePath))
				{					
					// Carregamento da textura com a função do directx (D3DX)
					if(FAILED(D3DXCreateTextureFromFile(pd3dDevice, texturePath.c_str(),
						&newMeshPack->exTextures[i])))
					{					
						
						MessageBox (0, "Falha no carregamento da textura",
							"CMeshHierarchy::CreateMeshContainer()", MB_OK);

					} // endif ( Carregamento da textura )
				
				} // endif ( Tools::FindFile(&texturePath) )				
				
			} // endif ( materials[i].pTextureFilename )
		
		} // endfor
	
	} // endif ( (numMaterials > 0) )
	
	else    
	
    // Criação de um material default caso o mesh não tenha um
	{
		ZeroMemory(&newMeshPack->exMaterials[0], sizeof( D3DMATERIAL9 ) );
        newMeshPack->exMaterials[0].Diffuse.r = 0.5f;
        newMeshPack->exMaterials[0].Diffuse.g = 0.5f;
        newMeshPack->exMaterials[0].Diffuse.b = 0.5f;        
		newMeshPack->exMaterials[0].Specular = newMeshPack->exMaterials[0].Diffuse;
		
		// Não vai ter textura
		newMeshPack->exTextures[0] = 0;
    }

	//  Quando pegamos o dispositivo, nós causamos a incrementação do contador de
	//  referências então agora precisamos liberá-lo.
	pd3dDevice->Release();		
	
			
	// E) Carregando dados de skin
	// ---------------------------------------------------------------------------
	// Se tem dados de skin associados com o mesh, vamos copiá-lo
	if (_pSkinInfo)
	{
		// Salve os dados de skin
	    newMeshPack->pSkinInfo = _pSkinInfo;
	    _pSkinInfo->AddRef();
    
		// Precisamos de uma array de 'matrizes de offset' para mover os vértices do
		// espaço de figura para o espaço de osso
		UINT numBones = _pSkinInfo->GetNumBones();
	    newMeshPack->exBoneOffsets = new D3DXMATRIX[numBones];
		
		// Criação de arrays para os ossos e as matrizes de frames
		newMeshPack->exFrameCombinedMatrixPointer = new D3DXMATRIX*[numBones];
	    
		// Pegue cada matriz de offset de osso para não precisarmos pegá-las mais
		// tarde
	    for (UINT i = 0; i < numBones; i++) newMeshPack->exBoneOffsets[i] = 
			*(newMeshPack->pSkinInfo->GetBoneOffsetMatrix(i));
		
		// Nota importante:  Nos exemplos da Microsoft a função GenerateSkinnedMesh() 
		// é chamada aqui para preparar os dados de skinning do mesh para  obter  uma 
		// ótima performance de aceleração de hardware. Como mencionado anteriormente, 
		// este exemplo não realiza o skinning em hardware mas  ao  invés  utiliza  o 
		// skinning feito em software que é mais fácil de entender.
	} // endif (_pSkinInfo)
	else	
	{		
		// Não tem informação de skin, então vamos zerar os ponteiros relativos
		newMeshPack->pSkinInfo		= 0;
		newMeshPack->exBoneOffsets	= 0;
		newMeshPack->exSkinMesh		= 0;
		newMeshPack->exFrameCombinedMatrixPointer = 0;
	} // end else
	

	// F) Carregando configurações de efeitos
	// ---------------------------------------------------------------------------
	// O mesh pode conter referência a arquivos de efeito
	if (_effectInstances)
	{
		// Não faça nada. O arquivo de efeito localizado não é tratado
		// por esta aplicação.			
		if (_effectInstances->pEffectFilename) int dummy = 0;
		
	} // endif


	
	// G) Retornando o meshcontainer carregado
	// ---------------------------------------------------------------------------
	// Configure o ponteiro de saída para o nosso recém-criado mesh container
	*_outNewMeshPack = newMeshPack;    
	return S_OK;
} // CMeshHierarchy::CreateMeshContainer().fim
// ---]


// [--- $CMeshHierarchy::DestroyMeshContainer() - Destruindo o mesh container#
// CMeshHierarchy::DestroyMeshContainer() - Esse método desaloca dados
// de mesh container
HRESULT CMeshHierarchy::DestroyMeshContainer( D3DXMESHCONTAINER 
											 *meshContainerBase)
{
	// Converte para nosso tipo estendido. OK para fazer isso porque 
    // sabemos com certeza o que temos aqui
    MESHPACK* meshContainer = (MESHPACK*) meshContainerBase;
	if (!meshContainer)
		return S_OK;

	// Nome
	if (meshContainer->Name)
	{
		delete[] meshContainer->Name;
		meshContainer->Name=0;
	}

	// array de materiais
	if (meshContainer->exMaterials)
	{
		delete[] meshContainer->exMaterials;
		meshContainer->exMaterials=0;
	}
	
	// Liberação das texturas depois de deletar a array
	if(meshContainer->exTextures)
	{
		for(UINT i = 0; i < meshContainer->NumMaterials; ++i)
		{
			if (meshContainer->exTextures[i])
				meshContainer->exTextures[i]->Release();
		}
	}

	// array de texturas
	if (meshContainer->exTextures)
		delete[] meshContainer->exTextures;

	// informação de adjacência
	if (meshContainer->pAdjacency)
		delete[] meshContainer->pAdjacency;
	
	// peças dos ossos
	if (meshContainer->exBoneOffsets)
	{
		delete[] meshContainer->exBoneOffsets;
		meshContainer->exBoneOffsets=0;
	}
	
	// matrizes dos ossos
	if (meshContainer->exFrameCombinedMatrixPointer)
	{
		delete[] meshContainer->exFrameCombinedMatrixPointer;
		meshContainer->exFrameCombinedMatrixPointer=0;
	}
	
	// liberação do skin mesh
	if (meshContainer->exSkinMesh)
	{
		meshContainer->exSkinMesh->Release();
		meshContainer->exSkinMesh=0;
	}
	
	// liberação do mesh principal
	if (meshContainer->MeshData.pMesh)
	{
		meshContainer->MeshData.pMesh->Release();
		meshContainer->MeshData.pMesh=0;
	}
		
	// liberação da informação de skin
	if (meshContainer->pSkinInfo)
	{
		meshContainer->pSkinInfo->Release();
		meshContainer->pSkinInfo=0;
	}	

	// Finalmente deletamos o container
	delete meshContainer;
	meshContainer=0;

    return S_OK;
} // CMeshHierarchy::DestroyMeshContainer().fim
// ---]
// fim da classe CMeshHierarchy
// fim do arquivo Hierarquia.cpp
