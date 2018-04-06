/* Programa: ptr01.c - track 14 */
/* Manipulando dados indiretamente via ponteiros */
#include "stdio.h"
#include "stdlib.h"

	
/* Protótipos */
void initSys( char *title);
void mostrar (int nIdade, int nAnos);
void falar (char *sMsg);

/* ------------------ Função main()  -------------------- */
int main(void)	{

int nIdade = 18;
int nAnos = 25;
int *np = NULL; 
np = &nIdade;

initSys("title ptr01.c");

falar(" Valores originais:"); 
mostrar(nIdade, nAnos);
falar("	int *np; np = &nIdade; \n");

nAnos = *np;
falar(" Valores alterados via nAnos = *np:"); 
mostrar(nIdade, nAnos);

nIdade = 18; nAnos = 25;
falar(" Valores originais:"); mostrar(nIdade, nAnos);
*np = nAnos;
falar(" Valores alterados via *np = nAnos"); 
mostrar(nIdade, nAnos);

(*np)++;
falar(" Valores alterados via (*np)++ "); 
mostrar(nIdade, nAnos);

*np = *np + 10;
falar(" Valores alterados via *np = *np + 10 "); 
mostrar(nIdade, nAnos);

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

/* ------------------ Função mostrar()  -------------------- */
void mostrar(int nIdade, int nAnos) {
printf("\t nIdade: %i \t nAnos: %i \n\n",nIdade, nAnos);
}

/* ------------------ Função falar()  -------------------- */
void falar(char *sMsg) {
printf("%s \n", sMsg);
}

