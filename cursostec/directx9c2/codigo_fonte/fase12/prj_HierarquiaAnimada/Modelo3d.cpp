// [--- $Aspectos globais: arquivo Modelo3d.cpp#
// -----------------------------------------------------------------------------
// Projeto: prj_HierarquiaAnimada - Arquivo: Modelo3d.cpp
// Esta aplicação mostra como renderizar uma hierarquia animada
// By Keith Ditchburn - Adaptação www.gameprog.com.br
// -----------------------------------------------------------------------------

#include "Modelo3d.h"
#include "Tools.h"
#include "Hierarquia.h"

// Este é o 'tempo' de transição entre um animationSet e outro
// Para ver como a fusão (merging) trabalha, aumente o valor desta
// variável para retardar a transição.
const float kMoveTransitionTime=0.25f;
// ---]

// Construtor
// [--- $CModelo::CModelo() - Construtor da classe#
CModelo::CModelo( IDirect3DDevice9 *d3dDevice) : m_d3dDevice(d3dDevice), 
m_speedAdjust(1.0f), m_firstMesh(0), m_currentTrack(0), m_currentTime(0),
m_numAnimationSets(0), m_currentAnimationSet(0), m_maxBones(0),
m_sphereRadius(0), m_sphereCentre(0,0,0), m_boneMatrices(0)
{
} // fim do construtor
// ---]

// Destrutor
// [--- $CModelo::~CModelo() - Destrutor da classe#
CModelo::~CModelo(void)
{
	
	// Deleta o controlador de animações
	if ( m_animController )
	{
		m_animController->Release();
		m_animController=0;
	} // endif

	// Deleta a hierarquia
	if (m_frameRoot)
	{		
		// Cria uma instância da classe de gestão da hierarquia para
		// controlar a remoção de memória da hierarquia de frames
		CMeshHierarchy memoryAllocator;
		D3DXFrameDestroy( m_frameRoot, &memoryAllocator);
		m_frameRoot = 0;
	} // endif

	// Deleta as matrizes dos ossos
	if (m_boneMatrices)
	{
		delete[] m_boneMatrices;
		m_boneMatrices = 0;
	} // endif
} // fim do destrutor
// ---]

// [--- $Load() - Carregando a hierarquia#
// Carrega o arquivo x
// A função D3DXLoadMeshHierarchyFromX() requer um objeto de suporte para
// manipular a alocação\desalocação de memória para ossos e meshes.  Esse
// objeto se concretiza em uma instância da classe CMeshHierarchy
bool CModelo::Load(const std::string &filename)
{
	// Cria o objeto da classe de gestão da hierarquia para controlar a 
	// alocação de memória. Apenas usada temporariamente.
	CMeshHierarchy *memoryAllocator = new CMeshHierarchy;	
	
	// Para facilitar a localização de texturas, atualize o diretório atual
	// para o diretório que contém o arquivo x.  Primeiro  vamos  guardar o
	// diretório corrente para recuperá-lo depois.
	std::string currentDirectory = Tools::GetTheCurrentDirectory();
	std::string xfilePath;
	Tools::SplitPath(filename,&xfilePath,&m_filename);
	SetCurrentDirectory(xfilePath.c_str());
	
	// Esta  função  faz  todo  o  trabalho  de  carregar  o  arquivo x.  Nós
	// providenciamos um ponteiro para  uma  instância  do  nosso  objeto  de
	// alocação de memória para manipulação da alocação de memória que ocorre
	// no carregamento dos frames e dos meshes
	HRESULT hr = D3DXLoadMeshHierarchyFromX( filename.c_str(), 
		D3DXMESH_MANAGED, m_d3dDevice, 	memoryAllocator, 
		NULL, &m_frameRoot, &m_animController);

	// Nesse momento a aplicação já se apossou do conteúdo do arquivo
	// para dentro de suas variáveis internas. Agora podemos deletar
	// a instância temporária da classe CMeshHierarchy
	delete memoryAllocator;
	memoryAllocator = 0;

	// Recupera o diretório corrente
	SetCurrentDirectory(currentDirectory.c_str());
	
	// Retorne se ocorreu alguma falha
	if ( Tools::FailedHr(hr) ) return false; 
	
	// Se o arquivo x contém alguma animação, vamos salvar quantos 
	// sets de animação ele têm.
	if(m_animController)
		m_numAnimationSets = m_animController->GetMaxNumAnimationSets();

	
	// Ossos para o skinning
	if ( m_frameRoot )
	{		
		// Configuração inicial dos ossos
		SetupBoneMatrices( (OSSO*) m_frameRoot, NULL );
		
		// Cria a array das matrizes de ossos para usar durante BoneMove() 
		// para segurar a transformação final
		m_boneMatrices  = new D3DXMATRIX[ m_maxBones ];
		ZeroMemory( m_boneMatrices, sizeof( D3DXMATRIX ) * m_maxBones );
		
		// Calcula   esfera   de   borda   para   este   modelo  (  usada  em
		// CalculateInitialViewMatrix() para posicionar a câmera corretamente
		D3DXFrameCalculateBoundingSphere( m_frameRoot, &m_sphereCentre, 
			&m_sphereRadius );
	} // endif ( m_frameRoot )

	return true;
} // Load().fim
// ---]




