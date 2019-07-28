#pragma once
#include<Siv3D/Fwd.hpp>

namespace s3dTiled
{
	/// <summary>
	/// Tiledの色文字列をパース
	/// </summary>
	s3d::Color ParseTiledColor(const s3d::String& str);
}
