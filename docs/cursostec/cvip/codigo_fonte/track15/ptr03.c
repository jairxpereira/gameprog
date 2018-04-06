/* Programa: ptr03.c - track 15 */
/* Todo vArray � um ponteiro autom�tico do elemento vArray[0] /*
/* e pode ser usado como tal */
#include "stdio.h"
#include "stdlib.h"
	
/* Prot�tipos */
void initSys( char *title);

/* ------------------ Fun��o main()  -------------------- */
int main(void)	{

int nValor[] = { 0,2,4,6,8,10,12,14,16,18,20};
char *sNome = "Jair";

initSys("title ptr03.c");

printf(" Posicao: 0 1 2 3 4 5  6  7  8  9  10 \n");
printf(" sNome[]: J a i r 0 \n");
printf(" Valores: 0 2 4 6 8 10 12 14 16 18 20 \n\n");
printf(" *(nValor + 3) = nValor[3] = %i \n", *(nValor+3) );
printf(" sNome[3] = %c \n", *(sNome+ 2) );

getchar();
return 1;
}

/* ------------------ Fun��o initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
