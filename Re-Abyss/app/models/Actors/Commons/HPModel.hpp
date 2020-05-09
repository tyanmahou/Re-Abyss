#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/commons/Fwd.hpp>
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

        HPModel& setHp(s3d::int32 hp);
        HPModel& setInvincibleTime(double invincibleTimeSec);

        s3d::int32 value() const;
        bool damage(s3d::int32 power);

        bool isDead() const;

        bool isInInvincibleTime() const;
    };
}

namespace abyss::experimental
{
    class HPModel : public IComponent
    {
    private:
        s3d::int32 m_hp;
        TimerEx m_invincibleTime;
        IActor* m_pActor;
    public:
        HPModel(IActor* m_pActor);

        void setup();

        HPModel& setHp(s3d::int32 hp);
        HPModel& setInvincibleTime(double invincibleTimeSec);

        s3d::int32 value() const;
        bool damage(s3d::int32 power);

        bool isDead() const;

        bool isInInvincibleTime() const;
    };
}