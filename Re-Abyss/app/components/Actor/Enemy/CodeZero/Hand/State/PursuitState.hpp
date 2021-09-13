#pragma once
#include "BaseState.hpp"
namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class PursuitState final : public BaseState
    { 
    public:
        PursuitState(bool slowStart = false);
        void update() override;
        void start()override;
        void lastUpdate() override;
    private:
        bool m_slowStart = false;
    };
}