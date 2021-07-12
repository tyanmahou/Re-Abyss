#pragma once
#include <abyss/commons/Fwd.hpp>

namespace abyss::Sys
{
    class IBooter
    {
    public:
        virtual ~IBooter() = default;

        virtual bool onBoot(Manager* pManager) const = 0;
    };
}