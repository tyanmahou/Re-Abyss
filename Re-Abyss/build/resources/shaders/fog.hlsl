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
float rand(float2 st)
{
	return frac(sin(dot(st.xy, float2(12.9898, 78.233))) * 43758.5453123);
}
float4 PS(PSInput input) : SV_TARGET
{
	float2 size;
	float  level;
	g_texture0.GetDimensions(0, size.x, size.y, level);

	float2 shiftOffs = g_z * g_z * 4 / size;
	float2 uv = input.uv;
	float2 ra = g_texture0.Sample(g_sampler0, uv + shiftOffs).ra;
	float2 ga = g_texture0.Sample(g_sampler0, uv).ga;
	float2 ba = g_texture0.Sample(g_sampler0, uv - shiftOffs).ba;
	float a = (ra.y + ga.y + ba.y) / 3;
	float4 texColor = float4(ra.x, ga.x, ba.x, a);

    float4 rawColor = (texColor * input.color) + g_colorAdd;
	
	float4 fogColor = g_fogColor -0.3 * g_z;
	float fog = exp(-g_fogFactor * (1 - (1 - g_z) * (1 - g_z)));

	float4 result = lerp(fogColor, rawColor, fog);
	result.a = rawColor.a;
	result.rgb += rand(uv) * 0.05 * g_z;
	return result;
}
