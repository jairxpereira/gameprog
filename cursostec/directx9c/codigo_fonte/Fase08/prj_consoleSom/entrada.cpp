// [---
// Projeto: prj_consoleSom - Arquivo: entrada.cpp
// Esta aplicação exemplifica como tocar um efeito sonoro
// contido em um arquivo do formato wav
// By www.toymaker.info \\ www.gameprog.com.br 

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include "SoundPlayer.h"

// Inclusão das bibliotecas
#pragma comment ( lib, "winmm.lib")
#pragma comment ( lib, "dxguid.lib")
#pragma comment ( lib, "dsound.lib")

// Protótipo das funções
void iniciar(void);
void menu(void);

// Ponteiro para um objeto CSoundPlayer
CSoundPlayer *g_Tocador = NULL;

// Vamos precisar do handle da janela de console
HWND	hJanela;

// ---]
// [---
int main(void)
{
	// Identifica qual efeito sonoro tocar
	int nSom = 0;	

	// Controle de pressionamento das teclas
	int ntecla = 0;
	int nchar = 0;

	// Inicializa a janela de console e mostra menu
	iniciar();
	menu();

	// Cria um objeto CSoundPlayer
	g_Tocador = new CSoundPlayer;

	// Inicializa o gerenciador de som
	hJanela		= GetConsoleWindow ();
	g_Tocador->Initialise(hJanela);

	// Adiciona efeitos sonoros na fila	
	g_Tocador->AddWav("drum1.wav", &nSom);	
	g_Tocador->AddWav("drum2.wav", &nSom);	

	// Toca um som inicialmente
	g_Tocador->PlaySoundA(0, false);

	// Pressione a letra 'Q' para quebrar o laço
	while ( true )
	{
		ntecla = _kbhit();
		if (ntecla != 0) nchar = _getch();

		// Indicação de qual id de som para manipular
		if ( nchar ==  '1') 	nSom = 0;
		if ( nchar ==  '2') 	nSom = 1;

		// Mostra o som sendo manipulado na janela
		if ( nchar ==  '1') 	system("title prj_consoleSom: drum1.wav");
		if ( nchar ==  '2') 	system("title prj_consoleSom: drum2.wav");

		// Toca o som indicado
		if ( nchar ==  'P') 	g_Tocador->PlaySoundA(nSom, false);
		if ( nchar ==  'p') 	g_Tocador->PlaySoundA(nSom, false);

		// Pára o som que está sendo tocado
		if ( nchar ==  'S') 	g_Tocador->StopSound (nSom);
		if ( nchar ==  's') 	g_Tocador->StopSound (nSom);

		// Toca o som continuamente (looping)
		if ( nchar ==  'L') 	g_Tocador->PlaySoundA (nSom, true);
		if ( nchar ==  'l') 	g_Tocador->PlaySoundA (nSom, true);

		// Encerra a aplicação
		if ( nchar ==  'Q') 	break;
		if ( nchar ==  'q') 	break;	

		// Limpa as variáveis de leitura do teclado
		if ( nchar != 'Q' ) nchar = 0;
		ntecla = 0;

	} // endwhile

	// Libera o objeto CSoundPlayer
	g_Tocador->~CSoundPlayer ();

	return 1;
} // main().fim
// ---]
// [---
void iniciar(void)
{
	system("color f1");
	printf("\n");
	system("title prj_consoleSom");
} // iniciar().fim
// ---]
// [---
void menu(void)
{
	printf (" \t 1- Seleciona drum1.wav \n");
	printf (" \t 2- Seleciona drum2.wav \n\n");

	printf (" \t P- Play ( Tocar ) \n");
	printf (" \t S- Stop ( Parar ) \n");
	printf (" \t L- Loop ( Tocar continuamente ) \n\n");

	printf (" \t Q- Quit ( Sair ) \n\n");

} // menu().fim
// ---]