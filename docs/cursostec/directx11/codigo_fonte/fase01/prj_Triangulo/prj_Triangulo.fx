// [--- $prj_Triangulo.fx - Código fonte do vertexshader\pixelshader#
//-----------------------------------------------------------------------------
// Projeto: prj_Triangulo - Arquivo: prj_Triangulo.fx
// Exemplo de renderização de um triângulo com HLSL
// Produzido por www.gameprog.com.br
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Vertexshader
//-----------------------------------------------------------------------------
float4 gpVertexShader( float4 Pos : POSITION ) : SV_POSITION
{
    return Pos;
}

//-----------------------------------------------------------------------------
// Pixelshader
//-----------------------------------------------------------------------------
float4 gpPixelShader( float4 Pos : SV_POSITION ) : SV_Target
{
    float4 azul = float4( 0.0f, 0.0f, 1.0f, 1.0f );
	return azul;
}
// ---]