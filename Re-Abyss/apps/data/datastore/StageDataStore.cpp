#include "StageDataStore.hpp"


#include "parser/MapEntityParser.hpp"
#include "../../application/types/Forward.hpp"

#include <Siv3D.hpp>

using namespace s3dTiled;
namespace abyss
{
	TiledStageDataStore::TiledStageDataStore(const s3d::String& filePath) :
		m_tiledMap(filePath)
	{}

	s3d::Array<DoorEntity> TiledStageDataStore::getDoorEntity() const
	{
		s3d::Array<DoorEntity> ret;
		// ”àî•ñ
		m_tiledMap.getLayer(L"door")->then(
			[this, &ret](const ObjectGroup & layer) {
				for (const auto& obj : layer.getObjects()) {
					Vec2 targetPos{ obj.getProperty(L"x").value_or(0.0), obj.getProperty(L"y").value_or(0.0) };
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
		// °î•ñ
		m_tiledMap.getLayer(L"map")->then(
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

		// •”‰®î•ñŽæ“¾
		m_tiledMap.getLayer(L"room")->then(
			[&ret](const ObjectGroup & layer) {
				for (const auto& obj : layer.getObjects()) {

					s3d::uint8 passbleBits = 0;
					if (obj.getProperty(L"up").value_or(false)) {
						passbleBits |= static_cast<uint8>(Forward::Up);
					}
					if (obj.getProperty(L"down").value_or(false)) {
						passbleBits |= static_cast<uint8>(Forward::Down);
					}
					if (obj.getProperty(L"left").value_or(false)) {
						passbleBits |= static_cast<uint8>(Forward::Left);
					}
					if (obj.getProperty(L"right").value_or(false)) {
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
			{L"slime", EnemyType::Slime}
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
			e.type = EnemyType::Slime;// toType(m_tiledMap.getTileProperty(gId, L"type").value_or(L"none"));
			Vec2 size = m_tiledMap.getTile(gId).size;
			e.pos = obj.pos + Vec2{ size.x / 2, -size.y / 2 };
			return e;
		};

		// “G
		m_tiledMap.getLayer(L"enemy")->then(
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
	s3d::Array<BackGroundEntity> TiledStageDataStore::getBackGroundEntity() const
	{
		s3d::Array<BackGroundEntity> ret;

		auto toEntity = [](const ImageLayer & layer)
		{
			BackGroundEntity e;
			e.texture = layer.getTexture();
			e.offset = layer.getOffset();
			e.loop = { layer.getProperty(L"loopX").value_or(false),layer.getProperty(L"loopY").value_or(false) };
			e.rate = { layer.getProperty(L"rateX").value_or(1.0), layer.getProperty(L"rateY").value_or(1.0) };
			return e;
		};
		// ”wŒiî•ñŽæ“¾
		m_tiledMap.getLayer(L"bgs")->then(
			[&](const GroupLayer & layer) {
				for (const auto& child : layer.getLayers()) {
					child.then([&](const ImageLayer & i) {
						ret.push_back(toEntity(i));
						});
				}
			}
		);
		return ret;
	}
	s3d::Array<LayerViewEntity> TiledStageDataStore::getLayerViewEntity() const
	{
		s3d::Array<LayerViewEntity> ret;

		s3d::Array<s3d::String> layerName{
			L"back", L"map", L"door",L"front"
		};
		auto map = m_tiledMap;
		for (auto&& name : layerName) {
			ret.emplace_back(
				name,
				[map, name](const s3d::RectF & rect){
					map.drawLayer(name, rect);
				}
			);
		}

		return ret;
	}
}