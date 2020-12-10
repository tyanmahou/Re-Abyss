#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Time/Time.hpp>
namespace abyss::Actor
{
    class AttackerData final : public IComponent
    {
        s3d::int32 m_power = 1;
    public:
        AttackerData(s3d::int32 power) :
            m_power(power)
        {}

        s3d::int32 getPower()const { return m_power; }
    };
}