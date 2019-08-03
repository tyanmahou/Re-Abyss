#pragma once

#include <Siv3D/Fwd.hpp>

#include <memory>

namespace s3dTiled
{
	class CTiledMap;

	std::shared_ptr<CTiledMap> ParseTmx(const s3d::FilePath& path);
}