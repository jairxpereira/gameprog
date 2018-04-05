// [---
// Projeto: prj_Modelo3d - Arquivo: motor.h
// Esta aplicação mostra como carregar e renderizar um
// modelo 3d. By www.gameprog.com.br

#include <d3d9.h>
#include <d3dx9.h>

#ifndef motor_h
	#define motor_h

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

	void inicializar_Camera(void);

	void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props);

	void CarregarModelo( char *diretorioBase, char *arquivo);

	void configurar_cenaEstados(void);

	//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);

#endif
// ---]
