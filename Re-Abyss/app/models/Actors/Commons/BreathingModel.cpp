#include "BreathingModel.hpp"
#include <Siv3D.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/Effects/Effects.hpp>
#include <abyss/views/Actors/Common/BreathEffect.hpp>

namespace abyss
{
    BreakthingModel::BreakthingModel(IActor* pActor):
        m_pActor(pActor),
        m_timer(5.0, true, pActor->getDrawTimer())
    {}

    void BreakthingModel::setup()
    {
        m_body = m_pActor->find<BodyModel>();
    }

    void BreakthingModel::onLastUpdate([[maybe_unused]]double dt)
    {
        if (m_timer.update() && RandomBool(0.5)) {
            m_pActor->getModule<Effects>()->add<EffectGroup::Bubble, BreathEffect>(m_body->getPos() + m_offset);
        }
    }
}
