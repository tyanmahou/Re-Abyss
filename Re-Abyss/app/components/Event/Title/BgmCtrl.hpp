#pragma once
#include <abyss/components/base/IComponent.hpp>

namespace abyss::Event::Title
{
    class BgmCtrl :
        public IComponent
    {
    public:
        BgmCtrl(IEvent* pEvent);

        void onStart() override;
        void onEnd() override;
    private:
        IEvent* m_pEvent;
    };
}