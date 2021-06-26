#include "System.hpp"
#include <abyss/modules/Master/Master.hpp>
#include <abyss/modules/Stage/Stage.hpp>

#include <abyss/modules/Light/Light.hpp>
#include <abyss/modules/Distortion/Distortion.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/views/Camera/SnapshotView.hpp>
#include <abyss/commons/Constants.hpp>

#include <abyss/modules/BackGround/BackGround.hpp>
#include <abyss/modules/Decor/Decors.hpp>

#include <abyss/modules/Cron/Crons.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>

#include <abyss/debugs/DebugManager/DebugManager.hpp>
#include <abyss/debugs/Menu/Menu.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    System::System(IMasterObserver* masterObserver) :
        m_master(std::make_unique<Master>(masterObserver)),
        m_light(std::make_unique<Light>()),
        m_distortion(std::make_unique<Distortion>()),
        m_stage(std::make_unique<Stage>()),
        m_backGround(std::make_unique<BackGround>()),
        m_decors(std::make_unique<Decors>()),
        m_crons(std::make_unique<Crons>()),
        m_temporary(std::make_unique<Temporary>()),
        m_playerManager(std::make_unique<Actor::Player::PlayerManager>()),
        m_drawer(std::make_unique<DrawManager>())
    {
        m_manager
            .set(m_master.get())
            .set(&m_time)
            .set(&m_camera)
            .set(m_light.get())
            .set(m_distortion.get())
            .set(&m_world)
            .set(&m_events)
            .set(&m_effects)
            .set(&m_sound)
            .set(&m_userInterface)
            .set(m_backGround.get())
            .set(m_decors.get())
            .set(m_stage.get())
            .set(m_crons.get())
            .set(m_temporary.get())
            .set(m_playerManager.get())
            .set(m_drawer.get())
            ;
        m_world.setManager(&m_manager);
        m_camera.setManager(&m_manager);
        m_events.setManager(&m_manager);
        m_userInterface.setManager(&m_manager);
        m_effects.init(m_time);
        m_stage->setManager(&m_manager);
        m_decors->setManager(&m_manager);
        m_crons->setManager(&m_manager);
    }
    System::~System()
    {    }

    void System::init()
    {
        m_stage->init();
    }

    void System::init(const std::shared_ptr<Actor::ActorObj>& player)
    {
        m_stage->init(player, nullptr);
    }
    void System::restart()
    {
        m_stage->restart();
    }

    void System::update()
    {
        m_time.update();
        m_light->clear();
        m_distortion->clear();

        double dt = m_time.deltaTime();
        m_world.updateDeltaTime(dt);

        // フラッシュは常にする
        m_world.flush();
        m_decors->flush();

        bool isWorldStop = m_events.isWorldStop();
        if (!isWorldStop) {
            m_world.update();
            m_world.move();
            m_world.physics();
        }
        m_camera.update(dt);
        if (!isWorldStop) {
            m_world.collision();
            m_world.lastUpdate();
        }

        m_events.update();
        m_userInterface.update();
        m_decors->update();
        m_backGround->update(m_time.time());
        m_crons->update();

        m_world.cleanUp();
#if ABYSS_DEBUG
        Debug::DebugManager::DrawDebug(*m_decors);
        Debug::DebugManager::DrawDebug(m_effects);
#endif
        m_master->sendNotify();
    }
    void System::draw() const
    {
        m_drawer->clear();

        // Actor Draw
        m_world.draw();
        // Deor Draw
        m_decors->draw();

        auto cameraView = m_camera.createView();
        auto* snapshot = m_camera.getSnapshot();
        // in camera
        {
            auto sceneRender = snapshot->startSceneRender();
            auto t2d = cameraView.getTransformer();

            // 背面
            {
                m_backGround->draw(cameraView);
                m_backGround->drawWaterSarfaceBack(cameraView);
                m_effects.update<EffectGroup::DecorBack>();
                m_drawer->draw(DrawLayer::DecorBack);
            }
            cameraView.drawDeathLine();

            // 中面
            m_drawer->draw(DrawLayer::DecorMiddle);

            m_effects.update<EffectGroup::WorldBack>();
            m_drawer->draw(DrawLayer::World);
            m_effects.update<EffectGroup::WorldFront>();

            // 全面
            m_drawer->draw(DrawLayer::DecorFront);

            m_effects.update<EffectGroup::Bubble>();
            m_backGround->drawWaterSarfaceFront(cameraView);

            // Light Map更新
            m_light->render(m_time.time());
            // Distortion Map更新
            m_distortion->render();

#if ABYSS_DEBUG
            Debug::DebugManager::DrawDebug(m_world);
#endif
        }
        // PostEffect適用
        {
            snapshot->copySceneToPost()
#if ABYSS_DEBUG
                .apply(Debug::Menu::IsDebug(Debug::DebugFlag::PostEffectLight), [=] { return m_light->start(m_backGround->getBgColor()); })
#else
                .apply([=] { return m_light->start(m_backGround->getBgColor()); })
#endif 
#if ABYSS_DEBUG
                .apply(Debug::Menu::IsDebug(Debug::DebugFlag::PostEffectDistortion), [=] { return m_distortion->start(); })
#else
                .apply([=] { return m_distortion->start(); })
#endif
                .draw(cameraView.getQuakeOffset());
        }
        {
            constexpr RectF blackBand{ 0, 0, Constants::GameScreenSize.x, Constants::GameScreenOffset.y };
            blackBand.draw(Palette::Black);

            m_userInterface.draw();
        }
    }
    void System::loadStage(const std::shared_ptr<StageData>& stageData)
    {
        m_stage->setStageData(stageData);
        m_stage->load();
    }
    void System::loadTemporaryData(const std::shared_ptr<TemporaryData>& tempData)
    {
        m_temporary->setTemporaryData(tempData);
    }
    std::shared_ptr<Actor::ActorObj> System::lockPlayer() const
    {
        return m_playerManager->getActor().lock();
    }

}
