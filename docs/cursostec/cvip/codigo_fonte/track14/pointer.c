/* Programa: pointer.c - track 14 */
/* Come�ando com ponteiros */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* Prot�tipo de initSys() */
void initSys( char *title);

/* -------------------- Fun��o main() --------------- */
int main(void)	{

int nIdade = 18;
float nSalario = 900.45;

/* -------------------- Criando ponteiros------------- */
int *np;
float *fp;

/* -------------------- Inicializando ponteiros------- */
np = &nIdade;
fp = &nSalario;

initSys("title pointer.c");

printf(" nIdade:                %i \n", nIdade);
printf(" nSalario:              %.2f \n", nSalario);

/* -- Mostrando endere�os e dados dos ponteiros ----- */
printf(" Endereco de nIdade:    %p \n", np);
printf(" Endereco de nSalario   %p \n", fp);
printf(" nIdade via ponteiro:   %i = *np \n",*np);
printf(" nSalario via ponteiro: %.2f = *fp \n", *fp);

getchar();

return 1;
}

/*************** Fun��o initSys()  */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
