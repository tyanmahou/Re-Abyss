#include "StageUseCase.hpp"
#include <domain/translator/RoomTranslator.hpp>
#include <domain/translator/MapTranslator.hpp>
#include <domain/translator/DoorTranslator.hpp>
#include <domain/model/RoomModel.hpp>
#include <domain/model/object/PlayerModel.hpp>
#include <domain/model/object/MapModel.hpp>
#include <domain/model/object/DoorModel.hpp>
#include <domain/usecase/WorldUseCase.hpp>

namespace
{
	using namespace abyss;
	Optional<RoomModel> GetNextRoom(const Vec2& pos, const Array<RoomEntity>& rooms)
	{
		RoomTranslator translator;
		for (const auto& room : rooms) {
			if (room.m_region.intersects(pos)) {
				return translator.create(room);
			}
		}
		return s3d::none;
	}
}
namespace abyss
{

	StageUseCase::StageUseCase()
	{
	}
	void StageUseCase::load(const s3d::FilePath& path)
	{
		auto store = m_stageData.load(path);
		this->onLoadStageFile().notify(store.get());
	}
	s3d::Optional<RoomModel> StageUseCase::init(WorldUseCase& world)
	{
		world.createObject<PlayerModel>();
		//
		world.getPlayer()->setPos({ 480, 2000 });
		return this->initRoom(world);
	}
	s3d::Optional<RoomModel> StageUseCase::initRoom(WorldUseCase& world)
	{
		Vec2 pos = world.getPlayer()->getPos();
		auto nextRoom = ::GetNextRoom(pos, m_stageData.getRooms());
		if (!nextRoom) {
			return s3d::none;
		}
		
		// 登録オブジェクトのリセット
		world.reset();

		MapTranslator mapTranslator;
		for (const auto& map : m_stageData.getMaps()) {
			if (!nextRoom->getRegion().intersects(map.pos)) {
				continue;
			}
			if (auto obj = mapTranslator.create(map)) {
				world.registerObject(obj);
			}
		}
		DoorTranslator doorTranslator;
		for (const auto& door : m_stageData.getDoors()) {
			if(!nextRoom->getRegion().intersects(door.pos)){
				continue;
			}
			if (auto && toRoom = ::GetNextRoom(door.targetPos, m_stageData.getRooms())) {
				if (auto obj = doorTranslator.create(door, *toRoom)) {
					world.registerObject(obj);
				}
			}
		}

		return nextRoom;
	}
}