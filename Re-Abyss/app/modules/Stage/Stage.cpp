#include <abyss/modules/Stage/Stage.hpp>

#include <Siv3D.hpp>

#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

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
#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/Temporary/RestartInfo/RestartInfo.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Env/Environment.hpp>

#include <abyss/entities/Room/RoomEntity.hpp>
#include <abyss/entities/Actor/Gimmick/StartPosEntity.hpp>
#include <abyss/entities/Actor/Gimmick/BgmChangerEntity.hpp>
#include <abyss/entities/Actor/Land/LandEntity.hpp>
#include <abyss/entities/Actor/Enemy/EnemyEntity.hpp>
#include <abyss/entities/Actor/Item/ItemEntity.hpp>
#include <abyss/entities/BackGround/BackGroundEntity.hpp>
#include <abyss/entities/Decor/DecorEntity.hpp>

#include <abyss/translators/Room/RoomTranslator.hpp>
#include <abyss/translators/Actor/Land/LandTranslator.hpp>
#include <abyss/translators/Actor/Enemy/EnemyTranslator.hpp>
#include <abyss/translators/Actor/Gimmick/GimmickTranslator.hpp>
#include <abyss/translators/Actor/Item/ItemTranslator.hpp>
#include <abyss/translators/BackGround/BackGroundTranslator.hpp>
#include <abyss/translators/Decor/DecorTranslator.hpp>

#include <abyss/services/BackGround/base/IBackGroundService.hpp>

namespace
{
    using namespace abyss;

    Optional<Room::RoomData> GetNextRoom(const s3d::Vec2& pos, const s3d::Array<RoomEntity>& rooms)
    {
        for (const auto& room : rooms) {
            if (room.region.intersects(pos)) {
                return RoomTranslator::ToModel(room);
            }
        }
        return s3d::none;
    }

    StartPosListModel GetStartPosList(const s3d::Array<std::shared_ptr<Actor::Gimmick::GimmickEntity>>& gimmicks)
    {
        StartPosListModel ret;

        for (const auto& gimmick : gimmicks) {
            if (gimmick->type != Actor::Gimmick::GimmickType::StartPos) {
                continue;
            }
            const auto& startPos = static_cast<const Actor::Gimmick::StartPosEntity&>(*gimmick);
            StartPosModel model{ startPos.startId, startPos.pos, startPos.forward, startPos.isSave };
            ret.add(model);
        }
        return ret;
    }
    Optional<FilePath> NextBgm(const Room::RoomData& nextRoom, const s3d::Array<std::shared_ptr<Actor::Gimmick::GimmickEntity>>& gimmicks)
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
    Stage::Stage()
    {}

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
        return true;
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

        // World初期化
        {
            auto world = m_pManager->getModule<World>();
            if (!this->initWorld(*world, *nextRoom, BuildTiming::All)) {
                return false;
            }
        }

        // カメラの初期化
        {
            auto camera = m_pManager->getModule<Camera>();
            camera->update(0);
        }

