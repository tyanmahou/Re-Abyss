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

float4 getOutLine(float2 uv)
{
	float4 result = g_texture0.Sample(g_sampler0, uv);
	if (result.a <= 0.0) {
		float2 offset = float2(g_outlineSize, g_outlineSize) / g_textureSize;

		if (g_texture0.Sample(g_sampler0, uv + float2(0, offset.y)).a > 0 ||
			g_texture0.Sample(g_sampler0, uv + float2(0, -offset.y)).a > 0 ||
			g_texture0.Sample(g_sampler0, uv + float2(offset.x, 0)).a > 0 ||
			g_texture0.Sample(g_sampler0, uv + float2(-offset.x, 0)).a > 0 ||
			g_texture0.Sample(g_sampler0, uv + float2(offset.x, offset.y)).a > 0 ||
			g_texture0.Sample(g_sampler0, uv + float2(offset.x, -offset.y)).a > 0 ||
			g_texture0.Sample(g_sampler0, uv + float2(-offset.x, offset.y)).a > 0 ||
			g_texture0.Sample(g_sampler0, uv + float2(-offset.x, -offset.y)).a > 0
			){
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
