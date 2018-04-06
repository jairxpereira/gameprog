// $prj_Camera.fx - C�digo fonte do vertexshader\pixelshader
// -----------------------------------------------------------------------------
// Projeto: prj_Camera - Arquivo: prj_Camera.fx
// Exemplo de uso de c�mera (directx 11)
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------

// [--- $Estrutura global do shader: cbuffer vsConstanbuffer #
// Estrutura para receber os dados advindos do constantbuffer da aplica��o
cbuffer vsConstantbuffer : register( b0 )
{

// Matrizes de configura��o da c�mera
// Matriz de mundo
matrix vsWorld; 

// Matriz de vis�o
matrix vsView; 

// Matriz de proje��o
matrix vsProject; 
}
// fim da estrutura vsConstanbuffer
// ---]

// $Estrutura global do shader: vsInput_PositionColored#
// Estrutura para receber os dados advindos da aplica��o
struct vsInput_PositionColored 
{

	// Posi��o do v�rtice
	float4 pos:POSITION;
	
	// Cor do v�rtice
	float4 color:COLOR;

};
// endstruct: vsInput_PositionColored 


// Estrutura global do shader: vsOutput_PositionColored
// --------------------------------------------------------------------------------------
// Estrutura para transmitir dados do vertexshader para o pixelshader
struct  vsOutput_PositionColored 
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
}; 
// endstruct: vsOutput_PositionColored


// -----------------------------------------------------------------------------
// [--- $A fun��o de entrada do vertexshader: gpVertexShader()#
vsOutput_PositionColored gpVertexShader( vsInput_PositionColored vs_entrada ) 
{
    // Cria��o da estrutura de sa�da
	vsOutput_PositionColored ps_saida = ( vsOutput_PositionColored ) 0;
	
    // Caminho de transforma��o dos v�rtices mundo -- vis�o -- proje��o
	ps_saida.pos = mul( vs_entrada.pos, vsWorld   );
    ps_saida.pos = mul( ps_saida.pos,   vsView    );
    ps_saida.pos = mul( ps_saida.pos,   vsProject );
	
    // Repassando cor e posi��o transformada para o pixelshader
	ps_saida.color = vs_entrada.color;
    return ps_saida;
}
// gpVertexShader().fim
// ---]


// -----------------------------------------------------------------------------
// A fun��o de entrada do pixelshader: gpPixelShader()
float4 gpPixelShader( vsOutput_PositionColored ps_entrada ) : SV_Target
{    
	return ps_entrada.color;
}
// gpPixelShader().fim
// fim do arquivo prj_Camera.fx