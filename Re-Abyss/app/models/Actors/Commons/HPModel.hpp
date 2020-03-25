#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>
namespace abyss
{
    class HPModel
    {
    private:
        s3d::int32 m_hp;
        TimerEx m_invincibleTime;
    public:
        HPModel();
        HPModel(s3d::int32 hp, double invincibleTimeSec = 0.0);

        void damage(s3d::int32 power);

        bool isInInvincibleTime() const;
    };
}