#pragma once
#include <abyss/system/base/IBooter.hpp>
#include <abyss/components/Cycle/Title/Master.hpp>

namespace abyss::Sys::Title
{
    class Booter final :
        public IBooter
    {
    public:
        Booter(Cycle::Title::IMasterObserver* pObserver);
        bool onBoot(Manager* pManager) const override;
    private:
        Cycle::Title::IMasterObserver* m_pObserver;
    };
}