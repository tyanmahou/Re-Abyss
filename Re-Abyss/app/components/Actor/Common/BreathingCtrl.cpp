#include "BreathingCtrl.hpp"
#include <Siv3D.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Effect/Effects.hpp>
#include <abyss/views/Actor/Common/BreathEffect.hpp>

namespace abyss::Actor
{
    BreathingCtrl::BreathingCtrl(ActorObj* pActor):
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
            m_pActor->getModule<Effects>()->createDecorFront<BreathEffect>(m_body->getPos() + m_offset);
        }
    }
}