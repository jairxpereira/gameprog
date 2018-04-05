#include "stdio.h"
#include "string.h"
#include "stdlib.h"

struct registro {
int nIdade;
char cClasse; };

/* Protótipos */
void initSys( char *title);
int menu(void);

void savegame(void);
void loadgame(void);


int main(void) {
xClientes[0].nIdade = 0;
xClientes[1].nIdade = 0;
xClientes[0].cClasse = 'X';
xClientes[1].cClasse = 'X';

printf("\tClasse \tIdade\n");
for (cx=0; cx<2;cx++)
printf("\t %c \t %d\n",xClientes[cx].cClasse, xClientes[cx].nIdade);

printf("\nPressione qualquer tecla para continuar.\n");
getch();


/* ....................... Segunda Parte/ Lendo Strutura ........ */


hMyFile = fopen(sFileName,"r");

if (hMyFile==NULL) {
printf("\nErro na abertura de arquivo. Programa abortado!\n");
exit (0); }

fread(&xClientes, nStrucSize, nRecords, hMyFile);

printf("\tClasse \tIdade\n");
for (cx=0; cx<2;cx++)
printf("\t %c \t %d\n",xClientes[cx].cClasse, xClientes[cx].nIdade);

fclose(hMyFile);
puts("\nEnd Of Program. Teste 15");
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


int menu(void) 
{
 
 char escolha = 0;
 
 printf ("\n\n");
 
 printf ("\t 1- Salvar jogo \n\n");
 printf ("\t 2- Carregar jogo \n\n");
 printf ("\t 3- Sair \n\n");
 
 printf("\t Sua escolha: ");
 escolha = getchar();
 
 switch (escolha)
 {
		case '1':
			return 1;
			break;
			
		case '2':
			return 2;
			break;
			
		case '3':
			return 3;
			break;
		
		default:
			return 3;
			break;
		
	
	} /* fim do switch */
	 
}

void savegame(void)
{
struct registro xClientes[2];
int nStrucSize;
int nRecords;
int cx=0;

FILE *hMyFile;
char sFileName[]="teste.txt";

int opt = 0;

xClientes[0].nIdade = 33;
xClientes[1].nIdade = 36;
xClientes[0].cClasse = 'A';
xClientes[1].cClasse = 'C';

initSys("title savegame.c");

opt = menu();

hMyFile = fopen(sFileName,"w");

if (hMyFile==NULL) {
printf("\nErro na abertura de arquivo. Programa abortado!\n");
exit(0); }

nStrucSize = sizeof(struct registro);
nRecords=2;

fwrite (&xClientes, nStrucSize, nRecords, hMyFile);

fclose(hMyFile);

}



