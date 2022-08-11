#include <abyss/components/Actor/Enemy/BazookaKun/State/WaitState.hpp>

namespace abyss::Actor::Enemy::BazookaKun
{
    void WaitState::start()
    {
    }
    Task<> WaitState::task()
    {
        co_return;
    }
}
