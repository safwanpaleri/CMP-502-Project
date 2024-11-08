// Colour pixel/fragment shader
// Basic fragment shader outputting a colour

Texture2D texture0 : register(t0);
SamplerState Sampler0 : register(s0);

struct InputType
{
	float4 position : SV_POSITION;
    //float4 colour : COLOR;
	float2 tex : TEXCOORD0;
};


float4 main(InputType input) : SV_TARGET
{
    float4 textureColor0;
    textureColor0 = texture0.Sample(Sampler0, input.tex);
    return textureColor0;

}