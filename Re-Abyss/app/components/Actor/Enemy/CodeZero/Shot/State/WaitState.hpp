#pragma once
#include <abyss/components/Actor/Enemy/CodeZero/Shot/State/BaseState.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class WaitState : public BaseState
    {
    public:
        void start();
        void end();
        void update() override;
    private:
        Ref<QuakeModel> m_quake;
    };
}