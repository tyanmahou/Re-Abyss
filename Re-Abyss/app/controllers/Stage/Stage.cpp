#include "Stage.hpp"

#include <Siv3D.hpp>

#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/World/World.hpp>

#include <abyss/repositories/Stage/StageRepository.hpp>

#include <abyss/translators/Room/RoomTranslator.hpp>
#include <abyss/translators/Map/MapTranslator.hpp>
#include <abyss/translators/Enemy/EnemyTranslator.hpp>
#include <abyss/translators/Door/DoorTranslator.hpp>

#include <abyss/views/Stage/base/IStageView.hpp>

namespace
{
	using namespace abyss;

	Optional<RoomModel> GetNextRoom(const s3d::Vec2& pos, const s3d::Array<RoomEntity>& rooms)
	{
		for (const auto& room : rooms) {
			if (room.m_region.intersects(pos)) {
				return RoomTranslator::ToModel(room);
			}
		}
		return s3d::none;
	}
}
namespace abyss
{

	Stage::Stage(std::unique_ptr<IStageRepository>&& repository, std::unique_ptr<IStageView>&& view) noexcept :
		m_stageData(std::move(repository)),
		m_view(std::move(view))
	{}

	Stage::~Stage()
	{}

	s3d::Optional<RoomModel> Stage::findRoom(const s3d::Vec2& pos)
	{
		return ::GetNextRoom(pos, m_stageData->getRooms());
	}
	bool Stage::init(World& world, const RoomModel& nextRoom)
	{
		auto player = PlayerActor::Create();
		player->setPos({ 480, 2000 });
		world.setPlayer(player);
		world.regist(player);

		return this->initRoom(world, nextRoom);
	}
	bool Stage::initRoom(World& world, const RoomModel& nextRoom)
	{
		for (const auto& map : m_stageData->getMaps()) {
			if (!nextRoom.getRegion().intersects(map.pos)) {
				continue;
			}
			if (auto obj = MapTranslator::ToActorPtr(map)) {
				world.regist(obj);
			}
		}
		for (const auto& door : m_stageData->getDoors()) {
			if (!nextRoom.getRegion().intersects(door.pos)) {
				continue;
			}
			if (auto&& toRoom = ::GetNextRoom(door.targetPos, m_stageData->getRooms())) {
				if (auto obj = DoorTranslator::ToActorPtr(door, *toRoom)) {
					world.regist(obj);
				}
			}
		}
		for (const auto& enemy : m_stageData->getEnemies()) {
			if (!nextRoom.getRegion().intersects(enemy.pos)) {
				continue;
			}
			if (auto obj = EnemyTranslator::ToActorPtr(enemy)) {
				world.regist(obj);
			}
		}

		return true;
	}
}