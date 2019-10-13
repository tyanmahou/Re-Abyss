#include "StageUseCase.hpp"
#include <domain/translator/RoomTranslator.hpp>
#include <domain/translator/MapTranslator.hpp>
#include <domain/translator/DoorTranslator.hpp>
#include <domain/translator/EnemyTranslator.hpp>
#include <domain/model/RoomModel.hpp>
#include <domain/actor/PlayerActor.hpp>
#include <domain/actor/MapActor.hpp>
#include <domain/actor/DoorActor.hpp>
#include <domain/actor/SlimeActor.hpp>
#include <domain/facade/WorldFacade.hpp>

namespace
{
	using namespace abyss;
	Optional<RoomModel> GetNextRoom(const s3d::Vec2& pos, const s3d::Array<RoomEntity>& rooms)
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

	StageUseCase::StageUseCase(std::unique_ptr<IStageRepository>&& repository) noexcept:
		m_stageData(std::move(repository))
	{}

	s3d::Optional<RoomModel> StageUseCase::findRoom(const s3d::Vec2& pos)
	{
		return ::GetNextRoom(pos, m_stageData->getRooms());
	}
	bool StageUseCase::init(World& world, const RoomModel& nextRoom)
	{
		auto player = PlayerActor::Create();
		player->setPos({ 480, 2000 });
		world.setPlayer(player);
		world.regist(player);

		return this->initRoom(world, nextRoom);
	}
	bool StageUseCase::initRoom(World& world, const RoomModel& nextRoom)
	{		
		MapTranslator mapTranslator;
		for (const auto& map : m_stageData->getMaps()) {
			if (!nextRoom.getRegion().intersects(map.pos)) {
				continue;
			}
			if (auto obj = mapTranslator.create(map)) {
				world.regist(obj);
			}
		}
		DoorTranslator doorTranslator;
		for (const auto& door : m_stageData->getDoors()) {
			if(!nextRoom.getRegion().intersects(door.pos)){
				continue;
			}
			if (auto && toRoom = ::GetNextRoom(door.targetPos, m_stageData->getRooms())) {
				if (auto obj = doorTranslator.create(door, *toRoom)) {
					world.regist(obj);
				}
			}
		}
		EnemyTranslator enemyTranslator;
		for (const auto& enemy : m_stageData->getEnemies()) {
			if (!nextRoom.getRegion().intersects(enemy.pos)) {
				continue;
			}
			if (auto obj = enemyTranslator.create(enemy)) {
				world.regist(obj);
			}
		}

		return true;
	}
}