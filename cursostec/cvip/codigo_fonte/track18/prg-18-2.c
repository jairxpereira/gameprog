/* Programa: ptr09.c - track 18            */
/* Determinando o endere�o do ponteiro     */
#include "stdio.h"
#include "stdlib.h"

/* Prot�tipos */
void initSys( char *title);

/* Determinando o endere�o de um ponteiro */


int main(void)  {


int idade = 25;

int *iptr;

int **iptr_ptr;


iptr = &idade;

iptr_ptr = &iptr;



initSys("title prg-18-2.c - PONTEIROS PARA PONTEIROS!");

printf("\n idade: %d %p \n ", idade, iptr);

printf("\n idade: %d %d \n ", *iptr, **iptr_ptr);
      



getchar();
return 1;
}
    
/* ------------------ Fun��o initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
