/* Programa: while.c - track07 */
/* Este programa testa a instru��o while */
#include "stdio.h"
#include "stdlib.h"

// Vari�vel global
int mcx = 6;

int teste(void) {
mcx--; 
printf(" mcx:%i  - teste( )\n",mcx);
return mcx;
}

int main(void)	{

/* Configura a janela */
system("title while.c");
system("color F1");
printf("\n\n");

while (teste());

printf("\n");
system("pause");

/* Este looping n�o roda - condi��o inicial falsa */
mcx = 5;
while (mcx > 10)
{
 mcx++;
 printf("mcx: %i - main( )\n",mcx);
}

printf("\n\n");
system("pause"); 
return 1;
}
