#include "stdlib.h"
#include "stdio.h"

int main(void)

{
unsigned char bytes[] = {
0xEB, 0x07, 0x46 , 0x61, 0x67, 0x6E, 0x65, 0x72, 0x24, 
0xB4, 0x09, 0xBA, 0x02, 0x01, 0xCD, 0x21,0xCD, 0x20, 0x00};

int ncx=0;

for (ncx=0; bytes[ncx]; ncx++)
{
printf ("%d ", bytes[ncx]);
if (ncx % 4 == 0) printf ("\n");
}


system("pause");


     

}
