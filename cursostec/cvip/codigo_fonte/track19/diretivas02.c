/* Programa: diretivas.c track 19            */
/* Testando diretivas de compilação        */
#include "windows.h"
#include <stdio.h>
#include <stdlib.h>

#include "gameprog.h"
#include <wincon.h>



int main(void)	
{
initSys("title diretivas02.c - DIRETIVAS DE COMPILAÇÃO");

HDC hdc;

hdc = GetDC(NULL);
TextOut (hdc, 10, 10, "Hackeado", 8);
ReleaseDC ( (HWND) GetConsoleWindow(), hdc);




#ifdef VERSAO_COMERCIAL
printf(" Versao completa Ok \n");
#else
printf(" Versao demo - Vai expirar em 30 dias... \n");
#endif

#if defined VERSAO_COMERCIAL
printf(" Todas as funcoes presentes... \n");
#endif


#ifndef VERSAO_COMERCIAL
printf(" Funcionalidades limitada... \n");
#else
     printf(" Todas as funcoes presentes... \n");
#endif

#if !defined VERSAO_COMERCIAL
printf(" Funcionalidades limitada... \n");
#endif

getchar();
return 1;
}

#include "gameprog.c"


