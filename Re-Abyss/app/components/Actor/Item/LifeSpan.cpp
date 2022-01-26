#include <abyss/components/Actor/Item/LifeSpan.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Item
{
    LifeSpan::LifeSpan(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void LifeSpan::onUpdate()
    {
        m_restTimeSec -= m_pActor->deltaTime();
        if (m_restTimeSec <= 0) {
            m_restTimeSec = 0;

            m_pActor->destroy();
        }
    }
}
