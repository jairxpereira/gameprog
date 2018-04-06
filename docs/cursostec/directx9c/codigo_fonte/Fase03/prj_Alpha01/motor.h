// [---
//-----------------------------------------------------------------------------
// Projeto: prj_Alpha01 - Arquivo: motor.h
// Esta aplicação mostra os efeitos de mistura de cor (blending)
// Produzido por www.gameprog.com.br
//-----------------------------------------------------------------------------
#ifndef motor_h
	#define motor_h

// Estrutura para guardar a coordenada de textura
struct TexCoord
{
			// Coordenada de textura
			float tu, tv;	

			// Construtor default
			TexCoord() {}

			TexCoord( float _tu, float _tv)
			{			
				// Configura coordenada textura
				tu = _tu;
				tv =_tv;
			}
}; // fim da estrutura TexCoord

// Estrutura para guardar cor, posição e rotação do objeto 3d
struct Propriedades3d
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
	D3DCOLORVALUE cor;
};


	
// Definição do formato de vértice utilizado por esta aplicação
#define CustomVertex_PositionTextured_Format ( D3DFVF_XYZ | D3DFVF_TEX1 )


// Estrutura de vértice customizado
struct CustomVertex_PositionTextured
{
	// Posição do vértice
	float x, y, z;

	// Coordenada da textura
	float tu, tv;

	// Construtor default
	CustomVertex_PositionTextured() {}

	CustomVertex_PositionTextured( float _x, float _y, float _z, TexCoord texcoord)
	{
		// Configura posição
		x = _x;
		y = _y;
		z = _z;

		// Configura textura
		tu = texcoord.tu;
		tv = texcoord.tv;
	} // fim do construtor

}; // fim da estrutura CustomVertex_PositionTextured


	// Esta função inicializa o Direct3D
	HRESULT initGfx (HWND hJanela);

	// Essa função libera os objetos utilizados
	void Limpar();

	// Essa função desenha a cena
	void Renderizar();  

	// Essa função monta formas geométricas
	void montar_Geometria (void);

	// Renderiza os vértices em formas geométricas
	void renderizar_Geometria (void);

	// Inicializa a textura
	void inicializar_Textura(void);

	// Inicializa a câmera
	void inicializar_Camera(void);

	// Configura o texto da janela
	void config_janelaTexto( char *texto);
	
	// Desenha um objeto 3d
	void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props);
	
	// Cria um material com a cor especificada
	void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor );

	// Desenha um quadrilátero (quad)
	void desenhar_Quad( Propriedades3d *props );

	//  Declaração da função que atende as mensagens da janela
 LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);

#endif
// ---]
