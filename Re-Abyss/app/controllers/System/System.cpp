#include "System.hpp"
#include <abyss/controllers/Stage/Stage.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/services/Event/Talk/TalkService.hpp>
#include <abyss/commons/Constants.hpp>

#include <abyss/controllers/BackGround/BackGround.hpp>
#include <abyss/controllers/Decor/Decor.hpp>

#include <abyss/controllers/Cron/Cron.hpp>
#include <abyss/controllers/Cron/BubbleGenerator/BubbleGeneratorJob.hpp>

namespace abyss
{
    System::System():
        m_stage(std::make_unique<Stage>()),
        m_backGround(std::make_unique<BackGround>()),
        m_decor(std::make_unique<Decor>()),
        m_cron(std::make_unique<Cron>())
    {
        m_manager
            .set(&m_time)
            .set(&m_camera)
            .set(&m_light)
            .set(&m_world)
            .set(&m_events)
            .set(&m_effects)
            .set(&m_sound)
            .set(&m_userInterface)
            ;
        m_world.setManager(&m_manager);
        m_camera.setManager(&m_manager);
        m_events.setManager(&m_manager);
        m_sound.setManager(&m_manager);
        m_userInterface.setManager(&m_manager);
        m_effects.init(m_time);
        m_cron->setManager(&m_manager);

        m_cron->create<cron::BubbleGenerator::BubbleGeneratorJob>(3s);
    }
    System::~System()
    {
    }

    void System::init()
    {
        m_stage->setup(&m_manager);

        if (auto room = m_stage->init(m_world)) {
            m_camera.setRoom(*room);
        }
        m_stage->initBackGround(*m_backGround);
        m_stage->initDecorGraphics(*m_decor);
        m_stage->initDecor(*m_decor, m_camera);
    }

    void System::init(const std::shared_ptr<Player::PlayerActor>& player)
    {
        m_stage->setup(&m_manager);

        if (auto room = m_stage->init(m_world, player)) {
            m_camera.setRoom(*room);
        }
        m_stage->initBackGround(*m_backGround);
        m_stage->initDecorGraphics(*m_decor);
        m_stage->initDecor(*m_decor, m_camera);
    }

    void System::update()
    {
        m_time.update();
        m_light.clear();

        double dt = m_time.deltaTime();
        m_world.updateDeltaTime(dt);

        if (!m_camera.isCameraWork() && m_events.isEmpty()) {
            m_world.update();
        }
        m_userInterface.update(dt);
        auto& player = *m_manager.getModule<Player::PlayerActor>();
        switch (auto event = m_camera.update(player)) {
            using enum Camera::Event;
        case OnCameraWorkStart:
        {
            // カメラワークが開始したらアクターのリセット
            m_world.reset();
            m_stage->initDecor(*m_decor, m_camera);
        }
        break;
        case OnCameraWorkEnd:
        {
            m_stage->initRoom(m_world, m_camera.getCurrentRoom());
        }
        break;
        case OnOutOfRoom:
        {
            const auto& pos = player.getPos();
            if (auto next = m_stage->findRoom(pos)) {
                m_camera.startCameraWork(*next, pos);
            }
        }
        break;
        case OnOutOfRoomDeath:
            break;
        default:
            break;
        }

        m_events.update(dt);
        m_decor->update(m_time.time());
        m_cron->update(dt);
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

            //m_light.draw(m_time.deltaTime(), cameraView);

            cameraView.drawCameraWork();
        }
        constexpr RectF blackBand{0, 0, Constants::GameScreenSize.x, Constants::GameScreenOffset.y};
        blackBand.draw(Palette::Black);
        
        m_events.draw();

        m_userInterface.draw();
    }
    void System::loadStage(const std::shared_ptr<StageData>& stageData)
    {
        m_stage->setStageData(stageData);
        m_stage->load();
    }
    std::shared_ptr<Player::PlayerActor> System::lockPlayer() const
    {
        return m_world.find<Player::PlayerActor>().lock();
    }
}
