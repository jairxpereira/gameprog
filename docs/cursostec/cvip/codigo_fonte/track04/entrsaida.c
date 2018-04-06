/* Programa entrsaida.c - track04 */
/* Teste de funções de entrada e saida */
#include "stdio.h"
#include "stdlib.h"

int main() {
	
int myage = 26;
char myname[31] = "Megaman";
float pi = 3.141516f;
	
/* Configura a janela */
system("title entrsaida.c"); 
system("color F1");

printf("\n\n");
printf(" %s %i %f \n\n", myname, myage, pi);

printf("\n Digite seu primeiro nome: ");
scanf("%s", myname);

printf(" Digite sua idade: ");
scanf("%i", &myage);
printf( " %s %i anos\n\n", myname, myage);

printf("\n Digite seu primeiro nome e idade separados por um espaco:\n ");
scanf("%s %d", myname, &myage);
printf( " %s %i anos\n\n", myname, myage);

system("pause");
return 1;	
	
}
