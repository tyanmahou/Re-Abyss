#include "WorldDataStore.hpp"


#include "parser/MapEntityParser.hpp"
#include "../../application/types/Forward.hpp"

#include <Siv3D.hpp>

using namespace s3dTiled;
namespace abyss
{
	TiledWorldDataStore::TiledWorldDataStore(const s3d::String& filePath):
		m_tiledMap(filePath)
	{}

	s3d::Array<DoorEntity> TiledWorldDataStore::getDoorEntity() const
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

	s3d::Array<MapEntity> TiledWorldDataStore::getMapEntity() const
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
	s3d::Array<RoomEntity> TiledWorldDataStore::getRoomEntity() const
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
}