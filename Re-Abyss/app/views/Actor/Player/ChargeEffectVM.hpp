#pragma once

namespace abyss::Actor::Player
{
    class ChargeEffectVM
    {
    public:
        ChargeEffectVM& setTime(double time)
        {
            m_time = time;
            return *this;
        }
        ChargeEffectVM& setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
            return *this;
        }
        ChargeEffectVM& setCharge(double charge)
        {
            m_charge = charge;
            return *this;
        }

        void draw() const;
    private:
        s3d::Vec2 m_pos;
        double m_charge = 0;
        double m_time = 0;
    };
}
