/* Programa: memoria.c - track 18            */
/* Alocação de memória                     */
#include "stdio.h"


// malloc() e free()
#include "stdlib.h"

/* Protótipos */
void initSys( char *title);

/* ------------------ Função main()  ------------------- */
int main(void)  {

int *memoria;
int *memoria_inicio;

memoria = NULL;
memoria_inicio = NULL;
                          
int ncx = 0;
unsigned int qtd = 0;

qtd = 100 * sizeof(int);

initSys("title ALOCAÇÃO DE MEMÓRIA.c");


memoria = malloc(qtd);

if (memoria == NULL)
{
printf("\n Memoria nao concedida! \n");
getchar(); return -1;
}
            
memoria_inicio = memoria;

for (ncx=1; ncx <= 100; ncx++)
{
*memoria = ncx;
memoria++;
}
                              
// mostrar os dados
memoria = memoria_inicio;
for (ncx=1; ncx <= 100; ncx++)
{
printf ("%i ", *memoria);

if (ncx % 10 == 0) printf("\n ");

memoria++;
}

free(memoria);







getchar();
}


/* ------------------ Função initSys()  ------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
