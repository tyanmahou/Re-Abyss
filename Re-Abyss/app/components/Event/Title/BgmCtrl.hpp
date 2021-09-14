#pragma once
#include <abyss/components/base/IComponent.hpp>

namespace abyss::Event::Title
{
    class BgmCtrl :
        public IComponent
    {
    public:
        BgmCtrl(EventObj* pEvent);

        void onStart() override;
        void onEnd() override;
    private:
        EventObj* m_pEvent;
    };
}