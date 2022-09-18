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
    float4 g_color;
}

float3 rgb2hsl(in float3 rgb)
{
    float r = rgb.r;
    float g = rgb.g;
    float b = rgb.b;

    float maxv = max(r, max(g, b));
    float minv = min(r, min(g, b));
    float h = -1;
    if (minv == maxv) {
        h = -1;
    } else if (minv == b) {
        h = ((g - r) / (maxv - minv) + 1.0) / 6.0;
    } else if (minv == r) {
        h = ((b - g) / (maxv - minv) + 3.0) / 6.0;
    } else if (minv == g) {
        h = ((r - b) / (maxv - minv) + 5.0) / 6.0;
    }
    float l = (maxv + minv) / 2.0;
    float s = (maxv - minv) / (1 - abs(maxv + minv - 1));
    return float3(h, s, l);
}

float3 hsl2rgb(in float3 hsl)
{
    float h = hsl.r;
    float s = hsl.g;
    float l = hsl.b;

    float maxv = l + (s * (1 - abs(2 * l - 1))) / 2;
    float minv = l - (s * (1 - abs(2 * l - 1))) / 2;

    float r, g, b;
    float h6 = h * 6;
    if (h < 0) {
        r = maxv;
        g = maxv;
        b = maxv;
    } else if (h6 <= 1) {
        r = maxv;
        g = minv + (maxv - minv) * h6;
        b = minv;
    } else if (h6 <= 2) {
        r = minv + (maxv - minv) * (2 - h6);
        g = maxv;
        b = minv;
    } else if (h6 <= 3) {
        r = minv;
        g = maxv;
        b = minv + (maxv - minv) * (h6 - 2);
    } else if (h6 <= 4) {
        r = minv;
        g = minv + (maxv - minv) * (4 - h6);
        b = maxv;
    } else if (h6 <= 5) {
        r = minv + (maxv - minv) * (h6 - 4);
        g = minv;
        b = maxv;
    } else {
        r = maxv;
        g = minv;
        b = minv + (maxv - minv) * (6 - h6);
    }
    return float3(r, g, b);
}

// カラー合成
// LCH空間のほうがそれっぽいが、コスト安なのでHSL空間でやる
float4 color(in float4 dest, in float4 src)
{
    float3 hslDest = rgb2hsl(dest.rgb);
    float3 hslSrc = rgb2hsl(src.rgb);

    // 色相、彩度を上書き
    float3 hslRet = hslDest;
    hslRet.r = hslSrc.r;
    hslRet.g = hslSrc.g;

    float4 ret;
    ret.rgb = hsl2rgb(hslRet);
    ret.a = dest.a * src.a;
    return ret;
}
float4 PS(PSInput input) : SV_TARGET
{
    const float2 uv = input.uv;
    float4 src = g_color;
    float4 dest = g_texture0.Sample(g_sampler0, uv);
    return color(dest, src);
}
