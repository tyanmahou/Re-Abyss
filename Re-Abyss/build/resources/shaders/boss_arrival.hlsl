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
	float g_timer;
	float2 g_pos;
}

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
static float2 g_vertexPrev[][4] = {
	{float2(74, 0), float2(81, 0), float2(74, 630), float2(81, 630)},       // B-1-1
	{float2(88, 0), float2(110, 0), float2(88, 630), float2(110, 630)},     // B-1-2
	{float2(0, 258), float2(1120, 258), float2(0, 280), float2(1120, 280)}, // B-2
	{float2(141, 0), float2(157, 0), float2(141, 630), float2(157, 630)},   // B-3
	{float2(0, 307), float2(1120, 307), float2(0, 325), float2(1120, 325)}, // B-4
	{float2(151, 0), float2(174, 0), float2(151, 630), float2(174, 630)},   // B-5
	{float2(0, 362), float2(1120, 362), float2(0, 379), float2(1120, 379)}, // B-6
  
	{float2(235, 0), float2(269, 0), float2(235, 630), float2(269, 630)},   // O-1
	{float2(0, 282), float2(1120, 282), float2(0, 297), float2(1120, 297)}, // O-2
	{float2(183, 0), float2(205, 0), float2(183, 630), float2(205, 630)},   // O-3
	{float2(0, 364), float2(1120, 364), float2(0, 379), float2(1120, 379)}, // O-4
  
	{float2(0, 282), float2(1120, 282), float2(0, 298), float2(1120, 298)}, // S1-1
	{float2(280, 0), float2(297, 0), float2(280, 630), float2(297, 630)},   // S1-2
	{float2(0, 314), float2(1120, 314), float2(0, 331), float2(1120, 331)}, // S1-3
	{float2(322, 0), float2(350, 0), float2(322, 630), float2(350, 630)},   // S1-4
	{float2(0, 364), float2(1120, 364), float2(0, 379), float2(1120, 379)}, // S1-5
  
	{float2(0, 282), float2(1120, 282), float2(0, 298), float2(1120, 298)}, // S2-1
	{float2(360, 0), float2(377, 0), float2(360, 630), float2(377, 630)},   // S2-2
	{float2(0, 314), float2(1120, 314), float2(0, 331), float2(1120, 331)}, // S2-3
	{float2(402, 0), float2(430, 0), float2(402, 630), float2(430, 630)},   // S2-4
	{float2(0, 364), float2(1120, 364), float2(0, 379), float2(1120, 379)}, // S2-5
  
	{float2(607, 0), float2(614, 0), float2(384, 630), float2(391, 630)},   // A1-1-1
	{float2(621, 0), float2(638, 0), float2(398, 630), float2(415, 630)},   // A1-1-2
	{float2(0, 258), float2(1120, 258), float2(0, 280), float2(1120, 280)}, // A1-2
	{float2(551, 0), float2(574, 0), float2(551, 630), float2(574, 630)},   // A1-3
	{float2(0, 313), float2(1120, 313), float2(0, 330), float2(1120, 330)}, // A1-4
  
	{float2(584, 0), float2(601, 0), float2(584, 630), float2(601, 630)},   // R1-1
	{float2(0, 282), float2(1120, 282), float2(0, 298), float2(1120, 298)}, // R1-2
	{float2(635, 0), float2(657, 0), float2(635, 630), float2(657, 630)},   // R1-3
	{float2(0, 320), float2(1120, 320), float2(0, 334), float2(1120, 334)}, // R1-4
	{float2(416, 0), float2(443, 0), float2(788, 630), float2(815, 630)},   // R1-5
  
	{float2(669, 0), float2(686, 0), float2(669, 630), float2(686, 630)},   // R2-1
	{float2(0, 282), float2(1120, 282), float2(0, 298), float2(1120, 298)}, // R2-2
	{float2(720, 0), float2(742, 0), float2(720, 630), float2(742, 630)},   // R2-3
	{float2(0, 320), float2(1120, 320), float2(0, 334), float2(1120, 334)}, // R2-4
	{float2(501, 0), float2(528, 0), float2(873, 630), float2(900, 630)},   // R2-5
  
	{float2(761, 0), float2(779, 0), float2(761, 630), float2(779, 630)},   // I-1
  
	{float2(695, 0), float2(730, 0), float2(908, 630), float2(911, 630)},   // V-1
	{float2(933, 0), float2(968, 0), float2(751, 630), float2(754, 630)},   // V-2
  
	{float2(884, 0), float2(906, 0), float2(884, 630), float2(906, 630)},   // A2-1
	{float2(0, 282), float2(1120, 282), float2(0, 297), float2(1120, 297)}, // A2-2
	{float2(936, 0), float2(958, 0), float2(936, 630), float2(958, 630)},   // A2-3
	{float2(0, 319), float2(1120, 319), float2(0, 334), float2(1120, 334)}, // A2-4
  
	{float2(969, 0), float2(979, 0), float2(969, 630), float2(979, 630)},   // L-1-1
	{float2(983, 0), float2(999, 0), float2(983, 630), float2(999, 630)},   // L-1-2
	{float2(0, 359), float2(1120, 359), float2(0, 379), float2(1120, 379)}, // L-2	
};
static int g_vertexTime[]={
	4+0,4+0,2-1,8+3,2+3,4-1,8+0,
	8+2,4+4,8+1,4+2,
	8+3,4+1,4+3,8+0,2+1,
	4+3,2+2,8+4,2+0,6+3,
	10+4,10+4,2+4,12-1,2+0,
	10-1,2+2,6+0,6-1,2-1,
	10+1,4+0,6+3,2+3,4+1,
	10+2,
	6+0,2+1,
	6+2,8-1,6+4,4-1,
	6+1,6+1,10+3
};
// static int g_vertexTime[]={
// 	1,1,2,3,4,5,6,
// 	1,2,3,4,
// 	1,2,3,4,5,
// 	1,2,3,4,5,
// 	1,1,2,3,4,
// 	1,2,3,4,5,
// 	1,2,3,4,5,
// 	1,
// 	1,2,
// 	1,2,3,4,
// 	1,1,2
// };
static uint g_modToIndex[]={0, 1, 2, 1, 2, 3};

