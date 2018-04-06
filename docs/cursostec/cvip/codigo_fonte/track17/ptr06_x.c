/* Programa: ptr06.c - track 17 */
/* Passagem de argumentos por refer�ncia */
#include "stdio.h"
#include "stdlib.h"
	
/* Prot�tipos */
void initSys( char *title);

int multiplica_byval ( int x, int y);

void multiplica_byref ( int *x, int *y);



/* ------------------ Fun��o main()  -------------------- */
int main(void)	{

int res = 0;
int dx = 7, dy = 4;

printf(" Valores originais dx:%i dy:%i resultado: %i\n\n",
 dx, dy, res);

res = multiplica_byval (dx, dy);
initSys("title PASSAGEM POR VALOR OU REFER�NCIA");

printf(" Valores originais dx:%i dy:%i resultado: %i\n\n",
 dx, dy, res);
 
multiplica_byref (&dx, &dy);
printf(" Valores originais dx:%i dy:%i \n\n",
 dx, dy);


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

int multiplica_byval ( int x, int y)
{
return x * y;
}

void multiplica_byref ( int *x, int *y){
    
 *x = *x * (*y);
     
}

