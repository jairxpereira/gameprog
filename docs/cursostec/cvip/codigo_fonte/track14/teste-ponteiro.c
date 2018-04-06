#include "stdio.h"
#include "stdlib.h"

void iniciar(void);
void esperar(void);



int main(void)
{
// Área de dados

int nIdade = 25;
int nSalario = 1500;

int *pIdade = 0;
int *pSalario = 0;

int *pSegredo = (int *) 0x22FF40;


unsigned char *pHichar = (unsigned char *) 0x22FF40;
unsigned char *pLowchar = (unsigned char *) 0x22FF41;
*pLowchar = 'A';


pIdade = &nIdade;
pSalario = &nSalario;

pHichar = pLowchar;
*pHichar = 'B';
pSalario++;


// Área de código
iniciar();

printf("\t Idade: %i - \tSalario: %d \n", nIdade, nSalario);
printf("\t Idade: %i - \tSalario: %i \n", *pIdade, *pSalario);
printf("\t Idade: %p - \tSalario: %p \n", pIdade, pSalario);
printf("\t Segredo: %i \t pSegredo: %p \n", *pSegredo, pSegredo);

printf("\n %d \t %d \n", *pHichar, *pLowchar);





esperar();    
    
} // main().fim


void iniciar(void)
{
system("title ponteiros");
system("color 1f");
printf("\n");     
} // iniciar().fim


void esperar(void)
{
system("pause");
} // esperar().fim

     
