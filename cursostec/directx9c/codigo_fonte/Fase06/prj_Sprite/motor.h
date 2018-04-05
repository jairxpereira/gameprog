// [---
// Projeto: prj_Sprite - Arquivo: motor.h
// Esta aplicação ilustra como renderizar uma sprite
#ifndef motor_h
	#define motor_h

	// Esta função inicializa o Direct3D
	HRESULT initGfx (HWND hJanela);

	// Essa função libera os objetos utilizados
	void Limpar();

	// Essa função desenha a cena
	void Renderizar();

  // Esta função inicializa o objeto para mostrar texto
  void inicializarTexto();   
  // Esta função mostra um texto na coordenada (x, y) da janela
  void mostrarTexto( int x, int y, char* texto);  

	// Inicializa a sprite
	void inicializarSprite();

  // Desenha a sprite
	void renderizarSprite();

	// Trata o pressionamento das setas do teclado
	void tratarTeclado( WPARAM wParam);

	//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);

#endif
// ---]
