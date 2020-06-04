#include "Stage.hpp"

#include <Siv3D.hpp>

#include <abyss/controllers/Camera/Camera.hpp>

#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Decor/Decor.hpp>
#include <abyss/controllers/Decor/DecorGraphicsManager.hpp>
#include <abyss/controllers/Stage/StageData.hpp>
#include <abyss/controllers/BackGround/BackGround.hpp>

#include <abyss/entities/Room/RoomEntity.hpp>
#include <abyss/entities/Actors/Gimmick/StartPosEntity.hpp>
#include <abyss/entities/Actors/Map/MapEntity.hpp>
#include <abyss/entities/Actors/Enemy/EnemyEntity.hpp>
#include <abyss/entities/BackGround/BackGroundEntity.hpp>

#include <abyss/models/Decor/base/IDecorModel.hpp>

#include <abyss/translators/Room/RoomTranslator.hpp>
#include <abyss/translators/Map/MapTranslator.hpp>
#include <abyss/translators/Enemy/EnemyTranslator.hpp>
#include <abyss/translators/Gimmick/GimmickTranslator.hpp>
#include <abyss/translators/BackGround/BackGroundTranslator.hpp>
#include <abyss/translators/Decor/DecorTranslator.hpp>

#include <abyss/services/Decor/base/IDecorService.hpp>
#include <abyss/services/Decor/base/IDecorGraphicsService.hpp>

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
    Stage::Stage()
    {}

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
    void Stage::initBackGround(BackGround& backGround)
    {
        BackGroundTranslator translator;
        for (const auto& entity : m_stageData->getBgs()) {
            backGround.add(translator.toVM(entity));
        }
    }
    void Stage::initDecorGraphics(Decor& decor)
    {
        if (!m_stageData) {
            return;
        }
        auto service = m_stageData->getDecorGraphicsService();
        if (!service) {
            return;
        }
        auto manager = decor.getGraphicsManager();
        for (const auto& [gId, graphics] : service->getGraphics()) {
            DecorGraphicsManager::Info info{
                .filePath = graphics.filePath,
                .offset = graphics.offset,
                .size = graphics.size
            };
            manager->addInfo(gId, std::move(info));
        }
        for (const auto& [gId, animes] : service->getAnimations()) {
            DecorGraphicsManager::Anime anime;
            for (const auto& elm : animes) {
                anime.add(elm.toGId, elm.timeMilliSec);
            }
            manager->addAnime(gId, std::move(anime));
        }
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
    void Stage::initDecor(Decor& decor, const Camera& camera) const
    {
        decor.clear();
        auto decorService = m_stageData->getDecorService();
        if (!decorService) {
            return;
        }
        DecorTranslator m_translator{ decor.getGraphicsManager() };

        auto add = [&](s3d::int32 order, const s3d::Array<std::shared_ptr<IDecorModel>>& decors) {
            for (const auto& model : decors) {
                if (!model) {
                    continue;
                }
                bool isInScreen = model->isInScreen(camera.getCurrentRoom().getRegion());
                if (const auto& nextRoom = camera.nextRoom(); nextRoom) {
                    isInScreen |= model->isInScreen(nextRoom->getRegion());
                }
                if (!isInScreen) {
                    continue;
                }
                if (auto vm = m_translator.toVM(*model)) {
                    decor.regist(order, vm);
                }
            }
        };
        add(DecorOrder::Front, decorService->getFront());
        add(DecorOrder::Back, decorService->getBack());
        add(DecorOrder::Middle, decorService->getCustom());
    }
    bool Stage::initRoom(World& world, const RoomModel& nextRoom)
    {
        if (!m_stageData) {
            return false;
        }
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
    void Stage::load()
    {
        if (!m_stageData) {
            return;
        }
        m_startPos = GetStartPosList(m_stageData->getGimmicks());
    }
    void Stage::setStageData(std::shared_ptr<StageData> stageData)
    {
        m_stageData = stageData;
    }
}