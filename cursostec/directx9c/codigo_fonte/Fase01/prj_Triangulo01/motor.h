// [---
// Projeto: prj_Triangulo01 - Arquivo: motor.h
// Esta aplicação ilustra como renderizar um triângulo
#ifndef motor_h
	#define motor_h

	// Esta função inicializa o Direct3D
	HRESULT initGfx (HWND hJanela);

	// Essa função libera os objetos utilizados
	void Limpar();

	// Essa função desenha a cena
	void Renderizar();  
	// <b>
	// Essa função monta formas geométricas
	void montar_Geometria (void);

	// Renderiza os vértices em formas geométricas
	void renderizar_Geometria (void);
	// </b>
	//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);

#endif
// ---]
