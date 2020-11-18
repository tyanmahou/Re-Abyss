// https://gist.github.com/Pctg-x8/4af54ef4c5c496b97dc1
Texture2D       g_texture0 : register(t0);
SamplerState    g_sampler0 : register(s0);

cbuffer PSConstants2D : register(b0)
{
    float4 g_colorAdd;
    float4 g_sdfParam;
    float4 g_internal;
}
cbuffer Wave : register(b1)
{
    float g_width;
    float g_height;
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

float4 qrot(float3 axis, float rad)
{
    return float4(axis.x * sin(rad / 2.0f), axis.y * sin(rad / 2.0f), axis.z * sin(rad / 2.0f), cos(rad / 2.0f));
}
float4 qmul(float4 qt, float4 qt2)
{
    float dt = dot(qt.xyz, qt2.xyz);
    float3 xs = cross(qt.xyz, qt2.xyz);
    return float4(qt.w * qt2.xyz + qt2.w * qt.xyz + xs, qt.w * qt2.w - dt);
}
float3 qtrans(float4 qt, float3 vec)
{
    float4 r = float4(-qt.x, -qt.y, -qt.z, qt.w);
    return qmul(qmul(r, float4(vec, 0.0f)), qt).xyz;
}

float4 PS(PSInput input) : SV_TARGET
{
    float2 lv = (input.uv - 0.5f) * float2(1.0f, g_height/g_width);
    float3 dirv = float3(normalize(lv), 0.0f);
    float l = length(lv) * 2.0f;
    float angle = sin(l * 8.0f * pi + g_timer) * 45.0f;
    float4 q1 = qrot(float3(0.0f, 0.0f, -1.0f), pi / 2.0f);
    float4 q2 = qrot(qtrans(q1, dirv), (angle - 90.0f) / 180.0f * pi);
    float3 nvec = qtrans(q2, dirv) * 0.5f;
    float4 result = float4(0.5f + nvec.x, 0.5f + nvec.y, 0.0f, 1.0f);

    float2 disp_texel = (result.xy * 2.0f - 1.0f) / float2(g_width, g_height) * g_multiply;
    return g_texture0.Sample(g_sampler0, input.uv + disp_texel);
}