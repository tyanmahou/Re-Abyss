#pragma once
#include <unordered_map>
#include <S3DTiled.hpp>
#include <abyss/entities/Actors/Map/MapEntity.hpp>

namespace abyss
{
	using s3dTiled::GId;

	class TmxMapParser
	{
		std::unordered_map<GId, MapType> m_fieldTypeMap;
		s3dTiled::TiledMap m_tiledMap;
		const s3d::Grid<GId>& m_grid;
		bool m_useAroundFilter;
		MapType getFieldType(GId gId);

		MapType getFieldType(s3d::uint32 x, s3d::uint32 y);

		ColDirection calcColDirectrion(s3d::uint32 x, s3d::uint32 y);
		ColDirection calcAroundFloor(s3d::uint32 x, s3d::uint32 y);

		s3d::Optional<MapEntity> tryToMapInfoModel(s3d::uint32 x, s3d::uint32 y);
	public:
		TmxMapParser(const s3dTiled::TiledMap& tiledMap, const s3d::Grid<GId>& grid, bool useAroundFilter = true);

		void forEach(std::function<void(const MapEntity&)> callback);
	};
}