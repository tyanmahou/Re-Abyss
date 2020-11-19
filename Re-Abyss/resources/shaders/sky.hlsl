Texture2D       g_texture0 : register(t0);
SamplerState    g_sampler0 : register(s0);
Texture2D       g_texture1 : register(t1);

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
static const int count = 2;
static const int g_radius = 10;
static const float2 g_size = float2(960, 120);

// 平均色と分散値を計算
// float4 rgb = 平均rgb, a に各色の分散の合計値
float4 calcAveAndV(float2 uv, int xBegin, int xEnd, int yBegin, int yEnd)
{
    float3 sum;       // 合計
    float3 sumSquare; // 2乗合計

    int width = (xEnd - xBegin + 1);
    int height = (yEnd - yBegin + 1);
    int num = width * height;
    for (int pixel = 0; pixel < num; ++pixel) {
        int x = pixel % (float)width + xBegin;
        int y = pixel / (float)width + yBegin;
        float3 texColor = float3(0, 0, 0);
        float alpha = 1.0 / (float)count + 0.3;
        for (int i = 1; i <= count; ++i) {
            float2 tmpUv = uv;
            int sign = (int)(i % 2.0) * -1;
            float2 offs = float2(i / (float)count, 0);
            tmpUv += offs;
            tmpUv.x += sin(g_timer / 50 * g_multiply * (count + 1 - i) * sign) * 0.4;
            texColor = texColor + g_texture0.Sample(g_sampler0, tmpUv + float2(x, y) / g_size).rgb * alpha;
        }
        sum += texColor;
        sumSquare += texColor * texColor;

    }

    float3 ave = sum / num;  // 平均
    float3 squ = sumSquare - sum * sum / num; // 平方和
    float3 v = squ / (num - 1); // 分散
    return float4(ave, v.r + v.g + v.b);
}

float4 PS(PSInput input) : SV_TARGET
{
    float2 uv = input.uv;
    uv.x -= 0.5;
    uv.y *= 1.2f; // ちょっとつぶす
    uv.x /= lerp(2, 0.2, uv.y);
    uv.x += g_timer / 100 * g_multiply;

    if (uv.y > 1 || uv.y < 0) {
        discard;
    }
    float4 result;
    float4 aveAndV;
    // 左上
    aveAndV = calcAveAndV(uv, -g_radius, 0, -g_radius, 0);
    result = aveAndV;
    // 右上
    aveAndV = calcAveAndV(uv, 0, g_radius, -g_radius, 0);
    if (result.a > aveAndV.a) {
        result = aveAndV;
    }
    // 左下
    aveAndV = calcAveAndV(uv, -g_radius, 0, 0, g_radius);
    if (result.a > aveAndV.a) {
        result = aveAndV;
    }
    // 右下
    aveAndV = calcAveAndV(uv, 0, g_radius, 0, g_radius);
    if (result.a > aveAndV.a) {
        result = aveAndV;
    }
    result.a = 1.0f;
    // 水面合成
    {
        uv *= 3.0;
        float4 c2 = g_texture1.Sample(g_sampler0, uv);
        c2 *= 1.2; // 補正
        result /= c2;
    }
    return (result * input.color) + g_colorAdd;
}