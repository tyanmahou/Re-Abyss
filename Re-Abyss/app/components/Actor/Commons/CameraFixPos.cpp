#include "CameraFixPos.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>

namespace abyss::Actor
{
    CameraFixPos::CameraFixPos(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void CameraFixPos::onStart()
    {
        m_body = m_pActor->find<Body>();
    }

    void CameraFixPos::onLastUpdate()
    {
        auto roomManager = m_pActor->getModule<RoomManager>();
        auto prevPos = m_body->getPos();
        m_body->setPos(roomManager->fixPos(prevPos));
    }
}
