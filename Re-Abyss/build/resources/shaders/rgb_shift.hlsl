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

float4 rgbShift(float2 uv)
{
    float2 size;
    float  level;
    g_texture0.GetDimensions(0, size.x, size.y, level);

    float2 shiftOffs = float2(2, -1) / size;
    float2 ra = g_texture0.Sample(g_sampler0, uv + shiftOffs).ra;
    float2 ga = g_texture0.Sample(g_sampler0, uv).ga;
    float2 ba = g_texture0.Sample(g_sampler0, uv - shiftOffs).ba;
    float a = (ra.y + ga.y + ba.y) / 3;
    return float4(ra.x, ga.x, ba.x, a);
}

float4 PS(PSInput input) : SV_TARGET
{
    const float2 uv = input.uv;
    float4 baseColor = rgbShift(uv);
    return (baseColor * input.color) + g_colorAdd;
}
