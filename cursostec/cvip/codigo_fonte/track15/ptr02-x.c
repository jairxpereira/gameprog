/* Programa: ptr02.c - track 15 */
/* Ponteiro para uma array */
#include "stdio.h"
#include "stdlib.h"
	
/* Protótipos */
void initSys( char *title);
void nMostrar (int ndx, int x);

/* ------------------ Função main()  -------------------- */
int main(void)	{

initSys("title ponteiros");

int idade = 28;

float pi = 3.1415f;

char nome[] = "Jair Pereira";

int *pIdade;
float *pPi;
char *pNome;

pIdade = &idade;
pPi = &pi;
pNome = &nome;

int valor = 2500;

pIdade = &valor;




printf (" %i \n", idade);
printf (" %s \n", nome);
printf( " %f \n\n", pi );


printf (" pIdade: %i \n", pIdade);
printf (" pPi   : %i \n", pPi);
printf( " pNome : %i \n\n", pNome );


printf (" *pIdade: %i \n", *pIdade);
printf (" *pPi   : %f \n", *pPi);

printf( " *pNome : %s \n", pNome );

















getchar();
return 1;
}

/* ------------------ Função initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}

/* ------------------ Função nMostrar()  -------------------- */
void nMostrar(int ndx, int x) {
printf(" nValor[%i] = %i \n", ndx,x);
}
