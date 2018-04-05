/* Programa: ptr08.c - track 17 */
/* Ponteiros para fun��es       */
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"


/* Prot�tipos */
void initSys( char *title);
void falar (char *sMsg);
void teste(void);
void msgEnfeitada(char *sMsg);

/* Prot�tipo da fun��o com fun��o como argumento */
void ChamaFunction (char *sMsg, void (* pPrint ) (char *sString));

int main(void)	{
/* Declarando vari�veis e ponteiros */
char Mensagem[] = " Conhecimento e' poder!";

/* Declara��o de ponteiros para fun��es */
void (*pFunction) (char *sInfo);
void (*fp) ();
void (*fpPrintEnfeitado) (char *s);

/* Inicializando o ponteiro de fun��es */
pFunction = falar;
fp = teste;
fpPrintEnfeitado = msgEnfeitada;

initSys("title ptr08.c");

ChamaFunction (" ChamaFunction() - com fpPrintEfeitado() ", fpPrintEnfeitado);
falar(" ------------------------------------------------------------- ");
ChamaFunction (" ChamaFunction() - com falar()", falar);
falar(" ------------------------------------------------------------- ");
ChamaFunction (" ChamaFunction() - com msgEnfeitada()", msgEnfeitada);

falar(" ------------------------------------------------------------- ");
falar(Mensagem);

/* Chamando a fun��o atrav�s do ponteiro */
pFunction (NULL);							/* = falar (NULL);           */
pFunction (" Teste Geral");   /* = falar (" Teste Geral"); */
fp();                         /* = teste();                */

/* Maneira alternativa de chamar as fun��es via ponteiro */
(*pFunction) ("\n");
(*fp) ();
(*pFunction) (" Sintaxe Alternativa  (*pFunction) (sMsg);");

getch();
return 1;
}

/******************** falar() *******************************/
void falar( char *sMsg) {
if (sMsg == NULL)
printf (" falar() - Argumento sMsg == NULL \n");
else
printf("%s \n",sMsg);
}

/******************* Teste() *****************************/
void teste(void) {
falar(" Dentro da funcao teste()");
}

/******************* ChamaFunction() ************************/
/* Fun��o que tem uma fun��o como argumento */
void ChamaFunction (char *sMsg, void (* pPrint) (char *sString)) {
(*pPrint) (" Dentro de ChamaFunction()");

/* Sintaxes alternativas */
(*pPrint) (sMsg);
 pPrint (sMsg);  
}

/************************* msgEnfeitada() ***********************/
void msgEnfeitada(char *sMsg) {
printf(" [--- %s ---] \n",sMsg);
}

/* ------------------ Fun��o initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
