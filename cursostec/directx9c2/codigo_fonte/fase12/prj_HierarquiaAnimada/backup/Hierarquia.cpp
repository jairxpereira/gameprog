// -----------------------------------------------------------------------------
// Projeto: prj_HierarquiaAnimada - Arquivo: Hierarquia.cpp
// Esta aplica��o mostra como renderizar uma hierarquia animada
// By Keith Ditchburn - Adapta��o www.gameprog.com.br
// -----------------------------------------------------------------------------

#include "Hierarquia.h"
#include "Tools.h"

// CMeshHierarchy::CreateFrame() - Esse  m�todo � chamado sempre que 
// um novo frame � encontrado durante o carregamento do modelo 3d (x).
// Name � o nome do frame
// retNewFrame - � o ponteiro de retorno aonde assinalamos o frame
// rec�m-criado.
HRESULT CMeshHierarchy::CreateFrame(LPCSTR _nome, LPD3DXFRAME *_outNovoOsso)
{
	
	// � sempre uma boa id�ia inicializar o ponteiro de retorno antes de avan�ar
	*_outNovoOsso = 0;
	
	// Cria o novo frame utilizando a vers�o derivada da estrutura
    OSSO *novoOsso = new OSSO;
	ZeroMemory(novoOsso,sizeof(OSSO));	

	// Agora vamos preencher os membros na estrutura de frame
	// Vamos inicializar outros membros para valores default
    D3DXMatrixIdentity(&novoOsso->TransformationMatrix);
    D3DXMatrixIdentity(&novoOsso->exCombinedTransformationMatrix);

	novoOsso->pMeshContainer = 0;
    novoOsso->pFrameSibling = 0;
    novoOsso->pFrameFirstChild = 0;
	
	// Assinala��o do ponteiro de retorno para nosso rec�m-criado frame
    *_outNovoOsso = novoOsso;	
	
	// Nome do frame (ele pode ser 0 ou ter tamanho zero)
	if (_nome && strlen(_nome))
	{
		novoOsso->Name = Tools::DuplicateCharString(_nome);			
	}

    
	return S_OK;

} // CMeshHierarchy::CreateFrame().fim


