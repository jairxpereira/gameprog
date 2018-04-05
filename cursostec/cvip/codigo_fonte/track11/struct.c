/* Programa: struct.c - track 11*/
/* Ilustra criação e uso de estrutura */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
	
void initSys( char *title);
void espera(void);

struct xFuncionario {
char nome[40];
char endereco[40];
int idade;
float salario;
} Vendedor;

int main(void)	{

struct xFuncionario programador;

initSys("title struct.c");

/* Preenche o registro Vendedor    */
strcpy(Vendedor.nome, "Jair Pereira");
strcpy(Vendedor.endereco, "Rua Geral, 386");
Vendedor.idade = 28;
Vendedor.salario = 700.75;

/* Preenche o registro programador */
strcpy(programador.nome, "Zeca Bytes");
strcpy(programador.endereco, "Rua Intel, 8088");
programador.idade = 55;
programador.salario = 1500.75;

/* Mostra o registro programador */
printf("\t Programador \n\n");
printf(" Nome:        %s    \n",programador.nome);
printf(" Endereco:    %s    \n",programador.endereco);
printf(" Idade:       %i    \n",programador.idade);
printf(" Salario:     %.2f  \n",programador.salario);

/* Mostra o registro vendedor */
printf("\n \t Vendedor \n\n");
printf(" Nome:        %s    \n",Vendedor.nome);
printf(" Endereco:    %s    \n",Vendedor.endereco);
printf(" Idade:       %i    \n",Vendedor.idade);
printf(" Salario:     %.2f  \n",Vendedor.salario);

getchar();

return 1;
}


/*************** Função initSys()  */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
