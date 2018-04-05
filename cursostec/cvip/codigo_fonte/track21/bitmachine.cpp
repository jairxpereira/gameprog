#include "stdio.h"
#include "stdlib.h"

int main (void)

{    
    system("title Configuração de bits");
    system("color 1f");
    
    
    typedef unsigned int uint;

    uint config, casado, palmeirense, evangelico;

    config = casado = palmeirense = evangelico = 0;


    casado      = 1 << 1;        // 1 - 0001
    palmeirense = 1 << 2;        // 2 - 0010
    evangelico  = 1 << 3;        // 4 - 0100

    // Combina os flags
    config =  casado | palmeirense | evangelico;

    config = config - casado ;


    printf ("\n Casado: %u \n", casado);
    printf (" palmeirense: %u \n", palmeirense);
    printf (" evangelico: %u \n", evangelico);
    printf ("\n config: %u \n", config);

    puts("\n");
    if (config & casado) printf (" vc e' casado! \n");
    if (config & palmeirense) printf (" vc e' palmeirense! \n");
    if (config & evangelico) printf (" vc e' evangelico! \n");


    puts("\n");
    system("pause");


} // main().end

