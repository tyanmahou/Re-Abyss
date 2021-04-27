#include "CodeZeroProxy.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    CodeZeroProxy::CodeZeroProxy(ActorObj* pActor):
        m_pActor(pActor)
    {}
    void CodeZeroProxy::onStart()
    {
        m_body = m_pActor->find<Body>();
        m_parts = m_pActor->find<PartsCtrl>();
    }
    void CodeZeroProxy::setActive(bool isActive)
    {
        m_pActor->setActive(isActive);
        m_parts->setActive(isActive);
    }
    const s3d::Vec2& CodeZeroProxy::getPos() const
    {
        return m_body->getPos();
    }
}
