/* Programa: loop02v2.c - track08 */
/* Funções de usuário e escopo de variável */
#include "stdio.h"
#include "stdlib.h"

/* Variável global g_limite */
int g_limite;

/* Protótipos */
int teste(void);
void initSys(void);
void espera(void);


/* Função main() */
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


/**************** Função teste()  */
int teste(void)
{
// Esta Variável ncx é local
int ncx = g_limite;

g_limite = g_limite - 1;

return ncx;

}

/*************** Função initSys()  */
void initSys(void)
{
/* Configura a janela */
system("title loop02.c - Ver 2.0");
system("color F1");
printf("\n\n");
g_limite = 6;
}


/*************** Função espera()  */
void espera(void)
{
printf("\n\n");
system("pause");             
}





