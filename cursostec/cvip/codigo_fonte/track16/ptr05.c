/* Programa: ptr05.c         */
/* Ponteiros para estruturas */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
	
/* Protótipos */
void initSys( char *title);

/* -------- Definindo a estrutura ponto ----------- */
struct xPonto {
int nId;
int x;
int y;
};

/* -------- Definindo a estrutura xFuncionario ---- */
struct xFuncionario {
char nome[40];
char endereco[40];
int idade;
float salario;
};

/* --------- Função main() ------------------------- */
int main(void)	{

struct xFuncionario programador;
struct xPonto ponto;

/* ------- Definindo ponteiro para as estruturas --- */
struct xFuncionario *px;
struct xPonto *xpos;

/* --- Inicializando os ponteiros das estruturas --- */
px 		= 	&programador;
xpos 	=	 	&ponto;

/* --- Veja como os campos são acessados ----------- */
xpos->nId = 1;
xpos->x = 320;
xpos->y = 240;

initSys("title ptr05.c");

strcpy(programador.nome, "Zeca Bytes");
strcpy(programador.endereco, "Rua Intel, 8088");
programador.idade = 55;
programador.salario = 1500.75;

/* ----- Mostrando a estrutura xFuncionario ----------- */
printf("\t Programador \n\n");
printf(" Nome:     %s \n",px->nome);
printf(" Endereco: %s \n",px->endereco);
printf(" Idade:    %i \n",px->idade);
printf(" Salario:  %.2f \n\n",px->salario);

/* ----- Mostrando a estrutura xPonto ------------------ */
printf(" Ponto.id: %i \n",xpos->nId);
printf(" Ponto.x:  %i \t",xpos->x);
printf(" Ponto.y:  %i \n",xpos->y);

getchar();
return 1;
}
	
/* ------------------ Função initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
