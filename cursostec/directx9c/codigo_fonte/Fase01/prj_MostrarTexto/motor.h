// [---
// Projeto: prj_MostrarTexto - Arquivo: motor.h
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
#endif
// ---]





