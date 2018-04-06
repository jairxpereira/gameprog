/* Programa: binload.c track 26            */
/* Ilustra leitura de arquivos binários    */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* Protótipos */
void initSys( char *title);

typedef struct dados {
char sTexto[18];
int nInteiro;
} DADOS;

int main( int nCmd, char *sCmd[]) {

/* ------------------ Variáveis de trabalho ------------- */
DADOS xDados[10];
FILE *hFile;
size_t nTamanho = sizeof(DADOS);	/* Tamanho do registro    */
size_t nRegLidos;									/* Qtd de registros lidos */
int nRegistros = 1; 							/* Qtd de registros a ler */

initSys("title binload.c");

/* ------------------ Abre o arquivo com fopen() --------- */
hFile = fopen("binteste.dat","rb");


/* ------------------ Verifica se houve falha ----------- */
if (hFile == NULL)
{
printf(" Falha na abertura do arquivo binteste.dat\n");
getch(); 
return -1;
}

/* --- Apontado para o inicio do terceiro registro: ------ */
fseek(hFile, nTamanho * 2,SEEK_SET);

/* ------------------ Lendo os dados  -------------------- */
nRegLidos = fread(&xDados[1], nTamanho, nRegistros, hFile);

/* ------------------ Mostra dados lidos ----------------- */
printf(" %d bytes foram lidos\n\n", nRegLidos * nTamanho);
printf(" xDados[1].sTexto:   %s \n",xDados[1].sTexto);
printf(" xDados[1].nInteiro: %d \n",xDados[1].nInteiro);

/* ------------------ Fecha o arquivo -------------------- */
fclose(hFile);

getch();
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
