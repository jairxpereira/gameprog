// [--- $Especificação da classe Tools: Tools.h#
// -----------------------------------------------------------------------------
// Projeto: prj_HierarquiaAnimada - Arquivo: Tools.h
// Esta aplicação mostra como renderizar uma hierarquia animada
// By Keith Ditchburn - Adaptação www.gameprog.com.br
// -----------------------------------------------------------------------------

#pragma once
#include <string>
#include <sstream>
#include <d3d9.h>
#include <assert.h>

// Template para converter tipos padrões em strings
template <class T>
std::string ToString(const T & t)
{
	std::ostringstream oss;
	oss.clear();
	oss << t;
	return oss.str();
}

// A classe Tools possui um conjunto de funções úteis
// que podem ser usadas sem o instanciamento da classe
class Tools
{
private:
	~Tools(void){};
public:
	Tools(void){};
	
	// Verificação de falha nas operações do directx
	static bool FailedHr(HRESULT hr);

	// Emite uma mensagem no painel de saída do Visual Studio
	static void DebugString(const std::string &str);
	
	// Duplica uma string
	static char* DuplicateCharString(const char* c_str);
	
	// Localização de arquivo
	static bool FindFile(std::string *filename);
	
	// Verificação da existência de um arquivo
	static bool DoesFileExist(const std::string &filename);
	
	// Separação dos elementos de um caminho
	static void SplitPath(const std::string& inputPath, 
		std::string* pathOnly, std::string* filenameOnly);
	
	// Verificação do diretório corrente
	static std::string GetTheCurrentDirectory();
};
// fim da classe Tools
// fim do arquivo Tools.h
// ---]
