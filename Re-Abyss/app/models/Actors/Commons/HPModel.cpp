#include "HPModel.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/ActorTimeModel.hpp>

namespace abyss
{
    HPModel::HPModel(IActor* pActor):
        m_hp(0),
        m_invincibleTime(1.0, false, [pActor] {return pActor->getTime();}),
        m_pActor(pActor)
    {}

    void HPModel::setup()
    {
    }
    HPModel& HPModel::setHp(s3d::int32 hp)
    {
        m_hp = hp;
        return *this;
    }

    HPModel& HPModel::setInvincibleTime(double invincibleTimeSec)
    {
        m_invincibleTime = TimerEx(invincibleTimeSec, false, [this] {return m_pActor->getTime(); });
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