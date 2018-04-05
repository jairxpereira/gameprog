/* Programa: ptr03-strs.c - track 15 */
/* Ponteiros e strings */
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "wincon.h"
	
/* Prot�tipos */
void initSys( char *title);


/* ------------------ Fun��o main()  -------------------- */
int main(void)	{

// Vari�vel contadora
int ncx = 0;

// Caracter
char c = 0;

int ndx = 2;


char sVirtude[6] = {'R', 'i', 'g','o','r','\0'};

char sMsg01[] = " sMsg01[] = Persist�ncia � fundamental!";

char *sMsg02  = " *sMsg02  = A repeti��o � a m�e do aprendizado!";

char *sVirtudes[] = {"Rigor","Ordem","Profissionalismo",
		"exatid�o","paci�ncia","perseveran�a"};
		
char sBric[4][20] = {"Brasil",
                      "R�ssia","�ndia", "China"};


initSys("title Ponteiros e Strings");
puts(sMsg01);
puts(sMsg02);
puts(sVirtude);

puts("\n");
for (ncx =0; ncx < 6; ncx++) 
printf(" sVirtudes[%d] = %s \n",ncx, sVirtudes[ncx]);

puts("\n");
c = *(sMsg01 + ndx);
printf(" *(sMsg01 + ndx) =  %c \n", c);

c = sMsg01[2];
printf(" sMsg01[2] = %c \n", c);

puts("\n");
for (ncx =0; ncx < 4; ncx++) 
printf(" sBric[%d] = %s \n",ncx,sBric[ncx]);

getchar();
return 1;
}

/* ------------------ Fun��o initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
SetConsoleOutputCP(1252);
printf("\n\n");
}
