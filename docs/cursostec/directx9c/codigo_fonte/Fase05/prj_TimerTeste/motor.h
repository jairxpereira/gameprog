// [--- $Aspectos globais - Arquivo motor.h#
// -----------------------------------------------------------------------------
// Projeto: prj_TimerTeste - Arquivo: motor.h
// Esta aplicação mostra como utilizar o timer de alta precisão
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------
#ifndef motor_h
	#define motor_h

	// Mostra os indicadores de performance da aplicação
	void mostrarTempo();
	void mostrarTempoEx();
	
	// Exibe uma mensagem temporizada
	void mostrarMensagemTemporizada();

	// Atualiza posição do 'jogador' na tela
	void atualizaMovimento();

	// Esta função inicializa o Direct3D
	HRESULT initGfx (HWND hJanela);

	// Essa função libera os objetos utilizados
	void Limpar();

	// Essa função desenha a cena
	void Renderizar();
  
	// Esta função inicializa o objeto para mostrar texto
    void inicializarTexto(); 

	// Esta função mostra um texto na coordenada (x, y) da janela
  void mostrarTexto( int x, int y, char* texto);  

		//  Declaração da função que atende as mensagens da janela
	LRESULT CALLBACK processaJanela (HWND hJanela, UINT mensagem, 
			WPARAM wParam, LPARAM lParam);

#endif
// ---]
// fim do arquivo: motor.h




