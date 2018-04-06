// [---
//-----------------------------------------------------------------------------
// Projeto: prj_Alpha02 - Arquivo: motor.h
// Esta aplicação mostra os efeitos de alpha blending
// com um objeto texturizado
// Produzido por www.gameprog.com.br 
//-----------------------------------------------------------------------------
#ifndef motor_h
	#define motor_h	

 #pragma comment (lib, "d3d9.lib")
 #pragma comment (lib, "d3dx9.lib")

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

	// Estrutura para guardar cor, posição e rotação do objeto 3d
	struct Propriedades3d
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 rot;
		D3DCOLORVALUE cor;
	};

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
	
	// Cria um material com a cor especificada
	void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor );

	// Desenha o quadriângulo de fundo
	void desenhar_Cortina(Propriedades3d *props );	

	// Desenha o quad de frente
	void desenhar_Quad(Propriedades3d *props);

	//  Declaração da função que atende as mensagens da janela
 LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);

#endif
// ---]
