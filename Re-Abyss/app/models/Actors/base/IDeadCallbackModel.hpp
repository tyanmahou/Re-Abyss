#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    class IDeadCallbackModel
    {
    public:
        virtual ~IDeadCallbackModel() = default;
        virtual void onDead() = 0;
    };
}