/* Programa: ptr06.c - track 17 */
/* Passagem de argumentos por refer�ncia */
#include "stdio.h"
#include "stdlib.h"
	
/* Prot�tipos */
void initSys( char *title);

void multiplica (int *x, int *y);


/* ------------------ Fun��o main()  -------------------- */
int main(void)	{

int dx = 7, dy = 4;

initSys("title ptr06.c");

printf(" Valores originais dx:%i dy:%i \n\n", dx, dy);

/* ------------------ Passagem de dados por refer�ncia---- */
multiplica( &dx, &dy);
printf(" multiplica(&dx, &dy); \n");
printf(" dx = dx * dy: %i \n\n", dx);

printf(" Valores depois da chamada por referencia: \n");
printf(" dx:%i dy:%i \n", dx, dy);

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

/* ------------------ Fun��o multiplica()  -------------------- */
void multiplica (int *x, int *y) {
*x = *x * (*y);
*y = 0;
}


