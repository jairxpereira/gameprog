/* Programa: loop02.c - track07 */
/* Este programa testa a instrução for */
#include "stdio.h"
#include "stdlib.h"

/* Variável global mcx */
int mcx;

/* Função teste() */
int teste(void)
{
mcx = mcx - 1;
return mcx;
}


/* Função main() */
int main(void)	{

int ncx = 0;
mcx = 6;

/* Configura a janela */
system("title loop02.c");
system("color F1");
printf("\n\n");

printf(" ncx - Var. de controle \n ----------------------- \n");

for (ncx=0; teste(); ncx++)
 {
   printf (" ncx:%i  mcx:%i\n", ncx, mcx);
 }

printf("\n\n");
system("pause");             
return 1;
}

