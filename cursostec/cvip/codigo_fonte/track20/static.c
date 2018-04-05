/* Programa: static.c - track 20      */
/* Testando static dentro das funções */
#include "stdio.h"

/* ----- Protótipos ------ */
void teste(void);
void initSys(char *title);


int main(void)	
{

/* auto indica que a variável é local */
auto int ncx;


initSys("title static.c");

for (ncx=0;ncx < 10; ncx++)
teste();

printf("\n\n");
getchar();
return 1;}

/* ------------------ Função teste()  ---------------------- */
void teste(void) {
static nValor = 20;
nValor++;
printf(" %d",nValor);
}

/* ------------------ Função initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}




