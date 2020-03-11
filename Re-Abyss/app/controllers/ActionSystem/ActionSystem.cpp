#include "ActionSystem.hpp"
#include <abyss/models/Stage/StageModel.hpp>
#include <abyss/models/actors/Player/PlayerActor.hpp>
#include <abyss/views/Camera/CameraView.hpp>

namespace abyss
{
    ActionSystem::ActionSystem()
    {
        s_main = this;
    }

    ActionSystem::ActionSystem(std::unique_ptr<StageModel> && stage):
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
            auto screen = cameraView.screenRegion();
            const auto& cameraPos = cameraView.getCameraPos();

            //// 背景
            //m_stageView->drawBg(cameraPos);

            //// back
            //m_stageView->drawLayer(U"back", screen);

            //m_cameraView->drawDeathLine();
            //// map
            //m_stageView->drawLayer(U"map", screen);
            //// door
            //m_stageView->drawLayer(U"door", screen);

            m_world.draw();

            ////front
            //m_stageView->drawLayer(U"front", screen);

            //m_bubbles.draw();

            cameraView.drawCameraWork();
        }
    }
    void ActionSystem::setStage(std::unique_ptr<StageModel>&& stage)
    {
        m_stage = std::move(stage);
    }
    ActionSystem* const ActionSystem::Main()
    {
        return s_main;
    }
    Camera* const ActionSystem::MainCamera()
    {
        return s_main ? &s_main->m_camera: nullptr;
    }
}