// [--- $SetupBoneMatrices() - Configuração das matrizes dos ossos#
// pFrame - o frame atual
// pParentMatrix - a matriz do frame pai (the parent frame matrix )
void CModelo::SetupBoneMatrices(OSSO *pFrame, D3DXMATRIX *pParentMatrix)
{
	
	// Primeiro realizamos um cast para nossa estrutura estendida
	MESHPACK* pMesh = ( MESHPACK* ) pFrame->pMeshContainer;
	
	// Verifica se este frame tem um mesh
	if ( pMesh )
	{
		
		// Nós precisamos identificar e salvar qual é o primeiro mesh na
		// hierarquia para usá-lo mais tarde na atualização em BoneMove()
		if( !m_firstMesh ) m_firstMesh = pMesh;		
		
		// se houver informação de skinning, então configure as matrizes de
		// ossos (bone matrices)
		if(pMesh->pSkinInfo && pMesh->MeshData.pMesh)
		{			
			// Crie uma cópia do mesh para utilizar skinning nele mais tarde
			D3DVERTEXELEMENT9 Declaration[ MAX_FVF_DECL_SIZE ];
			if ( FAILED( pMesh->MeshData.pMesh->GetDeclaration(Declaration) ) )
				return;

			// Clone o mesh agora com dados de skinning conforme declaração
			pMesh->MeshData.pMesh->CloneMesh( D3DXMESH_MANAGED, 
				Declaration, m_d3dDevice, 
				&pMesh->exSkinMesh);
			
			// m_maxBones é calculada para uso posterior para determinar depois
			// o tamanho da array de matrizes dos ossos ( bone matrices array )
			m_maxBones = max( m_maxBones, (int)pMesh->pSkinInfo->GetNumBones() );
			
			// Devemos trabalhar a matriz de cada osso individualmente
			for ( unsigned int i = 0; i < pMesh->pSkinInfo->GetNumBones(); i++ )
			{   				
				// Encontre o frame contendo o osso
				OSSO* pTempFrame = (OSSO*) D3DXFrameFind( m_frameRoot, 
						pMesh->pSkinInfo->GetBoneName(i) );

				// configure a peça do osso - aponte-o para a matriz de 
				// transformação
				pMesh->exFrameCombinedMatrixPointer[i] = 
					&pTempFrame->exCombinedTransformationMatrix;
			} // endfor

		} // endif ( pMesh->pSkinInfo && pMesh->MeshData.pMesh )
	} // endif (  pMesh )
	
	// Vamos prosseguir agora com os irmãos (sibling)
	if(pFrame->pFrameSibling)
		SetupBoneMatrices( (OSSO*) pFrame->pFrameSibling, pParentMatrix);

	// Vamos prosseguir agora com os filhos (children)
	if(pFrame->pFrameFirstChild)
		SetupBoneMatrices( (OSSO*) pFrame->pFrameFirstChild, 
		&pFrame->exCombinedTransformationMatrix);
} // SetupBoneMatrices().fim
// ---]


