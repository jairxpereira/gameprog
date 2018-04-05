/* Ponto3d.c - track10 */
/* Ilustra o uso arrays  */
#include "stdio.h"
#include "stdlib.h"

void initSys();
void waitSys();

int main() {

int nPonto3d[5][3] = {
		{1,2,3},
		{4,5,6},
		{7,8,9},
		{10,11,12},
		{13,14,15},
		};		
		
int ncx = 0;

initSys();

/* Imprime nPonto3d[5][3] */
for (ncx=0; ncx < 5; ncx++)
printf(" Ponto3d %i: (%i,%i,%i) \n", ncx, 
nPonto3d[ncx][0], 
nPonto3d[ncx][1], 
nPonto3d[ncx][2]);
printf("\n");

printf("\n");
	
waitSys();		
return 1;	
}

/* ************** initSys() */
void initSys()
{
 system("title Ponto3d.c"); system("color f1");
 printf("\n\n");
}

/* ************** waitSys() */
void waitSys()
{
printf("\n\n");
system("pause");
}


