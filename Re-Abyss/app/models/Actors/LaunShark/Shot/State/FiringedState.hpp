#pragma once
#include "BaseState.hpp"

namespace abyss::LaunShark::Shot
{
    class FiringedState final : public BaseState
    {
    public:
        void start();
        void update(double dt) override;
        void draw() const override;
    };
}