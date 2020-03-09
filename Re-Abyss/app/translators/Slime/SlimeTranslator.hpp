#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class SlimeTranslator
    {
    public:
        static SlimeViewModel ToViewModel(const SlimeActor*const actor);
    };
}
