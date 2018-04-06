/* Programa: iftst02.c - track05 */
/* Teste da instrução else       */
#include "stdio.h"
#include "stdlib.h"

int main(void)	{

int nIdade;
char sMsg[] = " Digite sua idade: ";

/* Configura a janela */
system("title iftst02.c");
system("color F1");
printf("\n\n");

/* Ler valor do teclado */
printf("%s", sMsg);
scanf("%i", &nIdade);

 if (nIdade == 18)
	printf(" Vc tem 18 anos!\n\n");
 else
	printf(" idade <> 18! \n\n");


/* Bloco de código if\else */
 if (nIdade == 18) 
 {
	printf(" Vc pode tirar sua carta de motorista!\n");
	printf(" Vc tem 18 anos!");
}

 else    
 {
	printf(" idade <> 18 \n");
	printf(" Vc nao tem 18 anos! \n");
	if (nIdade < 18) printf(" idade < 18! \n");
	if (nIdade > 18) printf (" idade > 18! \n");
 }

printf("\n\n");
system("pause");

return 1;
}

