#pragma once
#include "BaseState.hpp"

namespace abyss::Actor::LaunShark::Shot
{
    class FiringedState final : public BaseState
    {
    public:
        void start();

        void draw() const override;
    };
}