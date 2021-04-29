#include "System.hpp"
#include <abyss/modules/Master/Master.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/views/Camera/SnapshotView.hpp>
#include <abyss/commons/Constants.hpp>

#include <abyss/modules/BackGround/BackGround.hpp>
#include <abyss/modules/Decor/Decors.hpp>

#include <abyss/modules/Cron/Crons.hpp>
#include <abyss/modules/Save/Save.hpp>
#include <abyss/modules/DrawManager/DrawManager.hpp>

#include <abyss/debugs/DebugManager/DebugManager.hpp>
#include <abyss/debugs/Menu/Menu.hpp>
#include <Siv3D.hpp>

namespace abyss
{
    System::System(IMasterObserver* masterObserver) :
        m_master(std::make_unique<Master>(masterObserver)),
        m_stage(std::make_unique<Stage>()),
        m_backGround(std::make_unique<BackGround>()),
        m_decors(std::make_unique<Decors>()),
        m_crons(std::make_unique<Crons>()),
        m_save(std::make_unique<Save>()),
        m_playerManager(std::make_unique<Actor::Player::PlayerManager>()),
        m_drawer(std::make_unique<DrawManager>())
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
            .set(m_decors.get())
            .set(m_stage.get())
            .set(m_crons.get())
            .set(m_save.get())
            .set(m_playerManager.get())
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
        m_light.clear();

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
        m_camera.update();
        if (!isWorldStop) {
            m_world.collision();
            m_world.lastUpdate();
        }
        m_world.cleanUp();

        m_events.update();
        m_userInterface.update();
        m_decors->update();
        m_backGround->update(m_time.time());
        m_crons->update();

#if ABYSS_DEBUG
        Debug::DebugManager::DrawDebug(*m_decors);
        Debug::DebugManager::DrawDebug(m_effects);
#endif
        m_master->sendNotify();
    }
    void System::draw() const
    {
        auto cameraView = m_camera.createView();
        const auto& snapshot = m_camera.getSnapshot();
        // in camera
        {
            {
                auto postRender = snapshot.startPostRender();
                auto t2d = cameraView.getTransformer();
                {
                    auto sceneRender = snapshot.startSceneRender();
                    // 背面
                    {
                        m_backGround->draw(cameraView);
                        m_backGround->drawWaterSarfaceBack(cameraView);
                        m_effects.update<EffectGroup::DecorBack>();
                        m_decors->drawBack();
                    }
                    cameraView.drawDeathLine();

                    // 中面
                    m_decors->drawMiddle();

                    m_effects.update<EffectGroup::WorldBack>();
                    m_world.draw();
                    m_effects.update<EffectGroup::WorldFront>();

                    // 全面
                    m_decors->drawFront();

                    m_effects.update<EffectGroup::Bubble>();
                    m_backGround->drawWaterSarfaceFront(cameraView);
                }
                m_light.draw(snapshot.getSceneTexture(), m_time.time(), m_backGround->getBgColor());
            }
            // post effectなどあればここで
            snapshot.getPostTexture().draw(Constants::GameScreenOffset);
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
    std::shared_ptr<Actor::ActorObj> System::lockPlayer() const
    {
        return m_playerManager->getActor().lock();
    }

}
