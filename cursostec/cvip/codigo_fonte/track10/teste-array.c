#include "stdio.h"
#include "stdlib.h"


void iniciar(void);
void esperar(void);



int main()

{
    iniciar();
    int linha, coluna;
    linha = coluna = 0;
    
    int pontos[5][3] = {  160,140,1 ,
                       320, 240,1 ,
                       640,480,1,
                       1280, 960,1,
                       1368, 768,1 };
                       
    pontos[3][2] = 999;
    
    
    for (linha = 0; linha < 5; linha++)
    {
       
        
    printf (" p%i: %i %i %i \n", 
    linha, pontos[linha][0], pontos[linha][1], pontos[linha][2]);
        
         
    }        



    
esperar();    
} /* fim de main */


void iniciar(void)
{
system("title arrays ou tabelas ou matrizes ou vetores");
system("color 1f");
printf ("\n");     
} /* fim de iniciar() ou iniciar().fim */


void esperar(void)
{
printf("\n"); system("pause");
} /* fim de esperar() */
 
     
