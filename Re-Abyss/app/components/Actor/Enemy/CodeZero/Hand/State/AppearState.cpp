#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/AppearState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    AppearState::AppearState()
    {

    }
    void AppearState::start()
    {
        m_handMove->startAppear();
    }
    void AppearState::end()
    {
    }
    void AppearState::update()
    {}
}
