#include <abyss/modules/Stage/Stage.hpp>

#include <Siv3D.hpp>

#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

#include <abyss/components/Actor/God/Builder.hpp>
#include <abyss/components/Actor/Player/Builder.hpp>
#include <abyss/components/Cron/BubbleGenerator/Builder.hpp>
#include <abyss/components/Event/GameReady/Builder.hpp>

#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/Decor/Decors.hpp>
#include <abyss/modules/Decor/DecorGraphics.hpp>
#include <abyss/modules/Decor/DecorBuildUtil.hpp>
#include <abyss/modules/Stage/StageData.hpp>
#include <abyss/modules/Stage/StageTranslator.hpp>
#include <abyss/modules/Cron/Crons.hpp>
#include <abyss/modules/Sound/Sounds.hpp>
#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/Temporary/RestartInfo/RestartInfo.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Fade/Fader.hpp>
#include <abyss/modules/FieldEnv/Environment.hpp>

#include <abyss/entities/Room/RoomEntity.hpp>
#include <abyss/entities/Actor/Gimmick/StartPosEntity.hpp>
#include <abyss/entities/Actor/Gimmick/BgmChangerEntity.hpp>
#include <abyss/entities/Actor/Land/LandEntity.hpp>
#include <abyss/entities/Actor/Enemy/EnemyEntity.hpp>
#include <abyss/entities/Actor/Item/ItemEntity.hpp>
#include <abyss/entities/Decor/DecorEntity.hpp>

namespace
{
    using namespace abyss;

    Room::RoomData ToModel(const RoomEntity& entity)
    {
        return Room::RoomData(entity.region, entity.passbleBits, entity.lightColor);
    }

    Optional<Room::RoomData> GetNextRoom(const s3d::Vec2& pos, const s3d::Array<RoomEntity>& rooms)
    {
        for (const auto& room : rooms) {
            if (room.region.intersects(pos)) {
                return ToModel(room);
            }
        }
        return s3d::none;
    }

    StartPosContainer GetStartPosList(const s3d::Array<std::shared_ptr<Actor::Gimmick::GimmickEntity>>& gimmicks)
    {
        StartPosContainer ret;

        for (const auto& gimmick : gimmicks) {
            if (gimmick->type != Actor::Gimmick::GimmickType::StartPos) {
                continue;
            }
            const auto& startPos = static_cast<const Actor::Gimmick::StartPosEntity&>(*gimmick);
            StartPos entry{ startPos.startId, startPos.pos, startPos.forward, startPos.isSave };
            ret.add(entry);
        }
        return ret;
    }
    Optional<Sound::SoundLabel> NextBgm(const Room::RoomData& nextRoom, const s3d::Array<std::shared_ptr<Actor::Gimmick::GimmickEntity>>& gimmicks)
    {
        for (const auto& gimmick : gimmicks) {
            if (gimmick->type != Actor::Gimmick::GimmickType::BgmChanger) {
                continue;
            }
            if (!nextRoom.getRegion().intersects(gimmick->pos)) {
                continue;
            }

            const auto& bgmChanger = static_cast<const Actor::Gimmick::BgmChangerEntity&>(*gimmick);
            return bgmChanger.bgm;
        }
        return s3d::none;
    }
}
namespace abyss
{
    Stage::Stage(const std::shared_ptr<StageData>& stageData):
        m_stageData(stageData)
    {
        if (!m_stageData) {
            return;
        }
        m_startPos = GetStartPosList(m_stageData->getGimmicks());
    }

    Stage::~Stage()
    {}

    s3d::Optional<Room::RoomData> Stage::findRoom(const s3d::Vec2& pos)const
    {
        return ::GetNextRoom(pos, m_stageData->getRooms());
    }
    void Stage::setManager(Manager* pManager)
    {
        m_pManager = pManager;
    }
    bool Stage::init() const
    {
        auto* playerManager = m_pManager->getModule<Actor::Player::PlayerManager>();
        s3d::Optional<Room::RoomData> nextRoom = this->findRoom(playerManager->getPos());
        if (!nextRoom) {
            return false;
        }

        // Room初期化
        {
            auto roomManager = m_pManager->getModule<RoomManager>();
            roomManager->setRoom(*nextRoom);
            roomManager->init();
        }

        // Actor初期化
        {
            auto actors = m_pManager->getModule<Actors>();
            if (!this->initActor(*actors, *nextRoom, BuildTiming::All)) {
                return false;
            }
        }

        // カメラの初期化
        {
            auto camera = m_pManager->getModule<Camera>();
            camera->update(0);
        }

        // 装飾の初期化
        {
            auto decor = m_pManager->getModule<Decors>();
            decor->setGraphics(std::make_shared<Decor::DecorGraphics>(m_stageData->getDecorService()));

            if (!this->initDecor(*decor, *nextRoom)) {
                return false;
            }
        }

        // Light
        {
            auto* light = m_pManager->getModule<Light>();

            // デフォルトライトカラー設定
            light->setDefaultColor(m_stageData->getAttributeService()->getBgColor());
            light->initColor(nextRoom->getLightColor());
        }
        // Env
        {
            auto* env = m_pManager->getModule<Environment>();
            const auto bgColor = m_stageData->getAttributeService()->getBgColor();

            env->setThemeColor(bgColor);

            // Bg
            env->getBg()->setColor(bgColor);

            // Fog
            if (auto fog = env->getFog()) {
                fog->setFogColor(bgColor)
                    .setFogFactor(2.0);
            }

            // Fader
            {
                auto* fader = m_pManager->getModule<Fader>();
                fader->setDefaultColor(bgColor);
            }
        }
        // サウンド初期化
        {
            auto temporary = m_pManager->getModule<Temporary>();
            auto sound = m_pManager->getModule<Sounds>();
            if (auto&& bgm = ::NextBgm(*nextRoom, m_stageData->getGimmicks())) {
                sound->play(*bgm);
            } else if (auto&& restartBgm = temporary->getRestartBgm()) {
                sound->play(*restartBgm);
            }

            // 初期情報をリスタート情報として残す
            temporary->setRestartInfo(temporary->getRestartId().value_or(0), sound->currentBgmLabel());
        }

        // UI初期化
        {
            m_pManager->getModule<UIs>()->flush();
        }
        return true;
    }