// [--- $BoneMove() - Movendo o osso#
// CModelo::BoneMove() - chamado a cada atualização de frame com
// o tempo e a matriz de mundo atual.
// elapsedTime - tempo decorrido
// matWorld - matriz de mundo corrente do modelo
void CModelo::BoneMove( float elapsedTime, const D3DXMATRIX *matWorld )
{	
	// Ajuste da velocidade da animação
	elapsedTime /= m_speedAdjust;
	
	// Avance o tempo e configure-o no controlador
    if (m_animController != NULL)
        m_animController->AdvanceTime(elapsedTime, NULL);

	// Vamos acumular o tempo decorrido
	m_currentTime += elapsedTime;
	
	// Agora atualize as matrizes do modelo na hierarquia
    UpdateBoneMatrices( m_frameRoot, matWorld );
	
	// Se o modelo contiver um skinned mesh atualize os vértices
	MESHPACK* pMesh = m_firstMesh;
	if( pMesh && pMesh->pSkinInfo )
	{
		unsigned int Bones = pMesh->pSkinInfo->GetNumBones();

		// Cria as matrizes de ossos que transformam cada osso de espaço de osso
		// para espaço de figura ( via  exFrameCombinedMatrixPointer)  e  também
		// embrulha o mesh ao redor dos ossos utilizando  os  'bone offsets'  em 
		// exBoneOffsetsArray
		for (unsigned int i = 0; i < Bones; ++i)
			D3DXMatrixMultiply( &m_boneMatrices[i],
			&pMesh->exBoneOffsets[i], pMesh->exFrameCombinedMatrixPointer[i]);

		// Nós precisamos modificar as posições dos vértices baseado  nas novas
		// matrizes  de  ossos.  Isso  é  obtido  através  do  trancamento  dos
		// vertexbuffers e então chamar UpdateSkinnedMesh(). UpdateSkinnedMesh()
		// pega os dados originais de vértice ( em pMesh->MeshData.pMesh ),
		// aplica as matrizes e escreve os novos vértices para o skin mesh
		// (pMesh->exSkinMesh )

		// UpdateSkinnedMesh() faz skinning em software que  é  a  maneira mais
		// lenta de realizar skinning mas é a maneira mais fácil de descrever e
		// de se trabalhar na maioria  das  placas  gráficas.   Existem  outros
		// métodos que fazem o skinning no hardware -  vejas notas e  o exemplo
		// de  skinning  em  hardware  das  amostras  de  exemplo  do  directx.

		// Tranque o vertexbuffer fonte
		void *srcPtr = 0 ;
		pMesh->MeshData.pMesh->LockVertexBuffer( D3DLOCK_READONLY, 
			(void**) &srcPtr );

		// Tranque o vertexbuffer destino
		void *destPtr = 0;
		pMesh->exSkinMesh->LockVertexBuffer(0, (void**) &destPtr );

		
		// Atualize o skinned mesh
		pMesh->pSkinInfo->UpdateSkinnedMesh( m_boneMatrices, NULL, srcPtr, 
			destPtr );
		
		// Destranque os vertexbuffers do modelo 3d
		pMesh->exSkinMesh->UnlockVertexBuffer();
		pMesh->MeshData.pMesh->UnlockVertexBuffer();
	} // endif ( pMesh && pMesh->pSkinInfo )

} // BoneMove().fim
// ---]


// [--- $UpdateBoneMatrices() - Atualizando as matrizes#
// CModelo::UpdateBoneMatrices() -  este método  é  chamado  para  atualizar as
// matrizes dos frames na hierarquia para refletir o estágio da animação atual.
// frameBase - o frame sendo verificado
// parentMatrix - a matriz dos pais (se existir um)
void CModelo::UpdateBoneMatrices(const D3DXFRAME *frameBase, 
								 const D3DXMATRIX *parentMatrix)
{
    // Realizamos um cast para nosso tipo de osso
	OSSO *currentFrame = (OSSO*) frameBase;

	// se existe uma matriz do pai, vamos multiplicar nosso frame por ela!
    if (parentMatrix != NULL)
        D3DXMatrixMultiply( &currentFrame->exCombinedTransformationMatrix, 
		&currentFrame->TransformationMatrix, parentMatrix);
    else
        currentFrame->exCombinedTransformationMatrix = 
		currentFrame->TransformationMatrix;

	// se temos um irmão, então repetimos a função aqui.
    if ( currentFrame->pFrameSibling != NULL )
        UpdateBoneMatrices(currentFrame->pFrameSibling, parentMatrix);
	
	// se temos um filho, repetimos a função.
    if (currentFrame->pFrameFirstChild != NULL)
        UpdateBoneMatrices( currentFrame->pFrameFirstChild, 
		&currentFrame->exCombinedTransformationMatrix);
} // UpdateBoneMatrices().fim
// ---]


