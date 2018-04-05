/* Programa: ptr03-strs.c - track 15 */
/* Ponteiros e strings */
#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "wincon.h"
	
/* Protótipos */
void initSys( char *title);


/* ------------------ Função main()  -------------------- */
int main(void)	{

// Variável contadora
int ncx = 0;

// Caracter
char c = 0;

int ndx = 2;


char sVirtude[6] = {'R', 'i', 'g','o','r','\0'};

char sMsg01[] = " sMsg01[] = Persistência é fundamental!";

char *sMsg02  = " *sMsg02  = A repetição é a mãe do aprendizado!";

char *sVirtudes[] = {"Rigor","Ordem","Profissionalismo",
		"exatidão","paciência","perseverança"};
		
char sBric[4][20] = {"Brasil",
                      "Rússia","Índia", "China"};


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

/* ------------------ Função initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
SetConsoleOutputCP(1252);
printf("\n\n");
}
