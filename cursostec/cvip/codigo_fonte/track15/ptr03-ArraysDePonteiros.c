/* Programa: ptr03-Arrays de ponteiros.c - track 15 */
/* Arrays de ponteiros */
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "wincon.h"
	
/* Protótipos */
void initSys( char *title);

char *sVirtudes[] = {"Rigor","Ordem","Profissionalismo",
		"exatidão","paciência","perseverança"};


/* ------------------ Função main()  -------------------- */
int main(void)	{

// Variável contadora
int ncx = 0;

int idade = 44;
int peso  = 60;
int ano   = 2014;

int *pInteiros[4];

pInteiros[0] = &idade;
pInteiros[1] = &peso;
pInteiros[2] = &ano;

initSys("title 15.3 Arrays de ponteiros");


for (ncx=0; ncx < 3; ncx++)
{
printf(" Dado: %i \n", *pInteiros[ncx] );

printf(" Dado: %i \n", *( *(pInteiros + ncx) ) );
}


// Mostra a array de ponteiros (strings)
puts("\n");
for (ncx =0; ncx < 6; ncx++) 
printf(" sVirtudes[%d] = %s \n",ncx, sVirtudes[ncx]);


getchar();
return 1;
}

/* ------------------ Função initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
SetConsoleOutputCP(1252);
printf("\n\n");
}
