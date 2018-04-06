/* Programa: memoria.c - track 18            */
/* Aloca��o de mem�ria                     */
#include "stdio.h"


// malloc() e free()
#include "stdlib.h"

/* Prot�tipos */
void initSys( char *title);

/* ------------------ Fun��o main()  ------------------- */
int main(void)  {

int *memoria;
int *memoria_inicio;

memoria = NULL;
memoria_inicio = NULL;
                          
int ncx = 0;
unsigned int qtd = 0;

qtd = 100 * sizeof(int);

initSys("title ALOCA��O DE MEM�RIA.c");


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


/* ------------------ Fun��o initSys()  ------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
