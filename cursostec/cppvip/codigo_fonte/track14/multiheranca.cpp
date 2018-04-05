// multiheranca.cpp
// Este programa ilustra o uso heranca multipla
#include <iostream>
using namespace std;

// ------------------------- classe SistemaSom --------------------------
class SistemaSom {
		public:
	// Metodo playSom()
	void playSom(int nid = 0) {	
		if (nid != 0) cout << " O objeto #" << nid << " tocou o som ";	
		cout << "bang! boom! \n";
	} // fim do metodo: playSom()		
}; // fim da classe: SistemaSom
// **************************************************************************


// ------------------------- classe SpriteGestor --------------------------
class SpriteGestor {
	public:
	int m_id;
	int m_xpos;
	int m_ypos;
	
	static int autonumerador;
	
	// construtor da classe
	SpriteGestor(int x=0, int y=0): m_xpos(x), m_ypos(y)
	 {
	 m_id = autonumerador;
	 autonumerador++;		
  }
  
  void desenhar() 
  {
		char txt[40];
		sprintf(txt, " Obj #%d desenhado na posicao (x:%d y:%d)", m_id, m_xpos, m_ypos);
		cout << txt << "\n\n";
		
	} // fim do metodo: desenhar()		
	
}; // fim da classe SpriteGestor

int SpriteGestor::autonumerador = 1;
// **************************************************************************


// ------------------------- classe SpriteDinamica --------------------------
class SpriteDinamica: public SpriteGestor {
	public:
		
		SpriteDinamica(int x=11, int y=22): SpriteGestor(x,y) {}
		
		void mover (int dx, int dy)
		{
			m_xpos = m_xpos + dx;
			m_ypos = m_ypos + dy;
			cout << " Obj #" << m_id << " movido para nova posicao.\n";
		}	
		
	
}; // fim da classe: SpriteGestor
// **************************************************************************

// ------------------------- classe Vampiro --------------------------
class Vampiro: public SpriteDinamica, public SistemaSom {
	public:
	int m_estrago;	
	
	Vampiro (int x=33, int y=44): SpriteDinamica(x,y) { m_estrago = 55;}
	
	void morder() 
	{
	cout << " O vampiro #" << m_id << " te mordeu e vc perdeu ";
	cout << m_estrago << " pontos de energia \n";
	}	
	
}; // fim da classe Vampiro
// **************************************************************************



// ------------------------- Inicio do programa: main() ----------------------
int main() {
	system("color f0"); system("title multiheranca.cpp"); cout << endl;
	
	// Objeto base 1) SpriteGestor
	// Apenas pode desenhar-se
	SpriteGestor sprt01(320,240);
	
	
	// 1) SpriteGestor 2) SpriteDinamica
	// Pode desenhar-se e mover-se
	SpriteDinamica sprt02;
	
	
 	// 1) SpriteGestor 2) SpriteDinamica 3) Vampiro 4) SistemaSom
	 // dracula vai poder desenhar-se(SpriteGestor), mover-se(SpriteDinamica)
	 // morder(Vampiro) e tocar som(SistemaSom)	
	Vampiro dracula;		
	
	sprt01.desenhar();
	
	sprt02.desenhar();
	sprt02.mover(11,22);
	sprt02.desenhar();
	
	dracula.desenhar();
	dracula.mover(1,1);
	dracula.morder();
	dracula.playSom(dracula.m_id);	
	
cout << endl; system("pause");
} // fim da funcao: main()

