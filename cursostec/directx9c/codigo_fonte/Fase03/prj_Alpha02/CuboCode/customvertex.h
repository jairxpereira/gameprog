#ifndef customVertex_h
	#define customVertex_h

// Formato de v�rtice utilizado no cubo
#define CustomVertex_PositionNormalTextured_Format (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )

// Estrutura de v�rtice customizado com posi��o, normal e coordenada de textura
struct CustomVertex_PositionNormalTextured
{	
	// Posi��o
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
		// Configura��o da posi��o
		x = _x; 
		y = _y; 
		z = _z;
		
		// Configura��o da normal
		nx = _nx; 
		ny = _ny; 
		nz = _nz;

		// Configura��o da coordenada de textura
		tu = _tu;
		tv = _tv;

	} // fim do construtor
   
}; // CustomVertex_PositionNormalTextured


// Defini��o do formato de v�rtice utilizado por esta aplica��o
#define CustomVertex_PositionTextured_Format ( D3DFVF_XYZ | D3DFVF_TEX1 )

// Estrutura do v�rtice customizado
struct CustomVertex_PositionTextured
{
	// Posi��o do v�rtice
	float x, y, z;

	// Coordenada da textura
	float tu, tv;	

	// Construtor default
	CustomVertex_PositionTextured() {}

	CustomVertex_PositionTextured( float _x, float _y, float _z, float _tu, float _tv)
	{		
		// Configura posi��o
		x = _x;
		y = _y;
		z = _z;

		// Configura textura
		tu = _tu;
		tv = _tv;
	}

}; // fim da estrutura CustomVertex_PositionTextured
#endif
