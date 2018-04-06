/* Programa: mainpart.c */
/* Este programa ilustra o uso de extern */
#include "stdio.h"



/* Variáveis e funções externas */
extern char sNome[];
extern void say(char *sText);
extern void initSys(char *title);

extern char sCidade[];
extern int nIdade;


int main(void)	{
char sInfo[] = "Impresso via say() funcao do modulo.h";

initSys("title mainpart.c");

say (sInfo);
say (sNome);

printf("\n Declarada noutro modulo, porem nao declarada com extern: \n");
say(sCidade);
printf(" idade: %i \n\n", nIdade);

getchar();
return 1;
}


#include "modulo.h"

