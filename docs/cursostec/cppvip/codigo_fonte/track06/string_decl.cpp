	// string_decl.cpp
	// Ilustra definicao de objeto string
	#include <iostream>
	#include <string>

	using namespace std;

	int main() {
	system("color f0"); system("title string"); cout << "\n";	
	
	string snome = "gameprog";
	string sgame("Super Castlevania");
	
	cout << "\t" << snome << "\t" << sgame << "\n\n";	
	
	snome = "www." + snome + ".com.br";	
	sgame += " IV";	
	
	cout << "\t" << snome << "\t" << sgame << "\n\n";	
	
	system("pause");
	} // endmain
