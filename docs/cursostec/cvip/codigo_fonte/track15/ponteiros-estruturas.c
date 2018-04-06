#include "stdio.h"
#include "stdlib.h"


// Protótipos das funções
void iniciar(char *cmd);
void esperar(void);


void falar (char *msg);

#define pfString void (*pf) (char *msg)

void dizer (
char *info, 
void (*pf) (char *msg) 
);

int main(void)
{
    
void (*pf) ( char * msg);

pf = falar;

    
iniciar("title Ponteiros ");


falar ("Oi, estou aqui!\n");
pf ("Oi, estou aqui de novo!\n\n");

(*pf) ("Estou aqui mais uma vez!\n\n");

dizer ("Ja' estou pertubando...", falar);


esperar();


} // main().fim



// *** Função iniciar() ***
void iniciar(char *cmd)
{
system(cmd);
system("color 1f");
printf("\n");
} // iniciar().fim


// *** Função esperar() ***
void esperar(void)
{
printf("\n"); system("pause");
} // esperar().fim



void falar (char *msg)
{
printf(" ");
puts(msg);
}

void dizer (char *info, pfString)
{
pf (info);
}
 
