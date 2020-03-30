#pragma once
#include "IkalienBaseState.hpp"

namespace abyss
{
    class IkalienSwimState : public IkalienBaseState
    {
    public:
        void start()override;
        void update(double dt) override;
        void draw()const override;
    };
}