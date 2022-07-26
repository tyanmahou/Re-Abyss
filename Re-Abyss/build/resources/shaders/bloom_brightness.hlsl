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
	float4 g_lightColor;
}
static float g_threshold = 0.7;
static float g_power = 0.45;

float4 PS(PSInput input) : SV_TARGET
{
	float2 uv = input.uv;
	float4 texColor = g_texture0.Sample(g_sampler0, uv);
	float bright = dot(texColor.rgb, float3(0.2126, 0.7152, 0.0722));

	float tmp = bright / g_threshold;
	float factor = bright > g_threshold ? 1.0 : pow(tmp, 6.0);
	float4 result = texColor * factor;

	// 全体の明るさとの比較でパワーを変える
	// 暗いときのほうが光が目立つ
	float lightBright = dot(g_lightColor.rgb, float3(0.2126, 0.7152, 0.0722));
	result.a = lerp(0, g_power, 1 - lightBright);
	return result;
}
