#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/SaveSelect/BackGround/BgCtrl.hpp>

namespace abyss::UI::SaveSelect::BackGround
{
    void Builder::Build(UIObj* pUi)
    {
        // Bg
        pUi->attach<BgCtrl>(pUi)->setLayer(DrawLayer::BackGround);
    }
}