// [--- $DrawMeshContainer() - Renderização do modelo 3d#
// DrawMeshContainer() - Chamada para renderizar o mesh
// meshContainerBase - o mesh container
// frameBase - o frame contendo o mesh

void CModelo::DrawMeshContainer(D3DXMESHCONTAINER *meshContainerBase, 
								D3DXFRAME *frameBase) const
{
	// Realizamos um cast para nosso tipo de osso
	OSSO *frame = (OSSO*) frameBase;		

	// Realizamos um cast para nosso MESHPACK
	MESHPACK *meshContainer = (MESHPACK*) meshContainerBase;
	
	// Configuração da matriz de mundo
    m_d3dDevice->SetTransform(D3DTS_WORLD, 
		&frame->exCombinedTransformationMatrix);

	
	// Vamos repassar cada material e renderizar em cada ciclo o subset do mesh
    for ( unsigned int iMaterial = 0; iMaterial < meshContainer->NumMaterials; 
		iMaterial++)
    {
		
		// Use o material estocado em nosso membro estendido ao invés do
		// nativo meshContainer->pMaterials[iMaterial].MatD3D
		m_d3dDevice->SetMaterial( &meshContainer->exMaterials[iMaterial] );
		m_d3dDevice->SetTexture( 0, meshContainer->exTextures[iMaterial] );

		
		// Selecione o tipo certo de mesh carregado para renderizar
		// Se tiver dados de skinning então renderize o skinned mesh
		// ou caso contrário o mesh normal então.
		LPD3DXMESH pDrawMesh = 
			(meshContainer->pSkinInfo) ? 
			meshContainer->exSkinMesh: meshContainer->MeshData.pMesh;
		
		// Finalmente uma chamada para renderizar o subset do mesh
        pDrawMesh->DrawSubset(iMaterial);
    } // endfor ( iMaterial )
} // DrawMeshContainer().fim
// ---]


// [--- $DrawBone() - Renderizando o modelo 3d#
// DrawBone() - Chamada para renderizar o frame na hierarquia
// device - o dispositivo renderizador do Direct3D
// frame - o frame para renderizar
void CModelo::DrawBone(D3DXFRAME *frame) const
{	
	// Desenhe todos os meshes containers neste frame
    D3DXMESHCONTAINER *meshContainer = frame->pMeshContainer;
    while (meshContainer)
    {
        DrawMeshContainer( meshContainer, frame);
        meshContainer = meshContainer->pNextMeshContainer;
    }

	// Desenhe recursivamente os irmãos ( sibblings )
    if (frame->pFrameSibling != NULL)
        DrawBone(frame->pFrameSibling);

	// Desenhe recursivamente os filhos ( children )
	if (frame->pFrameFirstChild != NULL)
        DrawBone(frame->pFrameFirstChild);
} // DrawBone().fim
// ---]


// [--- $GetInitialCameraPosition() - Obtendo a posição inicial da câmera#
// Uma vez que esta app pode carregar modelos 3d com diversas formas e tamanhos
// configurar a posição da câmera é uma tarefa difícil.   Esta  função  utiliza
// a esfera de borda do modelo como base para estabelecer a posição  da  câmera
D3DXVECTOR3 CModelo::GetInitialCameraPosition() const
{
	D3DXVECTOR3 cameraPos(0.0f, m_sphereCentre.y, - (m_sphereRadius * 3) );
	return cameraPos;
} // GetInitialCameraPosition().fim
// ---]


// [--- $Render() - Iniciando a renderização do modelo 3d animado#
// CModelo::Render() - Renderiza o mesh animado
// Chama DrawBone() recursivamente na renderização com o frame raiz
void CModelo::Render() const
{
	if (m_frameRoot)
		DrawBone( m_frameRoot );
} // Render().fim
// ---]


// [--- $SetAnimationSet() - Modificação do animation set#
// CModelo::SetAnimationSet() - Modifica o animation set
// manipula a transição entre as animações para torná-las
// suaves e evita solavancos para uma nova posição
// index - o indicador do novo animation set

