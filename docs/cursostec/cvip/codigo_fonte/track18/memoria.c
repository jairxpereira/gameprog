/* Programa: memoria.c - track 18            */
/* Aloca��o de mem�ria                     */
#include "stdio.h"
#include "stdlib.h"

/* Prot�tipos */
void initSys( char *title);

/* ------------------ Fun��o main()  ------------------- */
int main(void)  {

/* Defini��o dos ponteiro que v�o receber o endere�o     */
/* inicial da �rea alocada.                              */
int *memoria = NULL;
int *memoria_inicio = NULL;

unsigned int qtd = 0;
int ncx = 0;

initSys("title memoria.c");

/* ------------------ Aloca espa�o para 100 inteiros ----- */
qtd = 100 * sizeof(int);
memoria = malloc (qtd);

/* ------------------ Mem�ria foi concedida? ------------- */
if (memoria == NULL)
{
printf(" Memoria nao concedida!");
getch();
return -1;
}

memoria_inicio = memoria;

printf(" Endereco da area de memoria: %p \n", memoria);
printf(" Tamanho: %u bytes. \n\n", qtd);

/* ---- Grava dados na mem�ria --------------------------- */
for (ncx=0; ncx < 100; ncx++)
{
*memoria = ncx+1;
memoria++;
}


/* ---- Retorna o ponteiro para o in�cio da area --------- */
memoria = memoria_inicio;


/* ---- Mostra o conte�do da �rea de mem�ria ------------- */
for (ncx=0; ncx < 100; ncx++)
{
printf (" %i", *memoria);

/* ---- Pule uma linha a cada dez nros mostrados --------- */
if ( (ncx+1) % 10 == 0) printf("\n");

memoria++;
}


/* ---- Libera a mem�ria alocada ------------------------- */
free (memoria);

getchar();
return 1;
}
    
/* ------------------ Fun��o initSys()  ------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
