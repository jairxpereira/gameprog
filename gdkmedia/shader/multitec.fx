//
// Intro to HLSL
//

// The world view and projection matrices
float4x4 Camera : WORLDVIEWPROJECTION;
sampler TextureSampler;
float4 cor : COLOR0;

// Transform our coordinates into world space
void Transform( in float4 inputPosition : POSITION,  in float2 inputTexCoord : TEXCOORD0,
    out float4 outputPosition : POSITION, out float2 outputTexCoord : TEXCOORD0 )
{
    // Transform our position
    outputPosition = mul(inputPosition, Camera);
	
    // Set our texture coordinates
    outputTexCoord = inputTexCoord;
}

void TextureColor( in float2 textureCoords : TEXCOORD0,  out float4 diffuseColor : COLOR0)
{
    // Get the texture color
    diffuseColor = tex2D(TextureSampler, textureCoords);
};

technique TransformTexture
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 Transform();
        PixelShader  = compile ps_1_1 TextureColor();
    }
}

void InverseTextureColor( in float2 textureCoords : TEXCOORD0, out float4 diffuseColor : COLOR0)
{
    // Get the inverse texture color
    diffuseColor = 1.0f - tex2D(TextureSampler, textureCoords);
};

technique TransformInverseTexture
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 Transform();
        PixelShader  = compile ps_1_1 InverseTextureColor();
    }
}

void TextureColorNoBlue( in float2 textureCoords : TEXCOORD0, out float4 diffuseColor : COLOR0)
{
    // Get the texture color
    diffuseColor = tex2D(TextureSampler, textureCoords);
    // Mask out the blue
    diffuseColor.b = 0.0f;
};
 
technique TransformTextureNoBlue
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 Transform();
        PixelShader  = compile ps_1_1 TextureColorNoBlue();
    }
}

void TextureColorOnlyBlue( in float2 textureCoords : TEXCOORD0, out float4 diffuseColor : COLOR0)
{
    // Get the texture color
    diffuseColor = tex2D(TextureSampler, textureCoords);
    // Mask out everything but blue
    diffuseColor.rga = 0.0f;
};



technique TransformTextureOnlyBlue
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 Transform();
        PixelShader  = compile ps_1_1 TextureColorOnlyBlue();
    }
}


void fnSwapTexture( in float2 textureCoords : TEXCOORD0, out float4 diffuseColor : COLOR0)
{
    // Get the texture color
	
	cor.rgba = 0.0f;	
	
    diffuseColor = tex2D(TextureSampler, textureCoords);
	
	cor.r = diffuseColor.r;
	cor.b = diffuseColor.b;
	cor.a = cor.r;
	cor.r = cor.b;
	cor.b = cor.a;
	
    // Mask out everything but blue
    diffuseColor.r = cor.r;
	diffuseColor.b = cor.b;
	diffuseColor.g = 0.0f;
	diffuseColor.a = 1.0f;
};

technique SwapTexture
{
    pass P0
    {
        // shaders
        VertexShader = compile vs_1_1 Transform();
        PixelShader  = compile ps_1_1 fnSwapTexture();
    }
}


