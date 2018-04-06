/* Programa: static.c - track 20      */
/* Testando static dentro das funções */
#include "stdio.h"

//  - static 
// const -  
// 

/* ----- Protótipos ------ */
void initSys(char *title);



void teste ( void );




int main(void)	
{

initSys("title especificadores - ESPECIFICADORES");


 float pi = 3.141516f;

 float *ppi = &pi;

float e = 6.28f;

pi = e;

ppi = &e;

int ncx = 0;

for (ncx=0; ncx < 10; ncx++) teste();





printf (" pi: %f \n\n", pi);
printf (" pi: %f \n\n", *ppi);

printf("\n\n");
getchar();
return 1;}



/* ------------------ Função initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}


void teste ( void )
{

 static int nval = 0;

nval = nval + 1;

printf (" %d ", nval);
     

}

