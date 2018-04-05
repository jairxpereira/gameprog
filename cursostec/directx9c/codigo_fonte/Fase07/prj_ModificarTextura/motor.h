// [---
//-----------------------------------------------------------------------------
// Projeto: prj_ModificarTextura - Arquivo: motor.h
// Esta aplicação mostra como modificar uma textura em tempo de execução
// By www.gameprog.com.br
//-----------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Desliga aviso de 'função insegura' devido ao uso das
// funções de string ( strcat etc... )
#pragma warning( disable:4996 )

#ifndef motor_h
	#define motor_h

// Estrutura para receber dados de cor da textura
struct ARGBCOR
{
	unsigned char a, r, g, b;
};

// Estrutura para controle de rotação e posição do objeto
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

	// Monta a câmera da aplicação
	void inicializar_Camera(void);

	// Desenha o modelo 3d
	void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props );

	// Carrega o modelo tiny.x
	void CarregarModeloTiny();

	// Configura alguns estados da cena
	void configurar_cenaEstados(void);

	// Modifica parcialmente a textura para tons de cinza
	void modificar_Textura (IDirect3DTexture9 *textura);
	
	// Modifica completamente a textura para tons de cinza
	void modificar_TexturaEx (IDirect3DTexture9 *textura);

	//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);

#endif
// ---]
