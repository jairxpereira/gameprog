/* Programa ptr07-1.c - track 17                  */
/* Retornando ponteiros */ 
#include "stdio.h"
#include "stdlib.h"


typedef struct Ponto
{
int x;
int y;
};
        
void mostraPonto ( struct Ponto *p){
     printf(" (%i, %i) \n", p->x, p->y); }
     
struct Ponto* dobraPonto( struct Ponto *pt)
{
pt->x = 2 * pt->x;
pt->y = 2 * pt->y;
return pt;       

}
    

/* Protótipos */
void initSys( char *title);



int main(void)	{

initSys("title RETORNANDO PONTEIROS");

struct Ponto pos = {2,4};

mostraPonto (&pos);

dobraPonto (&pos);
mostraPonto (&pos);


mostraPonto ( dobraPonto( &pos) );




getchar();

return 1;}


/* ------------------ Função initSys()  -------------------- */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}

                       
   


