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

cbuffer ShaderParam : register(b1)
{
	float g_timer;
}
float4 PS(PSInput input) : SV_TARGET
{
	float2 size;
	float  level;
	g_texture0.GetDimensions(0, size.x, size.y, level);

	float2 uv = input.uv;
	float2 offs = float2(0, 0);
	offs.x = sin(uv.y * 50 + g_timer * 2) * (2 / size.x);
	float4 outColor = g_texture0.Sample(g_sampler0, uv + offs);
    return outColor;
}
