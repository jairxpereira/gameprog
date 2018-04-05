#include "cubo.h"
#include "customvertex.h"

Cubo::Cubo(IDirect3DDevice9* device)
{

	// Acesso ao dispositivo
	m_device = device;

	// Criação do vertexbuffer
	m_device->CreateVertexBuffer(
		24 * sizeof(CustomVertex_PositionNormalTextured), 
		D3DUSAGE_WRITEONLY,	CustomVertex_PositionNormalTextured_Format,
		D3DPOOL_MANAGED, &m_vb,	0);

	// Ponteiro para os vértices
	CustomVertex_PositionNormalTextured* verts;
	
	// Acesso ao vertexbuffer
	m_vb->Lock(0, 0, (void**)&verts, 0);

	// Construção da caixa
	// face frontal
	verts[0] = CustomVertex_PositionNormalTextured(-1.0f, -1.0f, -1.0f, 
		0.0f, 0.0f, -1.0f, 0.0f, 0.0f);
	verts[1] = CustomVertex_PositionNormalTextured(-1.0f,  1.0f, -1.0f, 
		0.0f, 0.0f, -1.0f, 0.0f, 1.0f);
	verts[2] = CustomVertex_PositionNormalTextured( 1.0f,  1.0f, -1.0f, 
		0.0f, 0.0f, -1.0f, 1.0f, 1.0f);
	verts[3] = CustomVertex_PositionNormalTextured( 1.0f, -1.0f, -1.0f, 
		0.0f, 0.0f, -1.0f, 1.0f, 0.0f);

	// face traseira
	verts[4] = CustomVertex_PositionNormalTextured(-1.0f, -1.0f, 1.0f, 
		0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
	verts[5] = CustomVertex_PositionNormalTextured( 1.0f, -1.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f);
	verts[6] = CustomVertex_PositionNormalTextured( 1.0f,  1.0f, 1.0f, 
		0.0f, 0.0f, 1.0f, 1.0f, 1.0f);
	verts[7] = CustomVertex_PositionNormalTextured(-1.0f,  1.0f, 1.0f, 
		0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	// face do topo
	verts[8]  = CustomVertex_PositionNormalTextured(-1.0f, 1.0f, -1.0f, 
		0.0f, 1.0f, 0.0f, 0.0f, 0.0f);
	verts[9]  = CustomVertex_PositionNormalTextured(-1.0f, 1.0f,  1.0f, 
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
	verts[10] = CustomVertex_PositionNormalTextured( 1.0f, 1.0f,  1.0f, 
		0.0f, 1.0f, 0.0f, 1.0f, 1.0f);
	verts[11] = CustomVertex_PositionNormalTextured( 1.0f, 1.0f, -1.0f, 
		0.0f, 1.0f, 0.0f, 1.0f, 0.0f);

	// face do fundo
	verts[12] = CustomVertex_PositionNormalTextured(-1.0f, -1.0f, -1.0f, 
		0.0f, -1.0f, 0.0f, 0.0f, 0.0f);
	verts[13] = CustomVertex_PositionNormalTextured( 1.0f, -1.0f, -1.0f, 
		0.0f, -1.0f, 0.0f, 0.0f, 1.0f);
	verts[14] = CustomVertex_PositionNormalTextured( 1.0f, -1.0f,  1.0f, 
		0.0f, -1.0f, 0.0f, 1.0f, 1.0f);
	verts[15] = CustomVertex_PositionNormalTextured(-1.0f, -1.0f,  1.0f, 
		0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

	// face da esquerda
	verts[16] = CustomVertex_PositionNormalTextured(-1.0f, -1.0f,  1.0f, 
		-1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	verts[17] = CustomVertex_PositionNormalTextured(-1.0f,  1.0f,  1.0f, 
		-1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	verts[18] = CustomVertex_PositionNormalTextured(-1.0f,  1.0f, -1.0f, 
		-1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	verts[19] = CustomVertex_PositionNormalTextured(-1.0f, -1.0f, -1.0f, 
		-1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// face da direita
	verts[20] = CustomVertex_PositionNormalTextured( 1.0f, -1.0f, -1.0f, 
		1.0f, 0.0f, 0.0f, 0.0f, 0.0f);
	verts[21] = CustomVertex_PositionNormalTextured( 1.0f,  1.0f, -1.0f, 
		1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	verts[22] = CustomVertex_PositionNormalTextured( 1.0f,  1.0f,  1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f, 1.0f);
	verts[23] = CustomVertex_PositionNormalTextured( 1.0f, -1.0f,  1.0f, 
		1.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Libera o vertexbuffer para o directx
	m_vb->Unlock();

	// Criação do indexbuffer
	m_device->CreateIndexBuffer(36 * sizeof(WORD),D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,	D3DPOOL_MANAGED,	&m_ib,	0);

	// Ponteiro para o conjunto de índices
	WORD* indices = 0;

	// Acesso ao buffer de índices
	m_ib->Lock(0, 0, (void**)&indices, 0);

	// face frontal
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 0; indices[4] = 2; indices[5] = 3;

	// face traseira
	indices[6] = 4; indices[7]  = 5; indices[8]  = 6;
	indices[9] = 4; indices[10] = 6; indices[11] = 7;

	// face do topo
	indices[12] = 8; indices[13] =  9; indices[14] = 10;
	indices[15] = 8; indices[16] = 10; indices[17] = 11;

	// face do fundo
	indices[18] = 12; indices[19] = 13; indices[20] = 14;
	indices[21] = 12; indices[22] = 14; indices[23] = 15;

	// face da esquerda
	indices[24] = 16; indices[25] = 17; indices[26] = 18;
	indices[27] = 16; indices[28] = 18; indices[29] = 19;

	// face da direita
	indices[30] = 20; indices[31] = 21; indices[32] = 22;
	indices[33] = 20; indices[34] = 22; indices[35] = 23;

	m_ib->Unlock();
} // Cubo().fim 

Cubo::~Cubo()
{	
	// Libera vertexbuffer
	if (m_vb != NULL) m_vb->Release();
	
	// Libera indexbuffer
	if (m_ib != NULL) m_ib->Release();

	// Limpa os ponteiros
	m_vb = NULL;	
	m_ib = NULL;

} // fim do destrutor

bool Cubo::desenhar(IDirect3DTexture9* tex)
{	
	m_device->SetTexture(0, tex);

	m_device->SetStreamSource(0, m_vb, 0, sizeof(CustomVertex_PositionNormalTextured));
	
	m_device->SetIndices(m_ib);
	
	m_device->SetFVF(CustomVertex_PositionNormalTextured_Format);
	
	m_device->DrawIndexedPrimitive(	D3DPT_TRIANGLELIST, 0, 0, 24, 0,	12);  

	return true;
}