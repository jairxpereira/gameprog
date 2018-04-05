/* Programa: loop02v2.c - track08 */
/* Fun��es de usu�rio e escopo de vari�vel */
#include "stdio.h"
#include "stdlib.h"

/* Vari�vel global g_limite */
int g_limite;

/* Prot�tipos */
int teste(void);
void initSys(void);
void espera(void);


/* Fun��o main() */
int main(void)	{

int ncx = 0;

initSys();

printf(" ncx - Var. de controle \n ----------------------- \n");

for (ncx=0; teste(); ncx++)
 {
   printf (" ncx:%i  g_limite: %i\n", ncx, g_limite);
 } 

espera();
return 1;
}


/**************** Fun��o teste()  */
int teste(void)
{
// Esta Vari�vel ncx � local
int ncx = g_limite;

g_limite = g_limite - 1;

return ncx;

}

/*************** Fun��o initSys()  */
void initSys(void)
{
/* Configura a janela */
system("title loop02.c - Ver 2.0");
system("color F1");
printf("\n\n");
g_limite = 6;
}


/*************** Fun��o espera()  */
void espera(void)
{
printf("\n\n");
system("pause");             
}





