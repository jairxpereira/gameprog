/* Programa: ptr08.c - track 17 */
/* Ponteiros para funções       */
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"


/* Protótipos */
void initSys( char *title);
void falar (char *sMsg);
void teste(void);
void msgEnfeitada(char *sMsg);

/* Protótipo da função com função como argumento */
void ChamaFunction (char *sMsg, void (* pPrint ) (char *sString));

int main(void)	{
/* Declarando variáveis e ponteiros */
char Mensagem[] = " Conhecimento e' poder!";

/* Declaração de ponteiros para funções */
void (*pFunction) (char *sInfo);
void (*fp) ();
void (*fpPrintEnfeitado) (char *s);

/* Inicializando o ponteiro de funções */
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

/* Chamando a função através do ponteiro */
pFunction (NULL);							/* = falar (NULL);           */
pFunction (" Teste Geral");   /* = falar (" Teste Geral"); */
fp();                         /* = teste();                */

/* Maneira alternativa de chamar as funções via ponteiro */
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
/* Função que tem uma função como argumento */
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

/* ------------------ Função initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
