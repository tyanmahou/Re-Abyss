#pragma once

#include "BaseState.hpp"

namespace abyss::Slime
{

    class WalkState final : public BaseState
    {
    public:
        void start() override;

        void update(double dt) override;
    };
}