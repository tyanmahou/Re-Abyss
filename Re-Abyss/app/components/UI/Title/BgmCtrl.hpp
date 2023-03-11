#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>

namespace abyss::UI::Title
{
    class BgmCtrl :
        public IComponent
    {
    public:
        BgmCtrl(UIObj* pUi);

        void onStart() override;
        void onEnd() override;
    private:
        UIObj* m_pUi;
    };
}
