#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/AngryEndState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/PursuitState.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    AngryEndState::AngryEndState()
    {

    }
    void AngryEndState::start()
    {
    }
    void AngryEndState::end()
    {
    }
    Fiber<> AngryEndState::updateAsync()
    {
        m_handMove->startAngryEnd();

        co_await Coro::WaitUntil([&] {return m_handMove->isMoveEnd(); });

        this->changeState<PursuitState>(s3d::none, true);
    }
    void AngryEndState::update()
    {}
}
