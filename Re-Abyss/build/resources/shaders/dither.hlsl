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
cbuffer ShaderParam : register(b1)
{
    bool g_isShape;
    int g_kind;
}
float calcDither(float2 xy)
{
    if (g_kind == 0) {
        return g_texture1.Sample(g_sampler0, xy % 2 / 8.0).r;
    } else if (g_kind == 1) {
        return g_texture1.Sample(g_sampler0, xy % 3 / 8.0).g;
    } else if (g_kind == 2) {
        return g_texture1.Sample(g_sampler0, xy % 4 / 8.0).b;
    } else {
        return g_texture1.Sample(g_sampler0, xy % 8 / 8.0).a;
    }
}
float4 PS(PSInput input) : SV_TARGET
{
    const float2 uv = input.uv;

    float dither = calcDither(input.position.xy);

    float4 texColor;
    if (g_isShape) {
        texColor = float4(1, 1, 1, 1);
    } else {
        texColor = g_texture0.Sample(g_sampler0, uv);
    }
    float4 inputColor = input.color;

    float4 result = (texColor * inputColor) + g_colorAdd;

    if (result.a - dither <= 0) {
        discard;
    }
    result.a = 1.0;
    return result;
}
