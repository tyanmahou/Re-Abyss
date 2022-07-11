Texture2D		g_texture0 : register(t0);
SamplerState	g_sampler0 : register(s0);

cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_sdfOutlineColor;
	float4 g_sdfShadowColor;
	float4 g_internal;
}

struct PSInput
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR0;
	float2 uv		: TEXCOORD0;
};

cbuffer FogParam : register(b1)
{
	float4 g_fogColor;
	float g_fogFactor;
	float g_z;
}

float4 PS(PSInput input) : SV_TARGET
{
	float2 uv = input.uv;
	float4 outColor = g_texture0.Sample(g_sampler0, uv);
    float4 rawColor = (outColor * input.color) + g_colorAdd;

	float fog = exp(-g_fogFactor * 6.0 * g_z);

	float4 result = lerp(g_fogColor, rawColor, fog);
	result.a = rawColor.a;
	return result;
}
