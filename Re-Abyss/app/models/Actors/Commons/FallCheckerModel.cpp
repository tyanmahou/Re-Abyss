#include "FallCheckerModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/base/IDeadCallbackModel.hpp>

namespace abyss
{
    FallCheckerModel::FallCheckerModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void FallCheckerModel::setup()
    {
        m_hp = m_pActor->find<HPModel>();
        m_body = m_pActor->find<BodyModel>();
    }

    void FallCheckerModel::onLastUpdate([[maybe_unused]]double dt)
    {
        if (m_isFall) {
            return;
        }

        if (!m_pActor->getModule<Camera>()->isOutOfRoomDeath(m_body->getPos(), m_body->getHeight() / 2.0)) {
            return;
        }
        // 落下死
        m_isFall = true;

        if (m_hp) {
            m_hp->setHp(0);
        }
    }
}
