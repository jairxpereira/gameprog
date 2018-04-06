/* testArray.c - track10 */
/* Ilustra o uso arrays  */
#include "stdio.h"
#include "stdlib.h"

void initSys();
void waitSys();

int main() {
	
float nFloats [6] = { 1.3, 4.5, 2.7, 4.1, 0.0, 3.1415 }; 
                                                        
int nMatriz [3][4] = { 1, 2, 3, 4, 
5, 6, 7, 8, 
9, 10, 11, 12 };   
                                       
char sNome [10] = { 'J', 'o', 'a', 'o', '\0' }; 
                                                                
char sxNome [10] = "Joao";  
                                                                                     
char sClientes[3][10] = { "Joao", "Maria", "Jose" }; 
   
int i,j;

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

for (ncx=0; sNome[ncx]; ncx++)
printf(" %c.%d ", sNome[ncx], sNome[ncx]);

printf("\n %s %s \n",sNome, sxNome);

/* Imprime  sClientes[3][10] */
for (ncx=0; ncx < 3; ncx++) 
printf(" %s", sClientes[ncx]);

printf("\n\n");
for (ncx=0; ncx < 6; ncx++) 
printf(" %f", nFloats[ncx]);

printf("\n");

/* Imprime nMatriz[3][4] */
for (i=0; i < 3; i++)
{
	for (j=0; j< 4; j++)
	{
		printf(" %i ", nMatriz[i][j]);
	}
	printf("\n");

}	

	
waitSys();		
return 1;	
}

/* ************** initSys() */
void initSys()
{
 system("title testArray.c"); system("color f1");
 printf("\n\n");
}

/* ************** waitSys() */
void waitSys()
{
printf("\n\n");
system("pause");
}


