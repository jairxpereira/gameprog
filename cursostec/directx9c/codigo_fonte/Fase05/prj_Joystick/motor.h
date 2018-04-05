// [--- $Aspectos globais: arquivo: motor.h#
//-------------------------------------------------------------------
// Projeto: prj_Joystick - Arquivo: motor.h
// Esta aplicação mostra como utilizar o Joystick
// via DirectInput. Produzido por www.gameprog.com.br
//-------------------------------------------------------------------
#ifndef motor_h
 #define motor_h

#include <stdio.h>

// Desativa aviso de função string insegura
#pragma warning ( disable:4996 )

// ********** Classe para gravar um relatório ***********************
class Relatorio
{
public:
	FILE *m_arquivo;

// Construtor	
Relatorio() 
	{ 
		m_arquivo = NULL; 
	} // fim do construtor

// Destrutor
~Relatorio() 
	{ 
	if (m_arquivo != NULL) fclose (m_arquivo); 	
	} // fim do destrutor

	void Inicializar()
	{
	  if (m_arquivo == NULL)
		m_arquivo = fopen("joystick.txt", "wt");	
	} // abrirArquivo().fim

	void Gravar(char *info)
	{
	if (m_arquivo != NULL)
	fprintf(m_arquivo, "%s\n", info);
	} // gravarDados().fim

	void Fechar()
	{ 
		if (m_arquivo != NULL) fclose (m_arquivo); 
		m_arquivo = NULL;
	} // fecharArquivo().fim
}; // fim da classe Relatorio
// ********** Classe para gravar um relatório ***********************

// Esta função inicializa o Direct3D
HRESULT initGfx (HWND hJanela);

// Essa função libera os objetos utilizados
void Limpar();

// Essa função desenha a cena
void Renderizar();

// Esta função inicializa o objeto para mostrar texto
void inicializarTexto(); 

// Configura posição do jogador
void setJogadorPos( int xpos, int ypos);

// Esta função mostra um texto na coordenada (x, y) da janela
void mostrarTexto( int x, int y, char* texto); 

// Essa função inicializa o objeto DirectInput
bool inicializar_DirectInput();

// Mostra informações de estados do joystick
void mostrar_joyinfo();

// Essa função trata a entrada via joystick
HRESULT tratar_Joystick(void);

// Libera os objetos do DirectInput
void limpar_DirectInput();

//  Declaração da função que atende as mensagens da janela
LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
			WPARAM wParam, LPARAM lParam);
#endif
// ---]

