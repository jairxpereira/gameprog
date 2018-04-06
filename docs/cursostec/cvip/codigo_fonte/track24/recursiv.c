/* Programa: recursiv.c track 24            */
/* Testando recursividade                   */
#include "stdio.h"
#include "stdlib.h"

/* Prot�tipos */
void initSys( char *title);
int recursiva (void);
long fatorial(int nval);
long myfat = 0;

/* ------------------ Fun��o main()  ----------------------- */
int main( int nCmd, char *sCmd[])	{
initSys("title recursiv.c");

/* --- Esta fun��o chama a si mesma 5x --------------------- */
myfat = fatorial(5);

printf (" Fatorial 5!: %li \n\n", myfat);


/* --- Esta fun��o chama a si mesma 5x --------------------- */
recursiva();

printf("\n\n");
getchar();
return 1;
}


/* ------------------ Fun��o recursiva()  ----------------- */
int recursiva (void) {
static int nCiclo=1;
int nOldCiclo;

nOldCiclo = nCiclo;
printf(" nCiclo: %d \t nOldCiclo: %d\n",nCiclo, nOldCiclo);
nCiclo++;

if (nCiclo == 6) printf("\n");

/* --- Controle da recursividade abaixo ------------------- */
if (nCiclo <= 5) recursiva();


if (nCiclo > 5) 
 {
 printf(" Ciclo encerrado:%d ", nCiclo);
 printf("\t Ciclo antigo:%d\n", nOldCiclo);
 }

return 0;
}


/* ------------------ Fun��o initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}


/* ------------------ Fun��o fatorial()  ------------------- */
long fatorial(int nval)
{
static long fat = 1;
static long resultado;

fat = fat * nval;

/* --- Controle da recursividade abaixo ------------------- */
nval = nval - 1;

printf (" fat: %li nval: %i \n", fat, nval);
if (nval > 0) fatorial (nval);

if (nval == 0)
{
 resultado = fat;
 fat = 1;
}
 
return resultado;
}




