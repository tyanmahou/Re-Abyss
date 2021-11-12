Texture2D       g_texture0 : register(t0);
SamplerState    g_sampler0 : register(s0);
namespace s3d
{
	//
	//	VS Input (nothing)
	//

	//
	//	VS Output
	//
	struct PSInput
	{
		float4 position	: SV_POSITION;
		float4 color	: COLOR0;
		float2 uv		: TEXCOORD0;
	};

	//
	//	Siv3D Functions
	//
	float4 Transform2D(float2 pos, float2x4 t)
	{
		return float4((t._13_14 + (pos.x * t._11_12) + (pos.y * t._21_22)), t._23_24);
	}
}

//
//	Constant Buffer
//
cbuffer VSConstants2D : register(b0)
{
	row_major float2x4 g_transform;
	float4 g_colorMul;
}

cbuffer PSConstants2D : register(b0)
{
	float4 g_colorAdd;
	float4 g_sdfParam;
	float4 g_sdfOutlineColor;
	float4 g_sdfShadowColor;
	float4 g_internal;
}

cbuffer SoftShape : register(b1)
{
	float g_t;
}

static float2 size = float2(40, 20);
static float2 halfSize = size / 2;

float2 toUV(uint mod6)
{
	if (mod6 == 0) {
		return float2(0, 0);
	} else if (mod6 == 1) {
		return float2(1, 0);
	} else if (mod6 == 2) {
		return float2(0, 1);
	} else if (mod6 == 3) {
		return float2(0, 1);
	} else if (mod6 == 4) {
		return float2(1, 0);
	} else {
		return float2(1, 1);
	}
}

float timeRate0_1(float rate)
{
	float factor = lerp(1.0, 1.5, rate);
	float time = factor * g_t;
	float period = 1.6;
	return (period + time % period) % period / period;
}
float2 move(int xId, int yId, float rate, int column, int row)
{
	float2 moved = float2(0, 0);

	// base offs
	int mod = xId % 4.0;
	if (mod == 0) {
		moved.y += size.y;
	} else 	if (mod == 1) {
		moved.x -= halfSize.x;
	} else 	if (mod == 2) {
		moved.y -= halfSize.y;
	} else 	if (mod == 3) {
		moved.x += halfSize.x / 2;
	}

	// moveX
	float distX = 2.0 * max(35.0 + yId * 2.5 + mod * 2.5, halfSize.x);

	moved.x -= distX / 2.0;
	moved.x += distX * lerp(-column / 2, column / 2, rate);

	// moveY
	float distY = 9.0;
	float halfRow = row / 2.0;
	if (yId >= halfRow) {
		moved.y -= halfRow * distY;
	}
	moved.y += distY * (yId - halfRow);
	float hightOffs = 3.0 * (yId % 2.0 == 0 ? 1.0 : -1.0);
	moved.y += hightOffs * lerp(-column / 2, column / 2, rate);
	float sinHight = hightOffs * column;
	sinHight = sign(sinHight) * pow(abs(sinHight), 0.7);
	moved.y += sinHight * sin(yId * 45.0 + radians(rate * 360.0 + mod * 20) + g_t);
	moved.y += -2000.0 * rate;
	moved.y += 1000;
	return moved;
}

float2 toQuad(float2 uv, float rate, int xId, int yId, float2 movedDiff)
{
	float2 ret = lerp(halfSize, -halfSize, uv); // 反転させておく
	// スケール
	{
		int modX = xId % 4.0;
		ret *= 0.9 + 0.3 * (1.0 + sin(g_t + modX * 3.0 + yId * 2.0 + (rate * 10) % 10)) * 0.5;

		// ぷにぷに
		float puni01 = (1.0 + sin(g_t * 10.0 + (xId % 4.0) + yId)) * 0.5;
		ret.x *= 1.0 + 0.05 * puni01;
		ret.y *= 1.0 - 0.1 * puni01;
	}
	// 回転
	{
		// 移動差分から計算
		float theta = atan2(movedDiff.y, movedDiff.x);
		float cosTheta = cos(theta);
		float sinTheta = sin(theta);
		ret = mul(float2x2(cosTheta, -sinTheta, sinTheta, cosTheta), ret);
	}
	return ret;
}
float4 toColor(float rate)
{
	// アルファ値計算
	float alpha = sin(radians(rate * 180.0));
	alpha = 1 - (1 - alpha) * (1 - alpha);
	return float4(0.4, 0.4, 0.4, 0.07 * alpha);
}
s3d::PSInput VS(uint id: SV_VERTEXID)
{
	s3d::PSInput result;
	float2 pos = float2(1120, 640) / 2.0 + halfSize;
	const uint triId = id / 6;
	const uint mod6 = id % 6;

	// 整列
	const int column = 64;
	const int row = 8;
	const int xId = (int)(triId % column);
	const int yId = (int)(triId / column) % (float)row;

	// 周期0～1レート
	float rate = timeRate0_1(yId / (float)row);

	// 移動位置計算
	float posRate = (xId + 4 * rate) % (float)column / column;
	float2 moved = move(xId, yId, posRate, column, row);
	pos += moved;

	// 前回の位置
	float posRatePrev = (xId - 1 + 4 * rate) % (float)column / column;
	if (posRatePrev > posRate) {
		posRatePrev -= 1.0;
	}
	float2 movedPrev = move(xId, yId, posRatePrev, column, row);

	// Quadに変換
	float2 uv = toUV(mod6);
	float2 quadOffs = toQuad(uv, posRate, xId, yId, moved - movedPrev);
	pos += quadOffs;

	// カラー計算
	float4 color = toColor(posRate);

	// リザルト格納
	result.position = s3d::Transform2D(pos, g_transform);
	result.uv = uv;
	result.color = color * g_colorMul;

	return result;
}

float4 PS(s3d::PSInput input) : SV_TARGET
{
	const float4 texColor = g_texture0.Sample(g_sampler0, input.uv);
	return (texColor * input.color) + g_colorAdd;
}
