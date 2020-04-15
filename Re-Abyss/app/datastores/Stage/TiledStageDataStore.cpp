#include "TiledStageDataStore.hpp"

#include "parser/MapEntityParser.hpp"
#include "parser/EnemyEntityParser.hpp"
#include "parser/GimmickEntityParser.hpp"

#include <Siv3D.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss
{
    using namespace s3dTiled;

	TiledStageDataStore::TiledStageDataStore(const s3d::String& filePath) :
		m_tiledMap(filePath)
	{}

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
					ret.push_back({ obj.id, obj.toRectF(), passbleBits });
				}
			}
		);
		return ret;
	}
	s3d::Array<std::shared_ptr<EnemyEntity>> TiledStageDataStore::getEnemyEntity() const
	{
		s3d::Array<std::shared_ptr<EnemyEntity>> ret;

		// 敵
		m_tiledMap.getLayer(U"enemy")->then(
			[&](const ObjectGroup & layer) {
				for (const auto& obj : layer.getObjects()) {
					TiledEnemyEntityParser parser(obj);
					if (auto e = parser.parse();e && e->type != EnemyType::None) {
						ret.push_back(std::move(e));
					}
				}
			}
		);
		return ret;
	}

    s3d::Array<std::shared_ptr<GimmickEntity>> TiledStageDataStore::getGimmickEntity() const
    {
		s3d::Array<std::shared_ptr<GimmickEntity>> ret;

		// ギミック
		m_tiledMap.getLayer(U"gimmick")->then(
			[&](const ObjectGroup& layer) {
			for (const auto& obj : layer.getObjects()) {
				TiledGimmickEntityParser parser(obj);
				if (auto e = parser.parse(); e && e->type != GimmickType::None) {
					ret.push_back(std::move(e));
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