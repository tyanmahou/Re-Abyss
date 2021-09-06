#pragma once
#include <abyss/components/base/IComponent.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    class ChargeCtrl : public IComponent
    {
    public:
        void setRate(double rate)
        {
            m_chargeRate = rate;
        }
        double getRate() const
        {
            return m_chargeRate;
        }
    protected:
        double m_chargeRate = 0;
    };
}