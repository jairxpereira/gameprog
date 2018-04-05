/* Programa: loop01.c - track07 */
/* Este programa testa a instrução for */
#include "stdio.h"
#include "stdlib.h"

int main(void)  {                                                                                               
                                                                                                        
int ncx;                                                                                                
                                                                                                        
/* Configura a janela */
system("title loop01.c");
system("color F1");
printf("\n\n");                                                                                             
                                                                                                        
for (ncx = 1; ncx <= 3; ncx = ncx + 1) printf (" %i \n",ncx);                                            
                                                                                                        
printf("\n");  
                                                                                         
for (ncx = 0; ncx < 10; ncx = ncx + 2)      
{                                                            
printf (" %i \n",ncx);
}                                                                                   
                                                                                                        
printf("\n\n");
system("pause");                                                                                            
                                                                                                        
return 1;
}         
