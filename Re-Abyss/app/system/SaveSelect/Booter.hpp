#pragma once
#include <abyss/system/base/IBooter.hpp>
#include <abyss/components/Cycle/SaveSelect/Master.hpp>

namespace abyss::Sys::SaveSelect
{
    class Booter final :
        public IBooter
    {
    public:
        Booter(Cycle::SaveSelect::IMasterObserver* pObserver);
        bool onBoot(Manager* pManager) const override;
    private:
        Cycle::SaveSelect::IMasterObserver* m_pObserver;
    };
}