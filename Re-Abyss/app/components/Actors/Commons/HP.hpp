#pragma once
#include <Siv3D/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Actor
{
    class HP : public IComponent
    {
    private:
        s3d::int32 m_hp;
        s3d::int32 m_maxHp;

        TimerEx m_invincibleTime;
        IActor* m_pActor;
    public:
        HP(IActor* m_pActor);

        void setup();

        /// <summary>
        /// HP/最大HPをセット
        /// </summary>
        /// <param name="hp"></param>
        /// <returns></returns>
        HP& initHp(s3d::int32 hp);

        HP& setHp(s3d::int32 hp);
        HP& setInvincibleTime(double invincibleTimeSec);

        s3d::int32 value() const;

        bool heal(s3d::int32 value);
        bool damage(s3d::int32 power);

        /// <summary>
        /// HPを最大HPにリセット
        /// </summary>
        void reset();

        bool isDead() const;

        bool isInInvincibleTime() const;

        s3d::int32 getHp() const;
        s3d::int32 getMaxHp() const;

    };
}