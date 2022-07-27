Texture2D		g_texture0 : register(t0);
Texture2D		g_texture1 : register(t1);
Texture2D		g_texture2 : register(t2);
Texture2D		g_texture3 : register(t3);
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
	const float2 uv = input.uv;
	float4 tex0 = g_texture0.Sample(g_sampler0, uv);
	float bright0 = dot(tex0.rgb, float3(0.2126, 0.7152, 0.0722));

	float4 tex1 = g_texture1.Sample(g_sampler0, uv);
	float4 tex2 = g_texture2.Sample(g_sampler0, uv);
	float4 tex3 = g_texture3.Sample(g_sampler0, uv);

	float4 blur = tex1 * 0.1 + tex2 * 0.3 + tex3 * 0.6;
	blur.rgb = (2 * blur.rgb + (ceil(blur.rgb * 8.0) / 8.0)) / 3.0;
	float brightB = dot(blur.rgb, float3(0.2126, 0.7152, 0.0722));

	float4 ret = tex0;
	ret.rgb = max(
		tex0.rgb,
		lerp(
			tex0.rgb,
			blur.rgb,
			1 - (1 - bright0) * (1 - brightB)
		)
	);
	return ret;
}
