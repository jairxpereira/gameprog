/* Programa: datatype.c  - track03 */
#include "stdio.h"
#include "stdlib.h"

int main(void) {

char 					sString[] = "Testando tipo de dados";
char 					cRank = 'A';
unsigned int 	nInteiro = 50000;
long 					nLongo = -568600;
short int 		nShort= 15800;
unsigned char nEnergia = 98;
float 				pi = 3.141516;

/* Configura a janela */
system("title datatype.c"); 
system("color F1");    


printf("\n\n");
printf(" char:             %c\n", cRank);
printf(" sString[]:        %s\n", sString);
printf(" unsigned int:      %u\n", nInteiro);
printf(" long:            %li\n", nLongo);
printf(" unsigned char:    %d \n", nEnergia);
printf(" short int:        %hi \n", nShort);
printf(" float:            %f \n", pi);
printf(" Hexadecimal:      %x  %X \n", nShort, nShort);
printf("\n\n");

system("pause");
return 1; }

