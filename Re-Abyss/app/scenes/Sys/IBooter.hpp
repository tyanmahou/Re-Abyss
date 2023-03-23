#pragma once
#include <memory>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Sys2
{
    class Modules;

    class IBooter
    {
    public:
        virtual ~IBooter() = default;

        virtual std::shared_ptr<Modules> module() const = 0;
        virtual bool onBoot(Manager* pManager) const = 0;
    };
}
