// [--- $Aspectos globais: arquivo motor.h#
//-----------------------------------------------------------------------------
// Projeto: prj_Clone - Arquivo: motor.h
// Esta aplicação mostra como clonar objetos 3d
// By www.gameprog.com.br
//-----------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>

#ifndef motor_h
	#define motor_h

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// Definição do formato de vértice com posição apenas
#define CustomVertex_PositionOnly_Format ( D3DFVF_XYZ )


// Estrutura do formato de vértice
struct CustomVertex_PositionOnly   
{       
	// Posição do vértice
	float px, py, pz;   
	
	// Construtor padrão
	CustomVertex_PositionOnly(){}   
    
	// Construtor alternativo
	CustomVertex_PositionOnly(float _x, float _y, float _z )   
    {            
		// Configuração da posição
		px = _x;   		 
		py = _y;   		
		pz = _z;     
    } // fim do construtor      
};  // fim da estrutura CustomVertex_PositionOnly


// Estrutura para auxiliar no posicionamento, rotação e cor do objeto 3d
struct Propriedades3d
{
	// Posição, rotação e cor
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

	// Renderiza os vértices em formas geométricas
	void renderizar_Geometria (void);
	
	// Faz a configuração inicial da câmera
	void inicializar_Camera(void);

	// Configura o texto da janela
	void config_janelaTexto( char *texto);

	// Renderiza um objeto 3d do tipo ID3DXMesh
	void desenharObjeto ( ID3DXMesh *obj3d, Propriedades3d *props);

	// Prepara o material do objeto 3d
	void criarMaterial(D3DMATERIAL9 *mtl, D3DCOLORVALUE cvCor );

	// Coloca uma luz direcional na cena
	void colocar_DirectionalLight(D3DXVECTOR3 direcao, D3DCOLORVALUE cvCor);

	// Configura alguns estados da cena
	void configurar_cenaEstados(void);
	
	// Exbição de texto
	void inicializarTexto( void );
	void mostrarTexto(int x, int y, char* texto) ;

	//  Declaração da função que atende as mensagens da janela
	LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
								WPARAM wParam, LPARAM lParam);

#endif
// ---]
// fim do arquivo motor.h

