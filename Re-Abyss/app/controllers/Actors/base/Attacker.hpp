#pragma once
#include <Siv3D/Fwd.hpp>

namespace abyss
{
    class Attacker
    {
    protected:
        s3d::int32 m_power = 1;
    public:
        Attacker() = default;

        Attacker(s3d::int32 power) :
            m_power(power)
        {}
        virtual ~Attacker() = default;
        s3d::int32 getPower()const { return m_power; }
    };
}