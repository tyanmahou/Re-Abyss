#include "ActionSystem.hpp"
#include <abyss/controllers/Stage/Stage.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/views/Stage/base/IStageView.hpp>

namespace abyss
{
    ActionSystem::ActionSystem()
    {
        s_main = this;
    }

    ActionSystem::ActionSystem(std::unique_ptr<Stage> && stage):
        ActionSystem()
    {
        m_stage = std::move(stage);
    }
    ActionSystem::~ActionSystem()
    {
        if (s_main == this) {
            s_main = nullptr;
        }
    }

    void ActionSystem::init()
    {
        if (auto room = m_stage->findRoom({ 480, 2000 })) {
        	m_stage->init(m_world, *room);
        	m_camera.setRoom(*room);
        }
    }

    void ActionSystem::update()
    {
        if (!m_camera.isCameraWork()) {
            m_world.update();
        }
        auto& player = *m_world.getPlayer();
        switch (auto event = m_camera.update(player)) {
            using enum Camera::Event;
        case OnCameraWorkStart:
        {
            // カメラワークが開始したらアクターのリセット
            m_world.reset(); 
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

    void ActionSystem::draw() const
    {
        auto cameraView = m_camera.createView();

        // in camera
        {
            auto t2d = cameraView.getTransformer();

            auto*const stageView = m_stage->getView();

            // 背面
            stageView->drawBack(cameraView);

            cameraView.drawDeathLine();

            // 中面
            stageView->drawMiddle(cameraView);

            m_world.draw();

            // 全面
            stageView->drawFront(cameraView);

            cameraView.drawCameraWork();
        }
    }
    void ActionSystem::setStage(std::unique_ptr<Stage>&& stage)
    {
        m_stage = std::move(stage);
    }
    ActionSystem* const ActionSystem::Main()
    {
        return s_main;
    }
    Camera* const ActionSystem::Camera()
    {
        return s_main ? &s_main->m_camera: nullptr;
    }
}
