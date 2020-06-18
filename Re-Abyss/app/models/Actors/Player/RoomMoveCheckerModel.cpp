#include "RoomMoveCheckerModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>

#include <abyss/controllers/Event/Events.hpp>
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/controllers/Stage/Stage.hpp>

#include <abyss/controllers/Event/RoomMove/BasicMove/BasicMove.hpp>

namespace abyss::Player
{
    RoomMoveCheckerModel::RoomMoveCheckerModel(IActor* pActor):
        m_pActor(pActor)
    {}
    void RoomMoveCheckerModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
    }
    void RoomMoveCheckerModel::onLastUpdate([[maybe_unused]]double dt)
    {
        if (m_pActor->isDestroyed()) {
            // 死んでたらやらない
            return;
        }
        auto pos = m_body->getPos();
        auto camera = m_pActor->getModule<Camera>();
        if (camera->canNextRoom(pos)) {
            if (auto nextRoom = m_pActor->getModule<Stage>()->findRoom(pos)) {
                camera->setNextRoom(*nextRoom);
                m_pActor->getModule<Events>()->regist(Event::RoomMove::BasicMove::Create(*camera, pos));
            }
        }
    }
}
