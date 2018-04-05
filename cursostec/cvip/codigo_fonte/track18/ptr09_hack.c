/* Programa: ptr09.c - track 18            */
/* Determinando o endereço do ponteiro     */
#include "stdio.h"
#include "stdlib.h"

/* Protótipos */
void initSys( char *title);

/* Determinando o endereço de um ponteiro */


int main(void)  {


int idade = 25;

int *iptr;

unsigned int *ptr_hack = (int *) 0x0022FF44L;


iptr = &idade;

printf( "\n idade: %i  endereco: %p \n", idade, iptr);

*ptr_hack = 99;

printf( "\n idade_ptr: %i  endereco: %p \n", *ptr_hack, ptr_hack);
printf( "\n idade: %i  endereco: %p \n", idade, iptr);


initSys("title ptr09.c - DETERMINANDO ENDEREÇOS DE PONTEIROS");

      



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
