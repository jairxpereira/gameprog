// criando_classes_ver02.cpp
// ilustra a criacao de classes com sintaxe alternativa
#include <iostream>
#include <string>

using namespace std;

// prototipo de nossas funcoes basicas
void inicio();
void fim();

// Vamos criar uma classe Monstro para criar objetos monstro
class Monstro
{
private:
int m_energia;
int m_estrago;
string m_snome;		
		
public:
Monstro ();
Monstro (int energia, int estrago);
Monstro (int energia, int estrago, string nome);


				
void atacar();
string getName();
void setName(string nome);
void info();				
	
}; // endclass: Monstro

int main() {
	
inicio();

	
int energia, estrago;
	
// Criando um objeto da classe monstro
Monstro godzila;
Monstro vampiro = Monstro (22,222);
Monstro ogro = Monstro(33,333, "monstro_c3");
	
cout << "\n";
	
godzila.info();
ogro.info();
vampiro.info();
	
cout << "\n";	
	
// Vamos atacar
godzila.atacar();
vampiro.atacar();
ogro.atacar();	
	
vampiro.setName("Dracula");
cout << "\n\tvampiro.getName(): " << vampiro.getName() << "\n";
vampiro.info();

// int Mosntro::m_energia is private within this context
// vampiro.m_energia = 100;  	
	
fim();
} // endmain

//************* implementacao dos metodos ************************************
Monstro::Monstro() {
cout << "\t Construtor 01 chamado" << "\n";
m_energia = 11;
m_estrago = 111;
m_snome = "monstro_c1";
} // fim do construtor 01


Monstro::Monstro(int energia, int estrago): m_energia(energia), m_estrago(estrago),
m_snome("monstro_c2") {}
// fim do construtor 02

Monstro::Monstro(int energia, int estrago, string nome): m_energia(energia),
m_estrago(estrago), m_snome(nome) {
cout << "\t Construtor 03 chamado" << "\n";
} // fim do construtor 03

		
void Monstro::atacar() {
cout << "\t" << m_snome << " atacou e vc perdeu " 
<< m_estrago << " pontos de energia. \n";			

} // endmethod: atacar()

string Monstro::getName() { return m_snome; }

void Monstro::setName( string nome) { m_snome = nome; }

void Monstro::info() {
cout << "\t" << m_snome;
cout << "\t energia: " << m_energia;
cout << "\t estrago: " << m_estrago << "\n";	
} // endmethod: info()


//************* funcoes ******************************************************
void inicio() {
system("color f0");
system("title criando classes versao 02");
cout << "\n";	
} // endfunction: initsys()
	
void fim() {
cout << "\n";	system("pause");
} // endfunction: endsys()
