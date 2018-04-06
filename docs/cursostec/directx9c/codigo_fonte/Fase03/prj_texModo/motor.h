//-----------------------------------------------------------------------------
// Projeto: prj_texModo - Arquivo: motor.h
// Esta aplicação mostra os modos de endereçamento de textura
// Produzido por www.gameprog.com.br
//-----------------------------------------------------------------------------
#ifndef motor_h
	#define motor_h

 // Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Estrutura para suportar coordenadas de textura
struct TexCoord
{
			// Coordenada de textura
		float tu, tv;	

		// Construtor default
		TexCoord() {}

		TexCoord( float _tu, float _tv)
		{			
			// Configura coordenada de textura
			tu = _tu;
			tv =_tv;
		}
}; // fim da estrutura TexCoord
	
// Estrutura de vértice customizado
struct CustomVertex_PositionTextured
{
	// Posição do vértice
	float x, y, z;

	// Coordenada de textura
	float tu, tv;	

	// Construtor default
	CustomVertex_PositionTextured() {}

  CustomVertex_PositionTextured( float _x, float _y, float _z, TexCoord texcoord)
	{		
		// Configura posição
		x = _x;
		y = _y;
		z = _z;

		// Configura coordenada de textura
		tu = texcoord.tu;
		tv = texcoord.tv;
	}

}; // fim da estrutura CustomVertex_PositionTextured


// Definição do formato de vértice utilizado por esta aplicação
#define CustomVertex_PositionTextured_Format ( D3DFVF_XYZ | D3DFVF_TEX1 )


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

// Mostra um texto na barra da janela
void config_janelaTexto( char *texto);	

//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);

#endif

