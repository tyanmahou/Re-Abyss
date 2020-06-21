#include "CameraFixPosModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>

namespace abyss
{
    CameraFixPosModel::CameraFixPosModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void CameraFixPosModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
    }

    void CameraFixPosModel::onLastUpdate([[maybe_unused]]double dt)
    {
        auto camera = m_pActor->getModule<Camera>();
        auto prevPos = m_body->getPos();
        m_body->setPos(camera->fixPos(prevPos));
    }
}
