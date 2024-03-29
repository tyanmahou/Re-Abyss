#include <abyss/modules/Cycle/base/CycleObj.hpp>
#include <abyss/modules/Cycle/base/IListener.hpp>

namespace abyss::Cycle
{
    bool CycleObj::listen()
    {
        bool ret = false;
        for (auto&& com : this->finds<IListener>()) {
            ret |= com->listen();
        }
        return ret;
    }
}
