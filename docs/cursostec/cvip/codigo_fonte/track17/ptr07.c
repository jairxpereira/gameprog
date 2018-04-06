/* Programa ptr07.c - track 17                  */
/* As funções que recebem array como argumentos */ 
/* podem ser declaradas de três formas          */
#include "stdio.h"
#include "stdlib.h"

/* Protótipos */
void initSys( char *title);

void ShowArray (int vArray[10]);
void ZeraArray (int Tabela[]);
void EncheArray(int *vArray, int nValor);

int main(void)	{

int nDados[10];

initSys("title ptr07.c ");

EncheArray(nDados,15);
ShowArray (nDados);

ZeraArray (&nDados);
ShowArray (&nDados[0]);

getchar();

return 1;}

/* ------------------ Função ZeraArray()  ------------------ */
	void ZeraArray (int Tabela[]) {
	int ndx;

		for (ndx = 0; ndx < 10; ndx++)
			Tabela[ndx] = 0;

	}

/* ------------------ Função EncheArray()  ------------------ */
	void EncheArray(int *vArray, int nValor) {
	int ndx;
		for (ndx =0; ndx < 10; ndx++)
			vArray[ndx] = nValor;
	}

/* ------------------ Função ShowArray()  ------------------ */
	void ShowArray (int vArray[10]) {
	int ndx;
	printf(" ");
		for (ndx = 0; ndx < 10; ndx++)
			printf("%i ",vArray[ndx]);
		printf("\n");
	}


/* ------------------ Função initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
