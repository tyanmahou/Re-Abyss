#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/AttackWaitState.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/AttackState.hpp>
#include <abyss/utils/Coro/Fiber/FiberUtil.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    AttackWaitState::AttackWaitState()
    {}

    void AttackWaitState::start()
    {
        m_motion->set(Motion::AttackWait);
    }

    void AttackWaitState::end()
    {
        m_motion->set(Motion::Wait);
    }

    Fiber<> AttackWaitState::updateAsync()
    {
        m_handMove->startForAttackWait();

        // 一定時間追従
        co_await Coro::FiberUtil::WaitUntil([this] {
            return m_handMove->isMoveEnd();
        });

        // 攻撃
        this->changeState<AttackState>();
        co_return;
    }

    void AttackWaitState::update()
    {
    }
}
