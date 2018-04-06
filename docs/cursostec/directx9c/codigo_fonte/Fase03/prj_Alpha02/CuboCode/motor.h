// [---
// Projeto: prj_Alpha02 - Arquivo: motor.h
// Esta aplicação mostra os efeitos de alpha blending
// com um objeto texturizado
// Produzido por www.gameprog.com.br - Créditos: Frank Luna
#ifndef motor_h
	#define motor_h	

	#pragma comment (lib, "d3d9.lib")
	#pragma comment (lib, "d3dx9.lib")
	#pragma comment (lib, "winmm.lib")

	// Estrutura para guardar cor, posição e rotação do objeto 3d
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
	// <b>	

	// Essa função monta formas geométricas
	void montar_Geometria (void);

	// Renderiza os vértices em formas geométricas
	void renderizar_Geometria (void);

	// Inicializa a textura
	void inicializar_Textura(void);

	// Inicializa a câmera
	void inicializar_Camera(void);

	// Configura o texto da janela
	void config_janelaTexto( char *texto);	
	
	// Cria um material com a cor especificada
	void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor );

	// Desenha um quadriângulo
	void desenhar_Quad( Propriedades3d *props );
	// </b>

	void desenhar_Cubo(Propriedades3d *props);

	//  Declaração da função que atende as mensagens da janela
 LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);

#endif
// ---]
