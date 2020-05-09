#include "HPModel.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/ActorTimeModel.hpp>

namespace abyss
{
    s3d::int32 HPModel::value() const
    {
        return m_hp;
    }
    bool HPModel::damage(s3d::int32 damagePoint)
    {
        if (!this->isInInvincibleTime()) {
            m_hp -= damagePoint;
            m_invincibleTime.restart();
            return true;
        }
        return false;
    }

    bool HPModel::isDead() const
    {
        return m_hp <= 0;
    }

    HPModel::HPModel():
        HPModel(0)
    {}

    HPModel::HPModel(s3d::int32 hp, double invincibleTimeSec):
        m_hp(hp),
        m_invincibleTime(invincibleTimeSec, false, WorldTime::TimeMicroSec)
    {}


    HPModel& HPModel::setHp(s3d::int32 hp)
    {
        m_hp = hp;
        return *this;
    }

    HPModel& HPModel::setInvincibleTime(double invincibleTimeSec)
    {
        m_invincibleTime = TimerEx(invincibleTimeSec, false, WorldTime::TimeMicroSec);
        return *this;
    }

    bool HPModel::isInInvincibleTime() const
    {
        return !m_invincibleTime.reachedZero() && m_invincibleTime.isRunning();
    }

}

namespace abyss::experimental
{
    HPModel::HPModel(IActor* pActor):
        m_hp(0),
        m_pActor(pActor)
    {}

    void HPModel::setup()
    {
        auto timer = m_pActor->findComponent<ActorTimeModel>();
        m_invincibleTime = TimerEx(1.0, false, [timer] {
            return timer.lock()->getTime();
        });
    }
    HPModel& HPModel::setHp(s3d::int32 hp)
    {
        m_hp = hp;
        return *this;
    }

    HPModel& HPModel::setInvincibleTime(double invincibleTimeSec)
    {
        m_invincibleTime.set(s3d::Duration(invincibleTimeSec));
        return *this;
    }

    bool HPModel::isInInvincibleTime() const
    {
        return !m_invincibleTime.reachedZero() && m_invincibleTime.isRunning();
    }

    s3d::int32 HPModel::value() const
    {
        return m_hp;
    }
    bool HPModel::damage(s3d::int32 damagePoint)
    {
        if (!this->isInInvincibleTime()) {
            m_hp -= damagePoint;
            m_invincibleTime.restart();
            return true;
        }
        return false;
    }

    bool HPModel::isDead() const
    {
        return m_hp <= 0;
    }
}