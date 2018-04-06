// [--- $prj_Triangulo.fx - C�digo fonte do vertexshader\pixelshader#
//-----------------------------------------------------------------------------
// Projeto: prj_Triangulo - Arquivo: prj_Triangulo.fx
// Exemplo de renderiza��o de um tri�ngulo com HLSL
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