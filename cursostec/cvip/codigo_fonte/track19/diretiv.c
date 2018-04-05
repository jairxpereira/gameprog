/* Programa: diretiv.c track 19            */
/* Testando diretivas de compilação        */
#include <stdio.h>
#include <stdlib.h>

/* ----- Definição das constantes ---------------------------- */
#define		TESTE

#define		XTESTE 	12
#define		DOBRO(x) ((x) * 2)

/* Protótipos */
void initSys( char *title);

int main(void)	
{
initSys("title diretiv.c");

/* ------------------ Teste de #ifdef/#else/#endif ----------- */
#ifdef TESTE
printf(" A constante TESTE foi definida\n\n");
#else
printf(" A constante TESTE nao foi definida\n");
#endif

/* ------------------ Teste de #ifndef/#else/#endif ---------- */
#ifndef TESTE
printf(" A constante TESTE nao foi definida ou foi apagada\n");
#endif

/* ------------------ Teste de #ifndef/#else ---------------- */
#ifndef TESTE
printf("\n\n Testando #undef ifndef...\n");
printf(" A constante TESTE nao foi definida ou foi apagada\n");
#else
printf(" Testando #define #ifndef #else...\n\n");
#endif


/* ------------------ Teste de #elif ----------------------- */
#if (XTESTE == 10)
printf(" XTESTE == 10\n");
#elif (XTESTE == 12)
printf(" XTESTE == 12 (true) Testando #if\\#elif\n\n");
#endif


/* --------- Teste de #define DOBRO(x) ((x) * 2)  ---------- */
printf(" Dobro de 256: %i\n\n", DOBRO(256));


/* ------------------ Teste de #if defined()  -------------- */
#if defined(TESTE)
printf (" #if defined() ok \n\n");
#endif

/* ------------------ Apaga TESTE  ------------------------- */
#undef TESTE

/* ------------------ Teste de #if !defined()  ------------- */
#if !defined(TESTE)
printf(" #if !defined() ok \n\n");
#endif

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