        // 背景の初期化
        {
            auto backGround = m_pManager->getModule<BackGround>();
            if (!this->initBackGround(*backGround)) {
                return false;
            }
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

            // Fog
            if (auto fog = env->getFog()) {
                fog->setFogColor(m_stageData->getAttributeService()->getBgColor())
                    .setFogFactor(2.0);
            }
        }
        // サウンド初期化
        {
            auto temporary = m_pManager->getModule<Temporary>();
            auto sound = m_pManager->getModule<Sound>();
            if (auto&& bgm = ::NextBgm(*nextRoom, m_stageData->getGimmicks())) {
                sound->play(*bgm);
            } else if (auto&& restartBgm = temporary->getRestartBgm()) {
                sound->play(*restartBgm);
            }

            // 初期情報をリスタート情報として残す
            temporary->setRestartInfo(temporary->getRestartId().value_or(0), sound->currentBgmPath());
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
        if (!nextRoom) {
            return false;
        }
        // チェックアウト時にはルーム移動で消えるフラグを消す
        m_pManager->getModule<Temporary>()->clearFlag(TempLevel::Room);

        // World CheckOut
        {
            auto world = m_pManager->getModule<World>();
            world->onCheckOut();
            if (!this->initWorld(*world, *nextRoom, BuildTiming::CheckOut)) {
                return false;
            }
        }


        // 装飾のリセット
        {
            auto decor = m_pManager->getModule<Decors>();
            decor->onCheckOut();
            if (!this->initDecor(*decor, *nextRoom)) {
                return false;
            }
        }

        // サウンドが変わる場合は停止
        {
            auto sound = m_pManager->getModule<Sound>();
            if (auto bgm = ::NextBgm(*roomManager->nextRoom(), m_stageData->getGimmicks());bgm && *bgm != sound->currentBgmPath()) {
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

        // World CheckIn
        auto world = m_pManager->getModule<World>();
        {
            world->onCheckIn();
        }

        auto roomManager = m_pManager->getModule<RoomManager>();
        const auto& room = roomManager->currentRoom();

        // Light
        {
            m_pManager->getModule<Light>()->setNextColor(room.getLightColor());
        }

        // Sound
        auto sound = m_pManager->getModule<Sound>();
        {
            if (auto bgm = ::NextBgm(room, m_stageData->getGimmicks())) {
                sound->play(*bgm);
            }
        }

        // セーブ予約があった場合はリスタート地点の保存をする
        {
            auto temporary = m_pManager->getModule<Temporary>();
            if (auto reservedRestartId = temporary->popReservedRestartId()) {
                temporary->setRestartInfo(*reservedRestartId, sound->currentBgmPath());
            }
        }

        return this->initWorld(*world, room, BuildTiming::CheckIn);
    }

    bool Stage::initDecor(Decors& decor, const Room::RoomData& nextRoom) const
    {
        auto decorService = m_stageData->getDecorService();
        if (!decorService) {
            return false;
        }
        Decor::DecorTranslator m_translator;
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
                if(auto&& obj = m_translator.build(decor, *entity)){
                    obj->setDeployId(entity->id);
                }
            }
        }

        for (const auto& tileMap : decorService->getTileMap(nextRoom.getRegion())) {
            m_translator.build(decor, tileMap);
        }
        decor.flush();
        return true;
    }
    bool Stage::initWorld(World& world, const Room::RoomData& nextRoom, BuildTiming buildTiming) const
    {
        if (!m_stageData) {
            return false;
        }
        bool isCheckIn = (static_cast<int8>(buildTiming) & static_cast<int8>(BuildTiming::CheckIn)) != 0;
        bool isCheckOut = (static_cast<int8>(buildTiming) & static_cast<int8>(BuildTiming::CheckOut)) != 0;

        if (isCheckIn) {
            // マップの生成
            Actor::Land::LandTranslator landTranslator{};
            for (const auto& land : m_stageData->getLands()) {
                if (!nextRoom.getRegion().intersects(RectF(land->pos - land->size / 2.0, land->size))) {
                    continue;
                }
                landTranslator.buildActor(world, *land);
            }
        }

        if (isCheckOut) {
            // ギミックの生成
            Actor::Gimmick::GimmickTranslator gimmickTranslator{};
            for (const auto& gimmick : m_stageData->getGimmicks()) {
                if (!nextRoom.getRegion().intersects(gimmick->pos)) {
                    continue;
                }
                gimmickTranslator.buildActor(world, *gimmick);
            }
        }

        if (isCheckIn) {
            // エネミーの生成
            Actor::Enemy::EnemyTranslator enemyTranslator{};
            for (const auto& enemy : m_stageData->getEnemies()) {
                if (!nextRoom.getRegion().intersects(enemy->pos)) {
                    continue;
                }
                enemyTranslator.buildActor(world, *enemy);
            }
        }

        if (isCheckIn) {
            // アイテムの生成
            Actor::Item::ItemTranslator itemTranslator{};
            for (const auto& item : m_stageData->getItems()) {
                if (!nextRoom.getRegion().intersects(item->pos)) {
                    continue;
                }
                itemTranslator.buildActor(world, *item);
            }
        }

        // @note なぜ必要か忘れた
        // ないほうが嬉しいのでひとまずコメント
        //world.flush();
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
