#pragma once
#include <Siv3D/Fwd.hpp>
#include <unordered_map>

namespace s3dTiled
{
	using GId = s3d::uint32;
	using TileId = s3d::uint32;

	class TiledProperty;
	using TiledProperties = std::unordered_map<s3d::String, TiledProperty>;
}