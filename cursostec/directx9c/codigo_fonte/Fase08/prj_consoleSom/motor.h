// [---
//*******************************************************************
// Projeto: prj_consoleSom - Arquivo: motor.h
// Esta aplicação exemplifica como tocar um efeito sonoro
// contido em um arquivo do formato wav
// By www.toymaker.info \\ www.gameprog.com.br
//******************************************************************* 

#ifndef motor_h
 #define motor_h

// Exclui conteúdo raramente usado para agilizar compilação
#define WIN32_LEAN_AND_MEAN		

// Funcionalidades do Windows
#include <windows.h>

// Funcionalidades da linguagem C
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

// Acesso multimídia
#include <mmsystem.h>
#include <dxerr9.h>
#include <dsound.h>

//-----------------------------------------------------------------------------
// Macros de utilidades
//-----------------------------------------------------------------------------
// Deleta memória alocada com new
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p) = NULL; } }

// Deleta memória alocada com new em arrays
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p) = NULL; } }

// Libera interfaces do directx
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p) = NULL; } }
 
#endif
// ---]
