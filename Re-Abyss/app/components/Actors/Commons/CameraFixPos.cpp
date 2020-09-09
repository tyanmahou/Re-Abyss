#include "CameraFixPos.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>

namespace abyss::Actor
{
    CameraFixPos::CameraFixPos(IActor* pActor):
        m_pActor(pActor)
    {}

    void CameraFixPos::setup()
    {
        m_body = m_pActor->find<BodyModel>();
    }

    void CameraFixPos::onLastUpdate()
    {
        auto camera = m_pActor->getModule<Camera>();
        auto prevPos = m_body->getPos();
        m_body->setPos(camera->fixPos(prevPos));
    }
}
