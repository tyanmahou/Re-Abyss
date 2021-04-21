Texture2D		g_texture0 : register(t0);
Texture2D		g_texture1 : register(t1);
SamplerState	g_sampler0 : register(s0);

cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_internal;
}

struct PSInput
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR0;
	float2 uv		: TEXCOORD0;
};

float4 PS(PSInput input) : SV_TARGET
{
	const float2 uv = input.uv;

	float4 result = g_texture0.Sample(g_sampler0, uv);
	float2 ditherUv = input.position.xy % 4;
	float dither = g_texture1.Sample(g_sampler0, ditherUv).r;
	clip(dither - result.r);
	return (result * input.color) + g_colorAdd + float4(14, 56, 72, 0) / 255.0;
}
