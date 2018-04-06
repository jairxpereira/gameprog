#include "stdlib.h"
#include "stdio.h"

int main(void)
{
int nval = 1000;
char myc = 'q';
double pi = 3.1415;

void** p[3];

(int *) p[0] = &nval;

p[1] = &myc;

(double *) p[2] = (double *) &pi;
    
printf("\n\n *p[0]: %i \n", *p[0]);

printf("\n\n *p[1]: %c \n", *p[1]);


printf("\n\n *p[2]: %lf \n", *p[2]);


getchar();
} // main(void).fim
