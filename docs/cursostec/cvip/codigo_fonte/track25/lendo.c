/* Programa: lendo.c - track 25           */
/* Ilustra leitura de dados de arquivos   */
#include "stdio.h"
#include "stdlib.h"

/* Protótipos */
void initSys( char *title);

/* ------------------ Função main()  -------------------- */
int main( int nCmd, char *sCmd[])	{

FILE *hFile;
char sLinha[80];
int ncx;

initSys("title lendo.c");

/* ------------------ Abre o arquivo com fopen() --------- */
hFile = fopen("teste.txt","r");


/* ------------------ Verifica se houve falha    --------- */
if (hFile == NULL)
{
printf(" Falha na abertura do arquivo!");
getch();
return -1;
}

/* ------------------ Lê os dados ------------------------ */
for (ncx=0; ncx <= 10; ncx++){
fgets(sLinha, 80,hFile);
printf(" %s",sLinha);	}

/* ------------------ Fecha o arquivo -------------------- */
fclose(hFile);

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


