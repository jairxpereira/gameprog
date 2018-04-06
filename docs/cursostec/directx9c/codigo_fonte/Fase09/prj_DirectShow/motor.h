
// [---  
//-----------------------------------------------------------------------------
// Projeto: prj_DirectShow - Arquivo: motor.h
// Esta aplicação mostra como tocar vídeo e música
// com o DirectShow. By www.gameprog.com.br
// -----------------------------------------------------------------------------
#ifndef motor_h
	#define motor_h

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

#pragma warning (disable: 4996)


// Indicação se o DirectShow está tocando música ou vídeo
#define modo_video	1
#define modo_musica -1

// Definição do formato de vértice utilizado por esta aplicação
#define CustomVertex_PositionColored_Format ( D3DFVF_XYZ | D3DFVF_DIFFUSE )

// Estrutura do vértice customizado
struct CustomVertex_PositionColored
{
	float x, y, z;
	DWORD cor;

	// Construtor default
	CustomVertex_PositionColored() {}

	CustomVertex_PositionColored( float _x, float _y, float _z,  DWORD _cor)
	{
		x = _x;
		y = _y;
		z = _z;		
		cor = _cor;
	}
}; // fim da estrutura CustomVertex_PositionColored
	
	// Esta função inicializa o Direct3D
	HRESULT initGfx (HWND hJanela);

	// Essa função libera os objetos utilizados
	void Limpar();

	// Essa função desenha a cena
	void Renderizar();  
	
	// Essa função inicializa o buffer de índices e 
	// o buffer de vértices
	void inicializar_Buffers(void);
	
	// Essa função monta formas geométricas
	void montar_Geometria (void);

	// Renderiza os vértices em formas geométricas
	void renderizar_Geometria (void);
	
	// Configura a câmera da aplicação
	void inicializar_Camera(void);

	// <b>
	// Toca um arquivo de música ou vídeo
	void tocar_media(void);

	// Trata evento de mídia
	void tratarMediaEvento();
	// </b>

	//  Declaração da função que atende as mensagens da janela
	LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
		WPARAM wParam, LPARAM lParam);


#endif
// ---]
