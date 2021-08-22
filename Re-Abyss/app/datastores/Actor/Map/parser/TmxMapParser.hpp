#pragma once
#include <unordered_map>
#include <memory>
#include <S3DTiled.hpp>
#include <abyss/entities/Actor/Map/MapEntity.hpp>
#include <abyss/utils/Chunk/Chunk.hpp>

namespace abyss::Actor::Map
{
	using s3dTiled::GId;

	class TmxMapParser
	{
		struct MergeParam
		{
			MapEntity entity;
			s3d::int32 beginX = -1;
			s3d::int32 endX = -1;
			s3d::int32 beginY = -1;
			s3d::int32 endY = -1;
		};
	private:
		std::unordered_map<GId, MapType> m_fieldTypeMap;
		s3dTiled::TiledMap m_tiledMap;
		const s3dTiled::Chunk<GId>& m_chunk;
		bool m_isMerge;

		ChunkGrid<s3d::Optional<MapEntity>> m_entityGrid;

		MapType getFieldType(GId gId);

		MapType getFieldType(s3d::int32 x, s3d::int32 y);

		ColDirection calcColDirectrion(s3d::int32 x, s3d::int32 y);
		ColDirection calcAroundFloor(s3d::int32 x, s3d::int32 y);

		s3d::Optional<MapEntity> tryToMapInfoModel(s3d::int32 x, s3d::int32 y);
	public:
		TmxMapParser(const s3dTiled::TiledMap& tiledMap, const s3dTiled::Chunk<GId>& chunk, bool isMerge = true);

		const ChunkGrid<s3d::Optional<MapEntity>>& selectGrid();
		void forEach(std::function<void(const MapEntity&)> callback);
	};
}