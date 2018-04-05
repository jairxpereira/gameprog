 
// [--- 
//-----------------------------------------------------------------------------
// Projeto: prj_DirectShow - arquivo: gpmediaplayer.cpp
// Esta aplicação mostra como tocar vídeo e música
// com o DirectShow. By www.gameprog.com.br
// -----------------------------------------------------------------------------
#include <windows.h>
#include <dshow.h>

// Biblioteca do DirectShow
#pragma comment ( lib, "strmiids.lib")
#pragma warning (disable:4996)

// Notificação de eventos do DirectShow
#define WM_P_GRAPHNOTIFY WM_APP + 1

// Indicação se o DirectShow está tocando música ou vídeo
#define modo_video	1
#define modo_musica -1
// ---]
// [---
class GPMediaPlayer

{
private:
	
	// Membro para receber o handle da janela da aplicação
	HWND hJanela;

	// 1 = video // -1 = música
	int mediaModo;
// ---]
// [---
public:
	// Recebe os resultados das operações
	HRESULT m_hr;

	// Interface do construtor de gráficos
	IGraphBuilder *gfxConstrutor;

	// Interface de controle de mídia (play, stop, pause, etc...)
	IMediaControl *mdControle;

	// Interfaces de controle de evento
	IMediaEventEx *mdEventos;

