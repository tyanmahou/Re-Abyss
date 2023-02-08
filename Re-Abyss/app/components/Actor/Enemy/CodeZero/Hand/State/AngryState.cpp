#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/AngryState.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    AngryState::AngryState()
    {

    }
    void AngryState::start()
    {
        m_handMove->setActive(false);
        m_pActor->find<Body>()->setVelocity(s3d::Vec2::Zero());
    }
    void AngryState::end()
    {
        m_handMove->setActive(true);
    }
    void AngryState::update()
    {}
}
