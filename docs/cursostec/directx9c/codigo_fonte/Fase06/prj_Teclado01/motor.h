// [---
// Projeto: prj_Teclado01 - Arquivo: motor.h
// Esta aplicação ilustra como utilizar o teclado via DirectInput
#ifndef motor_h
 #define motor_h

 // Esta função inicializa o motor gráfico
 HRESULT initGfx (HWND hJanela);

 // Essa função libera os objetos utilizados
 void Limpar();

 // Essa função desenha a cena
 void Renderizar();

 // Esta função inicializa o objeto para mostrar texto
 void inicializarTexto();   
 // Esta função mostra um texto na coordenada (x, y) da janela
 void mostrarTexto( int x, int y, char* texto);  

 // Inicializa a sprite
 void inicializarSprite();

 // Desenha a sprite
 void renderizarSprite();
 // <b>
 // Essa função inicializa o objeto DirectInput
 bool inicializar_DirectInput();

 // Essa função inicializa o dispositivo de acesso ao teclado
 bool inicializar_Teclado();
 
 // Essa função trata o pressionamento do teclado
 void tratarTeclado();

 // Essa função libera os objetos do DirectInput
 void limpar_DirectInput();
 // </b>
//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
																 WPARAM wParam, LPARAM lParam);
#endif
// ---]
