#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void esperar(void);
void iniciar(char comando[]);


typedef struct tagPonto 
{
     
int x;
int y;
       
} Ponto;

      
typedef struct tagJogador 
{
Ponto pos;
int vidas;
int energia;
char nome[40];
} Jogador;

void mostrarJogador( Jogador* jog);

int main(void) {
    
    Jogador gameprog;
    Jogador mario = { 160, 120, 50, 88, "Mario"};
    
    Jogador inimigos[2];
    
    inimigos[0].pos.x = 100;
    inimigos[0].pos.y = 110;
    inimigos[0].energia = 100;
    inimigos[0].vidas = 1;
    strcpy (inimigos[0].nome, "wario");
    
    
    gameprog.pos.x = 320;
    gameprog.pos.y = 240;
    gameprog.vidas = 7;
    gameprog.energia = 99;
    
    strcpy( gameprog.nome, "Jair");
    

    
iniciar("title estruturas");
    mostrarJogador(&gameprog);
    mostrarJogador(&mario);
    mostrarJogador (&inimigos[0]);
    
    
    





esperar();

    
} // main().fim


void iniciar(  char comando[])
{
     
system(comando);
system("color 1f");
printf("\n\n");
} // iniciar().fim


void esperar(void)
{
printf("\n"); system("pause");
} // esperar().fim


void mostrarJogador( Jogador* jog) {
     
printf ( " Jogador: %s (%i, %i) [%i, %i] \n",
jog->nome, jog->pos.x, jog->pos.y, 
jog->vidas, jog->energia);
 
}
     
