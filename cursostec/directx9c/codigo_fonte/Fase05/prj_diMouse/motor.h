// [--- $Aspectos globais: arquivo: motor.h#
//------------------------------------------------------
// Projeto: prj_diMouse - Arquivo: motor.h
// Esta aplicação mostra como utilizar o mouse via 
// DirectInput. Produzido por www.gameprog.com.br
//------------------------------------------------------
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

// Configura posição do jogador
void setJogadorPos( int xpos, int ypos);

// Esta função mostra um texto na coordenada (x, y) da janela
void mostrarTexto( int x, int y, char* texto); 

// Essa função inicializa o objeto DirectInput
bool inicializar_DirectInput();

// Inicialização do dispositivo de acesso ao mouse
bool inicializar_Mouse();

// Essa função trata o mouse via DirectInput
HRESULT tratarMouse(void);

// Libera os objetos do DirectInput
void limpar_DirectInput();

//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
			WPARAM wParam, LPARAM lParam);
#endif
// ---]

