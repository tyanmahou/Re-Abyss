#include "Stage.hpp"

#include <Siv3D.hpp>

#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/World/World.hpp>

#include <abyss/repositories/Stage/StageRepository.hpp>

#include <abyss/translators/Room/RoomTranslator.hpp>
#include <abyss/translators/Map/MapTranslator.hpp>
#include <abyss/translators/Enemy/EnemyTranslator.hpp>
#include <abyss/translators/Gimmick/GimmickTranslator.hpp>

#include <abyss/views/Stage/base/IStageView.hpp>

#include <abyss/entities/Actors/Gimmick/StartPosEntity.hpp>

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

    StartPosListModel GetStartPosList(const s3d::Array<std::shared_ptr<GimmickEntity>>& gimmicks)
    {
        StartPosListModel ret;

        for (const auto& gimmick : gimmicks) {
            if (gimmick->type != GimmickType::StartPos) {
                continue;
            }
            const auto& startPos = static_cast<const StartPosEntity&>(*gimmick);
            StartPosModel model{ startPos.startId, startPos.pos, startPos.forward };
            ret.add(model);
        }
        return ret;
    }
}
namespace abyss
{

    Stage::Stage(std::unique_ptr<IStageRepository>&& repository, std::unique_ptr<IStageView>&& view) noexcept :
        m_stageData(std::move(repository)),
        m_view(std::move(view))
    {
        m_startPos = GetStartPosList(m_stageData->getGimmicks());
    }

    Stage::~Stage()
    {}

    s3d::Optional<RoomModel> Stage::findRoom(const s3d::Vec2& pos)const
    {
        return ::GetNextRoom(pos, m_stageData->getRooms());
    }
    s3d::Optional<RoomModel> Stage::init(World& world)
    {
        auto initStartPos = m_startPos.find(0);
        if (!initStartPos) {
            return s3d::none;
        }
        auto player = PlayerActor::Create();
        player->setPos(initStartPos->getPos());
        player->setForward(initStartPos->getForward());

        world.regist(player);

        auto nextRoom = this->findRoom(initStartPos->getPos());
        if (!nextRoom) {
            return s3d::none;
        }
        this->initRoom(world, *nextRoom);
        return nextRoom;
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

        GimmickTranslator gimmickTranslator(this);
        for (const auto& gimmick : m_stageData->getGimmicks()) {
            // TODO 
            if (!nextRoom.getRegion().intersects(gimmick->pos)) {
                continue;
            }
            if (auto obj = gimmickTranslator.toActorPtr(*gimmick)) {
                world.regist(obj);
            }
        }
        for (const auto& enemy : m_stageData->getEnemies()) {
            if (!nextRoom.getRegion().intersects(enemy->pos)) {
                continue;
            }
            if (auto obj = EnemyTranslator::ToActorPtr(*enemy)) {
                world.regist(obj);
            }
        }

        return true;
    }
    s3d::Optional<StartPosModel> Stage::findStartPos(const s3d::int32 startId)const
    {
        return m_startPos.find(startId);
    }
}