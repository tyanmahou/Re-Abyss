Texture2D		g_texture0 : register(t0);
Texture2D		g_texture1 : register(t1);
Texture2D		g_texture2 : register(t2);
SamplerState	g_sampler0 : register(s0);

cbuffer PSConstants2D : register(b0)
{
    float4 g_colorAdd;
    float4 g_sdfParam;
    float4 g_internal;
}

cbuffer ShaderParam : register(b1)
{
    float4 g_bgColor;
}
struct PSInput
{
    float4 position	: SV_POSITION;
    float4 color	: COLOR0;
    float2 uv		: TEXCOORD0;
};

float hardLight(float dest, float src)
{
    return src < 0.5 ? dest * src * 2.0: 1 - 2 * (1 - dest) * (1 - src);
}
float4 hardLight(float4 dest, float4 src)
{
    float4 color;
    color.r = hardLight(dest.r, src.r);
    color.g = hardLight(dest.g, src.g);
    color.b = hardLight(dest.b, src.b);
    color.a = 1.0;
    return color;
}

float screen(float dest, float src)
{
    return 1 - (1 - dest) * (1 - src);
}
float4 screen(float4 dest, float4 src)
{
    float4 color;
    color.r = screen(dest.r, src.r);
    color.g = screen(dest.g, src.g);
    color.b = screen(dest.b, src.b);
    color.a = 1.0;
    return color;
}
float squareInv(float src)
{
    return sqrt(src);
}
float4 squareInv(float4 src)
{
    float4 color;
    color.r = squareInv(src.r);
    color.g = squareInv(src.g);
    color.b = squareInv(src.b);
    color.a = src.a;
    return color;
}
float4 PS(PSInput input) : SV_TARGET
{
    const float2 uv = input.uv;
    float4 dest = g_texture0.Sample(g_sampler0, uv);
    float4 light = g_texture2.Sample(g_sampler0, uv);

    float2 ditherUv = input.position.xy % 4;
    float dither = g_texture1.Sample(g_sampler0, ditherUv).r;
    if (dither - light.r <= 0) {
        return dest;
    }

    float4 src = screen(light * input.color + g_colorAdd, g_bgColor);
    float4 outColor = hardLight(dest, src);
    return squareInv(outColor) * dest;
}
