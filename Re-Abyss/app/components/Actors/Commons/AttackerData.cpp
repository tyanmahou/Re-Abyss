#include "AttackerData.hpp"
#include <abyss/modules/Actors/base/ActorObj.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>

namespace abyss::Actor
{
    void AttackerData::onStart()
    {
        m_body = m_pActor->find<Body>();
    }

    s3d::Vec2 AttackerData::getPos() const
    {
        if (!m_body) {
            return s3d::Vec2::Zero();
        }
        return m_body->getCenterPos();
    }

    s3d::Vec2 AttackerData::getVelocity() const
    {
        if (!m_body) {
            return s3d::Vec2::Zero();
        }
        return m_body->getVelocity();
    }

}
