#include "ActionSystem.hpp"
#include <abyss/controllers/Stage/Stage.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/views/Camera/CameraView.hpp>
#include <abyss/views/Stage/base/IStageView.hpp>

#include <abyss/controllers/Event/Talk/base/Serif.hpp>
#include <abyss/controllers/Event/Talk/base/FaceManager.hpp>

namespace abyss
{
    ActionSystem::ActionSystem()
    {
        m_manager
            .set(&m_camera)
            .set(&m_light)
            .set(&m_world);
        m_world.setManager(&m_manager);
    }

    ActionSystem::ActionSystem(const std::shared_ptr<Stage>& stage) :
        ActionSystem()
    {
        m_stage = stage;
    }
    ActionSystem::~ActionSystem()
    {
    }

    void ActionSystem::init()
    {
        if (auto room = m_stage->init(m_world)) {
            m_camera.setRoom(*room);
        }
        m_stage->initDecor(m_camera);
    }

    void ActionSystem::update()
    {
        m_light.clear();

        if (!m_camera.isCameraWork()) {
            m_world.update();
        }
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
    
    Event::Talk::Serif GetSerif()
    {
        using namespace Event::Talk;
        SerifModel model;
        model.setSide(SerifModel::Side::Right);
        model.setActorName(U"?");
        model.addMessage(U"ようこそ！わらわの第一研究施設へ");
        model.addMessage(U"じゃが、ここに来たということは…\nそちも、あの女を追うものということ");
        model.addMessage(U"心苦しいが\nただで返すわけにはいかんのぉ…\nあああああ");
        Serif ret;
        ret.setModel(std::move(model));
        auto face = std::make_shared<FaceManager>();
        face->add(U"?", U"actors/CodeZero/face.json");
        ret.setFaceManager(face);
        return ret;
    }
    void ActionSystem::draw() const
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
        static Event::Talk::Serif s = GetSerif();
        s.update();
        s.draw();
    }
    void ActionSystem::setStage(std::unique_ptr<Stage>&& stage)
    {
        m_stage = std::move(stage);
    }
}
