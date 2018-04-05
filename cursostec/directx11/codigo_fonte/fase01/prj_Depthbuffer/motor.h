// -----------------------------------------------------------------------------
// Projeto: prj_Depthbuffer - Arquivo: motor.h
// Exemplo de uso do buffer de profundidade (directx 11)
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <xnamath.h>
#include <d3d11.h>

#if !defined motor_h
#define motor_h

// Formato de vértice com posição e cor
// --------------------------------------------------------------------------------------
struct CustomVertex_PositionColored
{
	// Posição do vértice (Pos.x, Pos.y, Pos.z)
	XMFLOAT3 Pos;	
	XMFLOAT4 Color;

	// Construtor padrão
	CustomVertex_PositionColored() {}

	CustomVertex_PositionColored(XMFLOAT3 _Pos, XMFLOAT4 _Color)
	{
		Pos   = _Pos;
		Color = _Color;

	} // fim do construtor	

}; // fim da estrutura CustomVertex_PositionColored

// Estrutura para intercâmbio de dados entre a GPU e a CPU
struct ConstantBuffer
{
	// Matriz de mundo para tranformações dos objetos 3d
	XMMATRIX mWorld;

	// Matriz de visualização
	XMMATRIX mView;
	
	// Matriz de projeção
	XMMATRIX mProjection;
}; // fim da estrutura ConstantBuffer

	// Controle de câmera
	HRESULT inicializar_Constantbuffer(void);
	void inicializar_Camera(void);	
	
	// Esta função compila um programa hlsl produzindo o vertexshader
	// ou o pixelshader
	HRESULT compilarEfeito( WCHAR* sArquivo, LPCSTR sEntradaFn, 
		LPCSTR sShaderMdl, ID3DBlob** hlslCompilado );

	// Essa função chama compilarEfeito() para inicializar o pixelshader 
	// e o vertexshader
	HRESULT inicializar_Efeito(void);

	// Essa função preenche uma array de vértices montando uma
	// forma geométrica
	void montar_Geometria(void);

	// Essa função declara o layout de vértice utilizado
	HRESULT declarar_Vertexlayout(void);

	// Essa função inicializa o vertexbuffer. O vertexshader e a geometria 
	// devem ser inicializados antes dele.
	HRESULT inicializar_Vertexbuffer(void);

	// Essa função inicializa o Indexbuffer. 
	HRESULT inicializar_Indexbuffer(void);

	// Função de processamento de mensagens da janela
	LRESULT CALLBACK    processaJanela( HWND, UINT, WPARAM, LPARAM );	

	// Inicializa o motor gráfico
	HRESULT initGfx();
	
	// [--- $Aspectos globais: arquivo motor.h#
	// <b>
	// Função para inicializar o buffer de profundidade e o stencil
	HRESULT inicializar_Depthbuffer(void);

	// Função para tratar o teclado	
	void tratarTeclado (WPARAM wParam);
		// </b>
	// ---]

	// Função principal de renderização da cena
	void	Renderizar( void );

	// Função auxiliar para renderizar o planeta (cubo central)
	void renderizar_Planeta(void);
	
	// Função auxiliar para renderizar a lua (cubo lateral )
	void renderizar_Lua(void);

	// Função para atualizar o timer de movimentação dos objetos
	void atualizar_Temporizador(void);
	
	// Função de liberar os objetos utilizados pela aplicação
	void	Limpar( void );	

#endif
// endfile: motor.h