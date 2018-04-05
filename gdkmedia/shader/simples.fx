// Introdução a programação em HLSL
// Arquivo: simples.fx - prj_HLSL01
// [---
// Matriz de projeção e visualização
float4x4 Camera : WORLDVIEWPROJECTION;
float nMovimento;
// ---]
// [---
// Transforma coordenadas em espaço de mundo
float4 vs_Main( float4 Pos  : POSITION) : POSITION
{
    // Declara variável de saída    
	float4 saida_pos;	
	
    // Transforma posição
	Pos.z += nMovimento * 2;
    saida_pos = mul(Pos, Camera);	    
	
    // Retorna posição transformada
    return saida_pos;
} // vs_Main().fim
// ---]
// [---
float4 ps_Main (  ) : COLOR0
{    
	// Declara uma variável para cor no padrão RGBA
	float4 cor = float4 (0.0f, 0.0f, 0.0f, 0.0f);
	
	// Configura individualmente os canais de cor
	cor.r = nMovimento;
    cor.b = 1 - nMovimento;
    cor.ga = 1.0f;	

return cor;
} // ps_Main().fim
// ---]

// [---
technique MovimentoCor
{
    pass P0
    {
        // Configura alguns estados do dispositivo
		CullMode = None;
		FillMode = Solid;
        
        // Compila o VertexShader e o PixelShader
		VertexShader = compile vs_1_1 vs_Main();
        PixelShader  = compile ps_2_0 ps_Main();
		
    } // fim do passo P0
} // fim da técnica
// ---]

