#ifndef customVertex_h
	#define customVertex_h

// Formato de vértice utilizado no cubo
#define CustomVertex_PositionNormalTextured_Format (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )

// Estrutura de vértice customizado com posição, normal e coordenada de textura
struct CustomVertex_PositionNormalTextured
{	
	// Posição
	float x, y, z;

	// Normais
	float nx, ny, nz;
	
	// Coordenadas de textura
	float tu, tv; 
	
	CustomVertex_PositionNormalTextured(){}

	CustomVertex_PositionNormalTextured(	
		float _x, float _y, float _z,
		float _nx, float _ny, float _nz,
		float _tu, float _tv)
	{
		// Configuração da posição
		x = _x; 
		y = _y; 
		z = _z;
		
		// Configuração da normal
		nx = _nx; 
		ny = _ny; 
		nz = _nz;

		// Configuração da coordenada de textura
		tu = _tu;
		tv = _tv;

	} // fim do construtor
   
}; // CustomVertex_PositionNormalTextured


// Definição do formato de vértice utilizado por esta aplicação
#define CustomVertex_PositionTextured_Format ( D3DFVF_XYZ | D3DFVF_TEX1 )

// Estrutura do vértice customizado
struct CustomVertex_PositionTextured
{
	// Posição do vértice
	float x, y, z;

	// Coordenada da textura
	float tu, tv;	

	// Construtor default
	CustomVertex_PositionTextured() {}

	CustomVertex_PositionTextured( float _x, float _y, float _z, float _tu, float _tv)
	{		
		// Configura posição
		x = _x;
		y = _y;
		z = _z;

		// Configura textura
		tu = _tu;
		tv = _tv;
	}

}; // fim da estrutura CustomVertex_PositionTextured
#endif
