#include "BreathingCtrl.hpp"
#include <Siv3D.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Effects/Effects.hpp>
#include <abyss/views/Actors/Common/BreathEffect.hpp>

namespace abyss::Actor
{
    BreathingCtrl::BreathingCtrl(IActor* pActor):
        m_pActor(pActor),
        m_timer(5.0, true, [this, pActor]{return pActor->getUpdateTime() + s3d::DurationCast<s3d::Microseconds>(s3d::Duration(m_timeOffsetSec)); }),
        m_timeOffsetSec(Random(0.0, 10.0))
    {}

    void BreathingCtrl::onStart()
    {
        m_body = m_pActor->find<Body>();
    }

    void BreathingCtrl::onLastUpdate()
    {
        if (m_timer.update() && RandomBool(0.7)) {
            m_pActor->getModule<Effects>()->add<EffectGroup::Bubble, BreathEffect>(m_body->getPos() + m_offset);
        }
    }
}
