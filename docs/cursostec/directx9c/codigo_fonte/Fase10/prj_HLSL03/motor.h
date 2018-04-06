// [---
// Projeto: prj_HLSL03 - Arquivo: motor.h
// Esta aplicação  ilustra  como  renderizar  um 
// modelo 3d texturizado com técnicas diferentes
// By www.gameprog.com.br
#ifndef motor_h
	#define motor_h

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Desliga aviso de 'função insegura' devido ao uso das
// funções de string ( strcat etc. . . )
#pragma warning( disable:4996 )

// Estrutura posição e rotação do objeto 3d
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

	// Renderiza o modelo 3d duas vezes com o objeto efeito
	void renderizar_Geometria (void);

	// Inicializa as matrizes da câmera
	void inicializar_Camera(void); 	

  // Inicializa o objeto efeito
	void inicializarEfeito(void);

	// Desenha o objeto 3d
	void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props);

	// Carrega o modelo 3d
	void CarregarModelo( char *diretorioBase, char *arquivo);

	//  Declaração da função que atende as mensagens da janela
  LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
									WPARAM wParam, LPARAM lParam);

#endif
// ---]
