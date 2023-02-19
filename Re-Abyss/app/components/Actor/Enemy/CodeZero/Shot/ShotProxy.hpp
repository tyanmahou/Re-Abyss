#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class ShotProxy final : public IComponent
    {
    public:
        ShotProxy(ActorObj* pActor):
            m_pActor(pActor)
        {}

        void startPursuit()
        {
            m_isStartedPursuit = true;
        }
        bool isStartedPursuit() const
        {
            return m_isStartedPursuit;
        }

        void setIsCharge(bool isCharge)
        {
            m_isCharge = isCharge;
        }
        bool isCharge() const
        {
            return m_isCharge;
        }
    private:
        ActorObj* m_pActor = nullptr;

        bool m_isStartedPursuit = false;
        bool m_isCharge = false;
    };
}