	// Interface da janela de vídeo
	IVideoWindow  *janelaVideo;

// [---
	// Construtor default
	GPMediaPlayer () 
	{
		gfxConstrutor = NULL;	
		mdControle		= NULL;	
		janelaVideo		= NULL;
		mdEventos		= NULL;
		m_hr			= 0;
		hJanela			= NULL;

	} // Contrutor().fim
// ---]
// [---
	void inicializar(void)
	{		
		// inicializa a interface COM
		CoInitialize(NULL);

		// Cria o gerenciador do gráfico de filtros
		m_hr = CoCreateInstance (CLSID_FilterGraph, NULL, 
			CLSCTX_INPROC_SERVER,	IID_IGraphBuilder, 
			(void **) &gfxConstrutor);

		// Cria a interface de controle de mídia
		m_hr = gfxConstrutor->QueryInterface(IID_IMediaControl, (void **)&mdControle);

		// Cria a interface de controle de eventos extras
		m_hr = gfxConstrutor->QueryInterface(IID_IMediaEventEx, (void **)&mdEventos);

	} // inicializar().fim
// ---]
// [---
	void carregarVideo( LPCWSTR videoArquivo)
	{  	
		// Carrega o arquivo de mídia apontado
		m_hr = gfxConstrutor->RenderFile(videoArquivo, NULL);

		// indica modo de vídeo
		mediaModo = modo_video;		

		// avisa se houver falha
		seHouverFalha("Falha: gfxConstrutor->RenderFile()", "GPMediaPlayer:carregarVideo()");
	} // carregarVideo().fim
// ---]
// [---	
	void carregarMusica( LPCWSTR musicaArquivo)
	{  
		// Carrega o arquivo de mídia apontado
		m_hr = gfxConstrutor->RenderFile(musicaArquivo, NULL);

		// indica modo de música
		mediaModo = modo_musica;

		// avisa se houver falha
		seHouverFalha("Falha: gfxConstrutor->RenderFile()", "GPMediaPlayer:carregarVideo()");
	} // carregarMusica().fim
// ---]
// [---
	void setOwner( HWND hWnd )
	{
		
		// Essa função não interessa pra música!
		if (mediaModo == modo_musica ) return;

		// Obtém a janela de vídeo
		if (janelaVideo == NULL)
		m_hr = gfxConstrutor->QueryInterface(IID_IVideoWindow, 
			(void **) &janelaVideo);

		// Verifica se houve falha
		if ( seHouverFalha("Falha: gfxConstrutor->QueryInterface()","Video::setOwner()") )
			return;	
		
		// Muda a janela de vídeo para a janela da aplicação
		m_hr = janelaVideo->put_Owner( (OAHWND) hWnd );
		// Configura janela de notificação
		mdEventos->SetNotifyWindow((OAHWND)hWnd, WM_P_GRAPHNOTIFY, 0);
		// Verifica se houve falha
		seHouverFalha("Falha: janelaVideo->put_Owner()","Video::setOwner()");		
		hJanela = hWnd;
	
		// Configura o estilo da janela de vídeo
		m_hr = janelaVideo->put_WindowStyle( WS_CHILD | WS_CLIPSIBLINGS );
		// Verifica se houve falha
		seHouverFalha("Falha: janelaVideo->put_WindowStyle()","Video::setOwner()");	

		// Configura o tamanho da janela
		// Pega o tamanho da janela
		RECT rect;
		GetClientRect(hWnd, &rect);

		// Reconfigura o tamanho da janela
		m_hr = janelaVideo->SetWindowPosition(0, 0, rect.right, rect.bottom);			
		// Verifica se houve falha
		seHouverFalha("Falha: janelaVideo->SetWindowPosition()","Video::setOwner()");		

	} // setOwner().fim
// ---]
// [---
	void play()
	{
		
		// Desconecte a janela da aplicação se for música
		if ( (janelaVideo != NULL) && (mediaModo == modo_musica) ) janelaVideo->put_Owner (NULL);

		// Reconecte com a janela da aplicação se for vídeo
		if ( (janelaVideo != NULL) && (mediaModo == modo_video) ) 
			if (hJanela != NULL) janelaVideo->put_Owner ( (OAHWND) hJanela);
		
		// Toque o arquivo de mídia
		m_hr = mdControle->Run();

		// Avisa se houve falha
		seHouverFalha("mdControle->Run()","GPMediaPlayer::play()");


	} // play().fim
// ---]

// [---
	void stop() 
	{
		// Pára de tocar o arquivo de mídia
		m_hr = mdControle->Stop();

		// Avisa se houve falha
		seHouverFalha("mdControle->Stop()","GPMediaPlayer::stop()");
	} // stop().fim
// ---]
// [---
	void pause()
	{
		// Pausa o arquivo de mídia
		m_hr = mdControle->Pause();

		// Avisa se houve falha
		seHouverFalha("mdControle->Pause()","GPMediaPlayer::pause()");		
	} // pause
// ---]
// [---
	void abortarVideo( DWORD nSleep)
	{

	  // Pára o arquivo de mídia
		m_hr = mdControle->Stop();

		// Avisa se houve falha
		seHouverFalha("mdControle->Stop()","GPMediaPlayer::abortarVideo()");	

		// Deixe por algum tempo a última imagem
		if (nSleep > 0) Sleep( nSleep);
		
		// Esconda a janela e desconecte da aplicação
		if (janelaVideo != NULL)
		{		
		janelaVideo->put_Visible (OAFALSE);
		janelaVideo->put_Owner (NULL);
		} // endif
		
	} // abortarVideo().fim
// ---]
	// [---
	bool seHouverFalha( char *aviso, char *processo)
	{
		bool status = false;

		// Verifica se houve erro
		if (FAILED(m_hr))
		{
			MessageBox (NULL, aviso, processo, MB_OK);

			status = true;
		} // endif

		return status;
	
	} // seHouverFalha().fim
// ---]
	// [---
	void limpar()
	{ 
		
		// Libera os objetos utilizados
		if ( gfxConstrutor	!= NULL ) gfxConstrutor->Release();
		if ( mdControle			!= NULL ) mdControle->Release();
		if ( janelaVideo		!= NULL ) janelaVideo->Release();
		if ( mdEventos			!= NULL ) mdEventos->Release();

		// Anula os ponteiros
		gfxConstrutor = NULL;
		mdControle		= NULL;
		janelaVideo		= NULL;
		mdEventos			= NULL;

		CoUninitialize();		

	} // limpar().fim
// ---]
}; // fim da classe
