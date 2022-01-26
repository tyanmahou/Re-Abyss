#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Hand/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class RollingAttackState final : public BaseState
    {
    public:
        RollingAttackState(bool isReverse);
        void start()override;
        void update()override;
    private:
        bool m_isReverse = false;
    };
}