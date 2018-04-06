/* Programa: ptr02.c - track 15 */
/* Ponteiro para uma array */
#include "stdio.h"
#include "stdlib.h"
	
/* Protótipos */
void initSys( char *title);
void nMostrar (int ndx, int x);

/* ------------------ Função main()  -------------------- */
int main(void)	{

int nValor[10] = {10,11,22,33,44,55,66,77,88,99};

int *np;

int ndx, x;

np = &nValor[0];

initSys("title ptr02.c");

 for (ndx = 0; ndx < 10; ndx++)
  {

   // x = nValor[ndx];

   x = *(nValor + ndx);
   
   nMostrar(ndx,x);
  }

getchar();
return 1;
}

/* ------------------ Função initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}

/* ------------------ Função nMostrar()  -------------------- */
void nMostrar(int ndx, int x) {
printf(" nValor[%i] = %i \n", ndx,x);
}
