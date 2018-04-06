/* Programa: thetypes.c - track 12*/
/* Ilustra tipos definidos pelo usuário*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
	
/* Protótipo de initSys() */
void initSys( char *title);


/* Declara um dado do tipo union */
union Byte_ou_Int {
unsigned char mybyte;
unsigned int myint;
} ByteOuInt;

/* Declara uma enumeração */
enum codigos 
{  
 GRAVAR,
 APAGAR,
 MODIFICAR,
 RETROCEDER
};

/* Declara byte como um tipo definido por usuário */
typedef unsigned char byte;

/* Declara a estrutura xFuncionario como um tipo definido */
typedef struct Funcionario
{
 char sNome[40];
 byte nIdade;
 float nSalario;
} xFuncionario;


/* -------------------------- main() ----------------------------- */
int main(void)	{

/* Declara programador diretamente como tipo xFuncionario */
xFuncionario programador;

initSys("title thetypes.c");

/* Preenche programador */
programador.nSalario = 3870.99;
programador.nIdade = 85;
strcpy(programador.sNome,"Jair Pereira");

/* Inicializa a estrutura union ByteOuInt */
ByteOuInt.mybyte = 170;
ByteOuInt.myint = 16800;

/* ---------------- Mostra programador */
printf(" Programador: %s   \n",programador.sNome);
printf(" Idade:       %d   \n", programador.nIdade);
printf(" Salario:     %.2f \n\n",programador.nSalario);

/* ---------------- Mostra a enumeração codigos*/
printf (" Codigos: \n");
printf (" gravar:    %d \t apagar:     %d \n",GRAVAR,APAGAR);
printf (" modificar: %d \t retroceder: %d \n\n",MODIFICAR,RETROCEDER);

/* ---------------- Mostra a union ByteOuInt */
printf(" ByteOutInt.mybyte:     %X %d \n",ByteOuInt.mybyte,ByteOuInt.mybyte);
printf(" ByteOuInt.myint:       %X %d \n",ByteOuInt.myint,ByteOuInt.myint);

getchar();

return 1;

}


/*************** Função initSys()  */
void initSys( char *title)
{
/* Configura a janela */
system(title);
system("color F1");
printf("\n\n");
}
