// SAPI Sample 1.cpp : Defines the entry point for the console application.
//

#include <sapi.h>

ISpVoice* Voice = NULL;				// The voice interface

int main ( int NumOfArguments, char** Argument )
{
	// Initialize COM
	CoInitialize ( NULL );

	// Create the voice interface object
	CoCreateInstance ( CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void**)&Voice );

	// Speak!
	Voice -> Speak ( L"Hello World!!!", SPF_DEFAULT, NULL );

	// Shutdown the voice
	if ( Voice != NULL ) Voice -> Release (); Voice = NULL;

	// Shutdown COM
	CoUninitialize ();

	return 0;
