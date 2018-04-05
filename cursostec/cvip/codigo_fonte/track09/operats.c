/* Programa: operats.c - track09  */
/* Operadores lógicos */
#include "stdio.h"
#include "stdlib.h"

void liberar(void);
void negado(void);
void initSys(void);
void espera(void);
void mostra_saldo(char* msg, int nValor);

int main(void)	{

int nIdade = 15, nCarteira = 2;	
int sim = 1, nao = 0;

int pgto_efetuado = nao;
int nIngressoValor = 5;

initSys();

printf(" Filme: O senhor dos aneis - Censura: 12 anos\n");
printf(" Valor do ingresso: R$ 5,00 \n\n");

printf(" Sua idade: %i \n", nIdade);
printf(" Pagamento: %i\n", nCarteira);

if (nCarteira < nIngressoValor) 
 printf(" Vc nao tem saldo para comprar o ingresso. \n");	

if (nCarteira >= nIngressoValor && nIdade > 12)
{
nCarteira -= nIngressoValor;  /* nCarteira = nCarteira - nIngressoValor; */		
pgto_efetuado = sim;
}


if (nIdade > 12 && pgto_efetuado == sim) liberar();
if (nIdade <= 12 || pgto_efetuado == nao) negado();

if (nCarteira > 0 && nIdade > 12)
 printf(" Seu troco: %i \n\n", nCarteira);		

nCarteira += 3; mostra_saldo("+= 3", nCarteira);
nCarteira *= 2; mostra_saldo("*= 2", nCarteira);
nCarteira++; mostra_saldo("++  ", nCarteira);
nCarteira /= 3; mostra_saldo("/= 3", nCarteira);
nCarteira %= 2; mostra_saldo("%= 2", nCarteira);
		
espera();
return 1;
}

/* ******************** funções ************************** */
/*************** Função liberar()  */
void liberar(void) {
printf(" Sessao de cinema liberada!\n");
}

/*************** Função negado()  */
void negado(void) {
printf(" Sessao apenas para maiores de 12 anos \n");
}


/*************** Função initSys()  */
void initSys(void)
{
/* Configura a janela */
system("title operats.c");
system("color F1");
printf("\n\n");
}

/*************** Função espera()  */
void espera(void)
{
printf("\n\n");
system("pause");             
}

void mostra_saldo(char *msg, int nvalor)
{
printf(" nCarteira %s \t Seu saldo:  R$ %i,00 \n", msg, nvalor);
}

