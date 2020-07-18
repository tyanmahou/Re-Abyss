#include "BodyUpdaterModel.hpp"
#include "BodyModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>

namespace abyss
{
    BodyUpdaterModel::BodyUpdaterModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void BodyUpdaterModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
    }

    void BodyUpdaterModel::onMove(double dt)
    {
        if (!m_isActive) {
            return;
        }
        if (!m_body) {
            return;
        }
        m_body->update(dt);
    }
}
