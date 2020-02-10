﻿#include "StageDataStore.hpp"

#include "parser/MapEntityParser.hpp"

#include <Siv3D.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss
{
    using namespace s3dTiled;

	TiledStageDataStore::TiledStageDataStore(const s3d::String& filePath) :
		m_tiledMap(filePath)
	{}

	s3d::Array<DoorEntity> TiledStageDataStore::getDoorEntity() const
	{
		s3d::Array<DoorEntity> ret;
		// 扉情報
		m_tiledMap.getLayer(U"door")->then(
			[this, &ret](const ObjectGroup & layer) {
				for (const auto& obj : layer.getObjects()) {
					Vec2 targetPos{ obj.getProperty(U"x").value_or(0.0), obj.getProperty(U"y").value_or(0.0) };
					Vec2 size = m_tiledMap.getTile(*obj.gId).size;
					Vec2 pos = obj.pos + Vec2{ size.x / 2, -size.y / 2 };
					ret.push_back({ pos, targetPos, size });
				}
			}
		);
		return ret;
	}

	s3d::Array<MapEntity> TiledStageDataStore::getMapEntity() const
	{
		s3d::Array<MapEntity> ret;
		// 床情報
		m_tiledMap.getLayer(U"map")->then(
			[&](const TileLayer & layer) {
				auto parser = std::make_unique<TiledMapEntityParser>(m_tiledMap, layer.getGrid());
				parser->forEach(
					[&](const MapEntity & info) {
						ret.push_back(info);
					}
				);
			}
		);
		return ret;
	}
	s3d::Array<RoomEntity> TiledStageDataStore::getRoomEntity() const
	{
		s3d::Array<RoomEntity> ret;

		// 部屋情報取得
		m_tiledMap.getLayer(U"room")->then(
			[&ret](const ObjectGroup & layer) {
				for (const auto& obj : layer.getObjects()) {

					s3d::uint8 passbleBits = 0;
					if (obj.getProperty(U"up").value_or(false)) {
						passbleBits |= static_cast<uint8>(Forward::Up);
					}
					if (obj.getProperty(U"down").value_or(false)) {
						passbleBits |= static_cast<uint8>(Forward::Down);
					}
					if (obj.getProperty(U"left").value_or(false)) {
						passbleBits |= static_cast<uint8>(Forward::Left);
					}
					if (obj.getProperty(U"right").value_or(false)) {
						passbleBits |= static_cast<uint8>(Forward::Right);
					}
					ret.push_back({ obj.toRectF(), passbleBits });
				}
			}
		);
		return ret;
	}
	s3d::Array<EnemyEntity> TiledStageDataStore::getEnemyEntity() const
	{
		s3d::Array<EnemyEntity> ret;

		static const std::unordered_map<String, EnemyType> toTypeMap{
			{U"slime", EnemyType::Slime}
		};
		static auto toType = [&](const String & type) {
			if (toTypeMap.find(type) != toTypeMap.end()) {
				return toTypeMap.at(type);
			}
			return EnemyType::None;
		};
		static auto toEntity = [&](const TiledObject & obj)
		{
			auto gId = *obj.gId;
			EnemyEntity e;
			e.type = toType(m_tiledMap.getTileProperty(gId, U"type").value_or(s3d::String(U"none")));
			Vec2 size = m_tiledMap.getTile(gId).size;
			e.pos = obj.pos + Vec2{ size.x / 2, -size.y / 2 };
			return e;
		};

		// 敵
		m_tiledMap.getLayer(U"enemy")->then(
			[&](const ObjectGroup & layer) {
				for (const auto& obj : layer.getObjects()) {
					EnemyEntity e = toEntity(obj);
					if (e.type != EnemyType::None) {
						ret.push_back(e);
					}
				}
			}
		);
		return ret;
	}

	const s3dTiled::TiledMap& TiledStageDataStore::getTiledMap() const
	{
		return m_tiledMap;
	}
}