// [--- $Aspectos globais: arquivo Tools.cpp#
// -----------------------------------------------------------------------------
// Projeto: prj_HierarquiaAnimada - Arquivo: Tools.cpp
// Esta aplicação mostra como renderizar uma hierarquia animada
// By Keith Ditchburn - Adaptação www.gameprog.com.br
// -----------------------------------------------------------------------------

#include "Tools.h"
#include "Dxerr.h"
#include <io.h>
#include <algorithm>
// ---]

// [--- $DebugString() - Mensagem no painel de saída do Visual Studio#
// Emite uma string no painel de saída do Visual Studio
void Tools::DebugString( const std::string &str )
{
	OutputDebugString( str.c_str() );
} // DebugString().fim
// ---]

// [--- $FailedHr() - Verificação de falha do directx#
// Emite uma string de erro em caso de falha nas operações do directx
bool Tools::FailedHr(HRESULT hr)
{
	if (FAILED(hr))
	{
		DebugString("DirectX Reported Error: " + 
			ToString( DXGetErrorString(hr) ) + " - " + 
			ToString( DXGetErrorDescription(hr) ) + "\n" );

		return true;
	}

	return false;
} // FailedHr().fim
// ---]

 
// [--- $DuplicateCharString() - Duplicação de string#
// Duplica e retorna a string passada ( charString )
// A função caller é responsável por liberar a memória
char* Tools::DuplicateCharString(const char* charString)
{
    if (!charString)
		return 0;

	size_t len = strlen(charString) + 1;
	char *newString = new char[len];
	memcpy( newString, charString, len*sizeof(char) );

	return newString;
} // DuplicateCharString().fim
// ---]

// [--- $FindFile() - Localização de arquivo#
// Tools::FindFile() Esta função tenta localizar o arquivo passado
// Pode ser  sofrido  localizar  um  arquivo  de  textura  pois  o
// caminho do arquivo pode estar ou não  com  o  nome  da  textura
// Para descobrir a configuração do nome da textura salve o modelo
// 3d(.x) em forma de texto e verifique diretamente o  arquivo  em
// um editor de texto
bool Tools::FindFile(std::string *filename)
{
	if (!filename)
		return false;
	
	// Procure primeiro utilizando o nome original do arquivo que
	// presume-se aqui estar com o caminho atrelado
	if (DoesFileExist(*filename))
		return true;
	
	// Agora vamos tirar o caminho e testar apenas com o nome do 
	// arquivo
	std::string pathOnly;
	std::string filenameOnly;
	SplitPath(*filename, &pathOnly, &filenameOnly);

	if ( DoesFileExist(filenameOnly) )
	{
		*filename = filenameOnly;
		return true;
	}
	
	// Poderia-se tentar agora olhar numa pasta específica...
	return false;
} // FindFile().fim
// ---]


// [--- $DoesFileExist() - Verificação de existência de arquivo#
// Aqui vamos verificar se o arquivo existe utilizando 
// uma função padrão da linguagem C
bool Tools::DoesFileExist(const std::string &filename)
{
	return ( _access( filename.c_str(), 0 ) != -1 );
} // DoesFileExist().fim
// ---]

// [--- $SplitPath()- Separação dos elementos de um caminho#
// Tools::SplitPath() - Esta função divide  uma  string  produzindo
// uma string em separado para o nome do arquivo e  o  seu  caminho
// pathOnly ou filenameOnly podem ser null se não forem necessários
void Tools::SplitPath(const std::string& inputPath, 
					  std::string* pathOnly, 
					  std::string* filenameOnly)
{
	std::string fullPath( inputPath );
	std::replace( fullPath.begin(), fullPath.end(), '\\', '/' );

	std::string::size_type lastSlashPos=fullPath.find_last_of('/');

	
	// Verificar a inexistência de um caminho na string de entrada
	if (lastSlashPos == std::string::npos)
	{
		*pathOnly = "";
		*filenameOnly = fullPath;
	} // endif
	else 
	// Realiza a separação das substrings
	{
		if (pathOnly)
			*pathOnly = fullPath.substr(0, lastSlashPos);

		if (filenameOnly)
			*filenameOnly = fullPath.substr( lastSlashPos + 1,
			fullPath.size() - lastSlashPos-1 );
	} // end else
} // Tools::SplitPath().fim
// ---]


// [--- $GetTheCurrentDirectory() - Obtendo o diretório corrente#
// Obtém o nome do diretório corrente
std::string Tools::GetTheCurrentDirectory()
{
	int bufferSize = GetCurrentDirectory(0,NULL);
	char *buffer = new char[bufferSize];

	GetCurrentDirectory( bufferSize, buffer);
	std::string directory( buffer );
	delete []buffer;

	return directory;
} // Tools::GetTheCurrentDirectory().fim
// fim do arquivo Tools.cpp
// ---]

