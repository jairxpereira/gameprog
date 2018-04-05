// [---
// Projeto: prj_Triangulo3d - Arquivo: motor.h
// Esta aplicação ilustra como configurar uma câmera e 
// renderizar um triângulo 3d. By www.gameprog.com.br
#ifndef motor_h
	#define motor_h

	// Esta função inicializa o Direct3D
	HRESULT initGfx (HWND hJanela);

	// Essa função libera os objetos utilizados
	void Limpar();

	// Essa função desenha a cena
	void Renderizar();  

	// Essa função monta formas geométricas
	void montar_Geometria (void);
	// <b>
	// Configura a câmera 3d da cena
	void inicializar_Camera(void);

	// Atualiza a câmera
	void atualizar_Camera(void);
	// </b>
	// Renderiza os vértices em formas geométricas
	void renderizar_Geometria (void);

	//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);

#endif
// ---]
