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

cbuffer ShaderParam : register(b1)
{
	float g_time;
	float g_column;
	float g_row;
	float g_scale;

	float2 g_pos;
	float g_speed;
	float g_angle;
	float2 g_size;

	float g_hightOffset;
	float g_amplitude;
}

static float2 halfSize = g_size / 2;
static float xDiffBase = max(70.0, g_size.x);
static float period = xDiffBase / g_speed * 4.0;
static float dt = min(1 / 60.0, period / 10.0);

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

float timeRate0_1(float time, float rate)
{
	float factor = lerp(1.0, 1.5, rate);
	return (period + factor * time % period) % period / period;
}
float rand(float2 st)
{
	return frac(sin(dot(st.xy, float2(12.9898, 78.233))) * 43758.5453123);
}
float2 move(float time, int xId, int yId, float rate)
{
	float2 moved = float2(0, 0);

	// base offs
	int mod = xId % 4.0;
	if (mod == 0) {
		moved.y += g_size.y;
	} else 	if (mod == 1) {
		moved.x -= halfSize.x;
	} else 	if (mod == 2) {
		moved.y -= halfSize.y;
	} else 	if (mod == 3) {
		moved.x += halfSize.x / 2;
	}

	// moveX
	const float randValue = rand(float2(mod, yId));
	const float distX = max(70.0 + (randValue + mod) * 5.0, g_size.x);

	moved.x -= distX / 2.0;
	moved.x += distX * lerp(-g_column / 2, g_column / 2, rate);

	// moveY
	const float distY = 9.0;
	const float halfRow = g_row / 2.0;
	moved.y += distY * (yId - halfRow);

	const float hightOffs = (randValue * g_row % 2.0 - 1.0);
	moved.y += hightOffs * lerp(-g_hightOffset / 2, g_hightOffset / 2, rate);

	moved.y += g_amplitude * sin(radians(rate * 360.0 + mod * 20 + yId * 45.0) + time / period * 0.01);

	return moved;
}
float2 rot(float2 xy, float theta)
{
	float cosTheta = cos(theta);
	float sinTheta = sin(theta);
	return mul(float2x2(cosTheta, -sinTheta, sinTheta, cosTheta), xy);
}
float2 toQuad(float2 uv, float rate, int xId, int yId, float2 movedDiff)
{
	float2 ret = lerp(halfSize, -halfSize, uv); // 反転させておく
	// スケール
	{
		int modX = xId % 4.0;
		ret *= 0.9 + 0.3 * (1.0 + sin(g_time + modX * 3.0 + yId * 2.0 + (rate * 10) % 10)) * 0.5;

		// ぷにぷに
		float puni01 = (1.0 + sin(g_time * 10.0 + modX + yId)) * 0.5;
		ret.x *= 1.0 + 0.05 * puni01;
		ret.y *= 1.0 - 0.1 * puni01;
	}
	// 回転
	{
		// 移動差分から計算
		float theta = atan2(movedDiff.y, movedDiff.x);
		ret = rot(ret, theta);
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
	float2 pos = g_pos;
	const uint triId = id / 6;
	const uint mod6 = id % 6;

	// 整列
	const int xId = (int)(triId % g_column);
	const int yId = (int)(triId / g_column) % g_row;

	// 周期0～1レート
	float rate = timeRate0_1(g_time, yId / g_row);

	// 移動位置計算
	float posRate = (xId + 4 * rate) % g_column / g_column;
	float2 moved = move(g_time, xId, yId, posRate);
	float2 offs = moved;

	// 前回の位置
	float prevTime = g_time - dt;
	float prevRate = timeRate0_1(prevTime, yId / g_row);
	float prevPosRate = (xId + 4 * prevRate) % g_column / g_column;
	int prevXId = xId;
	if (prevPosRate > posRate) {
		// 周期リセットした場合
		prevXId = xId - 4;
		prevPosRate = (prevXId + 4 * prevRate) % g_column / g_column;
	}
	float2 movedPrev = move(g_time, prevXId, yId, prevPosRate);

	// Quadに変換
	float2 uv = toUV(mod6);
	float2 quadOffs = toQuad(uv, posRate, xId, yId, moved - movedPrev);
	offs += quadOffs;

	// カラー計算
	float4 color = toColor(posRate);

	// リザルト格納
	pos += rot(offs, g_angle) * g_scale;
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
