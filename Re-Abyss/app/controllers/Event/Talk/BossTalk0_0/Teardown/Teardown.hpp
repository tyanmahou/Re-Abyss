#pragma once
#include <abyss/controllers/Event/base/IEvent.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    class Teardown : public IEvent
    {
        void init()override;
        bool update(double dt) override;
    };
}