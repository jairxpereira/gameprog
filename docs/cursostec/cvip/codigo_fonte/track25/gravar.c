/* Programa: gravar.c - track 25           */
/* Ilustra abertura e gravaçao de arquivos */
#include "stdio.h"
#include "stdlib.h"

/* Protótipos */
void initSys( char *title);

/* ------------------ Função main()  -------------------- */
int main( int nCmd, char *sCmd[])	{

FILE *hFile;
int ncx;
const char sMode[] = "aw";
const char sFileName[] = "teste.txt";
char sMsg[] = "Mensagem nro";

initSys("title gravar.c");

/* ------------------ Abre o arquivo com fopen() --------- */
hFile = fopen(sFileName, sMode);


/* ------------------ Verifica se houve falha    --------- */
if (hFile == NULL)
{
printf("Falha na abertura do arquivo!");
getch();
return -1;
}

/* ------------------ Grava dados ------------------------ */
for (ncx =0; ncx < 10; ncx++) {
printf(" %s %d \n",sMsg,ncx);
fprintf(hFile, "%s %d\n",sMsg,ncx);	}

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


