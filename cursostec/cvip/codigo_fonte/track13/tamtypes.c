/* Programa: tamtypes.c - track 13*/
/* Ilustra sizeof() - tamanho dos tipos */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
	
/* Protótipo de initSys() */
void initSys( char *title);

/* Estrutura Funcionario */
typedef struct _Funcionario {
char sNome[40];
char sEndereco[40];
float nSalario;
int nIdade;
} Funcionario;

int main(void)	{

/* Declaração de alguns tipos */
signed char          nByte;
signed int           nInteiro;
signed long          nLongo;
float         nFloat;
double        nDouble;

initSys("title tamtypes.c");

Funcionario vendedor;

/* Mostra o tamanho dos tipos mais usados */
printf(" Char...: \t %d byte\n",    sizeof(nByte));
printf(" Inteiro: \t %d bytes \n",  sizeof(nInteiro));
printf(" Longo..: \t %d bytes \n",  sizeof(nLongo));
printf(" Float..: \t %d bytes \n",  sizeof(nFloat));
printf(" Double.: \t %d bytes \n\n",sizeof(nDouble));

printf(" Estrutura Funcionario     : %d bytes \n",sizeof(vendedor));
puts ("--------------------------------------- \n");
printf(" sizeof(vendedor.sNome)    : %d bytes \n",sizeof(vendedor.sNome));
printf(" sizeof(vendedor.sEndereco): %d bytes \n",sizeof(vendedor.sEndereco));
printf(" sizeof(vendedor.nIdade)   : %d bytes \n",sizeof(vendedor.nIdade));
printf(" sizeof(vendedor.nSalario) : %d bytes \n",sizeof(vendedor.nSalario));


getchar();
return 1;
}


/*************** Função initSys()  */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
