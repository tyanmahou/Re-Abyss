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

// https://chilliant.com/rgb2hsv.html
float3 hue2rgb(in float h)
{
    float r = abs(h * 6 - 3) - 1;
    float g = 2 - abs(h * 6 - 2);
    float b = 2 - abs(h * 6 - 4);
    return saturate(float3(r, g, b));
}

float3 hsv2rgb(in float3 hsv)
{
    float3 rgb = hue2rgb(hsv.x);
    return ((rgb - 1) * hsv.y + 1) * hsv.z;
}

static const float epsilon = 1e-10;
float3 rgb2hcv(in float3 rgb)
{
    float4 p = (rgb.g < rgb.b) ? float4(rgb.bg, -1.0, 2.0 / 3.0) : float4(rgb.gb, 0.0, -1.0 / 3.0);
    float4 q = (rgb.r < p.x) ? float4(p.xyw, rgb.r) : float4(rgb.r, p.yzx);
    float c = q.x - min(q.w, q.y);
    float h = abs((q.w - q.y) / (6 * c + epsilon) + q.z);
    return float3(h, c, q.x);
}
float3 rgb2hsv(in float3 rgb)
{
    float3 hcv = rgb2hcv(rgb);
    float s = hcv.y / (hcv.z + epsilon);
    return float3(hcv.x, s, hcv.z);
}

// カラー合成
float4 color(in float4 dest, in float4 src)
{
    float3 hsvDest = rgb2hsv(dest.rgb);
    float3 hsvSrc = rgb2hsv(src.rgb * src.a);

    // 色相、彩度を上書き
    float3 hsvRet = hsvDest;
    hsvRet.b = hsvDest.b;
    
    float4 ret;
    ret.rgb = hsv2rgb(hsvRet);
    ret.a = dest.a;
    return ret;
}
float4 PS(PSInput input) : SV_TARGET
{
    const float2 uv = input.uv;
    float4 src = g_color;
    float4 dest = g_texture0.Sample(g_sampler0, uv);
    return color(dest, src);
}
