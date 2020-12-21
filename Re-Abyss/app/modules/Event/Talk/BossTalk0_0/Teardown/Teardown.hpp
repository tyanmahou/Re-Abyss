#pragma once
#include <abyss/modules/Event/base/IEvent.hpp>

namespace abyss::Event::Talk::BossTalk0_0
{
    class Teardown : public IEvent
    {
        void onStart()override;
        bool update(double dt) override;
    };
}