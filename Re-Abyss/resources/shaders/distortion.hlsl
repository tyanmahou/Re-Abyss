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

cbuffer ShaderParam : register(b1)
{
	float2 g_textureSize;
}

float4 PS(PSInput input) : SV_TARGET
{
    // 歪みマップ
    float4 dist = g_texture1.Sample(g_sampler0, input.uv);
    float2 dir = dist.xy * 2.0f - 1.0f;
    dir = (dir.x == 0.0f && dir.y == 0.0f) ? float2(0, 0) : normalize(dir);
    // 歪み
    float2 distTex = (dist.xy * 2.0f - 1.0f) * dist.z * 255.0f / g_textureSize;
    return g_texture0.Sample(g_sampler0, input.uv + distTex);
}
