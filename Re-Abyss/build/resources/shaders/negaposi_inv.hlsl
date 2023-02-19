Texture2D		g_texture0 : register(t0);
Texture2D		g_texture1 : register(t1);
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

float4 PS(PSInput input) : SV_TARGET
{
    float4 baseColor = g_texture0.Sample(g_sampler0, input.uv);
	float3 rgb = baseColor.rgb;
	float3 rgbInv = float3(1, 1, 1) - rgb;

	float mask = g_texture1.Sample(g_sampler0, input.uv).a;
	return float4(lerp(rgbInv, rgb, mask), baseColor.a);
}
