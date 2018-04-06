// -----------------------------------------------------------------------------
// Projeto: prj_Estados - Arquivo: prj_Estados.fx
// Exemplo de renderização de um triângulo com HLSL
// Produzido por www.gameprog.com.br
// -----------------------------------------------------------------------------

// [--- $Estrutura global do shader: vsCustomVertex_PositionColored ( VS_INPUT )#
// Estrutura para receber os dados advindos da aplicação
struct vsInput_PositionColored 
{

	// Posição do vértice
	float4 pos:POSITION;
	
	// Cor do vértice
	float4 color:COLOR;

};
// endstruct: vsInput_PositionColored 
// ---]

// [--- $Estrutura global do shader: vsOutput_PositionColored (VS_OUTPUT ) #
// --------------------------------------------------------------------------------------


// Estrutura para transmitir dados do vertexshader para o pixelshader
struct  vsOutput_PositionColored 
{
    float4 pos : SV_POSITION;
    float4 color : COLOR0;
}; 
// endstruct: vsOutput_PositionColored

// ---]

// -----------------------------------------------------------------------------
// Vertexshader
// -----------------------------------------------------------------------------
// [--- $A função de entrada do vertexshader: gpVertexShader()#
vsOutput_PositionColored gpVertexShader( vsInput_PositionColored vs_entrada ) 
{
    vsOutput_PositionColored ps_saida = (vsOutput_PositionColored) 0;
	ps_saida.pos   = vs_entrada.pos;
	ps_saida.color = vs_entrada.color;
	return ps_saida;
}
// ---]

// -----------------------------------------------------------------------------
// Pixelshader
// -----------------------------------------------------------------------------
// [--- $A função de entrada do pixelshader: gpPixelShader()#
float4 gpPixelShader( vsOutput_PositionColored ps_entrada ) : SV_Target
{    
	return ps_entrada.color;
}
// ---]