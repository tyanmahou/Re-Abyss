#pragma once
#include "BaseState.hpp"

namespace abyss::LaunShark::Shot
{
    class StartState : public BaseState
    {
    public:
        void start()override;
        void update(double dt) override;
    };
}