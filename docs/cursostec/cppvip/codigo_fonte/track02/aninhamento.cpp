// aninhamento.cpp
#include <iostream>
using namespace std;

int main()
{	
	system("color f0"); system ("title aninhamento.cpp");
	
for (int ncx = 0; ncx < 10; ncx++)
 {		
		{
				int nteste = 5;
				{
				for (int mcx =0; mcx < nteste; mcx++) cout << mcx <<  "\t";
				}	// fim do bloco mais interno			
			
	  }	// fim do bloco mais externo
	
		cout <<  ncx <<  endl;
		
	} // fim for ncx 
	
	system("pause");
} // endmain
