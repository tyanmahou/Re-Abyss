#pragma once
#include "../../entity/MapEntity.hpp"
#include <S3DTiled.hpp>
#include <unordered_map>

namespace abyss
{
	using s3dTiled::GId;

	class IMapEntityParser
	{
	public:
		virtual void forEach(std::function<void(const MapEntity&)> callback) = 0;
	};

	class TiledMapEntityParser : public IMapEntityParser
	{
		std::unordered_map<GId, MapType> m_fieldTypeMap;
		s3dTiled::TiledMap m_tiledMap;
		const s3d::Grid<GId>& m_grid;

		MapType getFieldType(GId gId);

		MapType getFieldType(s3d::uint32 x, s3d::uint32 y);

		ColDirection calcColDirectrion(s3d::uint32 x, s3d::uint32 y);

		s3d::Optional<MapEntity> tryToMapInfoModel(s3d::uint32 x, s3d::uint32 y);
	public:
		TiledMapEntityParser(const s3dTiled::TiledMap& tiledMap, const s3d::Grid<GId>& grid);

		void forEach(std::function<void(const MapEntity&)> callback) override;
	};
}