#include "Stage.hpp"

#include <Siv3D.hpp>

#include <abyss/modules/Camera/Camera.hpp>

#include <abyss/components/Actor/God/Builder.hpp>
#include <abyss/components/Actor/Player/Builder.hpp>
#include <abyss/components/Cron/BubbleGenerator/Builder.hpp>
#include <abyss/components/Event/GameReady/Builder.hpp>

#include <abyss/modules/World/World.hpp>
#include <abyss/modules/Decor/Decors.hpp>
#include <abyss/modules/Decor/DecorGraphics.hpp>
#include <abyss/modules/Decor/DecorBuildUtil.hpp>
#include <abyss/modules/Stage/StageData.hpp>
#include <abyss/modules/BackGround/BackGround.hpp>
#include <abyss/modules/Cron/Crons.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/Save/Save.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>

#include <abyss/entities/Room/RoomEntity.hpp>
#include <abyss/entities/Actor/Gimmick/StartPosEntity.hpp>
#include <abyss/entities/Actor/Gimmick/BgmChangerEntity.hpp>
#include <abyss/entities/Actor/Map/MapEntity.hpp>
#include <abyss/entities/Actor/Enemy/EnemyEntity.hpp>
#include <abyss/entities/BackGround/BackGroundEntity.hpp>
#include <abyss/entities/Decor/DecorEntity.hpp>

#include <abyss/models/Save/RestartInfo/RestartInfoModel.hpp>

#include <abyss/translators/Room/RoomTranslator.hpp>
#include <abyss/translators/Map/MapTranslator.hpp>
#include <abyss/translators/Enemy/EnemyTranslator.hpp>
#include <abyss/translators/Gimmick/GimmickTranslator.hpp>
#include <abyss/translators/BackGround/BackGroundTranslator.hpp>
#include <abyss/translators/Decor/DecorTranslator.hpp>

