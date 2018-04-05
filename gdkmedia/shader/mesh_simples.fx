// prj_HLSL02: Renderizando mesh iluminado com hlsl
// Arquivo: mesh_simples.fx
// Produzido por www.gameprog.com.br
// [---
// Estrutura de saida do Shader, posição e cor
struct vsSaida
{
    float4 pos : POSITION;
    float4 cor : COLOR0;
};

float nMovimento;

// Direção da luz no espaço de mundo
float3 DirecaoLuz = {0.0f, 0.0f, -1.0f};

// Matriz de mundo, visualização e projeção
float4x4 Camera : WORLDVIEWPROJECTION;
// ---]
// [---
// Transforma as coordenadas em espaço de mundo
vsSaida vs_Main( float4 Pos : POSITION, float3 Normal : NORMAL )
{
    // Declaração da estrutura de retorno
    vsSaida saida = (vsSaida) 0;

    // Transforma a normal para dentro do mesmo sistema de 
	// coordenadas.
    float4 normalTransformada = mul(Normal, Camera);
    
    // Configura a cor
    saida.cor.r = nMovimento;
    saida.cor.b = 1 - nMovimento;
    saida.cor.ga = 1.0f;	
    
	// Aplica a luz na cor
	saida.cor = saida.cor * dot (normalTransformada, DirecaoLuz);

    // Transforma posição
    saida.pos = mul(Pos, Camera);

    // Retorna
    return saida;
} // vs_Main().fim
// ---]
// [---
technique MovimentoCor
{
    pass trataCilindro
    {        	
        VertexShader = compile vs_1_1 vs_Main();
        PixelShader  = NULL;
    }
}
// ---]
