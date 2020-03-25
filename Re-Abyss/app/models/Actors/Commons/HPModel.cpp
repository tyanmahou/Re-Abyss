#include "HPModel.hpp"
#include <abyss/controllers/World/WorldTime.hpp>

namespace abyss
{
    void HPModel::damage(s3d::int32 damagePoint)
    {
        if (!this->isInInvincibleTime()) {
            m_hp -= damagePoint;
            m_invincibleTime.restart();
        }
    }

    HPModel::HPModel():
        HPModel(0)
    {}

    HPModel::HPModel(s3d::int32 hp, double invincibleTimeSec):
        m_hp(0),
        m_invincibleTime(invincibleTimeSec, false, WorldTime::TimeMicroSec)
    {}

    bool HPModel::isInInvincibleTime() const
    {
        return !m_invincibleTime.reachedZero();
    }

}
