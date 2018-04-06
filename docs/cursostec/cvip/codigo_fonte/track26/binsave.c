/* Programa: binsave.c - track 26           */
/* Ilustra gravaçao de arquivos binários    */
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/* Protótipos */
void initSys( char *title);

/* -- Estrutura de dados para gravar ----- */
typedef struct registro {
char sNome[18];
int nIdade;
} REGISTRO;

int main( int nCmd, char *sCmd[]) {


REGISTRO ficha[10];
FILE *hFile;

size_t nTamanho = sizeof(REGISTRO); /* Tamanho do registro */
size_t nRegGravados; /* Status de quantos registros gravados */
int nRegistros = 3; /* Qtd de registros a ser gravada */

/* ------------------ Preenche alguns registros---------- */
strcpy(ficha[1].sNome,"Jair Pereira");
ficha[1].nIdade = 35;

strcpy(ficha[2].sNome,"Pedro Cabral");
ficha[2].nIdade = 28;

strcpy(ficha[3].sNome,"Luiza Santos");
ficha[3].nIdade = 26;

initSys("title binsave.c");

/* ------------------ Abre o arquivo com fopen() --------- */
hFile = fopen("binteste.dat","wb");

/* ------------------ Verifica se houve falha    --------- */
if (hFile == NULL) 
{
printf("Falha na abertura do arquivo binteste.dat");
getch(); 
return -1;

}

/* ------------------ Grava dados ------------------------ */
nRegGravados = fwrite(&ficha[1], nTamanho, nRegistros, hFile);

/* ------------------ Status da gravação ----------------- */
printf(" nRegGravados: %i nTamanho: %i\n\n", nRegGravados, nTamanho);
printf(" %u bytes foram gravados\n\n", nRegGravados * nTamanho);

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
