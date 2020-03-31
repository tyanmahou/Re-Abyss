#pragma once
#include "IkalienBaseState.hpp"

namespace abyss
{
    class IkalienWaitState : public IkalienBaseState
    {
    public:
        void update(double dt) override;
        void draw()const override;
    };
}