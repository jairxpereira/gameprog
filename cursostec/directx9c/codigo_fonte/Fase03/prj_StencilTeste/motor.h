// [--- $Aspectos globais: arquivo motor.h#
// -------------------------------------------------------------------
// Projeto: prj_StencilTeste - Arquivo: motor.h
// Esta aplicação mostra um exemplo simples de uso do stencil
// Produzido por www.gameprog.com.br
// -------------------------------------------------------------------
#ifndef motor_h
	#define motor_h

	// Estrutura para guardar uma coordenada de textura
	struct TexCoord
		{
				// Coordenada da textura
			float tu, tv;	

			// Construtor default
			TexCoord() {}

			TexCoord( float _tu, float _tv)
			{			
				// Configura textura
				tu = _tu;
				tv =_tv;
			}
		}; // fim da estrutura TexCoord

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
	
	// Essa função monta formas geométricas
	void montar_Geometria (void);

	// Renderiza os vértices em formas geométricas
	void renderizar_Geometria (void);

	// Inicializa a textura
	void inicializar_Textura(void);

	// Inicializa a câmera
	void inicializar_Camera(void);

	// Configura estados da cena
	void configurar_cenaEstados(void);

	// Cria um material com a cor especificada
	void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor );

	// Desenha um quad
	void desenhar_Quad( Propriedades3d *props );
	
	// Exibição de texto
	void inicializarTexto();
	void mostrarTexto(int x, int y, char* texto);
	// <b>
	// Liga e desliga a renderização no backbuffer
	void desligar_backbuffer(void);
	void ligar_backbuffer(void);
	
	// Configuração do stencil para renderizar tudo
	void configurar_stencil(void);

	// Renderiza no stencil para marcá-lo
	void marcar_stencil(void);

	// Gera um valor móvel ping-pong para mover o quad
	float gerarDelta(void);
	// </b>

	//  Declaração da função que atende as mensagens da janela
 LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
			                           WPARAM wParam, LPARAM lParam);

#endif
// ---]
// fim do arquivo: motor.h