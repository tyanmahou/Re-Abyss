#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Fade/IrisOut/FadeCtrl.hpp>


namespace abyss::UI::Fade::IrisOut
{
    void Builder::Build(UIObj* pUi)
    {
        // メイン追加
        {
            pUi->attach<FadeCtrl>(pUi)->setOrder(DrawOrder::UI::Fade);
        }
    }
}