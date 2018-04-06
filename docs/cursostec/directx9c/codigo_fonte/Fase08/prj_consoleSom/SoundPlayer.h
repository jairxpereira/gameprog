// [---
//*******************************************************************
// SoundPlayer.h: Interface para a classe CSoundPlayer.
// Descrição: Usa o  DirectSound para tocar sons
// Nota: Faz uso dos arquivos dsutil.cpp e dsutil.h que pertencem
// ao framework do directx. Estes arquivos definem as classes
// CSoundManager e CSound usadas por este programa
// Criado por Keith Ditchburn 30/01/2004
//*******************************************************************  

#ifndef soundplayer_h
 #define soundplayer_h

#include <vector>

// Classes utilizadas na implementação deste arquivo
class CSoundManager;
class CSound;

class CSoundPlayer  
{

private:
	// Objeto gerenciador de som
	CSoundManager *m_soundManager;

	// Coleção de arquivos de som
	std::vector <CSound*> m_soundVector;

public:

	// Adiciona um arquivo wav ao vetor produzindo um id
	bool AddWav(char *filename, int *id);

	// Toca o som com repetição continua se loop = TRUE
	bool PlaySound(int id, bool loop);

	// Pára de tocar o som
	void StopSound(int id);

	// Inicializa o objeto tocador de som (CSoundManager)
	HRESULT Initialise(HWND hWnd);

	// Construtor
	CSoundPlayer();

	// Destrutor
	virtual ~CSoundPlayer();

};

#endif
// ---]