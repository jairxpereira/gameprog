// -----------------------------------------------------------------------------
// Projeto: prj_PointSprite - Arquivo: motor.h
// Esta aplicação mostra como renderizar partículas com pontosprites
// By www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <d3d9.h>
#include <d3dx9.h>

// Inclui as bibliotecas do Direct3D 
#pragma comment ( lib, "d3d9.lib" )
#pragma comment ( lib, "d3dx9.lib")

// [--- $Aspectos globais - arquivo motor.h#
#ifndef motor_h
	#define motor_h
 // <b>
 // Definição do formato de vértice de suporte ao pontosprite
 #define CustomVertex_PointSprite_Format ( D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE )
 
 // Formato de vértice de suporte ao ponto sprite
 struct CustomVertex_PointSprite
 {
	 // Posição e tamanho do pontosprite
	 float x, y, z, nTamanho;
	
	 // Cor do pontosprite
	 DWORD dwCor;
 };

 // Inicializar a configuração de pointsprite
 void inicializar_Pointsprite(void);

 // Renderiza o objeto Pointsprite
 void renderizar_Pointsprite();
 // </b>
 

 // Esta função inicializa o Direct3D
 HRESULT initGfx (HWND hJanela);

 // Essa função libera os objetos utilizados
 void Limpar();

 // Essa função desenha a cena
 void Renderizar();  	

 // Configuração inicial da câmera
 void inicializar_Camera(void);

//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (
HWND hJanela, UINT mensagem, WPARAM wParam, LPARAM lParam);

#endif
// ---]
// fim do arquivo: motor.h
