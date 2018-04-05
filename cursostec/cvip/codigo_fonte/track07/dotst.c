/* Programa: dotst.c - track07 */
/* Este programa testa o conjunto do...while */
#include "stdio.h"
#include "stdlib.h"
int main(void)	{
    
int ncx = 0;

/* Configura a janela */
system("title dotst.c");
system("color F1");
printf("\n\n");

do {
ncx++;
printf(" %i \n", ncx);
} while (ncx < 3);

/* Avança ncx até 30 */
do ncx++; while(ncx < 30);

do {
ncx++;
printf(" %i ==> Executado sob condicao falsa \n", ncx);
} while (ncx < 2);

printf("\n\n");
system("pause");
return 1;
}