    bool Stage::checkOut() const
    {
        auto roomManager = m_pManager->getModule<RoomManager>();
        const auto& nextRoom = roomManager->nextRoom();
        // チェックアウト時にはルーム移動で消えるフラグを消す
        m_pManager->getModule<Temporary>()->clearFlag(TempLevel::Room);

        // Actor CheckOut
        {
            auto actors = m_pManager->getModule<Actors>();
            actors->onCheckOut();

            if (nextRoom) {
                if (!this->initActor(*actors, *nextRoom, BuildTiming::CheckOut)) {
                    return false;
                }
            }
        }


        // 装飾のリセット
        {
            auto decor = m_pManager->getModule<Decors>();
            decor->onCheckOut();
            if (nextRoom) {
                if (!this->initDecor(*decor, *nextRoom)) {
                    return false;
                }
            }
        }

        // サウンドが変わる場合は停止
        if (nextRoom) {
            auto sound = m_pManager->getModule<Sounds>();
            if (auto bgm = ::NextBgm(*nextRoom, m_stageData->getGimmicks());bgm && bgm != sound->currentBgmLabel()) {
                sound->stop();
            }
        }
        return true;
    }

    bool Stage::checkIn() const
    {
        // Decor CheckIn
        {
            auto decor = m_pManager->getModule<Decors>();
            decor->onCheckIn();
        }

        // Actor CheckIn
        auto actors = m_pManager->getModule<Actors>();
        {
            actors->onCheckIn();
        }

        auto roomManager = m_pManager->getModule<RoomManager>();
        const auto& room = roomManager->currentRoom();

        // Light
        {
            m_pManager->getModule<Light>()->setNextColor(room.getLightColor());
        }

        // Sound
        auto sound = m_pManager->getModule<Sounds>();
        {
            if (auto bgm = ::NextBgm(room, m_stageData->getGimmicks())) {
                sound->play(*bgm);
            }
        }

        // セーブ予約があった場合はリスタート地点の保存をする
        {
            auto temporary = m_pManager->getModule<Temporary>();
            if (auto reservedRestartId = temporary->popReservedRestartId()) {
                temporary->setRestartInfo(*reservedRestartId, sound->currentBgmLabel());
            }
        }

        return this->initActor(*actors, room, BuildTiming::CheckIn);
    }

    bool Stage::initDecor(Decors& decor, const Room::RoomData& nextRoom) const
    {
        auto decorService = m_stageData->getDecorService();
        if (!decorService) {
            return false;
        }
        auto&& deloyIds = decor.getDeployIds();

        for (const auto& entity : decorService->getDecors()) {
            if (!entity) {
                continue;
            }
            if (!DecorBuildUtil::IsInScreen(*entity, nextRoom.getRegion())) {
                continue;
            }
            if (deloyIds.contains(entity->id)) {
                // すでに生成済みなら引継ぎする
                deloyIds[entity->id]->setBufferLayer(decor.getBufferLayer());
            } else {
                if(auto&& obj = StageTranslator::Build(decor, *entity)){
                    obj->setDeployId(entity->id);
                }
            }
        }

        for (const auto& tileMap : decorService->getTileMap(nextRoom.getRegion())) {
            StageTranslator::Build(decor, tileMap);
        }
        decor.flush();
        return true;
    }
    bool Stage::initActor(Actors& actors, const Room::RoomData& nextRoom, BuildTiming buildTiming) const
    {
        if (!m_stageData) {
            return false;
        }
        bool isCheckIn = (static_cast<int8>(buildTiming) & static_cast<int8>(BuildTiming::CheckIn)) != 0;
        bool isCheckOut = (static_cast<int8>(buildTiming) & static_cast<int8>(BuildTiming::CheckOut)) != 0;

        if (isCheckIn) {
            // マップの生成
            for (const auto& land : m_stageData->getLands()) {
                if (!nextRoom.getRegion().intersects(RectF(land->pos - land->size / 2.0, land->size))) {
                    continue;
                }
                StageTranslator::Build(actors, *land);
            }
        }

        if (isCheckOut) {
            // ギミックの生成
            for (const auto& gimmick : m_stageData->getGimmicks()) {
                if (!nextRoom.getRegion().intersects(gimmick->pos)) {
                    continue;
                }
                StageTranslator::Build(actors, *gimmick);
            }
        }

        if (isCheckIn) {
            // エネミーの生成
            for (const auto& enemy : m_stageData->getEnemies()) {
                if (!nextRoom.getRegion().intersects(enemy->pos)) {
                    continue;
                }
                StageTranslator::Build(actors, *enemy);
            }
        }

        if (isCheckIn) {
            // アイテムの生成
            for (const auto& item : m_stageData->getItems()) {
                if (!nextRoom.getRegion().intersects(item->pos)) {
                    continue;
                }
                StageTranslator::Build(actors, *item);
            }
        }

        return true;
    }
    s3d::String Stage::mapName() const
    {
        return m_stageData->getMapName();
    }
    s3d::Optional<StartPos> Stage::findStartPos(const s3d::int32 startId)const
    {
        return m_startPos.find(startId);
    }
}