static uint g_modToMirrorIndex[]={1,0,3,2};
static uint g_modToFlipIndex[]={2,3,0,1};
static int g_revMap[]={
	0,0,1,0,1,0,1,
	0,1,0,1,
	1,0,1,0,1,	
	1,0,1,0,1,	
	0,0,1,0,1,
	0,1,0,1,0,
	0,1,0,1,0,
	0,
	0,0,
	0,1,
};
s3d::PSInput VS(uint id: SV_VERTEXID)
{
	// 矩形単位に分割
	const uint quadId = id / 6;
	// エフェクトか
	const bool isEffect = quadId > 46;

	// エッジのID
	const uint objId = quadId % 46;

	// タイム 1~20
	const float time = g_timer * 20;
	// α計算
	const float alpha = (time >= g_vertexTime[objId]) ?	1.0 
	                  : (time >= g_vertexTime[objId] - 1) ? time % 1.0
					  : 0.0;
	// エフェクトのα計算
	float alphaEffect = (time >= g_vertexTime[objId] + 1) ? 0.0
	                  : (time >= g_vertexTime[objId]) ? 1.0 - time % 1.0
					  : (time >= g_vertexTime[objId] - 1) ? time % 1.0
					  : 0;
	// 最後だけアクセントとして長めにとる
	const float alphaLast = (time >= g_vertexTime[objId] + 3) ? 0.0
		                   :(time >= g_vertexTime[objId] + 2) ? 0.5 - (time % 1.0)*0.5
		                   :(time >= g_vertexTime[objId] + 1) ? 1.0 - (time % 1.0)*0.5
					       :(time >= g_vertexTime[objId])     ? 0.5 + (time % 1.0) * 0.5
					       :(time >= g_vertexTime[objId] - 1) ? (time % 1.0) * 0.5
					       :0;
	alphaEffect = lerp(alphaEffect, alphaLast, (quadId == 46 + 21) || (quadId == 46 + 22));

	// 頂点インデックス 0~4
	const int index = g_modToIndex[id % 6];

	// エフェクトのアニメ
	const float2 effectAnimePos = (g_vertexPrev[objId][index] + lerp(g_vertexPrev[objId][g_modToMirrorIndex[index]],g_vertexPrev[objId][g_modToFlipIndex[index]], g_revMap[objId]))/2.0;
	const float et = 1 - alphaEffect * alphaEffect * alphaEffect;
	float2 effectPos = lerp(effectAnimePos, g_vertexPrev[objId][index], et);

	// 座標
	float2 pos = lerp(g_vertex[objId][index], effectPos, isEffect);
	// フェードアウトアニメ
	pos = lerp(pos, lerp(pos, ((int)(index % 2.0) == 0) ? float2(0, 315) : float2(1120, 315), 1 - (20 - time) / 1.0) , time >= 19);

	// 色
	const float4 color = float4(1, 0, 0, lerp(alpha, alphaEffect, isEffect));

	// リザルト格納
	s3d::PSInput result;
	result.position = s3d::Transform2D(pos + g_pos, g_transform);
	result.uv = float2(0, 0);
	result.color = color * g_colorMul;

	return result;
}