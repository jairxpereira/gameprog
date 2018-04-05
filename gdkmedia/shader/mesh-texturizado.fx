// prj_HLSL03: Renderizando mesh texturizado com hlsl
// Arquivo: mesh_texturizado.fx
// Produzido por www.gameprog.com.br
// [---
// Variágeis globais de camera e textura
// As estruturas também são globais
float4x4 Camera : WORLDVIEWPROJECTION;
sampler textura;

// Dados de saída: posição e coordenada de textura
struct vsSaida
{
float4 pos      : POSITION;
float2 texCoord : TEXCOORD0;
};

// Dados de entrada: posição e coordenada de textura
struct vsEntrada
{
float4 pos      : POSITION;
float2 texCoord : TEXCOORD0;
};
// ---]
// [---
// Retorna posição e coordenadas de textura
vsSaida vs_Main ( vsEntrada entrada )
{    
	// Declara estrutura de saída
	vsSaida saida = (vsSaida) 0;	
	
	// Transforma posição para espaço de mundo
    saida.pos = mul(entrada.pos, Camera);
    
    // Repassa para a saida as coordenadas de textura
	saida.texCoord = entrada.texCoord;	
	
	// Retorna posição transformada e coordenadas originais
	// de textura
	return saida;
}
// ---]
// [---
 float4 ps_TexturaOriginal( float2 texCoord   : TEXCOORD0, 
                            float4 cor_difusa :  COLOR0 ) : COLOR0
{
    // Pega a cor do pixel da textura
	cor_difusa = tex2D(textura, texCoord);	
	
	// Retorna sem modificações
	return cor_difusa;
};
// ---]
// [---
technique texturaOriginal
{
    pass P0
    {
        // Aplicando textura original
        VertexShader = compile vs_1_1 vs_Main();
        PixelShader  = compile ps_2_0 ps_TexturaOriginal();
    }
}
// ---]
// [---
// --------------------- Estrutura da segunda técnica -------------------------
// Testando instruções in e out
void ps_TexturaNegativa( in  float2 texCoord   : TEXCOORD0, 
                         out float4 cor_difusa : COLOR0     )
{
    // Pega a cor do pixel da textura
	cor_difusa = tex2D(textura, texCoord);	
	
	// Modifica a cor original
	cor_difusa.r = 1.0f - cor_difusa.r;
	cor_difusa.g = 1.0f - cor_difusa.g;
	cor_difusa.b = 1.0f - cor_difusa.b;	
	
} 
// ---]
// [---                             
technique texturaNegativa
{
    pass P0
    {
        // Aplicando textura negativa
        VertexShader = compile vs_1_1 vs_Main();
        PixelShader  = compile ps_2_0 ps_TexturaNegativa();
    }
}
// ---]
