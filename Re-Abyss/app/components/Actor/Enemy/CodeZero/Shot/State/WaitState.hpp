#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class WaitState : public BaseState
    {
    public:
        void start();
        void end();
        void update() override;

        void draw() const;
    private:
        Ref<QuakeModel> m_quake;
    };
}