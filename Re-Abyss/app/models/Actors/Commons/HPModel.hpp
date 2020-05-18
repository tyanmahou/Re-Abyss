#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss
{
    class HPModel : public IComponent
    {
    private:
        s3d::int32 m_hp;
        s3d::int32 m_maxHp;

        TimerEx m_invincibleTime;
        IActor* m_pActor;
    public:
        HPModel(IActor* m_pActor);

        void setup();

        HPModel& initHp(s3d::int32 hp);
        HPModel& setHp(s3d::int32 hp);
        HPModel& setInvincibleTime(double invincibleTimeSec);

        s3d::int32 value() const;

        bool heal(s3d::int32 value);
        bool damage(s3d::int32 power);

        bool isDead() const;

        bool isInInvincibleTime() const;

        s3d::int32 getHp() const;
        s3d::int32 getMaxHp() const;

    };
}