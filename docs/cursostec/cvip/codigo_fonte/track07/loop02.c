/* Programa: loop02.c - track07 */
/* Este programa testa a instru��o for */
#include "stdio.h"
#include "stdlib.h"

/* Vari�vel global mcx */
int mcx;

/* Fun��o teste() */
int teste(void)
{
mcx = mcx - 1;
return mcx;
}


/* Fun��o main() */
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