#include <abyss/services/BackGround/base/IBackGroundService.hpp>

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
            StartPosModel model{ startPos.startId, startPos.pos, startPos.forward, startPos.isSave };
            ret.add(model);
        }
        return ret;
    }
    Optional<FilePath> NextBgm(const RoomModel& nextRoom, const s3d::Array<std::shared_ptr<GimmickEntity>>& gimmicks)
    {
        for (const auto& gimmick : gimmicks) {
            if (gimmick->type != GimmickType::BgmChanger) {
                continue;
            }
            if (!nextRoom.getRegion().intersects(gimmick->pos)) {
                continue;
            }

            const auto& bgmChanger = static_cast<const BgmChangerEntity&>(*gimmick);
            return bgmChanger.bgm;
        }
        return s3d::none;
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
    void Stage::setManager(Manager* pManager)
    {
        m_pManager = pManager;
    }
    bool Stage::initBackGround(BackGround& backGround)const
    {
        if (!m_stageData) {
            return false;
        }
        auto service = m_stageData->getBackGroundService();
        if (!service) {
            return false;
        }
        BackGroundTranslator translator;
        for (const auto& entity : service->getBgs()) {
            backGround.add(translator.toVM(entity));
        }

        backGround.setBgColor(service->getBgColor());
        return true;
    }
    bool Stage::restart() const
    {
        auto save = m_pManager->getModule<Save>();
        auto restartId = save->getRestartId().value_or(0);
        return this->init(restartId);
    }
    bool Stage::init(
        const std::shared_ptr<Actor::ActorObj>& player,
        const std::shared_ptr<Event::IEvent>& readyEvent
    ) const {
        bool result = true;
        // Readyイベント開始
        if(readyEvent) {
            auto events = m_pManager->getModule<Events>();
            events->regist(readyEvent);
            events->init();
        }

        s3d::Optional<RoomModel> nextRoom;
        // World初期化
        {
            // プレイヤーを登録
            auto* playerManager = m_pManager->getModule<Actor::Player::PlayerManager>();
            playerManager->regist(player);

            auto world = m_pManager->getModule<World>();
            world->create<Actor::God::Builder>();
            world->regist(player);
            if (nextRoom = this->findRoom(playerManager->getPos())) {
                result &= this->initRoom(*world, *nextRoom, BuildTiming::All);
            } else {
                result = false;
            }
        }
        // カメラの初期化
        auto camera = m_pManager->getModule<Camera>();
        if (nextRoom) {
            camera->setRoom(*nextRoom);
            camera->update();
        }
        // 背景の初期化
        {
            auto backGround = m_pManager->getModule<BackGround>();
            result &= this->initBackGround(*backGround);
        }
        // 装飾の初期化
        {
            auto decor = m_pManager->getModule<Decors>();
            decor->setGraphics(std::make_shared<DecorGraphics>(m_stageData->getDecorService()));
            if (nextRoom) {
                result &= this->initDecor(*decor, *nextRoom);
            } else {
                result = false;
            }
        }

        // バブルエフェクト開始
        {
            auto cron = m_pManager->getModule<Crons>();
            cron->create<Cron::BubbleGenerator::BuildIntervalTime>(3s);
        }
        auto save = m_pManager->getModule<Save>();
        auto sound = m_pManager->getModule<Sound>();
        // サウンド初期化
        if (nextRoom) {
            if (auto bgm = ::NextBgm(*nextRoom, m_stageData->getGimmicks())) {
                sound->play(*bgm);
            } else if (auto restartBgm = save->getRestartBgm()) {
                sound->play(*restartBgm);
            }
        }
        // 初期情報をリスタート情報として残す
        save->setRestartInfo(save->getRestartId().value_or(0), sound->currentBgmPath());

        // UI初期化
        {
            m_pManager->getModule<UIs>()->flush();
        }
        return result;
    }
    bool Stage::init(s3d::int32 startId) const
    {
        auto initStartPos = m_startPos.find(startId);
        if (!initStartPos) {
            return false;
        }
        auto player = std::make_shared<Actor::ActorObj>();
        Actor::Player::Builder::Build(player.get(), *initStartPos);

        auto readyEvent = std::make_shared<Event::IEvent>();
        Event::GameReady::Builder::Build(readyEvent.get());
        return this->init(player, readyEvent);
    }

    bool Stage::checkOut() const
    {
        auto camera = m_pManager->getModule<Camera>();
        bool result = true;
        // World CheckOut
        {
            auto world = m_pManager->getModule<World>();
            world->onCheckOut();
            if (const auto& nextRoom = camera->nextRoom()) {
                result &= this->initRoom(*world, *nextRoom, BuildTiming::CheckOut);
            } else {
                result = false;
            }
        }


        // 装飾のリセット
        {
            auto decor = m_pManager->getModule<Decors>();
            decor->onCheckOut();
            if (const auto& nextRoom = camera->nextRoom()) {
                result &= this->initDecor(*decor, *nextRoom);
            } else {
                result = false;
            }
        }
        // サウンドが変わる場合は停止
        auto sound = m_pManager->getModule<Sound>();
        if (auto bgm = ::NextBgm(*camera->nextRoom(), m_stageData->getGimmicks()); bgm && *bgm != sound->currentBgmPath()) {
            sound->stop();
        }
        return result;
    }

    bool Stage::checkIn() const
    {
        // Decor CheckIn
        {
            auto decor = m_pManager->getModule<Decors>();
            decor->onCheckIn();
        }
        // World CheckIn
        auto world = m_pManager->getModule<World>();
        world->onCheckIn();

        auto camera = m_pManager->getModule<Camera>();
        const auto& room = camera->getCurrentRoom();
        auto sound = m_pManager->getModule<Sound>();
        if (auto bgm = ::NextBgm(room, m_stageData->getGimmicks())) {
            sound->play(*bgm);
        }
        // セーブ予約があった場合はリスタート地点の保存をする
        auto save = m_pManager->getModule<Save>();
        if (auto reservedRestartId = save->popReservedRestartId()) {
            save->setRestartInfo(*reservedRestartId, sound->currentBgmPath());
        }
        return this->initRoom(*world, room, BuildTiming::CheckIn);
    }

    bool Stage::initDecor(Decors& decor, const RoomModel& nextRoom) const
    {
        auto decorService = m_stageData->getDecorService();
        if (!decorService) {
            return false;
        }
        Decor::DecorTranslator m_translator;
        auto idTable = decor.getIdTable();

        for (const auto& entity : decorService->getDecors()) {
            if (!entity) {
                continue;
            }
            if (!DecorBuildUtil::IsInScreen(*entity, nextRoom.getRegion())) {
                continue;
            }
            if (idTable[entity->type.categoryId()].contains(entity->id)) {
                // すでに生成済みなら引継ぎする
                idTable[entity->type.categoryId()][entity->id]->setBufferLayer(decor.getBufferLayer());
            } else {
                m_translator.build(decor, *entity);
            }
        }

        for (const auto& tileMap : decorService->getTileMap(nextRoom.getRegion())) {
            m_translator.build(decor, tileMap);
        }
        decor.flush();
        return true;
    }
    bool Stage::initRoom(World& world, const RoomModel& nextRoom, BuildTiming buildTiming) const
    {
        if (!m_stageData) {
            return false;
        }
        bool isCheckIn = (static_cast<int8>(buildTiming) & static_cast<int8>(BuildTiming::CheckIn)) != 0;
        bool isCheckOut = (static_cast<int8>(buildTiming) & static_cast<int8>(BuildTiming::CheckOut)) != 0;

        if (isCheckIn) {
            // マップの生成
            MapTranslator mapTranslator{};
            for (const auto& map : m_stageData->getMaps()) {
                if (!nextRoom.getRegion().intersects(RectF(map->pos - map->size / 2.0, map->size))) {
                    continue;
                }
                mapTranslator.buildActor(world, *map);
            }
        }

        if (isCheckOut) {
            // ギミックの生成
            GimmickTranslator gimmickTranslator(this);
            for (const auto& gimmick : m_stageData->getGimmicks()) {
                if (!nextRoom.getRegion().intersects(gimmick->pos)) {
                    continue;
                }
                gimmickTranslator.buildActor(world, *gimmick);
            }
        }

        if (isCheckIn) {
            // エネミーの生成
            EnemyTranslator enemyTranslator{};
            for (const auto& enemy : m_stageData->getEnemies()) {
                if (!nextRoom.getRegion().intersects(enemy->pos)) {
                    continue;
                }
                enemyTranslator.buildActor(world, *enemy);
            }
        }
        world.flush();
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
    std::shared_ptr<StageData> Stage::lockStageData() const
    {
        return m_stageData;
    }
}