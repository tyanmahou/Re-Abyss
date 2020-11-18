Texture2D       g_texture0 : register(t0);
SamplerState    g_sampler0 : register(s0);

cbuffer PSConstants2D : register(b0)
{
    float4 g_colorAdd;
    float4 g_sdfParam;
    float4 g_internal;
}
cbuffer ShaderParam : register(b1)
{
    float g_timer;
    float g_multiply;
}
struct PSInput
{
    float4 position : SV_POSITION;
    float4 color    : COLOR0;
    float2 uv       : TEXCOORD0;
};

static const float pi = 4.0f * atan(1.0f);
static const int count = 3;
float4 PS(PSInput input) : SV_TARGET
{
    float4 texColor = float4(0,0,0,1);
    for (int i = 1; i <= count; ++i) {
        float2 uv = input.uv;
        uv.x += (1 - uv.y) / 6 * i;
        uv.x += g_timer / 50 * g_multiply * (count + 1- i);
        float alpha = 1.0 / (float)count + 0.2;
        texColor = texColor + g_texture0.Sample(g_sampler0, uv) * alpha;
    }

    return (texColor * input.color) + g_colorAdd;
}