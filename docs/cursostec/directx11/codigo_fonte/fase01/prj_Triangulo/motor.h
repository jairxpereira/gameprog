//-----------------------------------------------------------------------------
// Projeto: prj_Triangulo - Arquivo: motor.h
// Exemplo de renderização de um triângulo com HLSL (directx 11)
// Produzido por www.gameprog.com.br
//-----------------------------------------------------------------------------
#include <windows.h>
#include <xnamath.h>
#include <d3d11.h>

#if !defined motor_h
#define motor_h

// [--- $Aspectos globais: arquivo motor.h#
// Formato de vértice apenas com posição
//--------------------------------------------------------------------------------------
struct CustomVertex_Position
{
	// Posição do vértice (Pos.x, Pos.y, Pos.z)
	XMFLOAT3 Pos;	

	// Construtor padrão
	CustomVertex_Position() {}

	CustomVertex_Position(XMFLOAT3 _Pos)
	{
		Pos = _Pos;
	} // fim do construtor	

}; // fim da estrutura CustomVertex_Position

	
	// Esta função compila um programa hlsl produzindo o vertexshader
	// ou o pixelshader
	HRESULT compilarEfeito( WCHAR* sArquivo, LPCSTR sEntradaFn, 
		LPCSTR sShaderMdl, ID3DBlob** hlslCompilado );

	// Essa função chama compilarEfeito() para inicializar o pixelshader e
	// o vertexshader
	HRESULT inicializar_Efeito(void);

	// Essa função preenche uma array de vértices montando um triângulo
	void montar_Geometria(void);

	// Essa função declara o layout de vértice utilizado
	HRESULT declarar_Vertexlayout(void);

	// Essa função inicializa o vertexbuffer. O vertexshader e a geometria devem
	// ser inicializados antes dele.
	HRESULT inicializar_Vertexbuffer(void);
	// ---]

	// Função de processamento de mensagens da janela
	LRESULT CALLBACK    processaJanela( HWND, UINT, WPARAM, LPARAM );	

	// Inicializa o motor gráfico
	HRESULT initGfx();
	
	// Função de renderizar a cena
	void	Renderizar( void );
	
	// Função de liberar os objetos utilizados pela aplicação
	void	Limpar( void );	

#endif
// endfile: motor.h