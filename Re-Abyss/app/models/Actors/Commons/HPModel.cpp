#include "HPModel.hpp"
#include <abyss/controllers/World/WorldTime.hpp>

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
