/* Programa: printf.c */
#include "stdio.h"
#include "stdlib.h"

int main(void)	{
char sNome[]="Megaman";
int nIdade = 26;
  
/* Configura a janela */
system("title printf.c"); 
system("color F1");
	
printf("\n Nome: %s - %i anos (2013) \n\n", sNome,nIdade);
  
system("pause");

return 1;
}




