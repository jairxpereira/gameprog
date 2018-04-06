/* Programa: iftst01.c - track05*/
/* Este programa testa a instrução if */
#include "stdio.h"
#include "stdlib.h"

int main(void)	{

int nIdade;
char sMsg[] = " Digite sua idade: ";
char sMenor[] = " Vc e' menor de idade!";
char sIgual[] = " Vc tem 18 anos!";
char sMaior[] = " Vc e' maior de idade!";
char sCarta[] = " Vc ja' pode tirar sua carta de motorista!";

/* Configura a janela */
system("title iftst01.c");
system("color F1");

printf("\n%s ",sMsg);
scanf("%i", &nIdade);

if (nIdade == 18)  printf("%s \n",sIgual);
if (nIdade <= 18)  printf(" idade <= 18 \n");
if (nIdade >= 18)  printf(" idade >= 18 \n");
if (!(nIdade == 18)) printf (" !(18) Vc nao tem 18 anos!\n");


if (nIdade < 18)
printf("%s \n",sMenor);

/* {} Um bloco de código if */
if (nIdade >= 18)
{
printf("%s \n",sMaior);
printf("%s \n",sCarta);
}

printf("\n\n");
system("pause");

return 1;
}

