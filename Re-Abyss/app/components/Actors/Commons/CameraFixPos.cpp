#include "CameraFixPos.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>

namespace abyss::Actor
{
    CameraFixPos::CameraFixPos(IActor* pActor):
        m_pActor(pActor)
    {}

    void CameraFixPos::onStart()
    {
        m_body = m_pActor->find<Body>();
    }

    void CameraFixPos::onLastUpdate()
    {
        auto camera = m_pActor->getModule<Camera>();
        auto prevPos = m_body->getPos();
        m_body->setPos(camera->fixPos(prevPos));
    }
}
