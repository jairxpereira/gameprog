// vetores_02.cpp
// Ilustra o uso de vetores - parte 2
#include <iostream>
#include <vector>

using namespace std;

// ----------------------- classse sistema ---------------------------------
// ------ demonstra o uso de funcoes estaticas numa classe -----------------
class Sistema {
public:
static void inicio() { 
system("color f0"); system ("title vetores_02.cpp");
cout << "\n";	
} // fim do metodo: inicio()

static void fim() {
cout << endl;
system("pause");
} // fim do metodo: fim()

}; // fim da classe sistema


// ----------------------- classse monstro ---------------------------------
class Monstro {
public:

int m_estrago;
int m_id;
static int id_automatico;

Monstro(int estrago = 10): m_estrago(estrago) {
m_id = id_automatico;
id_automatico++;
} // fim do construtor		
		
void atacar() {
cout << "\t O monstro #" << m_id << " te atacou e vc perdeu ";
cout << m_estrago << " pontos de energia" << "\n";		
} // fim do metodo atacar()		

}; // fim da classe monstro

int Monstro::id_automatico = 1;

vector<Monstro *> lista_monstro;
vector<Monstro *>::iterator ncx_iter;

// ------------------ funcoes para manipular monstros -------------------------
void mostra_monstro() {
for (ncx_iter = lista_monstro.begin(); ncx_iter != lista_monstro.end(); ncx_iter++)
(*ncx_iter)->atacar();	
} // fim da funcao monstro

void monstro_vencido( int nMonstro) {
nMonstro = nMonstro - 1;
ncx_iter = lista_monstro.begin() + nMonstro;
lista_monstro.erase(ncx_iter);	
} // fim da funcao: monstro_vencido()

// -------------------- inicio da funcao principal ---------------------------
int main() {
Sistema::inicio();	

for (int ncx=0; ncx < 5; ncx++) {
int temp_estrago = (ncx+1) * 11;
lista_monstro.push_back( new Monstro( temp_estrago) );
}


for (int ncx=0; ncx < 5; ncx++)	lista_monstro[ncx]->atacar();

cout << "\n\n \tO jogador matou o monstro #2 e #3\n";
cout << "\t--------------------------------------\n";
monstro_vencido (2); monstro_vencido(2);
mostra_monstro();

Sistema::fim();
} // endmain
