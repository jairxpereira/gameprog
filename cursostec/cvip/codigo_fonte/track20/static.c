/* Programa: static.c - track 20      */
/* Testando static dentro das fun��es */
#include "stdio.h"

/* ----- Prot�tipos ------ */
void teste(void);
void initSys(char *title);


int main(void)	
{

/* auto indica que a vari�vel � local */
auto int ncx;


initSys("title static.c");

for (ncx=0;ncx < 10; ncx++)
teste();

printf("\n\n");
getchar();
return 1;}

/* ------------------ Fun��o teste()  ---------------------- */
void teste(void) {
static nValor = 20;
nValor++;
printf(" %d",nValor);
}

/* ------------------ Fun��o initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}