void CModelo::SetAnimationSet(unsigned int index)
{
	// Se o índice indicado fora igual ao animation set corrente
	// então retorne porque não tem o que mudar.
	if (index == m_currentAnimationSet) return;

	
	// Se o índice está fora da faixa válida, vamos zerá-lo.
	if (index >= m_numAnimationSets) index = 0;
	
	// Lembre-se do animation set corrente
	m_currentAnimationSet = index;
	
	// Pegue o animation set do controlador de animações
	ID3DXAnimationSet *set;
	m_animController->GetAnimationSet( m_currentAnimationSet, &set );	

	// Nota: para uma transição suave entre as animações, nós podemos usar
	// duas trilhas e assinalar a nova animação para uma trilha vaga ( que não
	// está tocando ) e então inserir chaves ( Keys ) na trilha de chaves 
	// ( KeyTrack ) para fazer a transição entre as trilhas.
	// As trilhas podem ser misturadas juntas a fim de que possam gradualmente
	// se modificar para uma nova animação.

	
	// Alternando a nossa trilha
	DWORD newTrack = ( m_currentTrack == 0 ? 1 : 0 );
	
	// Assinale para a nossa trilha
	m_animController->SetTrackAnimationSet( newTrack, set );
    set->Release();	
	
	// Vamos limpar qualquer evento de trilha atualmente assinalados
	// em nossas trilhas
	m_animController->UnkeyAllTrackEvents( m_currentTrack );
    m_animController->UnkeyAllTrackEvents( newTrack );
	
	// Adicione uma chave de evento para desabilitar a trilha atualmente
	// tocando kMoveTransitionTime segundos no futuro.
    m_animController->KeyTrackEnable( m_currentTrack, FALSE, m_currentTime
		+ kMoveTransitionTime );	
	
	// Adicione uma chave de evento para acelerar o completamento da animação
	// corrente em kMoveTransitionTime segundos.    
    m_animController->KeyTrackSpeed( m_currentTrack, 0.0f, m_currentTime, 
		kMoveTransitionTime, D3DXTRANSITION_LINEAR );	
	
	// Adiciona um evento para mudar o peso da trilha corrente
	// ( isso afeta a mistura com a segunda trilha )
    m_animController->KeyTrackWeight( m_currentTrack, 0.0f, m_currentTime, 
		kMoveTransitionTime, D3DXTRANSITION_LINEAR );
	
	// Habilite a nova trilha
    m_animController->SetTrackEnable( newTrack, TRUE );	
	
	// Habilite uma chave de evento para configurar a velocidade
	// da trilha.
    m_animController->KeyTrackSpeed( newTrack, 1.0f, m_currentTime, 
		kMoveTransitionTime, D3DXTRANSITION_LINEAR );
	

	// Adiciona um evento para mudar o peso da trilha corrente
	// ( isso afeta a mistura com a primeira trilha )
	// Como vc pode ver isto vai caminhar de zero efeito (0.0f) até efeito
	// o total (1.0f) em kMoveTransitionTime segundos e a primeira trilha
	// vai caminhar do efeito total até 0.0f no mesmo tempo.  
	
	m_animController->KeyTrackWeight( newTrack, 1.0f, m_currentTime, 
		kMoveTransitionTime, D3DXTRANSITION_LINEAR );

    // Lembre-se da trilha corrente ( agora como nova trilha assumindo )
	m_currentTrack = newTrack;

} // SetAnimationSet().fim
// ---]


// [--- $NextAnimation() - Avanço para a próxima animação#
void CModelo::NextAnimation()
{	
	unsigned int newAnimationSet = m_currentAnimationSet + 1;
	if (newAnimationSet >= m_numAnimationSets)
		newAnimationSet = 0;

	SetAnimationSet( newAnimationSet );
} // NextAnimation().fim


// [--- $GetAnimationSetName() - Obtendo o nome da animação#
std::string CModelo::GetAnimationSetName( unsigned int index )
{
	if (index >= m_numAnimationSets )
		return "Error: No set exists";

	// Obtendo o set de animação
	ID3DXAnimationSet *set;
	m_animController->GetAnimationSet(m_currentAnimationSet, &set );

	std::string nameString(set->GetName());

	set->Release();

	return nameString;
} // GetAnimationSetName().fim
// ---]

// [--- $AnimateSlower() - Desacelerando animação#
void CModelo::AnimateSlower()
{
	m_speedAdjust += 0.1f;
} // AnimateSlower().fim


// [--- $AnimateFaster() - Acelerando a animação#
void CModelo::AnimateFaster()
{
	if (m_speedAdjust>0.1f)
		m_speedAdjust-=0.1f;
} // AnimateFaster().fim
// ---]
// fim do arquivo Modelo3d.cpp

