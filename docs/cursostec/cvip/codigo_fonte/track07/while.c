/* Programa: while.c - track07 */
/* Este programa testa a instrução while */
#include "stdio.h"
#include "stdlib.h"

// Variável global
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

/* Este looping não roda - condição inicial falsa */
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
