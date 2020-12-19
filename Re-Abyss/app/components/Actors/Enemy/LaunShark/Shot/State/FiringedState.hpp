#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::Enemy::LaunShark::Shot
{
    class FiringedState final : public BaseState
    {
    public:
        Task<> start();

        void draw() const override;
    };
}