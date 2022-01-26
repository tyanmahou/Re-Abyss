#include <abyss/components/Actor/Common/HP.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor
{
    HP::HP(ActorObj* pActor):
        m_hp(0),
        m_pActor(pActor)
    {}

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
        m_hp -= damagePoint;
        if (m_hp < 0) {
            m_hp = 0;
        }
        return true;
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