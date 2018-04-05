/* Programa: casting.c - track 22				*/
/* Ilustra casting de tipos             */
#include "stdio.h"                                                                                              
#include "stdlib.h"  

/* Protótipos */
void initSys( char *title); 

/* ------------------ Função main()  -------------------- */
int main( int nCmd, char *sCmd[])	{

int x = 5;
int y = 2;

float z = 0.0f;


initSys("title casting.c");

printf ("\t x = %i	y = %i	z = %f \n\n", x, y, z);

/* ----- Z vale 2 --------------------------------------- */
z = (x / y) + 2;
printf ("\t z = x / y ==> %f \n\n", z);

/* ----- Z vale 2.5 com o type casting de x ------------ */
z = x / (float) y;
printf ("\t z = x / (float) y ==> %f \n\n", z);

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
