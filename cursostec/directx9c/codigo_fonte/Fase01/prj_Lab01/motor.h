// [---
// Projeto: prj_Lab01 - Arquivo: motor.h
// Esta aplicação estabelece um ambiente para testar as
// matrizes de transformações. By www.gameprog.com.br
#ifndef motor_h
#define motor_h

// Tamanho do buffer de coleta de dados
#define nFloatBuffer 20

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
BOOL CALLBACK processaJanela( HWND hDlgWnd, UINT Message, WPARAM wParam, LPARAM lParam );

// Configura inicialmente alguns controles
void config_inicial_controles(void);

// Aumenta ou reduz o valor das variáveis
void incrementar_Variaveis(void);
void reduzir_Variaveis(void);

// Exibe a valor das variáveis nas textboxes
void mostrar_Variaveis(void);
void setFloatText (int controle, float nVal);

void atualizar_Controles(void);

// Puxa o valores das checkboxes para as variáveis
void verificar_Checkboxes(void);
bool getCheckboxState (int chk );

// Reconfigura as variáveis para os valores iniciais
void reset_Variaveis(void);

// Executa o pressionamento dos botões 
void on_wmCommand (  WPARAM wParam, LPARAM lParam  );

// Prepara o ambiente inicial antes de mostrar a janela
void on_wmInitDialog (  WPARAM wParam, LPARAM lParam  );

#endif
// ---]
