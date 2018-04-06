/* Programa: switch.c - track06 */
/* Este programa testa a instrução switch */
#include "stdio.h"
#include "stdlib.h"

	int main(void)	{

		int nEscolha;
		int nDinheiro = 500;
		int espada_custo = 50;
		int bota_custo = 60;
		int capa_custo = 80; 
		
		int capa, bota, espada;
		capa = bota = espada = 0;

/* Configura a janela */
system("title switch.c");
system("color F1");
printf("\n\n");

		printf(" espada:%i bota:%i capa:%i \n", espada, bota, capa);
		printf(" Seu saldo: %i \n\n", nDinheiro);
		
		printf(" 1- espada  - 50 pts \n");
		printf(" 2- bota    - 60 pts \n");
		printf(" 3- capa    - 80 pts \n");
		printf("\n\n Que item vc quer comprar? ");
		scanf("%i", &nEscolha);

		switch(nEscolha) {
		case 1:
		printf(" Saindo uma espada...\n");
		nDinheiro = nDinheiro - espada_custo;
		espada = espada + 1;
		break;

		case 2:
		printf(" Saindo uma bota...\n");
		nDinheiro = nDinheiro - bota_custo;
		bota = bota + 1;
		break;

		case 3:
		printf(" Saindo uma capa...\n");
		nDinheiro = nDinheiro - capa_custo;
		capa = capa + 1;
		break;

		default:
		printf(" ...Hoje nao temos este item... \n");
		} /* endswith */
		
		
		printf("\n\n Seu saldo: %i \n", nDinheiro);
		printf(" espada:%i bota: %d capa: %i \n", espada, bota, capa);


	printf("\n\n");
	system("pause");

	return 1;
	}
