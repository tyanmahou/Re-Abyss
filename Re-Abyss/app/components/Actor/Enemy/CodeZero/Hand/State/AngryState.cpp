#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/AngryState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    AngryState::AngryState()
    {

    }
    void AngryState::start()
    {
        m_handMove->startAngry();
    }
    void AngryState::end()
    {
    }
    void AngryState::update()
    {}
}
