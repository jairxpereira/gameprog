// [---
//-----------------------------------------------------------------------------
// Projeto: prj_Meshes01 - Arquivo: motor.h
// Esta aplicação mostra como renderizar as formas primitivas
// By www.gameprog.com.br
//-----------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>

#ifndef motor_h
	#define motor_h

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Estrutura para auxiliar no posicionamento, rotação e cor do objeto 3d
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

	// Renderiza os vértices em formas geométricas
	void renderizar_Geometria (void);
	
	// Faz a configuração inicial da câmera
	void inicializar_Camera(void);

	// Configura o texto da janela
	void config_janelaTexto( char *texto);

	// Renderiza um objeto 3d do tipo ID3DXMesh
	void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props);

	// Prepara o material do objeto 3d
	void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor );

	// Coloca uma luz direcional na cena
	void colocar_DirectionalLight(D3DXVECTOR3 direcao, D3DCOLORVALUE cvCor);

	// Configura alguns estados da cena
	void configurar_cenaEstados(void);

	//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);

#endif
// ---]
