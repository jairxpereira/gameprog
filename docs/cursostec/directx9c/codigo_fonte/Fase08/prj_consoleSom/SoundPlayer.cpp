//******************************************************************/
// SoundPlayer.cpp: implementação da classe CSoundPlayer
// Descrição: Usa o  DirectSound para tocar sons
// Nota: Faz uso dos arquivos dsutil.cpp e dsutil.h que pertencem
// ao framework do directx. Estes arquivos definem as classes
// CSoundManager e CSound usadas por este programa
// Criado por Keith Ditchburn 30/01/2004
//******************************************************************/

#include "motor.h"
#include "SoundPlayer.h"
#include <assert.h>
#include "dsutil.h"

//******************************************************************/
CSoundPlayer::CSoundPlayer()
{
	m_soundManager=NULL;
}

//******************************************************************/
CSoundPlayer::~CSoundPlayer()
{
	if (m_soundManager)
		delete m_soundManager;
}

//******************************************************************/
// Inicializa o DirectSound usando a classe CSoundManager
//******************************************************************/
HRESULT CSoundPlayer::Initialise(HWND hWnd)
{
	HRESULT hr=S_OK;

    m_soundManager = new CSoundManager();

	// Configura o nível de cooperação para DSSCL_PRIORITY, 
    if( FAILED( hr = m_soundManager->Initialize( hWnd, DSSCL_PRIORITY) ) )
    {
			MessageBox( hWnd, "DirectSound: falha na inicialização!", 
                            "CSoundPlayer::Initialise()", 
														MB_OK | MB_ICONERROR );
        return hr;
    } // endif

    	

		// Configura o formato do buffer primário ( primary buffer formato)
		// para estéreo, 22kHz e saída 16-bit
    if( FAILED( hr = m_soundManager->SetPrimaryBufferFormat( 2, 22050, 16 ) ) )
    {
   			MessageBox( hWnd, "DirectSound: falha na inicialização!", 
                            "CSoundPlayer::Initialise()", 
														MB_OK | MB_ICONERROR );
        return hr;
    } // endif

	return hr;
}

//******************************************************************/
// Desc: Adiciona uma som no format wav
// Retorna FALSE em caso de falha
// No sucesso retorna TRUE e preenche um id para este som
//******************************************************************/
bool CSoundPlayer::AddWav(char *filename, int *id)
{
	assert(filename);
	assert(id);

	// Cria o arquivo de som
	CSound *newSound=NULL;

	HRESULT hr;

	  // Carrega o arquivo wav para dentro desse buffer do DirectSound
    if( FAILED( hr = m_soundManager->Create( &newSound, 
			filename, 0, GUID_NULL ) ) )
		return FALSE;

	
	// No sucesso, adiciona o som ao vetor e preenche o id em retorno
	m_soundVector.push_back(newSound);

	*id = m_soundVector.size() - 1;

	return TRUE;
}

//******************************************************************/
// Toca o som referente ao id passado, Se loop for TRUE o som tocará
// continuamente até ser parado
//******************************************************************/
bool CSoundPlayer::PlaySound(int id, bool loop)
{
	assert(id >= 0 && id < m_soundVector.size());

    DWORD flags=0;
	if (loop)
		flags = DSBPLAY_LOOPING;

    HRESULT hr = m_soundVector[id]->Play( 0, flags );

	return FAILED(hr);
}

//******************************************************************/
// Pára o som sendo tocado
//******************************************************************/
void CSoundPlayer::StopSound(int id)
{
	assert(id >= 0 && id < m_soundVector.size());

	m_soundVector[id]->Stop();
}
