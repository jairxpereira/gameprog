// [---
// -----------------------------------------------------------------------------
// Projeto: prj_HLSL01 - Arquivo: motor.h
// Esta aplicação mostra como renderizar um 
// quadrado  colorido  com  HLSL. 
// By www.gameprog.com.br
// -----------------------------------------------------------------------------
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

#ifndef motor_h
	#define motor_h

// Definição do formato de vértice utilizado por esta aplicação
#define CustomVertex_PositionOnly_Format ( D3DFVF_XYZ )

// Estrutura de vértice customizado com posição apenas.
struct CustomVertex_PositionOnly
{
	float x, y, z;

	// Construtor default
	CustomVertex_PositionOnly() {}

	CustomVertex_PositionOnly( float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;

	}
}; // fim da estrutura CustomVertex_PositionOnly

// Esta função inicializa o Direct3D
HRESULT initGfx (HWND hJanela);

// Essa função libera os objetos utilizados
void Limpar();

// Essa função coordena a renderização a cena
void Renderizar();

// Essa função inicializa o buffer de vértices
void inicializar_Buffers(void);

// Essa função monta as formas geométricas
void montar_Geometria (void);

// Renderiza as formas geométricas
void renderizar_Geometria (void);

// Faz a configuração inicial da câmera
void inicializar_Camera(void); 

// Elabora a declaração de vértices 
void DeclararVertices_Auto(void);
void DeclararVertices_Manual(void);

// Inicializa o objeto efeito
void inicializarEfeito(void);

// Atualiza a câmera
void atualizarCamera(void);

	//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela ( HWND hJanela, UINT mensagem, 
	WPARAM wParam, LPARAM lParam);

#endif
// ---]
