Texture2D		g_texture0 : register(t0);
Texture2D		g_texture1 : register(t1);
SamplerState	g_sampler0 : register(s0);
SamplerState	g_sampler1 : register(s1);

cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_internal;
}

cbuffer ShaderParam : register(b1)
{
	int g_isEqual;
}

struct PSInput
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR0;
	float2 uv		: TEXCOORD0;
};

float4 PS(PSInput input) : SV_TARGET
{
	float4 texColor = g_texture0.Sample(g_sampler0, input.uv);
	
	float mask = g_texture1.Sample(g_sampler1, input.uv).a;
	if (!g_isEqual) {
		mask = 1 - mask;
	}
	texColor.r *= mask;
	texColor.g *= mask;
	texColor.b *= mask;

	float invA = 1 - texColor.a;
	texColor.a = 1 - invA * mask;

	return (texColor * input.color) + g_colorAdd;
}
