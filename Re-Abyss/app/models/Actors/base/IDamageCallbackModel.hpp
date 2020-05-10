#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class IDamageCallbackModel
    { 
    public:
        virtual ~IDamageCallbackModel() = default;
        virtual void onDamaged() = 0;
    };
}