#pragma once
#include<Siv3D/Fwd.hpp>

namespace s3dTiled
{
	class TiledMap;

	bool ParseTmx(const s3d::FilePath& path, TiledMap& map);
}