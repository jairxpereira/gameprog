// [---
//-----------------------------------------------------------------------------
// Projeto: prj_Superficie - Arquivo: motor.h
// Esta aplicação mostra como renderizar a cena na textura
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
void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props);

 // Carrega o modelo tiny.x
void CarregarModeloTiny(void);

// Configura alguns estados da cena
void configurar_cenaEstados(void);

// Inicializa os objetos envolvidos na renderização 
// da cena na textura
void inicializar_texRenderizador(void);

// Renderiza a cena na textura
void renderizar_naTextura(void);

// Renderiza a sprite na tela
void renderizarSprite();

// Salva o backbuffer como arquivo de imagem no disco
void salvarImagem(void);

	//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (
	HWND hJanela, UINT mensagem, WPARAM wParam, LPARAM lParam);

#endif
// ---]
