Texture2D       g_texture0 : register(t0);
Texture2D       g_mapChip : register(t1);
Texture2D       g_gIdMap : register(t2);
SamplerState    g_sampler0 : register(s0);

cbuffer PSConstants2D : register(b0)
{
    float4 g_colorAdd;
    float4 g_sdfParam;
    float4 g_internal;
}
cbuffer Params : register(b1)
{
    float2 g_textureSize;
    float2 g_mapChipSize;
    float2 g_mapChipGIdSize;
    float2 g_tileSize;
}
struct PSInput
{
    float4 position : SV_POSITION;
    float4 color    : COLOR0;
    float2 uv       : TEXCOORD0;
};

float4 PS(PSInput input) : SV_TARGET
{
    float2 uv = input.uv;
    float4 gIdMapColor = g_gIdMap.Sample(g_sampler0, uv);
    if (gIdMapColor.a < 1.0) {
        // 描画しない
        discard;
    }
    // タイル番号
    float gId = gIdMapColor.r * 255.0;

    // マップチップテクスチャのピクセルオフセットを計算
    float2 pixel = uv * g_textureSize;
    float2 ajustPixel = pixel % g_tileSize;

    // タイル番号からマップチップテクスチャのuvを計算
    float x = gId % g_mapChipGIdSize.x;
    float y = floor(gId / g_mapChipGIdSize.x);
    float2 mapChipUv = (float2(x, y) * g_tileSize + ajustPixel) / g_mapChipSize;

    float4 result = g_mapChip.Sample(g_sampler0, mapChipUv);

    return (result * input.color) + g_colorAdd;
}