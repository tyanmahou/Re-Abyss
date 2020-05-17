#include "System.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Stage/Stage.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/views/Stage/base/IStageView.hpp>
#include <abyss/services/Event/Talk/TalkService.hpp>
#include <abyss/commons/Constants.hpp>

#include <abyss/views/UI/BossHPBar/BossHPBarVM.hpp>

namespace abyss
{
    System::System()
    {
        m_manager
            .set(&m_camera)
            .set(&m_light)
            .set(&m_world)
            .set(&m_events)
            .set(&m_sound)
            .set(&m_userInterface)
            ;
        m_world.setManager(&m_manager);
        m_events.setManager(&m_manager);
        m_sound.setManager(&m_manager);
        m_userInterface.setManager(&m_manager);
    }

    System::System(const std::shared_ptr<Stage>& stage) :
        System()
    {
        m_stage = stage;
    }
    System::~System()
    {
    }

    void System::init()
    {
        if (auto room = m_stage->init(m_world)) {
            m_camera.setRoom(*room);
        }
        m_stage->initDecor(m_camera);
    }

    void System::init(const std::shared_ptr<Player::PlayerActor>& player)
    {
        if (auto room = m_stage->init(m_world, player)) {
            m_camera.setRoom(*room);
        }
        m_stage->initDecor(m_camera);
    }

    void System::update()
    {
        m_light.clear();

        double dt = WorldTime::DeltaTime();
        if (!m_camera.isCameraWork() && !m_events.update(dt)) {
            m_world.update(dt);
        }
        m_userInterface.update(dt);
        auto& player = *m_manager.getModule<Player::PlayerActor>();
        switch (auto event = m_camera.update(player)) {
            using enum Camera::Event;
        case OnCameraWorkStart:
        {
            // カメラワークが開始したらアクターのリセット
            m_world.reset();
            m_stage->initDecor(m_camera);
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
    }
    void System::draw() const
    {
        auto cameraView = m_camera.createView();

        // in camera
        {
            auto t2d = cameraView.getTransformer();

            auto* const stageView = m_stage->getView();

            // 背面
            stageView->drawBack(cameraView);
            cameraView.drawDeathLine();

            // 中面
            stageView->drawMiddle(cameraView);

            m_world.draw();

            // 全面
            stageView->drawFront(cameraView);

            //m_light.draw(cameraView);

            cameraView.drawCameraWork();
        }
        constexpr RectF blackBand{0, 0, Constants::GameScreenSize.x, Constants::GameScreenOffset.y};
        blackBand.draw(Palette::Black);
        if (m_events.isEmpty()) {
            m_userInterface.draw();
        } else {
            m_events.draw();
        }
        static ui::BossHPBarVM hpBar;
        static double hp = 10;
        if (KeyUp.down()) {
            hp++;
        } else if (KeyDown.down()) {
            hp--;
        }
        hpBar.setHp(hp).setMaxHp(10).draw();
    }
    void System::setStage(std::unique_ptr<Stage>&& stage)
    {
        m_stage = std::move(stage);
    }
    std::shared_ptr<Player::PlayerActor> System::lockPlayer() const
    {
        return m_world.find<Player::PlayerActor>().lock();
    }
}
