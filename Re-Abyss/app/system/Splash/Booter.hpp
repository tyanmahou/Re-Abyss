#pragma once
#include <abyss/system/base/IBooter.hpp>

namespace abyss::Sys::Splash
{
    class Booter final :
        public IBooter
    {
    public:
        bool onBoot(Manager* pManager) const override;
    };
}