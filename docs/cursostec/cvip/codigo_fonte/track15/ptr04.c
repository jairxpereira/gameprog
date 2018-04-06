/* Programa: ptr04.c - track 15*/
/* Acesso de array bidimensional via ponteiro */
#include "stdio.h"
#include "stdlib.h"
	
/* Prot�tipos */
void initSys( char *title);

/* ------------------ Fun��o main()  -------------------- */
	int main(void)	{

int nLinha, nColuna, ncx, *pTab;

int nTabela[50][20];

pTab = &nTabela[0][0];

initSys("title ptr04.c");

		/* Acessando elemento do jeito tradicional */
		for (nLinha = 0; nLinha < 50; nLinha++) {
			for (nColuna = 0; nColuna < 20; nColuna++)
			{
			nTabela[nLinha][nColuna] = 0;
			printf("%i", nTabela[nLinha][nColuna]); }}

		getch();		
		
		/* Acessando elemento via ponteiro */
		for (ncx = 0; ncx < 1000; ncx ++)
		{
		*pTab = 5;
		printf("%i", *pTab);
		pTab++;
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
