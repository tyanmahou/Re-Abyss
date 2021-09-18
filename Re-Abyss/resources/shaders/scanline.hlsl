Texture2D		g_texture0 : register(t0);
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
	float g_timer;
}

float rand(float2 st)
{
	return frac(sin(dot(st.xy, float2(12.9898, 78.233))) * 43758.5453123);
}

float4 PS(PSInput input) : SV_TARGET
{
	float2 uv = input.uv;
	float4 outColor = g_texture0.Sample(g_sampler0, uv);

	// scan line
	float scanline = floor(input.position.y) % 2.0 / 2.0;
	outColor.rgb -= lerp(0, 0.05, scanline);

	// noise
	outColor.rgb -= rand(uv * g_timer) * 0.08;
    return outColor;
}
