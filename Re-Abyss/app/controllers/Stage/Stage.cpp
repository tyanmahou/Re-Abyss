#include "Stage.hpp"

#include <Siv3D.hpp>

#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Decor/Decor.hpp>

#include <abyss/services/Stage/base/IStageService.hpp>

#include <abyss/entities/Room/RoomEntity.hpp>
#include <abyss/entities/Actors/Gimmick/StartPosEntity.hpp>
#include <abyss/entities/Actors/Map/MapEntity.hpp>
#include <abyss/entities/Actors/Enemy/EnemyEntity.hpp>

#include <abyss/translators/Room/RoomTranslator.hpp>
#include <abyss/translators/Map/MapTranslator.hpp>
#include <abyss/translators/Enemy/EnemyTranslator.hpp>
#include <abyss/translators/Gimmick/GimmickTranslator.hpp>

namespace
{
    using namespace abyss;

    Optional<RoomModel> GetNextRoom(const s3d::Vec2& pos, const s3d::Array<RoomEntity>& rooms)
    {
        for (const auto& room : rooms) {
            if (room.region.intersects(pos)) {
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
    Stage::Stage(
        std::shared_ptr<IStageService> service,
        std::shared_ptr<Decor> decor,
        std::shared_ptr<BackGround> backGround
    ):
        m_stageData(service),
        m_decor(decor),
        m_backGround(backGround)
    {
        m_startPos = GetStartPosList(m_stageData->getGimmicks());
    }

    Stage::~Stage()
    {}

    s3d::Optional<RoomModel> Stage::findRoom(const s3d::Vec2& pos)const
    {
        return ::GetNextRoom(pos, m_stageData->getRooms());
    }
    void Stage::setup(Manager* pManager)
    {
        m_pManager = pManager;
    }
    s3d::Optional<RoomModel> Stage::init(World& world, const std::shared_ptr<Player::PlayerActor>& player)
    {
        world.regist(player);

        auto nextRoom = this->findRoom(player->getPos());
        if (!nextRoom) {
            return s3d::none;
        }
        this->initRoom(world, *nextRoom);
        return nextRoom;
    }
    s3d::Optional<RoomModel> Stage::init(World& world, s3d::int32 startId)
    {
        auto initStartPos = m_startPos.find(startId);
        if (!initStartPos) {
            return s3d::none;
        }
        auto player = Player::PlayerActor::Create();
        player->setPos(initStartPos->getPos());
        player->setForward(initStartPos->getForward());

        return this->init(world, player);
    }
    void Stage::initDecor(const Camera& camera) const
    {
        m_decor->init(camera);
    }
    bool Stage::initRoom(World& world, const RoomModel& nextRoom)
    {
        for (const auto& map : m_stageData->getMaps()) {
            if (!nextRoom.getRegion().intersects(map->pos)) {
                continue;
            }
            if (auto obj = MapTranslator::ToActorPtr(*map)) {
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
        world.init();
        return true;
    }
    s3d::Optional<StartPosModel> Stage::findStartPos(const s3d::int32 startId)const
    {
        return m_startPos.find(startId);
    }
}