/* Programa: argmain.c - track 23				*/
/* Argumentos da fun��o main()          */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* Prot�tipos */
void initSys( char *title);

int main (int argc, char *argv[])
{
	                                                                               
int ncx;                                                                                                      
initSys("title argmain.c");

for (ncx = 0; ncx < argc; ncx++)
{
printf(" argv[%d]\n %s\n\n",ncx, argv[ncx]);
if (!strcmp(argv[ncx], "\\h")) printf("\t\t Hello!\n");
}

	
                                                                                                               
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

