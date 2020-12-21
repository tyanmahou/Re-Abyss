#include "System.hpp"
#include <abyss/controllers/Master/Master.hpp>
#include <abyss/controllers/Stage/Stage.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/services/Event/Talk/TalkService.hpp>
#include <abyss/commons/Constants.hpp>

#include <abyss/controllers/BackGround/BackGround.hpp>
#include <abyss/controllers/Decor/Decor.hpp>

#include <abyss/controllers/Cron/Cron.hpp>
#include <abyss/controllers/Save/Save.hpp>

#include <abyss/debugs/DebugManager/DebugManager.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    System::System(IMasterObserver* masterObserver):
        m_master(std::make_unique<Master>(masterObserver)),
        m_stage(std::make_unique<Stage>()),
        m_backGround(std::make_unique<BackGround>()),
        m_decor(std::make_unique<Decor>()),
        m_cron(std::make_unique<Cron>()),
        m_save(std::make_unique<Save>()),
        m_playerManager(std::make_unique<Actor::Player::PlayerManager>())
    {
        m_manager
            .set(m_master.get())
            .set(&m_time)
            .set(&m_camera)
            .set(&m_light)
            .set(&m_world)
            .set(&m_events)
            .set(&m_effects)
            .set(&m_sound)
            .set(&m_userInterface)
            .set(m_backGround.get())
            .set(m_decor.get())
            .set(m_stage.get())
            .set(m_cron.get())
            .set(m_save.get())
            .set(m_playerManager.get())
            ;
        m_world.setManager(&m_manager);
        m_camera.setManager(&m_manager);
        m_events.setManager(&m_manager);
        m_userInterface.setManager(&m_manager);
        m_effects.init(m_time);
        m_stage->setManager(&m_manager);
        m_cron->setManager(&m_manager);
    }
    System::~System()
    {
    }

    void System::init()
    {
        m_stage->init();
    }

    void System::init(const std::shared_ptr<Actor::IActor>& player)
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
        m_light.clear();

        double dt = m_time.deltaTime();
        m_world.updateDeltaTime(dt);

        bool isWorldStop = m_events.isWorldStop();
        if (!isWorldStop) {
            m_world.update();
            m_world.move();
            m_world.physics();
        }
        m_camera.update();
        if (!isWorldStop) {
            m_world.collision();
            m_world.lastUpdate();
            m_world.cleanUp();
        }

        m_events.update(dt);
        m_userInterface.update(dt);
        m_decor->update(m_time.time());
        m_backGround->update(m_time.time());
        m_cron->update(dt);

#if ABYSS_DEBUG
        if (Debug::DebugManager::IsLogEffectNum()) {
            Debug::DebugManager::LogEffectNum(m_effects);
        }
#endif
        m_master->sendNotify();
    }
    void System::draw() const
    {
        auto cameraView = m_camera.createView();

        // in camera
        {
            auto t2d = cameraView.getTransformer();

            auto cameraScreen = m_camera.screenRegion();
            // 背面
            {
                m_backGround->draw(cameraView);
                m_backGround->drawWaterSarfaceBack(cameraView);
                m_effects.update<EffectGroup::DecorBack>();
                m_decor->drawBack(cameraScreen);
            }
            cameraView.drawDeathLine();
            

            // 中面
            m_decor->drawMiddle(cameraScreen);

            m_effects.update<EffectGroup::WorldBack>();
            m_world.draw();
            m_effects.update<EffectGroup::WorldFront>();

            // 全面
            m_decor->drawFront(cameraScreen);

            m_effects.update<EffectGroup::Bubble>();
            m_backGround->drawWaterSarfaceFront(cameraView);
            //m_light.draw(m_time.deltaTime(), cameraView);
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
    void System::loadSaveData(const std::shared_ptr<SaveData>& saveData)
    {
        m_save->setSaveData(saveData);
    }
    std::shared_ptr<Actor::IActor> System::lockPlayer() const
    {
        return m_playerManager->getActor().lock();
    }

}
