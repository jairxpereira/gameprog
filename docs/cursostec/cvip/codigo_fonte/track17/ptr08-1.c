/* Programa: ptr08.c - track 17 */
/* Ponteiros para funções       */
#include "stdio.h"
#include "stdlib.h"
#include "conio.h"



/* Protótipos */
void initSys( char *title);
int main(void) {

void digaMsg(char* msg) {  printf( " %s \n", msg); }

void (*pfnMsg) (char *msg);




void recado( char* recado, 
                   void (*pfnfalar) (char *msg) )
{
pfnfalar( recado );
(*pfnfalar) ( recado );                   

}


            



initSys("title PONTEIROS PARA FUNÇÕES");

digaMsg("Uso normal");

pfnMsg = digaMsg;

pfnMsg( "Uso via ponteiro 01");

(*pfnMsg) ("Uso via ponteiro 02");



recado( "acesse www.gameprog.com.br", digaMsg);

recado( "acesse www.gameprog.com.br", pfnMsg);



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

void digaOi(void)
{
printf ("\n Oi! \n");
}
 
