#pragma once
#include <abyss/system/base/IBooter.hpp>
#include <abyss/components/Cycle/Splash/Master.hpp>

namespace abyss::Sys::Splash
{
    class Booter final :
        public IBooter
    {
    public:
        Booter(Cycle::Splash::IMasterObserver* pObserver);
        bool onBoot(Manager* pManager) const override;
    private:
        Cycle::Splash::IMasterObserver* m_pObserver;
    };
}