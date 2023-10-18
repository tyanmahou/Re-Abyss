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
	float2 g_pos;
}

static uint edges = 7 + 4 + 5 + 5 + 5 + 5 + 5 + 1 + 2 + 4 + 3;
static float2 g_vertex[][4] = {
	{float2(74, 258), float2(81, 258), float2(74, 379), float2(81, 379)},       // B-1-1
	{float2(88, 258), float2(110, 258), float2(88, 379), float2(110, 379)},     // B-1-2
	{float2(88, 258), float2(157, 258), float2(88, 280), float2(157, 280)},     // B-2
	{float2(141, 258), float2(157, 258), float2(141, 325), float2(157, 325)},   // B-3
	{float2(88, 307), float2(174, 307), float2(88, 325), float2(174, 325)},     // B-4
	{float2(151, 307), float2(174, 307), float2(151, 379), float2(174, 379)},   // B-5
	{float2(88, 362), float2(174, 362), float2(88, 379), float2(174, 379)},     // B-6
  
	{float2(235, 282), float2(269, 282), float2(235, 379), float2(269, 379)},   // O-1
	{float2(183, 282), float2(269, 282), float2(183, 297), float2(269, 297)},   // O-2
	{float2(183, 282), float2(205, 282), float2(183, 379), float2(205, 379)},   // O-3
	{float2(183, 364), float2(269, 364), float2(183, 379), float2(269, 379)},   // O-4
  
	{float2(280, 282), float2(350, 282), float2(280, 298), float2(350, 298)},   // S1-1
	{float2(280, 282), float2(297, 282), float2(280, 331), float2(297, 331)},   // S1-2
	{float2(280, 314), float2(350, 314), float2(280, 331), float2(350, 331)},   // S1-3
	{float2(322, 314), float2(350, 314), float2(322, 379), float2(350, 379)},   // S1-4
	{float2(278, 364), float2(350, 364), float2(278, 379), float2(350, 379)},   // S1-5
  
	{float2(360, 282), float2(430, 282), float2(360, 298), float2(430, 298)},   // S2-1
	{float2(360, 282), float2(377, 282), float2(360, 331), float2(377, 331)},   // S2-2
	{float2(360, 314), float2(430, 314), float2(360, 331), float2(430, 331)},   // S2-3
	{float2(402, 314), float2(430, 314), float2(402, 379), float2(430, 379)},   // S2-4
	{float2(358, 364), float2(430, 364), float2(358, 379), float2(430, 379)},   // S2-5
  
	{float2(516, 258), float2(523, 258), float2(473, 379), float2(480, 379)},   // A1-1-1
	{float2(530, 258), float2(547, 258), float2(487, 379), float2(504, 379)},   // A1-1-2
	{float2(530, 258), float2(574, 258), float2(530, 280), float2(574, 280)},   // A1-2
	{float2(551, 258), float2(574, 258), float2(551, 379), float2(574, 379)},   // A1-3
	{float2(531, 313), float2(580, 313), float2(531, 330), float2(580, 330)},   // A1-4
  
	{float2(584, 282), float2(601, 282), float2(584, 379), float2(601, 379)},   // R1-1
	{float2(584, 282), float2(657, 282), float2(584, 298), float2(657, 298)},   // R1-2
	{float2(635, 282), float2(657, 282), float2(635, 334), float2(657, 334)},   // R1-3
	{float2(584, 320), float2(657, 320), float2(584, 334), float2(657, 334)},   // R1-4
	{float2(605, 320), float2(632, 320), float2(640, 379), float2(667, 379)},   // R1-5
  
	{float2(669, 282), float2(686, 282), float2(669, 379), float2(686, 379)},   // R2-1
	{float2(669, 282), float2(742, 282), float2(669, 298), float2(742, 298)},   // R2-2
	{float2(720, 282), float2(742, 282), float2(720, 334), float2(742, 334)},   // R2-3
	{float2(669, 320), float2(742, 320), float2(669, 334), float2(742, 334)},   // R2-4
	{float2(690, 320), float2(717, 320), float2(725, 379), float2(752, 379)},   // R2-5
  
	{float2(761, 282), float2(779, 282), float2(761, 379), float2(779, 379)},   // I-1
  
	{float2(790, 282), float2(811, 282), float2(823, 379), float2(839, 379)},   // V-1
	{float2(852, 282), float2(873, 282), float2(823, 379), float2(839, 379)},   // V-2
  
	{float2(884, 282), float2(906, 282), float2(884, 379), float2(906, 379)},   // A2-1
	{float2(884, 282), float2(958, 282), float2(884, 297), float2(958, 297)},   // A2-2
	{float2(936, 282), float2(958, 282), float2(936, 379), float2(958, 379)},   // A2-3
	{float2(911, 319), float2(958, 319), float2(911, 334), float2(958, 334)},   // A2-4
  
	{float2(969, 258), float2(979, 258), float2(969, 379), float2(979, 379)},   // L-1-1
	{float2(983, 258), float2(999, 258), float2(983, 379), float2(999, 379)},   // L-1-2
	{float2(983, 359), float2(1049, 359), float2(983, 379), float2(1049, 379)}, // L-2	
};
uint modToVertexIndex(uint mod6)
{
    if (mod6 == 0){
    	return 0;
    } else if (mod6 == 1 || mod6 == 3){
    	return 1;	
    } else if (mod6 == 2 || mod6 == 4){
    	return 2;	
    } else {
    	return 3;
    }
}
s3d::PSInput VS(uint id: SV_VERTEXID)
{
	s3d::PSInput result;
	float2 pos = g_pos;
	const uint triId = id / 6;
	const uint mod6 = id % 6;
	float4 color = float4(1, 0, 0, 1);
	
	const int index = modToVertexIndex(mod6);

	pos = g_vertex[triId][index];

	// リザルト格納
	result.position = s3d::Transform2D(pos, g_transform);
	result.uv = float2(0, 0);
	result.color = color * g_colorMul;

	return result;
}