/* Programa: struc02.c - track 11*/
/* Ilustra criação e uso de array de estruturas */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* Protótipo initSys() */
void initSys( char *title);


/* Estrutura xEndereco */
struct xEndereco {
char srua[40];
char sbairro[40];
unsigned int nrua;
unsigned int ncep;
};

/* Estrutura xFuncionario */
struct xFuncionario {
char nome[40];
struct xEndereco endereco;
int idade;
float salario;
} Vendedor;

/* ********************** main() ***************** */
int main(void)  {

struct xFuncionario programadores[10];
int ncx = 0;

initSys("title struc02.c");

/* Preenche programadores[0] */
strcpy(programadores[0].nome, "Zeca Bytes");
strcpy(programadores[0].endereco.srua, "Rua Intel");
strcpy(programadores[0].endereco.sbairro, "Vila do Silicio");
programadores[0].endereco.nrua = 8088;
programadores[0].idade = 55;
programadores[0].salario = 1500.75;

/* Preenche programadores[1] */
strcpy(programadores[1].nome, "Zeca Bit");
strcpy(programadores[1].endereco.srua, "Rua Intel");
strcpy(programadores[1].endereco.sbairro, "Vale do Silicio");
programadores[1].endereco.nrua = 8086;
programadores[1].endereco.srua[0] = 'X';
programadores[1].idade = 16;
programadores[1].salario = 1500.75;

/* Mostra programadores[ncx] */
for (ncx = 0; ncx < 2; ncx++) {
printf("\n \t Programador:\n");
printf(" Nome:     %s \n",programadores[ncx].nome);
printf(" Endereco: %s, ",programadores[ncx].endereco.srua);
printf(" nro:      %u \n",programadores[ncx].endereco.nrua);
printf(" Idade:    %i \n",programadores[ncx].idade);
printf(" Salario:  %.2f \n",programadores[ncx].salario);}

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
