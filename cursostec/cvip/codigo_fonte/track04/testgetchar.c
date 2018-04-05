/* Programa testgetchar.c - track04 */
/* Teste de funções de entrada e saida */
#include "stdio.h"
#include "stdlib.h"

int main() {
	
unsigned char mychar = 0;
	
/* Configura a janela */
system("title testgetchar.c"); 
system("color F1");

printf(" Digite uma tecla e aperte enter: ");
mychar = getchar();

printf("mychar: %c %d \n\n", mychar, mychar);

mychar = 'A';
printf("mychar: %c %d \n\n", mychar, mychar);

system("pause");		
}

