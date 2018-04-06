// $prj_Camera.fx - Código fonte do vertexshader\pixelshader
// -----------------------------------------------------------------------------
// Projeto: prj_Camera - Arquivo: prj_Camera.fx
// Exemplo de uso de câmera (directx 11)
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------

// [--- $Estrutura global do shader: cbuffer vsConstanbuffer #
// Estrutura para receber os dados advindos do constantbuffer da aplicação
cbuffer vsConstantbuffer : register( b0 )
{

// Matrizes de configuração da câmera
// Matriz de mundo
matrix vsWorld; 

// Matriz de visão
matrix vsView; 

// Matriz de projeção
matrix vsProject; 
}
// fim da estrutura vsConstanbuffer
// ---]

// $Estrutura global do shader: vsInput_PositionColored#
// Estrutura para receber os dados advindos da aplicação
struct vsInput_PositionColored 
{

	// Posição do vértice
	float4 pos:POSITION;
	
	// Cor do vértice
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
// [--- $A função de entrada do vertexshader: gpVertexShader()#
vsOutput_PositionColored gpVertexShader( vsInput_PositionColored vs_entrada ) 
{
    // Criação da estrutura de saída
	vsOutput_PositionColored ps_saida = ( vsOutput_PositionColored ) 0;
	
    // Caminho de transformação dos vértices mundo -- visão -- projeção
	ps_saida.pos = mul( vs_entrada.pos, vsWorld   );
    ps_saida.pos = mul( ps_saida.pos,   vsView    );
    ps_saida.pos = mul( ps_saida.pos,   vsProject );
	
    // Repassando cor e posição transformada para o pixelshader
	ps_saida.color = vs_entrada.color;
    return ps_saida;
}
// gpVertexShader().fim
// ---]


// -----------------------------------------------------------------------------
// A função de entrada do pixelshader: gpPixelShader()
float4 gpPixelShader( vsOutput_PositionColored ps_entrada ) : SV_Target
{    
	return ps_entrada.color;
}
// gpPixelShader().fim
// fim do arquivo prj_Camera.fx