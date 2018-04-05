/* Programa: ptr06.c - track 17 */
/* Passagem de argumentos por referência */
#include "stdio.h"
#include "stdlib.h"
	
/* Protótipos */
void initSys( char *title);

void multiplica (int *x, int *y);


/* ------------------ Função main()  -------------------- */
int main(void)	{

int dx = 7, dy = 4;

initSys("title ptr06.c");

printf(" Valores originais dx:%i dy:%i \n\n", dx, dy);

/* ------------------ Passagem de dados por referência---- */
multiplica( &dx, &dy);
printf(" multiplica(&dx, &dy); \n");
printf(" dx = dx * dy: %i \n\n", dx);

printf(" Valores depois da chamada por referencia: \n");
printf(" dx:%i dy:%i \n", dx, dy);

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

/* ------------------ Função multiplica()  -------------------- */
void multiplica (int *x, int *y) {
*x = *x * (*y);
*y = 0;
}


