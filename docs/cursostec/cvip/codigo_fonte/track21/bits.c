/* Programa: bits.c - track 21				*/
/* Convers�o num�rica                 */
#include "stdio.h"                                                                                              
#include "stdlib.h"  

/* Prot�tipos */
void initSys( char *title);                                                                                           
                                                                                                                
int main (void) {

char sNumber[40]; 
                                                                                               
unsigned long int nLongNumber = 0xAAAAFFFF;

char *sString;

initSys("title bits.c");

/* Converte o n�mero longo para bin�rio */
sString = _ultoa (nLongNumber, sNumber, 16);

printf(" %lu nLongNumber \n\n %s sNumber \n\n",nLongNumber,sNumber);
printf(" %s String retornada \n\n",sString);

getch(); 
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
