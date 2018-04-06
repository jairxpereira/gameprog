// [---
// Projeto: prj_Luz - Arquivo: motor.h
// Esta aplicação ilustra como iluminar um triângulo
// By www.gameprog.com.br
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
	
	// Configura a câmera 3d da cena
	void inicializar_Camera(void);

	// Atualiza a câmera
	void atualizar_Camera(void);

	// Renderiza os vértices em formas geométricas
	void renderizar_Geometria (void);
	// </b>	
	// Configura alguns estados de renderização
	void configurar_cenaEstados(void);

	// Cria um material
	void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor);
	
	// Configura e coloca uma luz pointlight na cena
	void colocar_PointLight(D3DXVECTOR3 pos, D3DCOLORVALUE cvCor);	
	
	// Faz o cálculo da normal para iluminar o triângulo
	void calcularNormal(D3DXVECTOR3* p0, D3DXVECTOR3* p1,
														D3DXVECTOR3* p2, D3DXVECTOR3* pSaida);
	
	// Ajuda a visualizar a localização do ponto 3d
	void ajuda_visual(D3DXVECTOR3 pos, D3DCOLORVALUE cvCor);
	// </b>	
	//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);

#endif
// ---]
