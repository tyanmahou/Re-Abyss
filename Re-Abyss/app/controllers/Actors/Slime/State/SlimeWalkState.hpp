#pragma once

#include "SlimeBaseState.hpp"

namespace abyss
{

    class SlimeWalkState final : public SlimeBaseState
    {
        bool m_onCollision = false;
        void onColisionMapUp() override;
    public:
        void start() override;

        void update(double dt) override;

        void draw() const override;
    };
}