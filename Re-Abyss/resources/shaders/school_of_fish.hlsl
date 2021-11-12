Texture2D		g_texture0 : register(t0);
SamplerState	g_sampler0 : register(s0);
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
s3d::PSInput VS(uint id: SV_VERTEXID)
{
	s3d::PSInput result;
	float2 pos = float2(1120, 640) / 2.0 + halfSize;
	const uint triId = id / 6;
	const uint mod6 = id % 6;

	result.uv = toUV(mod6);

	const float2 texOffs = lerp(-halfSize, halfSize, result.uv);
	float2 moved = texOffs;
	int column = 32;
	int row = 6;
	int xId = (-column / 2 + (int)(triId % column));
	int yId = (-row / 2 + (int)(triId / column));
	yId = yId % (float)row;
	float factor = -((yId + row / 2.0) * 0.1 + 1.0);
	float time = factor * g_t;
	float period = 0.3;
	float rate = (period + time % period) % period / period;

	float posRate = (xId + column / 2 + rate) % (float)column / column;

	moved *= 0.9 + 0.3 * (1.0 + sin(g_t + yId * 2.0 + (posRate * 10) % 10)) * 0.5;
	// moveX
	float distX = 2.0 * max(35.0 + (yId + row / 2) * 2.5, halfSize.x);

	moved.x -= distX / 2.0;
	moved.x += distX * lerp(-column / 2, column / 2, posRate);

	// moveY
	float distY = 9.0;
	if (yId >= 0) {
		moved.y -= (row / 2) * distY;
	}
	moved.y += distY * yId;
	float hightOffs = 4.0 * sin(g_t * 1.5 + yId * 0.5) * (yId % 2.0 == 0 ? 1.0 : -1.0);
	moved.y += hightOffs * lerp(-column / 2, column / 2, posRate);
	moved.y += hightOffs * sqrt(column) * sin(g_t + radians(posRate * 360.0) * 2.0);

	// move
	pos += moved;
	result.position	= s3d::Transform2D(pos, g_transform);

	float alpha = sin(radians(posRate * 180.0));
	alpha = 1 - (1 - alpha) * (1 - alpha);
	result.color = float4(0.5, 0.5, 0.5, alpha);
	return result;
}

float4 PS(s3d::PSInput input) : SV_TARGET
{
	const float4 texColor = g_texture0.Sample(g_sampler0, input.uv);
	return ((texColor * input.color) + g_colorAdd);
}
