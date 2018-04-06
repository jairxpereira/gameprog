/* Programa: memoria.c - track 18            */
/* Alocação de memória                     */
#include "stdio.h"
#include "stdlib.h"

/* Protótipos */
void initSys( char *title);

/* ------------------ Função main()  ------------------- */
int main(void)  {

/* Definição dos ponteiro que vão receber o endereço     */
/* inicial da área alocada.                              */
int *memoria = NULL;
int *memoria_inicio = NULL;

unsigned int qtd = 0;
int ncx = 0;

initSys("title memoria.c");

/* ------------------ Aloca espaço para 100 inteiros ----- */
qtd = 100 * sizeof(int);
memoria = malloc (qtd);

/* ------------------ Memória foi concedida? ------------- */
if (memoria == NULL)
{
printf(" Memoria nao concedida!");
getch();
return -1;
}

memoria_inicio = memoria;

printf(" Endereco da area de memoria: %p \n", memoria);
printf(" Tamanho: %u bytes. \n\n", qtd);

/* ---- Grava dados na memória --------------------------- */
for (ncx=0; ncx < 100; ncx++)
{
*memoria = ncx+1;
memoria++;
}


/* ---- Retorna o ponteiro para o início da area --------- */
memoria = memoria_inicio;


/* ---- Mostra o conteúdo da área de memória ------------- */
for (ncx=0; ncx < 100; ncx++)
{
printf (" %i", *memoria);

/* ---- Pule uma linha a cada dez nros mostrados --------- */
if ( (ncx+1) % 10 == 0) printf("\n");

memoria++;
}


/* ---- Libera a memória alocada ------------------------- */
free (memoria);

getchar();
return 1;
}
    
/* ------------------ Função initSys()  ------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
