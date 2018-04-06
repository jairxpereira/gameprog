// test_cout.cpp

#include <iostream>
#include <iomanip>


using namespace std;

int main() {
	
system("color f0"); system ("title testando cout");
	
	float pi = 3.1415f;
	int nvalor = 170, nvidas = 0;
	string txt = "Programming is cool!";
	float nsalario = 800.00;
	char sbuffer[255];	
	bool lgame_over = nvidas > 0;
	
	cout << "\n";
	cout << "\t Mensagem: " << txt << "\t\t";
	cout << "pi: " << pi << "\n\n";
	
	cout << showbase << uppercase;
	cout << "\t nvalor: " << hex << nvalor <<  "\t" << 255 << "\n";
	 
	cout << showbase << nouppercase;
	cout << "\t nvalor: " << dec << nvalor <<  "\t" << 255 << "\n";
	
	
	cout << "\t nvalor: " << hex << nvalor <<  "\t" << 255 << "\n";
	
	cout << setiosflags(ios_base::dec | ios_base::showpos );
	

	cout << "\t nsalario: " <<  nsalario << "\t nvalor: "  << nvalor << "\n";
	
	cout << "\t lgame_over: " << noshowpos << lgame_over << "\t";
	cout << boolalpha << "\t lgame_over: " << lgame_over << "\n";
	
	cout << "\t \"cCedilha: \x87\" \n\n";
	
	sprintf(sbuffer, "\t String formatada: nvalor: %d nsalario: %f \n\n" , nvalor, nsalario);
	
	cout << sbuffer << "\n";		
	
	system("pause");	
	
} // endmain
