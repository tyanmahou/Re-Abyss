#include "PlayerProxy.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>

namespace abyss::Actor::Player
{
    PlayerProxy::PlayerProxy(IActor* pActor):
        m_pActor(pActor)
    {}
    void PlayerProxy::onStart()
    {
        m_body = m_pActor->find<Body>();
    }
    const s3d::Vec2& PlayerProxy::getPos() const
    {
        return m_body->getPos();
    }
    Forward PlayerProxy::getForward() const
    {
        return m_body->getForward();
    }
}
