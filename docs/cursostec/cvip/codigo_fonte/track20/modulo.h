/* Arquivo: modulo.h             */
/* Ilustra o uso de extern       */
/* parte do programa mainpart.c  */

char sNome[] = "Variavel sNome[] do modulo.h";
char sCidade[] = "Sorocaba";
int nIdade = 33;

/* ------------------ Fun��o say()  ----------------------- */	
void say(char *sText) {
printf(" %s \n",sText);
}


/* ------------------ Fun��o initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}

