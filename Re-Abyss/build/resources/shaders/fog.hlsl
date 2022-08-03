Texture2D		g_texture0 : register(t0);
Texture2D		g_texture1 : register(t3);
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

float pinLight(float dest, float src)
{
	return src < 0.5 ? min(dest, 2 * src) : max(dest, 2 * (src - 0.5));
}
float4 pinLight(float4 dest, float4 src)
{
	float4 color;
	color.r = pinLight(dest.r, src.r);
	color.g = pinLight(dest.g, src.g);
	color.b = pinLight(dest.b, src.b);
	color.a = src.a;
	return color;
}
float4 PS(PSInput input) : SV_TARGET
{
	float2 uv = input.uv;
	float4 texColor = g_texture0.Sample(g_sampler0, uv);

    float4 rawColor = (texColor * input.color) + g_colorAdd;

	float4 result = rawColor;
	{
		float4 fogColor = g_fogColor;
		float fog = exp(-g_fogFactor * (1 - (1 - g_z) * (1 - g_z)));

		result = lerp(fogColor, result, fog);
	}
	{
		float height = (-40 + (640 - input.position.y)) * lerp(0, 4.2, g_z * sqrt(g_z));
		float dist = 10 + g_z * g_z * 1120;
		float k = height / dist;
		float a0 = 0.3;
		float b = 0.9;
		float4 fogColor = g_fogColor - g_z * 0.05;
		float fog = 2 * exp(a0 * 1 * (exp(-b * height) - 1) / (b * k));

		float2 ditherUv = input.position.xy % 8 / 8.0;
		float dither = g_texture1.Sample(g_sampler0, ditherUv).a;
		if (fog - dither <= 0) {
			result = fogColor;
		}
	}
	{
		result.a = rawColor.a;
	}
	return lerp(result, pinLight(rawColor, result), 0.4);
}