// CMeshHierarchy::CreateMeshContainer() Esse m�todo �  chamado  sempre  que um
// 'mesh data' ou dados de mesh  s�o  encontrados  durante  o  carregamento  do
//  modelo 3d( .x ),
// _nome - nome  do Mesh (const char*)
// _meshData - dados do mesh
// _materials - array de materiais
// _effectInstances - arquivos e configura��es de efeito
// _numMaterials - n�mero de materiais no mesh
// _adjacency - array de informa��o de adjac�ncia 
// _pSkinInfo - informa��o de skin
// __outNewMeshPack - ponteiro externo para assinalar o mesh container r�cem
// criado
HRESULT CMeshHierarchy::CreateMeshContainer(
    LPCSTR						_nome,
    CONST D3DXMESHDATA			*_meshData,
    CONST D3DXMATERIAL			*_materials,
    CONST D3DXEFFECTINSTANCE	*_effectInstances,
    DWORD						_numMaterials,
    CONST DWORD					*_adjacency,
    LPD3DXSKININFO				_pSkinInfo,
    LPD3DXMESHCONTAINER*		_outNewMeshPack)
{    
	// Cria��o da estrutura mesh container e inicializa��o dela para  os  zeros
	// iniciais. Perceba que a estrutura mesh containter � uma vers�o estendida
	// que foi definida no arquivo MeshStructures.h (MESHPACK)
	MESHPACK *newMeshPack = new MESHPACK;
	ZeroMemory(newMeshPack, sizeof(MESHPACK));
	
	// Inicializa��o de seguran�a do ponteiro de retorno
	*_outNewMeshPack = 0;
	
	// Nome do mesh (que pode ser 0) necessita ser copiado
	if ( _nome && strlen(_nome))
	{
		newMeshPack->Name = Tools::DuplicateCharString(_nome);		
	}
	
	
	
	// Tipo de mesh ( D3DXMESHTYPE_MESH, D3DXMESHTYPE_PMESH ou 
	// D3DXMESHTYPE_PATCHMESH )
	if (_meshData->Type != D3DXMESHTYPE_MESH)
	{
		// Esta app apenas manipula mesh padr�o. Esta app n�o manipula outros
		// tipos   de  mesh  como  D3DXMESHTYPE_PMESH ( progressive mesh )  e 
		// D3DXMESHTYPE_PATCHMESH (patch mesh)
		DestroyMeshContainer(newMeshPack);
		return E_FAIL;
	}

	newMeshPack->MeshData.Type = D3DXMESHTYPE_MESH;	

	// Informa��o de adjac�ncia. � requerida pelo objeto ID3DMESH
	DWORD dwFaces = _meshData->pMesh->GetNumFaces();
	newMeshPack->pAdjacency = new DWORD[dwFaces*3];
	memcpy(newMeshPack->pAdjacency, _adjacency, sizeof(DWORD) * dwFaces * 3);
	
	// Dispositivo renderizador Direct3D. Esse dado � mantido no pr�prio mesh mas
	// deve ser liberado quando o mesh tiver sido utilizado.
	LPDIRECT3DDEVICE9 pd3dDevice = 0;
	_meshData->pMesh->GetDevice(&pd3dDevice);
	
	// N�o precisa clonar. Basta apenas assinalar o ponteiro e adicionar uma
	// refer�ncia.
	newMeshPack->MeshData.pMesh = _meshData->pMesh;
	newMeshPack->MeshData.pMesh->AddRef();
	
	// Cria��o da array de texturas e materiais. Perceba que que eu quero ter ao
	// menos um
	newMeshPack->NumMaterials = max(_numMaterials, 1);
	newMeshPack->exMaterials = new D3DMATERIAL9[newMeshPack->NumMaterials];
	newMeshPack->exTextures  = new LPDIRECT3DTEXTURE9[newMeshPack->NumMaterials];

	ZeroMemory(newMeshPack->exTextures, 
		sizeof(LPDIRECT3DTEXTURE9) * newMeshPack->NumMaterials);



	
	if (_numMaterials > 0)
	{		
		// Carregamento de todas as texturas e c�pia do material por cima
		for(DWORD i = 0; i < _numMaterials; ++i)
		{
			newMeshPack->exTextures[i] = 0;	
			newMeshPack->exMaterials[i] = _materials[i].MatD3D;

			if(_materials[i].pTextureFilename)
			{
				std::string texturePath( _materials[i].pTextureFilename );
				
				if (Tools::FindFile(&texturePath))
				{					
					// Carregamento da textura com a fun��o do directx (D3DX)
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
	
    // Cria��o de um material default caso o mesh n�o tenha um
	{
		ZeroMemory(&newMeshPack->exMaterials[0], sizeof( D3DMATERIAL9 ) );
        newMeshPack->exMaterials[0].Diffuse.r = 0.5f;
        newMeshPack->exMaterials[0].Diffuse.g = 0.5f;
        newMeshPack->exMaterials[0].Diffuse.b = 0.5f;
        
		newMeshPack->exMaterials[0].Specular = 
			newMeshPack->exMaterials[0].Diffuse;
		
		newMeshPack->exTextures[0]=0;
    }

	
	// Se tem dados de skin associados com o mesh, vamos copi�-lo
	if (_pSkinInfo)
	{
		// Salve os dados de skin
	    newMeshPack->pSkinInfo = _pSkinInfo;
	    _pSkinInfo->AddRef();
    
		// Precisamos de uma array de 'matrizes de offset' para mover os v�rtices do
		// espa�o de figura para o espa�o de osso
		UINT numBones = _pSkinInfo->GetNumBones();
	    newMeshPack->exBoneOffsets = new D3DXMATRIX[numBones];
		
		// Cria��o de arrays para os ossos e as matrizes de frames
		newMeshPack->exFrameCombinedMatrixPointer = new D3DXMATRIX*[numBones];
	    
		// Pegue cada matriz de offset de osso para n�o precisarmos peg�-las mais
		// tarde
	    for (UINT i = 0; i < numBones; i++)
	        newMeshPack->exBoneOffsets[i] = 
			*(newMeshPack->pSkinInfo->GetBoneOffsetMatrix(i));
		
		// Nota importante:  Nos exemplos da Microsoft a fun��o GenerateSkinnedMesh() 
		// � chamada aqui para preparar os dados de skinning do mesh para  obter  uma 
		// �tima performance de acelera��o de hardware. Como mencionado anteriormente, 
		// este exemplo n�o realiza o skinning em hardware mas  ao  inv�s  utiliza  o 
		// skinning feito em software que � mais f�cil de entender.
	}
	else	
	{		
		// N�o tem informa��o de skin, ent�o vamos zerar os ponteiros relativos
		newMeshPack->pSkinInfo = 0;
		newMeshPack->exBoneOffsets = 0;
		newMeshPack->exSkinMesh = 0;
		newMeshPack->exFrameCombinedMatrixPointer = 0;
	}
	
	//  Quando pegamos o dispositivo, n�s causamos a incrementa��o do contador de
	//  refer�ncias ent�o agora precisamos liber�-lo.
	pd3dDevice->Release();
	
	// O mesh pode conter refer�ncia a arquivos de efeito
	if (_effectInstances)
	{
		// N�o fa�a nada. O arquivo de efeito localizado n�o � tratado
		// por esta aplica��o.			
		if (_effectInstances->pEffectFilename) int dummy = 0;
		
	} // endif
	
	// Configure o ponteiro de sa�da para o nosso rec�m-criado mesh container
	*_outNewMeshPack = newMeshPack;    
	return S_OK;
}

// CMeshHierarchy::DestroyFrame() - Esse m�todo desaloca dados de frame
HRESULT CMeshHierarchy::DestroyFrame(LPD3DXFRAME frameToFree) 
{	
	// Converte para nosso tipo estendido. OK para fazer isso porque temos
    // certeza de que temos um frame aqui
	OSSO *frame = (OSSO*) frameToFree;

	if (frame->Name)
		delete[] frame->Name;
	delete frame;

    return S_OK; 
}

// CMeshHierarchy::DestroyMeshContainer() - Esse m�todo desaloca dados
// de mesh container
HRESULT CMeshHierarchy::DestroyMeshContainer( LPD3DXMESHCONTAINER 
											 meshContainerBase)
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
	
	// Libera��o das texturas depois de deletar a array
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

	// informa��o de adjac�ncia
	if (meshContainer->pAdjacency)
		delete[] meshContainer->pAdjacency;
	
	// pe�a dos ossos
	if (meshContainer->exBoneOffsets)
	{
		delete[] meshContainer->exBoneOffsets;
		meshContainer->exBoneOffsets=0;
	}
	
	// matrizes de frame
	if (meshContainer->exFrameCombinedMatrixPointer)
	{
		delete[] meshContainer->exFrameCombinedMatrixPointer;
		meshContainer->exFrameCombinedMatrixPointer=0;
	}
	
	// libera��o do skin mesh
	if (meshContainer->exSkinMesh)
	{
		meshContainer->exSkinMesh->Release();
		meshContainer->exSkinMesh=0;
	}
	
	// libera��o do mesh principal
	if (meshContainer->MeshData.pMesh)
	{
		meshContainer->MeshData.pMesh->Release();
		meshContainer->MeshData.pMesh=0;
	}
		
	// libera��o da informa��o de skin
	if (meshContainer->pSkinInfo)
	{
		meshContainer->pSkinInfo->Release();
		meshContainer->pSkinInfo=0;
	}	

	// Finalmente deletamos o container
	delete meshContainer;
	meshContainer=0;

    return S_OK;
}

// fim do arquivo Hierarquia.cpp
