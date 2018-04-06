// -----------------------------------------------------------------------------
// Projeto: prj_Indexbuffer - Arquivo: motor.h
// Exemplo de renderização de um quadrado usando indexbuffer
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <xnamath.h>
#include <d3d11.h>

#if !defined motor_h
#define motor_h

// [--- $Aspectos globais: arquivo motor.h#
// Formato de vértice com posição e cor
//--------------------------------------------------------------------------------------
struct CustomVertex_PositionColored
{
	// Posição do vértice (Pos.x, Pos.y, Pos.z)
	XMFLOAT3 Pos;	
	
	// Cor dos vértices (Color.r, Color.g, Color.b, Color.a)
	XMFLOAT4 Color;

	// Construtor padrão
	CustomVertex_PositionColored() {}

	// Construtor alternativo e mais usado
	CustomVertex_PositionColored(XMFLOAT3 _Pos, XMFLOAT4 _Color)
	{
		Pos   = _Pos;
		Color = _Color;

	} // fim do construtor	

}; // fim da estrutura CustomVertex_PositionColored
	
	// Essa função preenche uma array de vértices montando um quadrado
	void montar_Geometria(void);

	// Essa função declara o layout de vértice utilizado
	HRESULT declarar_Vertexlayout(void);

	// Essa função inicializa o vertexbuffer. O vertexshader e a geometria devem
	// ser inicializados antes dele.
	HRESULT inicializar_Vertexbuffer(void);
	// <b>
	// Inicialização do indexbuffer
	HRESULT inicializar_Indexbuffer(void);
	// </b>
	// Função de processamento de mensagens da janela
	LRESULT CALLBACK    processaJanela( HWND, UINT, WPARAM, LPARAM );	
	
	// Inicializa o motor gráfico
	HRESULT initGfx();
	
	// Função de renderizar a cena
	void	Renderizar( void );	

	// Esta função compila um programa hlsl produzindo o vertexshader
	// ou o pixelshader
	HRESULT compilarEfeito( WCHAR* sArquivo, LPCSTR sEntradaFn, 
		LPCSTR sShaderMdl, ID3DBlob** hlslCompilado );

	// Essa função chama compilarEfeito() para inicializar o pixelshader e
	// o vertexshader
	HRESULT inicializar_Efeito(void);
	
	// Função de liberar os objetos utilizados pela aplicação
	void	Limpar( void );	

#endif
// endfile: motor.h
// ---]