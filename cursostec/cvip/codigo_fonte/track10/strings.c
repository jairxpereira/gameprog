/* string.c - track 10 */
/* Manipulação de strings */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
	
void initSys();
void espera();

int main (void) {
char sStr_x[]="mouse";

char sStr_y[]="rato";

char sStr_z[]="mouse";

char sStr_u[]="MOUSE";

char sFonte[]="Seja perseverante!";

char sDestino[40];

int nSts;

initSys();

// nSts = (mouse == rato)
nSts = strcmp(sStr_x, sStr_y);	
printf(" %s \t%d \t%s \n\n",sStr_x, nSts, sStr_y);	

// nSts = (mouse == mouse)
nSts = strcmp(sStr_x, sStr_z);
printf(" %s \t%d \t%s \n",sStr_x, nSts, sStr_z);
if (!nSts) puts(" As string sao iguais!\n");

// nSts = (mouse == MOUSE)
nSts = strcmp(sStr_x, sStr_u);
printf(" %s \t%d \t%s \n",sStr_x,nSts, sStr_u);

// sDestino = sFonte
strcpy (sDestino,sFonte);
printf("\n sDestino: %s\n", sDestino);

espera();

}

/* ************** initSys() */
void initSys()
{
system("title strings.c"); system("color f1");
printf("\n\n");
}

/* ************** waitSys() */
void espera()
{
printf("\n\n");
system("pause");
}

