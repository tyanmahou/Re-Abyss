#include "CycleObj.hpp"
#include <abyss/components/Cycle/base/IListener.hpp>

namespace abyss::Cycle
{
    void CycleObj::listen()
    {
        for (auto&& com : this->finds<IListener>()) {
            com->listen();
        }
    }
}
