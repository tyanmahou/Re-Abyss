#include "HP.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor
{
    HP::HP(ActorObj* pActor):
        m_hp(0),
        m_invincibleTime(1.0, false, [pActor] {return pActor->getUpdateTime();}),
        m_pActor(pActor)
    {}

    void HP::setup()
    {
    }
    HP& HP::initHp(s3d::int32 hp)
    {
        m_hp = hp;
        m_maxHp = hp;
        return *this;
    }
    HP& HP::setHp(s3d::int32 hp)
    {
        m_hp = hp;
        return *this;
    }

    HP& HP::setInvincibleTime(double invincibleTimeSec)
    {
        m_invincibleTime = TimerEx(invincibleTimeSec, false, [this] {return m_pActor->getUpdateTime(); });
        return *this;
    }

    bool HP::isInInvincibleTime() const
    {
        return !m_invincibleTime.reachedZero() && m_invincibleTime.isRunning();
    }

    s3d::int32 HP::getHp() const
    {
        return m_hp;
    }

    s3d::int32 HP::getMaxHp() const
    {
        return m_maxHp;
    }

    s3d::int32 HP::value() const
    {
        return m_hp;
    }
    bool HP::heal(s3d::int32 value)
    {
        m_hp += value;
        if (m_hp > m_maxHp) {
            m_hp = m_maxHp;
        }
        return true;
    }
    bool HP::damage(s3d::int32 damagePoint)
    {
        if (!this->isInInvincibleTime()) {
            m_hp -= damagePoint;
            m_invincibleTime.restart();
            return true;
        }
        return false;
    }

    void HP::reset()
    {
        m_hp = m_maxHp;
    }

    bool HP::isFull() const
    {
        return m_hp >= m_maxHp;
    }

    bool HP::isDead() const
    {
        return m_hp <= 0;
    }
}