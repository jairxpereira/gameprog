// [---
//-----------------------------------------------------------------------------
// Projeto: prj_Modelo3d - Arquivo: motor.h
// Esta aplicação mostra como carregar e renderizar
// um modelo 3d estático. By www.gameprog.com.br
//-----------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

#ifndef motor_h
	#define motor_h

// Estrutura para posição e rotação do objeto 3d
struct Propriedades3d
{
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rot;
};

	// Esta função inicializa o Direct3D
	HRESULT initGfx (HWND hJanela);

	// Essa função libera os objetos utilizados
	void Limpar();

	// Essa função desenha a cena
	void Renderizar();  	

	// Configuração inicial da câmera
	void inicializar_Camera(void);
	
	// Carrega o modelo do arquivo em disco
	void CarregarModelo( char *diretorioBase, char *arquivo);

	// Renderiza os vértices em formas geométricas
	void renderizar_Geometria (void);

	// Desenha o objeto 3d
	void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props);

	// Simplificação do modelo
	void gerarModeloSimplificado( void );

	// Configura alguns estados da cena
	void configurar_cenaEstados(void);

	// Exibição de texto
	void inicializarTexto( void );
	void mostrarTexto(int x, int y, char* texto);	

	//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (
	HWND hJanela, UINT mensagem, WPARAM wParam, LPARAM lParam);

#endif
// ---]
