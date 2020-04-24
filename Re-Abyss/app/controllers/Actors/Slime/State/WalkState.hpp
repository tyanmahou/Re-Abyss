#pragma once

#include "BaseState.hpp"

namespace abyss::Slime
{

    class WalkState final : public BaseState
    {
        bool m_onCollision = false;
        void onColisionMapUp() override;
    public:
        void start() override;

        void update(double dt) override;

        void draw() const override;
    };
}