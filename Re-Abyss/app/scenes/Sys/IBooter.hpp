#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Sys2
{
    class IBooter
    {
    public:
        virtual ~IBooter() = default;
        virtual bool onBoot(Manager* pManager) const = 0;
    };
}
