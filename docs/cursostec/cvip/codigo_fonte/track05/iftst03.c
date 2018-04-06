/* Programa: iftst03.c - track05 */
/* Teste da instrução else if    */
#include "stdio.h"
#include "stdlib.h"

int main(void)	{

int nIdade;
char sMsg[] = " Digite sua idade: ";

/* Configura a janela */
system("title iftst03.c");
system("color F1");
printf("\n\n");

/* Lê dado do teclado */
printf("%s", sMsg);
scanf("%i", &nIdade);

if (nIdade == 18) printf(" Vc tem 18 anos!");

else if (nIdade < 18) printf (" Vc e' menor de idade!\n");

else if (nIdade > 18) 
{
 printf(" Vc e' maior de idade!\n");
 printf(" Vc pode tirar sua carta de motorista!\n");
}


printf("\n\n");
system("pause");
return 1;
}
