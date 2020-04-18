#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class BackGroundTranslator
    {
    public:
        BackGroundVM toVM(const BackGroundEntity& entity)const;
    };
}