/* Programa: ptr09.c - track 18            */
/* Determinando o endereço do ponteiro     */
#include "stdio.h"
#include "stdlib.h"

/* Protótipos */
void initSys( char *title);

/* Determinando o endereço de um ponteiro */
unsigned int  *myint_ptr = (int *) 0x0022FF18L;

int main(void)  {

/* Definição de nval e seu ponteiro */
int nval = 100;
int *nval_ptr;
nval_ptr = &nval;

initSys("title ptr09.c");

printf(" *nval_ptr: %i  &nval_ptr:  %p \n", *nval_ptr, nval_ptr);
printf(" *myint_ptr:%i  &myint_ptr: %p \n", *myint_ptr, myint_ptr);
printf("\n\n");
    
*myint_ptr = 999;       

printf(" nval foi hackeada pelo ponteiro com endereco determinado\n");
printf(" *nval_ptr: %i  &nval_ptr:  %p \n", *nval_ptr, nval_ptr);
printf(" *myint_ptr:%i  &myint_ptr: %p \n", *myint_ptr, myint_ptr);

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
