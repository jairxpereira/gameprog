/* Programa: getmax.c - track06 */
/* Este programa testa a instrução ?: */
#include "stdio.h"
#include "stdlib.h"

int main(void)	{

int a = 10;
int b = 20;
int nMaior = 0;

/* Configura a janela */
system("title getmax.c");
system("color F1");
printf("\n\n");

printf (" Digite dois numeros: ");
scanf("%i", &a);
scanf("%i", &b);

/* nMaior = (a > b) ? a:b; */

if (a > b) nMaior = a;
else
nMaior = b;


printf (" O maior e' %i \n",nMaior);

printf("\n\n");
system("pause");

return 1;
}
