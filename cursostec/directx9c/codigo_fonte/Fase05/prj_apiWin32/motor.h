// [--- $Aspectos globais - Arquivo motor.h#
//-----------------------------------------------------------------------------
// Projeto: prj_apiWin32 - Arquivo: motor.h
// Esta aplicação mostra como manipular mouse e teclado
// utilizando a api nativa do Windows. 
// Produzido por www.gameprog.com.br
//-----------------------------------------------------------------------------
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

	// Verifica e processa o pressionamento das teclas
	void tratarTeclado(void);
  
  // verifica e processa o pressionamento do mouse
	void tratarMouse (UINT mensagem, WPARAM wParam, LPARAM lParam);

	// Essa função configura a posição do jogador
	void setJogadorPos( int xpos, int ypos);

	// Esta função mostra um texto na coordenada (x, y) da janela
  void mostrarTexto( int x, int y, char* texto);  

		//  Declaração da função que atende as mensagens da janela
	LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
			WPARAM wParam, LPARAM lParam);
#endif
// ---]





