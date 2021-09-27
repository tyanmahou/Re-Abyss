//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

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

cbuffer ShaderParam : register(b1)
{
	float4 g_outlineColor;
	float2 g_textureSize;
	float g_outlineSize;
}

struct PSInput
{
	float4 position	: SV_POSITION;
	float4 color	: COLOR0;
	float2 uv		: TEXCOORD0;
};

bool checkOutLine(float2 uv)
{
	bool ret = false;
	// どうせサイズ変えないと思うから定数化してる
	float outlineSize = 1;// g_outlineSize;
	float rangeSq = outlineSize * outlineSize;
	int thick = outlineSize;
	int count = thick + 1;
	int countSq = count * count;

	// (size + 1)^2 の値をいれる
	[unroll(4)] for (int i = 0; i < countSq; ++i) {
		int x = (int)(i / (float)count) - thick;
		int y = (int)(i % (float)count) - thick;
		float a = g_texture0.Sample(g_sampler0, uv + float2(x, y) / g_textureSize).a +
			g_texture0.Sample(g_sampler0, uv + float2(x, -y) / g_textureSize).a +
			g_texture0.Sample(g_sampler0, uv + float2(-x, y) / g_textureSize).a +
			g_texture0.Sample(g_sampler0, uv + float2(-x, -y) / g_textureSize).a;
		if (a > 0.0 && x * x + y * y <= rangeSq) {
			ret = true;
			break;
		}
	}
	return ret;
}
float4 getOutLine(float2 uv)
{
	float4 result = g_texture0.Sample(g_sampler0, uv);
	if (result.a <= 0.0) {
		if (checkOutLine(uv)) {
			result = g_outlineColor;
		}
	}
	return result;
}
float4 PS(PSInput input) : SV_TARGET
{
	float4 result = getOutLine(input.uv);
	return (result * input.color) + g_colorAdd;
}
