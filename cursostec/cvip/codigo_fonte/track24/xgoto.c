/* Programa: xgoto.c - track 24				*/
/* Ilustra salto incondicional        */
#include "stdio.h"                                                                                              
#include "stdlib.h"  

/* Prot�tipos */
void initSys( char *title); 

/* ------------------ Fun��o main()  -------------------- */
int main( int nCmd, char *sCmd[])	{
int ncx = 0;

initSys("title xgoto.c");

Start:
ncx++;
printf(" %d.salto incondicional \n",ncx);
if (ncx == 3) goto Final;
goto Start;

Final:
printf("\n Final do programa...\n\n");


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

